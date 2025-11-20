#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VarState {
 public:
  void setValue(const std::string& name, int value);//变量赋值
  int getValue(const std::string& name) const;//获取某变量的值
  void clear();//清空

 private:
  std::unordered_map<std::string, int> values_;
};
