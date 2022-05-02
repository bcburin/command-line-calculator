#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>

class Statement {
  private:
    std::string m_str;
  public:
    Statement(std::string str);
    std::string str() { return m_str; }
    virtual void execute() = 0;
};

class Expression: public Statement {
  private:
    double m_result;
    bool run_mode;
    std::ostream* os;
  public:
    Expression(std::string str, std::ostream* os = nullptr, bool run_mode = false);
    double result() { return m_result; }
    void execute() override;
    static double evaluate(std::string str);
};

class DeleteStatement: public Statement {
  private:
    std::string m_variable;
  public:
    DeleteStatement(std::string str);
    void execute() override;
};

class RunStatement: public Statement {
  private:
    std::string filename;
    std::vector<std::string> arguments;
  public:
    RunStatement(std::string str);
    void execute() override;
};

class PrintStatement: public Statement {
  private:
    std::string expression;
    std::ostream* os;
  public:
    PrintStatement(std::string str, std::ostream* os);
    void execute() override;
};

class MultilineStatement: public Statement {
  private:
    std::vector<Statement*> m_nested_statements;
  public:
    MultilineStatement(std::string str, std::vector<Statement*> nested_statements);
    std::vector<Statement*> nested_statements() { return m_nested_statements; }
    virtual void execute() = 0;
};

class IfStatement: public MultilineStatement {
  private:
    std::string m_condition;
  public:
    IfStatement(std::string str, std::vector<Statement*> nested_statements);
    void execute() override;
};

class WhileStatement: public MultilineStatement {
  private:
    std::string m_condition;
  public:
    WhileStatement(std::string str, std::vector<Statement*> nested_statements);
    void execute() override;
};

class ForStatement: public MultilineStatement {
  private:
    std::string m_init;
    std::string m_condition;
    std::string m_increase;
  public:
    ForStatement(std::string str, std::vector<Statement*> nested_statements);
    void execute() override;
};

#endif