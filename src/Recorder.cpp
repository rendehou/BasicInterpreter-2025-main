// TODO: Imply interfaces declared in the Recorder.hpp.
#include <map>
#include <memory>
#include <vector>
#include <iostream>

#include "Statement.hpp"
#include "Recorder.hpp"

Recorder::~Recorder(){
    for (auto it = RecorderMap.begin();it != RecorderMap.end();it++){
        delete it->second;
    }
}

void Recorder::add(int line,Statement* stmt){
    if(RecorderMap.find(line) == RecorderMap.end()){
        RecorderMap.insert(std::make_pair(line,stmt));
    }
    else {
        RecorderMap.find(line)->second = stmt;
    }
}

void Recorder::remove(int line){
    RecorderMap.erase(line);
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
    for (auto it = RecorderMap.begin();it != RecorderMap.end();it++){
        delete it->second;
        RecorderMap.erase(it->first);
    }
}

void Recorder::printLines() const{
    for(auto it = RecorderMap.begin(); it != RecorderMap.end();it++){
        std::cout << (it->second)->text() << std::endl;
    }
}

int Recorder::nextLine(int line) const noexcept{
    auto it = RecorderMap.upper_bound(line);
    if(it != RecorderMap.end()) return it->first;
    else return -1;
}