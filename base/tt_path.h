/*
*
* author: ChenFawang
* tt_path.h
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#ifndef __TT_PATH_H__
#define __TT_PATH_H__
#include <string>
namespace task_top {
class Path {
public:
  Path(const std::string &path_base);
public:
  std::string Pathname();
  void AppendFolder(const std::string &folder);
  void SetFile(const std::string &file_name);
  void DeletePath(int level = 0);
private:
  std::string path_;
};
}

#endif