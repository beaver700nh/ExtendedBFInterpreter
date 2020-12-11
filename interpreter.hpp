#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <unordered_map>
#include <string>
#include <stack> 

#define MIN_BUF 0
#define MAX_BUF 1024

#define COMMENT    '!'
#define INCREMENT  '+'
#define DECREMENT  '-'
#define IDX_LEFT   '<'
#define IDX_RIGHT  '>'
#define PRINT_CHAR '.'
#define INPUT_CHAR ','
#define INPUT_LINE '~'
#define LOOP_BEGIN '['
#define LOOP_END   ']'
#define STACK_PUSH '^'
#define STACK_POP  'v'
#define JUMP_TO    ':'

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
    void interpret_jump_label();
};

#endif