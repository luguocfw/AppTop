/*
*
* author: ChenFawang
* tt_global.h
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#ifndef __TT_GLOBAL_H__
#define __TT_GLOBAL_H__
#include <string>
namespace task_top {
namespace global {
const std::string g_system_stat_path_ = "/proc/stat";
const std::string g_system_proc_path_ = "/proc";
const std::string g_task_folder_ = "task";
const std::string g_app_and_task_name_file_ = "comm";
const std::string g_stat_filename_ = "stat";
const std::string g_noname_string_ = "NoName";
}
}

#endif