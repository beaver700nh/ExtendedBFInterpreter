#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <unordered_map>
#include <string>
#include <stack> 

#define MIN_BUF 0
#define MAX_BUF 1024

class Interpreter {
  public:
    Interpreter(std::string prog);

    int interpret_program();

  private:
    std::string prog;
    std::string lexed_prog;

    int this_ch_num;
    char this_ch;

    int buf[MAX_BUF];
    int idx = 0;

    std::unordered_map<char, int> jump_map = {};

    std::stack<int> prog_stack;

    void lex_program();
    bool is_instruction(char ch);

    void interpret_char();

    void interpret_increment();
    void interpret_decrement();
    void interpret_idx_left();
    void interpret_idx_right();
    void interpret_print_char();
    void interpret_input_char();
    void interpret_input_line();
    void interpret_loop_begin();
    void interpret_loop_end();
    void interpret_stack_push();
    void interpret_stack_pop();
    void interpret_jump_to();
    void interpret_jump_zero();
    void interpret_jump_nzero();
    void interpret_jump_pos();
    void interpret_jump_neg();

    static const char COMMENT    = '!';
    static const char INCREMENT  = '+';
    static const char DECREMENT  = '-';
    static const char IDX_LEFT   = '<';
    static const char IDX_RIGHT  = '>';
    static const char PRINT_CHAR = '.';
    static const char INPUT_CHAR = ',';
    static const char INPUT_LINE = '~';
    static const char LOOP_BEGIN = '[';
    static const char LOOP_END   = ']';
    static const char STACK_PUSH = '^';
    static const char STACK_POP  = 'v';
    static const char JUMP_TO    = '|';
    static const char JUMP_ZERO  = '/';
    static const char JUMP_NZERO = '\\';
    static const char JUMP_POS   = ':';
    static const char JUMP_NEG   = ';';

    static const std::string instructions;
};

#endif