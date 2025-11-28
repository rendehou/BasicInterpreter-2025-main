#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  try{
    while (std::getline(std::cin, line)) {
      if (line.empty()) {
        continue;
      }
      else {
        TokenStream token_stream = lexer.tokenize(line);
        token_stream.reset();
        const Token* token = token_stream.peek();
        if(token && token->type == TokenType::QUIT) {
          break;
        }
        else if(token && token->type == TokenType::RUN) {
          program.run();
        }
        else if(token && token->type == TokenType::CLEAR) {
          program.clear();
        }
        else if(token && token->type == TokenType::LIST) {
          program.list();
        }
        else {
          token_stream.reset();
          ParsedLine parsed_line;
          Statement* statement = nullptr;
          try {
            parsed_line = parser.parseLine(token_stream, line);
            statement = parsed_line.getStatement();
          } catch (const BasicError& e) {
            std::cout << e.message() << std::endl;
            continue;
          }
          std::optional<int> line_number = parsed_line.getLine().value_or(0);
          if(line_number == 0) 
          {
            try{
              if (statement) {
                program.execute(statement);
              }
            }catch (const BasicError& e) {
              std::cout << e.message() << std::endl;
            }
            if (statement) {
              delete statement;
            }
          }
          else if(statement == nullptr && line_number != 0) {
            program.removeStmt(line_number.value());
          }
          else {
            try {
              program.addStmt(line_number.value(), statement);
            } catch (const BasicError& e) {
              std::cout << e.message() << std::endl;
              if (statement) {
                delete statement;
              }
            }
          }
        }
      }
    }
  } catch (...) {

  }
  return 0;
}