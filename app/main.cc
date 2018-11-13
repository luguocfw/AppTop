/*
*
* author: ChenFawang
* main.cc
* 2018 - 11 - 12
* mail: cfwang_9984@163.com
*
*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <signal.h>

#include "tt_hander.h"
static bool app_is_run_ = true;
void Usage() {
  printf("tasktop [options] argu\n");
  printf("options :\n\t-p set display pid ,this is can mult pid, but can't without\n\t-d loop time sec (Default 5s)\n");
  printf("example: tasktop -p 1234 -p 12765 -p 2376 -d 3\n");
}

bool AllIsNum(const std::string &str) {
  int i;
  for (i = 0; i < str.length(); i++) {
    if (str[i]<'0' || str[i]>'9') {
      return false;
    }
  }
  return true;
}

void DisplayCpuInfo(task_top::SystemCpuInfo &sys_cpu, std::list<task_top::AppCpuInfoAll> &apps_cpu) {
  printf("system:\n\tUSER:%.2l%%\tSYS:%.2f%%\tNIC:%.2f%%\tIDLE:%.2f%%\n\tIO:%.2f%%\tIRQ:%.2f%%\tSIRQ:%.2f%%\n",
    sys_cpu.user_ * 100, sys_cpu.sys_ * 100, sys_cpu.nic_ * 100,
    sys_cpu.idle_ * 100, sys_cpu.io_ * 100, sys_cpu.irq_, sys_cpu.sirq_);
  if (apps_cpu.size() != 0) {
    printf("-----------------------apps cpu info---------------------\n");
    printf("PID\t\tNAME\t\tCPU\n");
    for (auto app = apps_cpu.begin(); app != apps_cpu.end(); app++) {
      printf("%d\t\t%s\t\t%.2f%%\n", app->pid, app->name.c_str(),
        (app->app_cpu.cstime + app->app_cpu.cutime + app->app_cpu.stime + app->app_cpu.utime));
      if (app->task.size() != 0) {
        printf("\t\t    TID\t\tNAME\t\tCPU\n");
        for (auto task = app->task.begin(); task != app->task.end(); task++) {
          printf("\t\t|---%d\t\t%s\t\t%.2f%%\n", task->tid, task->name.c_str(),
            (task->cpu.cstime + task->cpu.cutime + task->cpu.stime + task->cpu.utime));
        }
      }
    }
  }
}
static void HandleSig(int signo) {
  app_is_run_ = false;
}

int main(int argc, char* argv[]) {
  signal(SIGINT, HandleSig);
  signal(SIGTERM, HandleSig);
  signal(SIGKILL, HandleSig);
  if (argc < 3 || argc % 2 != 1) {
    Usage();
    return -1;
  }
  int loop_time = 5;
  std::list<int> pids;
  pids.clear();
  int i;
  for (i = 1; i < argc; i = i + 2) {
    std::string option = argv[i];
    if (option == "-p") {
      std::string pid = argv[i + 1];
      if (!AllIsNum(pid)) {
        Usage();
        return -2;
      }
      pids.push_back(task_top::stoi(pid));
    } else if (option == "-d") {
      std::string sec = argv[i + 1];
      if (!AllIsNum(sec)) {
        Usage();
        return -3;
      }
      loop_time = task_top::stoi(sec);
    } else {
      printf("unknow option: %s\n", argv[i]);
      Usage();
      return -4;
    }
  }
  if (pids.size() == 0) {
    printf("without input pid !!!\n");
    Usage();
    return -5;
  }
  task_top::TaskTopHandler task_top(pids);
  while (app_is_run_) {
    std::list<task_top::AppCpuInfoAll> apps_cpu;
    task_top::SystemCpuInfo sys_cpu;
    apps_cpu.clear();
    task_top.GetCpuInfo(apps_cpu, sys_cpu);
    DisplayCpuInfo(sys_cpu, apps_cpu);
    int wait = (loop_time * 1000) / 200;
    while (wait--&&app_is_run_) {
      usleep(1000 * 200);
    }
  }
  return 0;
}