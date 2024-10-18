//
// Created by caogaoshuai on 2024/6/25.
//

#ifndef HDNS_C_SDK_HDNS_UTILS_H
#define HDNS_C_SDK_HDNS_UTILS_H

#include "hdns_define.h"

HDNS_API char* hdns_get_user_home_dir(hdns_pool_t* p);

HDNS_API bool hdns_is_valid_ipv6(const char* ipv6);

HDNS_API bool hdns_is_valid_ipv4(const char* ip);

HDNS_API void hdns_md5(const char* content, size_t size, char* digest);

HDNS_API void hdns_encode_hex(const unsigned char* data, size_t size, char* hex);
#endif
