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
#include "utils/Error.hpp"

Program::Program(){
    recorder_.clear();
    vars_.clear();
    programCounter_ = -1;
    programEnd_ = 1;
}

void Program::addStmt(int line, Statement* stmt){
    recorder_.add(line,stmt);
}

void Program::removeStmt(int line){
    recorder_.remove(line);
}

void Program::run(){
    programEnd_ = 0;
    programCounter_ = -1;
    while(programEnd_ != 1){
        int next = recorder_.nextLine(programCounter_);
        if(next == -1) break;
        programCounter_ = next;
        const Statement* stmt = recorder_.get(next);
        try{
            stmt->execute(vars_,(*this));
        }catch(const BasicError &e){
            std::cout << e.message() << std::endl;
        }
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
    else {
        return -1;
    }
}

void Program::changePC(int line){
    if(recorder_.hasLine(line)){
        programCounter_ = line;
    }
    else{
        throw BasicError("LINE NUMBER ERROR");
    }
    //?
}

void Program::programEnd(){
    if(programEnd_ == 0) programEnd_ = 1;
    else throw BasicError("SYNTAX ERROR");
}

void Program::resetAfterRun() noexcept{
    (*this).clear();
    programCounter_ = -1;
}