/*
*
* author: ChenFawang
* tt_path.cc
* 2018 - 11 - 13
* mail: cfwang_9984@163.com
*
*/
#include "tt_path.h"
namespace task_top {
const std::string path_delimiter_ = "/";
Path::Path(const std::string & path_base) {
  path_ = path_base;
  if (path_.rfind(path_delimiter_) != path_.size() - 1) {
    path_ += path_delimiter_;
  }
}
void Path::AppendFolder(const std::string & folder) {
  path_ += folder;
  if (path_.rfind(path_delimiter_) != path_.size() - 1) {
    path_ += path_delimiter_;
  }
}
void Path::SetFile(const std::string & file_name) {
  path_ += file_name;
}
void Path::DeletePath(int level) {
  //TODO
}
}