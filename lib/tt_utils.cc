/*
*
* author: ChenFawang
* tt_utils.c
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#include "tt_utils.h"
#include "tt_log.h"
namespace task_top {
int SystemStatResolv::Resolv(const std::string & file_data, SystemStatData & stat_data_out) {
  int param_num = 7;
  std::size_t addr;
  LogInfo("input str: %s\n", file_data.c_str());
  std::string temp = file_data;
  for (addr = 0; addr < temp.length(); addr++) {
    if (temp[addr] >= '0'&&temp[addr] <= '9') {
      break;
    }
  }
  if (addr >= temp.length() - 1) {
    return -1;
  }
  temp = temp.substr(addr);
  int ret = sscanf(temp.c_str(), "%d %d %d %d %d %d %d", &stat_data_out.user, &stat_data_out.nice, &stat_data_out.sys, &stat_data_out.idle, &stat_data_out.io, &stat_data_out.irq, &stat_data_out.sirq);
  if (ret != param_num) {
    LogError("sscanf get stat data failed\n");
    return -2;
  }
  stat_data_out.total = stat_data_out.user + stat_data_out.nice + stat_data_out.sys + stat_data_out.idle + stat_data_out.io + stat_data_out.irq + stat_data_out.sirq;
  return 0;
}
int AppAndTaskStatResolv::Resolv(const std::string & file_data, AppAndTaskStatData & stat_data_out) {
  int pid, ppid, pgrp, session, tty_nr, tpgid;
  unsigned int flags;
  unsigned long minft, cminflt, majflt, cmajflt;
  char comm[64] = { 0 };
  char state;
  int ret = sscanf(file_data.c_str(), "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %lu %lu %ld %ld ",
    &pid, comm, &state, &ppid, &pgrp, &session, &tty_nr, &tpgid, &flags, &minft, &cminflt, &majflt,
    &cmajflt, &stat_data_out.utime, &stat_data_out.stime, &stat_data_out.cutime, &stat_data_out.cstime);
  if (ret != 17) {
    LogError("sscanf get app or task stat data failed\n");
    return -1;
  }
  return 0;
}
int AppTaskScan::GetTids(int pid, std::list<int>& tids) {
  return 0;
}
int AppTaskScan::GetTids(const std::string & app_stat_path, std::list<int>& tids) {
  return 0;
}
int AppTaskScan::GetTids(const std::string &app_stat_path, std::list<std::string> &tid_folders) {
 
}
}
