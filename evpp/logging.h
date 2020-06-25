#pragma once

#include "evpp/platform_config.h"

#ifdef __cplusplus
#define GOOGLE_GLOG_DLL_DECL           // 使用静态glog库时，必须定义这个
#define GLOG_NO_ABBREVIATED_SEVERITIES // 没这个编译会出错,传说因为和Windows.h冲突

#include <glog/logging.h>

// 强制修改evpp的日志等级
#define LOG_TRACE LOG(TRACE) << __FUNCTION__ << " "
#define DLOG_TRACE LOG(TRACE) << __PRETTY_FUNCTION__ << " "
#define LOG_INFO  LOG(TRACE) << __FUNCTION__ << " "
#define LOG_DEBUG LOG(DEBUG) << __FUNCTION__ << " "
#define LOG_NOTICE LOG(NOTICE) << __FUNCTION__ << " "
#define DLOG_NOTICE LOG(NOTICE) << __PRETTY_FUNCTION__ << " "
#define LOG_WARN  LOG(WARNING) << __FUNCTION__ << " "
#define DLOG_WARN LOG(WARNING) << __PRETTY_FUNCTION__ << " "
#define LOG_ERROR LOG(ERROR) << __FUNCTION__ << " "
#define LOG_FATAL LOG(FATAL) << __PRETTY_FUNCTION__ << " "  // fatal级别有特殊含义

#endif // end of define __cplusplus