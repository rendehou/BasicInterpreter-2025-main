// TODO: Imply interfaces declared in the Recorder.hpp.
#include <map>
#include <memory>
#include <vector>
#include <iostream>

#include "Statement.hpp"
#include "Recorder.hpp"
#include "utils/Error.hpp"
Recorder::~Recorder(){
    for (auto it = RecorderMap.begin();it != RecorderMap.end();it++){
        delete it->second;
    }
}

void Recorder::add(int line, Statement* stmt){
    if(RecorderMap.find(line) != RecorderMap.end()){
        delete RecorderMap[line];
    }
    RecorderMap[line] = stmt;  // 使用[]操作符进行覆盖
}
/**/
void Recorder::remove(int line){//???这样写对吗
    auto it = RecorderMap.find(line);
    if(it != RecorderMap.end()){
        delete it->second;
        RecorderMap.erase(it);
    }
}

const Statement* Recorder::get(int line) const noexcept {
    if(RecorderMap.find(line) != RecorderMap.end()) {
        return RecorderMap.find(line)->second;
    }
    else {
        return nullptr;
    }
}

bool Recorder::hasLine(int line) const noexcept{
    if(RecorderMap.find(line) != RecorderMap.end()) return true;
    else return false;
}

void Recorder::clear() noexcept{
    while (!RecorderMap.empty()) {
        auto it = RecorderMap.begin();
        delete it->second;
        RecorderMap.erase(it);
    }
}

void Recorder::printLines() const{
    if(!RecorderMap.empty()){
        for(auto it = RecorderMap.begin(); it != RecorderMap.end();it++){
            std::cout << (it->second)->text() << std::endl;
        }
    }
    else return ;
}

int Recorder::nextLine(int line) const noexcept{
    auto it = RecorderMap.upper_bound(line);
    if(it != RecorderMap.end()) return it->first;
    else return -1;
}