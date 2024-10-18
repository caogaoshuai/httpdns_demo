#pragma once

#include "commfunc_global.h"

#include <QUrl>
#include <string>

COMMFUNC_EXPORT bool HttpDnsSetup(bool use);
COMMFUNC_EXPORT void HttpDnsCleanup();
COMMFUNC_EXPORT std::string Resolve(const std::string& host);
COMMFUNC_EXPORT QUrl Resolve(QUrl url);
COMMFUNC_EXPORT bool HttpDnsResolved(QUrl url);
COMMFUNC_EXPORT bool HttpDnsResolved();
