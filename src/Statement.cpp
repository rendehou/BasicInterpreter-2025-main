#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.
//LetStatement
LetStatement::LetStatement(std::string source, std::string varName, Expression* expr)
    : Statement(source), varName_(varName), expr_(expr) {}
LetStatement::~LetStatement() {
    delete expr_;
}
void LetStatement::execute(VarState& state,Program& program) const{
    int x = expr_->evaluate(state);
    state.setValue(varName_,x);
}
//PrintStatement
PrintStatement::PrintStatement(std::string source, Expression* expr)
    : Statement(source),expr_(expr) {}
PrintStatement::~PrintStatement(){
    delete expr_;
}
void PrintStatement::execute(VarState& state, Program& program) const{
    int x = expr_->evaluate(state);
    std::cout << x << std::endl;
}
//InputStatement
InputStatement::InputStatement(std::string source, std::string varName)
    : Statement(source), varName_(varName) {}
InputStatement::~InputStatement() {}
void InputStatement::execute(VarState& state,Program& program) const{
    while (true) {
        int x;
        std::cout << " ?" << " ";
        std::string input;
        std::getline(std::cin, input);
        try {
            x = std::stoi(input);
            size_t pos = 0;
            std::stoi(input, &pos);
            if (pos != input.length()) {
                std::cout << "INVALID NUMBER" << std::endl;
                continue;
            }
            state.setValue(varName_, x);
            break;
        } catch (const std::invalid_argument&) {
            std::cout << "INVALID NUMBER" << std::endl;
            continue;
        } 
    }
}
//GotoStatement
GotoStatement::GotoStatement(std::string source,int num)
    : Statement(source),num_(num) {}
GotoStatement::~GotoStatement() {}
void GotoStatement::execute(VarState& state,Program& program) const{
    program.changePC(num_);
}
//RemStatement
RemStatement::RemStatement(std::string source)
    : Statement(source) {}
RemStatement::~RemStatement() {}
void RemStatement::execute(VarState& state,Program& program) const{}
//EndStatement
EndStatement::EndStatement(std::string source)
    : Statement(source) {}
EndStatement::~EndStatement() {}
void EndStatement::execute(VarState& state,Program& program) const{
    program.programEnd();
}
//IfStatement
IfStatement::IfStatement(std::string source,Expression* expr_left,Expression* expr_right,int num,char op)
    :Statement(source),expr_left_(expr_left),expr_right_(expr_right),num_(num),op_(op) {}
  IfStatement::~IfStatement() {
    delete expr_left_;
    delete expr_right_;
  }
void IfStatement::execute(VarState& state,Program& program) const{
    int x = expr_left_->evaluate(state);
    int y = expr_right_->evaluate(state);
    if (op_ == '=') { 
        if(x == y) program.changePC(num_);
    }
    else if (op_ == '<') {
        if (x < y) program.changePC(num_);
    }
    else if (op_ == '>') {
        if (x > y) program.changePC(num_);
    }
}