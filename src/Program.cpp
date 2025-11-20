// TODO: Imply interfaces declared in the Program.hpp.
#include <map>
#include <memory>
#include <vector>
#include <iostream>

#include "Statement.hpp"
#include "Recorder.hpp"
#include "Program.hpp"
#include "Expression.hpp"
#include "VarState.hpp"

Program::Program(){
    recorder_.clear();
    vars_.clear();
    programCounter_ = -1;
    programEnd_ = 0;
}

void Program::addStmt(int line, Statement* stmt){
    recorder_.add(line,stmt);
}

void Program::removeStmt(int line){
    if(recorder_.hasLine(line)) recorder_.remove(line);
}

void Program::run(){
    while(recorder_.nextLine(programCounter_) != -1){
        recorder_.get(recorder_.nextLine(programCounter_))->execute(vars_,*this);
    }
    programEnd();
}

void Program::list() const{
    recorder_.printLines();
}

void Program::clear(){
    recorder_.clear();
    vars_.clear();
}

void Program::execute(Statement* stmt){
    stmt->execute(vars_,*this);
}

int Program::getPC() const noexcept{
    if(!programEnd_) return programCounter_;
}
void Program::changePC(int line){
    if(recorder_.hasLine(line)){
        programCounter_ = line-1;
    }
    //
}
void Program::programEnd(){
    programEnd_ = 1;
}

void Program::resetAfterRun() noexcept{
    (*this).clear();
    programCounter_ = -1;
    programEnd_ = 0;
}