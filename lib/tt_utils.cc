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
#include "tt_global.h"
#include "tt_path.h"

#include <direct.h>
#include <string>
#include <fstream>
#include <sstream>

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
  std::string base_path = task_top::global::g_system_proc_path_;
  Path pathname(base_path);
  pathname.AppendFolder(std::to_string(pid));
  return GetTids(pathname.Pathname(), tids);
}
int AppTaskScan::GetTids(const std::string & app_proc_path, std::list<int>& tids) {
  Path pathname(app_proc_path);
  pathname.AppendFolder(task_top::global::g_task_folder_);
  struct dirent *ent = NULL;
  DIR *p_dir;
  p_dir = opendir(pathname.Pathname().c_str());
  if (p_dir == NULL) {
    LogError("open dir :%s failed\n", pathname.Pathname().c_str());
    return -1;
  }
  tids.clear();
  while ((ent = readdir(p_dir)) != NULL) {
    if (ent->d_reclen == 16) {
      std::string tid_str = ent->d_name;
      if (tid_str != "."&&tid_str != "..") {
        int tid = std::stoi(tid_str);
        LogInfo("get pid %d application tid:%d \n", pid, tid);
        tids.push_back(tid);
      }
    }
  }
  closedir(p_dir);
  if (tids.size() == 0) {
    return -2;
  }
  return 0;
}
int AppTaskScan::GetTids(const std::string &app_proc_path, std::list<std::string> &tid_folders) {
  Path pathname(app_proc_path);
  pathname.AppendFolder(task_top::global::g_task_folder_);
  struct dirent *ent = NULL;
  DIR *p_dir;
  p_dir = opendir(pathname.Pathname().c_str());
  if (p_dir == NULL) {
    LogError("open dir :%s failed\n", pathname.Pathname().c_str());
    return -1;
  }
  tid_folders.clear();
  while ((ent = readdir(p_dir)) != NULL) {
    if (ent->d_reclen == 16) {
      std::string tid_str = ent->d_name;
      if (tid_str != "."&&tid_str != "..") {
        LogInfo("get pid %d application tid:%s \n", pid, tid_str.c_str());
        tid_folders.push_back(tid_str);
      }
    }
  }
  closedir(p_dir);
  if (tid_folders.size() == 0) {
    return -2;
  }
  return 0;
}
std::string AppTaskScan::GetThrName(int pid, int tid) {
  Path path(task_top::global::g_system_proc_path_);
  path.AppendFolder(std::to_string(pid));
  path.AppendFolder(task_top::global::g_task_folder_);
  path.AppendFolder(std::to_string(tid));
  path.SetFile(task_top::global::g_app_and_task_name_file_);
  std::ifstream ifs(path.Pathname());
  if (!ifs.is_open()) {
    return task_top::global::g_noname_string_;
  }
  std::stringstream ss;
  ss << ifs.rdbuf();
  std::string name = ss.str();
  return name;
}
std::string AppTaskScan::GetAppName(int pid) {
  Path path(task_top::global::g_system_proc_path_);
  path.AppendFolder(std::to_string(pid));
  path.SetFile(task_top::global::g_app_and_task_name_file_);
  std::ifstream ifs(path.Pathname());
  if (!ifs.is_open()) {
    return task_top::global::g_noname_string_;
  }
  std::stringstream ss;
  ss << ifs.rdbuf();
  std::string name = ss.str();
  return name;
}
}
