//
// Created by cagaoshuai on 2024/3/26.
//

#ifndef HDNS_C_SDK_HDNS_SESSION_H
#define HDNS_C_SDK_HDNS_SESSION_H

#include "hdns_define.h"

HDNS_CPP_START

HDNS_API int hdns_session_pool_init(hdns_pool_t* parent_pool, int flags);

HDNS_API CURL* hdns_session_require();

HDNS_API void hdns_session_release(CURL* session);

HDNS_API void hdns_session_pool_cleanup();

HDNS_CPP_END

#endif
