/*
*
* author: ChenFawang
* tt_log.h
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#ifndef __TT_LOG_H__
#define __TT_LOG_H__
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

namespace task_top {


extern bool log_is_init_;                  //
extern pthread_mutex_t log_mux_;          //

typedef struct {
  bool         en_log;    // 1: open log 0: close log
  bool         en_time;   // 1: open time of log 0: close time of log
  bool         en_line;   // 1: open line of log 0: close line of log
}OneLogAttr;

typedef struct {
  FILE                *file_fp;    // pFileFp = NULL: log printf to console, pFileFp != NULL: log write to file of pFileFp
  OneLogAttr          error_log_attr;
  OneLogAttr          info_log_attr;
}LogAttr;
extern LogAttr log_attr_;              // #####################don't change this value, only use LogSetAttr interface to change


#define INFO_LOG_OPEN
#define ERROR_LOG_OPEN
#define USE_DEBUG_LINE
#define USE_DEBUG_TIME

#define PRINTF(fp,fmt,args...)       do{\
                                    if((fp)!=NULL) {\
                                      fprintf((fp),fmt,##args);\
                                    }else{\
                                      printf(fmt,##args);\
                                    }\
                                  }while(0);


#define filename(x)		strrchr(x,'/')?strrchr(x,'/')+1:x

#ifdef USE_DEBUG_LINE
#define DEBUG_LINE(fp)	          do{\
                                    PRINTF((fp),"%s:%d",filename(__FILE__),__LINE__);\
                                }while(0);
#else
#define DEBUG_LINE(fp)	
#endif

#ifdef USE_DEBUG_TIME
#define DEBUG_TIME(fp)            do{\
                                    struct timeval log_time;\
                                    gettimeofday(&log_time,NULL);\
                                    PRINTF((fp),"[%ld:%ld]",log_time.tv_sec,log_time.tv_usec/1000);\
                                }while(0);
#else
#define DEBUG_TIME(fp)
#endif


#ifdef INFO_LOG_OPEN
#define LogInfo(fmt,args...)       	do{\
                                      pthread_mutex_lock(&log_mux_);\
                                      if(log_is_init_ == true&&log_attr_.info_log_attr.en_log==true) {\
                                        if(log_attr_.info_log_attr.en_time==true){\
											                    DEBUG_TIME(log_attr_.file_fp);\
											                    PRINTF(log_attr_.file_fp," ");\
                                        }\
                                        if(log_attr_.info_log_attr.en_line==true){\
											                    DEBUG_LINE(log_attr_.file_fp);\
											                    PRINTF(log_attr_.file_fp," ");\
                                        }\
											                  PRINTF(log_attr_.file_fp,fmt,##args);\
                                      }\
                                      pthread_mutex_unlock(&log_mux_);\
										                }while(0);
#else
#define LogInfo(fmt,args...)
#endif


#ifdef ERROR_LOG_OPEN
#define LogError(fmt,args...)      do{\
                                    pthread_mutex_lock(&log_mux_);\
                                    if(log_is_init_ == true&&log_attr_.error_log_attr.en_log==true) {\
                                      if(log_attr_.error_log_attr.en_time==true){\
										                    DEBUG_TIME(log_attr_.file_fp);\
                                        PRINTF(log_attr_.file_fp," ");\
                                      }\
                                      if(log_attr_.error_log_attr.en_line==true){\
										                    DEBUG_LINE(log_attr_.file_fp);\
									                      PRINTF(log_attr_.file_fp," ");\
                                      }\
										                  PRINTF(log_attr_.file_fp,fmt,##args);\
                                    }\
                                    pthread_mutex_unlock(&log_mux_);\
									                }while(0);
#else
#define LogInfo(fmt,args...)
#endif




int LogInit(const LogAttr *attr);

void LogExit();

void LogSetAttr(const LogAttr *attr);

void LogGetAttr(LogAttr *attr);

}

#endif