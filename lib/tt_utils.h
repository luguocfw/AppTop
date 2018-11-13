/*
*
* author: ChenFawang
* tt_utils.h
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#ifndef __TT_UTILS_H__
#define __TT_UTILS_H__
#include <string>
#include <list>
namespace task_top {
typedef struct {
  int   user;
  int   nice;
  int   sys;
  int   idle;
  int   io;
  int   irq;
  int   sirq;
  int   total;
}SystemStatData;
typedef struct {
  unsigned long       utime;
  unsigned long       stime;
  long                cutime;
  long                cstime;
}AppAndTaskStatData;
class SystemStatResolv {
  static int Resolv(const std::string &file_data, SystemStatData &stat_data_out);
};
class AppAndTaskStatResolv {
  static int Resolv(const std::string &file_data, AppAndTaskStatData &stat_data_out);
};
class AppTaskScan {
  static int GetTids(int pid, std::list<int> &tids);
  static int GetTids(const std::string &app_stat_path, std::list<int> &tids);
  static int GetTids(const std::string &app_stat_path, std::list<std::string> &tid_folders);
};
}
#endif