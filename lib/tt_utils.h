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
public:
  static int Resolv(const std::string &file_data, SystemStatData &stat_data_out);
};
class AppAndTaskStatResolv {
public:
  static int Resolv(const std::string &file_data, AppAndTaskStatData &stat_data_out);
};
class AppTaskScan {
public:
  static int GetTids(int pid, std::list<int> &tids);
  static int GetTids(const std::string &app_proc_path, std::list<int> &tids);
  static int GetTids(const std::string &app_proc_path, std::list<std::string> &tid_folders);
  static std::string GetThrName(int pid, int tid);
  static std::string GetAppName(int pid);
};
int stoi(const std::string &s);
std::string to_string(int val);
}
#endif