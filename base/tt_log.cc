/*
*
* author: ChenFawang
* tt_log.c
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#include "tt_log.h"
#include <stdio.h>
namespace task_top {
bool log_is_init_ = false;
pthread_mutex_t log_mux_ = PTHREAD_MUTEX_INITIALIZER;
LogAttr log_attr_;

int LogInit(const LogAttr *attr) {
  int ret;
  pthread_mutex_lock(&log_mux_);
  if (log_is_init_ == true) {
    printf("logger is already init\n");
    pthread_mutex_unlock(&log_mux_);
    return -1;
  }
  if (attr != NULL) {
    memcpy(&log_attr_, attr, sizeof(LogAttr));
  } else {
    log_attr_.file_fp = NULL;
    log_attr_.error_log_attr.en_log = true;
    log_attr_.error_log_attr.en_line = true;
    log_attr_.error_log_attr.en_time = true;
    memcpy(&log_attr_.info_log_attr, &log_attr_.error_log_attr, sizeof(OneLogAttr));
  }
  log_is_init_ = true;
  pthread_mutex_unlock(&log_mux_);
  return 0;
}

void LogExit() {
  pthread_mutex_lock(&log_mux_);
  if (log_is_init_ == false) {
    printf("logger without init\n");
    pthread_mutex_unlock(&log_mux_);
    return;
  }
  log_attr_.file_fp = NULL;
  log_attr_.error_log_attr.en_log = true;
  log_attr_.error_log_attr.en_line = true;
  log_attr_.error_log_attr.en_time = true;
  memcpy(&log_attr_.info_log_attr, &log_attr_.error_log_attr, sizeof(OneLogAttr));
  log_is_init_ = false;
  pthread_mutex_unlock(&log_mux_);
}


void LogSetAttr(const LogAttr *attr) {
  pthread_mutex_lock(&log_mux_);
  memcpy(&log_attr_, attr, sizeof(LogAttr));
  pthread_mutex_unlock(&log_mux_);
}

void LogGetAttr(LogAttr *attr) {
  pthread_mutex_lock(&log_mux_);
  memcpy(attr, &log_attr_, sizeof(LogAttr));
  pthread_mutex_unlock(&log_mux_);
}
}
