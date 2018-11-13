/*
*
* author: ChenFawang
* tt_hander.h
* 2018 - 11 - 12
* mail: cfwang_9984@163.com
*
*/
#ifndef __TT_HANDLER_H__
#define __TT_HANDLER_H__
#include "tt_utils.h"
#include <list>
namespace task_top {
typedef struct {
  float               utime;
  float               stime;
  float               cutime;
  float               cstime;
}AppAndTaskCpuInfo;
typedef struct {
  int                 tid;
  std::string         name;
  AppAndTaskCpuInfo   cpu;
}TaskInfo;
typedef struct {
  int                             pid;
  std::string                     name;
  AppAndTaskCpuInfo               app_cpu;
  std::list<TaskInfo>             task;
}AppCpuInfoAll;

typedef struct {
  int                   tid;
  AppAndTaskStatData    stat;
}TaskStat;
typedef struct {
  int                     pid;
  AppAndTaskStatData      app_stat;
  std::list<TaskStat>     tasks_stat;
}AppStatAll;
typedef struct {
  float user_;
  float sys_;
  float nic_;
  float idle_;
  float io_;
  float irq_;
  float sirq_;
} SystemCpuInfo;

typedef struct {
  int               tid;
  std::string       stat_str;
}TaskStatStr;

typedef struct {
  int                       pid;
  std::string               stat_str;
  std::list<TaskStatStr>    thrs_stat;
}AppStatStrAll;

class TaskTopHandler {
public:
  TaskTopHandler(const std::list<int> &pids);
  TaskTopHandler(const int *pids, int pid_count);
  ~TaskTopHandler();
public:
  void GetCpuInfo(std::list<AppCpuInfoAll> &infos, SystemCpuInfo &sys_info);
private:
  bool GetAllStat(SystemStatData &sys_stat, std::list<AppStatAll> &apps_stat, std::list<int> &pids);
  void GetAllCpu(std::list<AppCpuInfoAll> &infos_out, SystemCpuInfo &sys_info_out, SystemStatData &sys_stat_in, std::list<AppStatAll> &apps_stat_in);
  bool GetAllStatString(std::list<int>& pids, std::string & sys_stat_str, std::list<AppStatStrAll>& apps_stat_str);
  bool GetSystemStatString(std::string &stat_data);
  bool GetOneAppStatString(int pid, std::string &stat_data);
  bool GetOneTaskStatString(int pid, int tid, std::string &stat_data);
  bool GetOneAppOrTaskStatString(const std::string &stat_path, std::string &stat_data);
  bool GetOldAppStatData(int pid, AppAndTaskStatData &old_stat);
  bool GetOldTaskStatData(int pid, int tid, AppAndTaskStatData &old_stat);
  void GetAppCpuInfo(int pid, AppAndTaskStatData& cur_stat_data, int total_diff, AppAndTaskCpuInfo &cpu_info);
  void GetTaskCpuInfo(int pid, int tid, AppAndTaskStatData& cur_stat_data, int total_diff, AppAndTaskCpuInfo &cpu_info);
private:
  std::list<AppStatAll> apps_stat_;
  std::list<int> pids_;
  SystemStatData sys_stat_;
};
}
#endif