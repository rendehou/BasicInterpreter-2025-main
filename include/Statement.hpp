#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.
//Let
class LetStatement : public Statement{
 public:
  LetStatement(std::string source, std::string varName, Expression* expr);
  ~LetStatement() override;

  void execute(VarState& state, Program& program) const;

 private:
  std::string varName_;
  Expression* expr_;
};
//Print
class PrintStatement : public Statement{
 public:
  PrintStatement(std::string source, Expression* expr);
  ~PrintStatement() override;

  void execute(VarState& state, Program& program) const;

 private:
  std::string varName_;
  Expression* expr_;
};
//Input
class  InputStatement : public Statement{
  public:
  InputStatement(std::string source, std::string varName);
  ~InputStatement() override;

  void execute(VarState& state, Program& program) const;

 private:
  std::string varName_;
};
//Goto
class GotoStatement : public Statement{
  public:
  GotoStatement(std::string source,int num);
  ~GotoStatement() override;

  void execute(VarState& state,Program& program) const;

  private:
  int num_;
};
//Rem
class RemStatement : public Statement{
  public:
  RemStatement(std::string source);
  ~RemStatement() override;

  void execute(VarState& state,Program& program) const;
};
//End
class EndStatement : public Statement{
  public:
  EndStatement(std::string source);
  ~EndStatement() override;

  void execute(VarState& state,Program& program) const;
};
//If
class IfStatement : public Statement{
  public:
  IfStatement(std::string source,Expression* expr_left,Expression* expr_right,int num,char op);
  ~IfStatement() override;
  
  void execute(VarState& state,Program& program) const;
  private:
  Expression *expr_left_,*expr_right_;
  int num_;
  char op_;
};