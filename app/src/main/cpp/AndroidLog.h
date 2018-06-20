//
// Created by liuqikang on 2018/6/20.
//

#ifndef OPENSSLTEST_ANDROIDLOG_H
#define OPENSSLTEST_ANDROIDLOG_H

#endif //OPENSSLTEST_ANDROIDLOG_H

#include <android/log.h>
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG, "lqkssltest", FORMAT, ##__VA_ARGS__)