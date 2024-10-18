#include "HttpDns.h"
#include "hdns_api.h"

#include <memory>
#include <QMap>
#include <QDebug>
#include <QReadWriteLock>
#include <QDir>
#include <QApplication>

constexpr const char* HTTPDNS_ACCOUNT = "139450";
constexpr const char* HTTPDNS_SECRET = "xxxxxxxx";

QReadWriteLock m_dnsLock(QReadWriteLock::Recursive);
QMap<QString, QString> m_dnsCache;
bool m_bUseHttpDns = false;
QDir appPath = QApplication::applicationDirPath();

struct HttpDns final
{
	hdns_client_t* client_ = nullptr;

	HttpDns()
	{
		if (hdns_sdk_init() == HDNS_OK)
		{
			client_ = hdns_client_create(HTTPDNS_ACCOUNT, HTTPDNS_SECRET);
			if (client_)
			{
				hdns_log_set_log_file_path(appPath.absoluteFilePath("Log/httpdns.log").toStdString().c_str());
				hdns_log_set_level(hdns_log_level_e::HDNS_LOG_DEBUG);
				hdns_client_set_timeout(client_, 3000);
				hdns_client_set_using_cache(client_, true);
				hdns_client_set_using_https(client_, false);
				hdns_client_set_using_sign(client_, false);
				hdns_client_set_retry_times(client_, 3);
				hdns_client_set_region(client_, "global");

				hdns_client_start(client_);
			}
		}
	}
	~HttpDns()
	{
		if (client_)
		{
			hdns_client_cleanup(client_);
			hdns_sdk_cleanup();
		}
	}
};

std::unique_ptr<HttpDns> s_httpdns;

bool HttpDnsSetup(bool use)
{
	//return false;
	m_bUseHttpDns = use;
	s_httpdns = std::make_unique<HttpDns>();
	return s_httpdns->client_ != nullptr;
}

void HttpDnsCleanup()
{
	s_httpdns = nullptr;
}

std::string Resolve(const std::string& host)
{
	//return host;
	hdns_list_head_t* results = nullptr;
	auto s = hdns_get_result_for_host_sync_with_cache(s_httpdns->client_, host.c_str(), HDNS_QUERY_AUTO, NULL, &results);
	if (hdns_status_is_ok(&s))
	{
		char ip[HDNS_IP_ADDRESS_STRING_LENGTH];
		//const auto ret = hdns_select_ip_randomly(results, HDNS_QUERY_AUTO, ip)
		const auto ret = hdns_select_first_ip(results, HDNS_QUERY_AUTO, ip);
		hdns_list_cleanup(results);
		if (ret == HDNS_OK)
		{
			//Resolve success, pick one
			m_dnsLock.lockForWrite();
			if (!m_dnsCache.contains(QString::fromStdString(host))) 
			{
				m_dnsCache.insert(QString::fromStdString(host),ip);
			}
			m_dnsLock.unlock();
			qDebug() << "Resolve e" << ip;
			return ip;
		}

		//Resolve empty, return orginal
	}
	qDebug() << "Resolve e error" << QString::fromStdString(host);
	//Resolve fail, return orginal
	return host;
}

QUrl Resolve(QUrl url)
{
	qDebug() << "start Resolve" << url.toString() << url.host();
	const auto host = Resolve(url.host().toStdString());
	url.setHost(QString::fromStdString(host));
	qDebug() << "end Resolve" << url.toString();

	return url;
}

bool HttpDnsResolved(QUrl url) 
{
	m_dnsLock.lockForRead();
	QString host = url.host();
	QStringList hosts = m_dnsCache.keys();
	m_dnsLock.unlock();
	if (hosts.contains(host,Qt::CaseInsensitive))
		return true;
	return false;
}

COMMFUNC_EXPORT bool HttpDnsResolved()
{
	QReadLocker lock(&m_dnsLock);
	return !m_dnsCache.isEmpty() || m_bUseHttpDns;
}
