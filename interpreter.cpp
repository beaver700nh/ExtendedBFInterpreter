#include <unordered_map>
#include <iostream>
#include <string>
#include <stack>

#include "interpreter.hpp"

Interpreter::Interpreter(std::string _prog) {
  prog = _prog;

  for (int i = 0; i < MAX_BUF; ++i) {
    buf[i] = 0;
  }
}

int Interpreter::interpret_program() {
  bool in_comment = false;

  for (this_ch_num = 0; this_ch_num < prog.length(); ++this_ch_num) {
    this_ch = prog.at(this_ch_num);

    if (this_ch == '!' && !in_comment) {
      in_comment = true;
    }
    else if (this_ch == '!' && in_comment) {
      in_comment = false;
    }
    else if (!in_comment) {
      interpret_char();
      // std::cout << "Char:   " << this_ch << "\n";
      // std::cout << "Index:  " << std::to_string(idx) << "\n";
      // std::cout << "Value:  " << std::to_string(buf[idx]) << "\n\n";
    }
  }

  std::cin.rdbuf();

  return 0;
}

void Interpreter::interpret_char() {
  if (this_ch == INCREMENT) {
    interpret_increment();
  }
  else if (this_ch == DECREMENT) {
    interpret_decrement();
  }
  else if (this_ch == IDX_RIGHT) {
    interpret_idx_right();
  }
  else if (this_ch == IDX_LEFT) {
    interpret_idx_left();
  }
  else if (this_ch == PRINT_CHAR) {
    interpret_print_char();
  }
  else if (this_ch == INPUT_CHAR) {
    interpret_input_char();
  }
  else if (this_ch == INPUT_LINE) {
    interpret_input_line();
  }
  else if (this_ch == LOOP_BEGIN) {
    interpret_loop_begin();
  }
  else if (this_ch == LOOP_END) {
    interpret_loop_end();
  }
  else if (this_ch == STACK_PUSH) {
    interpret_stack_push();
  }
  else if (this_ch == STACK_POP) {
    interpret_stack_pop();
  }
  else if (this_ch == JUMP_TO) {
    interpret_jump_to();
  }
  else {
    interpret_jump_label();
  }
}

void Interpreter::interpret_increment() {
  ++buf[idx];
}

void Interpreter::interpret_decrement() {
  --buf[idx];
}

void Interpreter::interpret_idx_left() {
  if (--idx == MIN_BUF - 1) {
    idx = MAX_BUF - 1;
  }
}

void Interpreter::interpret_idx_right() {
  if (++idx == MAX_BUF) {
    idx = MIN_BUF;
  }
}

void Interpreter::interpret_print_char() {
  std::cout << (char) buf[idx];
}

void Interpreter::interpret_input_char() {
  buf[idx] = std::cin.get();
}

void Interpreter::interpret_input_line() {
  std::string new_input;
  std::getline(std::cin, new_input);

  for (int i = new_input.size() - 1; i >= 0; --i) {
    prog_stack.push(new_input.at(i));
  }
}

void Interpreter::interpret_loop_begin() {

}

void Interpreter::interpret_loop_end() {

}

void Interpreter::interpret_stack_push() {
  prog_stack.push(buf[idx]);
}

void Interpreter::interpret_stack_pop() {
  buf[idx] = prog_stack.top();
  prog_stack.pop();
}

void Interpreter::interpret_jump_to() {
  this_ch_num = jump_map[prog.at(this_ch_num + 1)];
}

void Interpreter::interpret_jump_label() {
  jump_map[this_ch] = this_ch_num;
}
