#include <unordered_map>
#include <iostream>
#include <cctype>
#include <string>
#include <stack>

#include "interpreter.hpp"

//#define DEBUG_PRINT

const std::string Interpreter::instructions = "!+-<>.,~[]^v|/\\:;";

Interpreter::Interpreter(std::string _prog) {
  prog = _prog;

  for (int i = 0; i < MAX_BUF; ++i) {
    buf[i] = 0;
  }
}

int Interpreter::interpret_program() {
  lex_program();

  for (this_ch_num = 0; this_ch_num < lexed_prog.length(); ++this_ch_num) {
    this_ch = lexed_prog.at(this_ch_num);

    interpret_char();
#ifdef DEBUG_PRINT
    std::cout << "Char:   " << this_ch << "\n";
    std::cout << "Index:  " << std::to_string(idx) << "\n";
    std::cout << "Value:  " << std::to_string(buf[idx]) << "\n\n";
#endif
  }

  std::cin.rdbuf();

  return 0;
}

void Interpreter::lex_program() {
  bool in_comment = false;

  for (int i = 0, j = 0, k = 0; i < prog.length(); ++i) {
    char ch = prog.at(i);

    if (ch == '!' && !in_comment) {
      in_comment = true;
    }
    else if (ch == '!' && in_comment) {
      in_comment = false;
    }
    else if (!in_comment && !std::isspace(ch)) {
      lexed_prog.push_back(ch);

      if (!is_instruction(ch) && prog.at(i - 1) != JUMP_TO) {
        // ch is a label
        jump_map[ch] = j;
      }
      else if (ch == LOOP_BEGIN) {
        loop_map[k++][0] = j;
      }
      else if (ch == LOOP_END) {
        loop_map[k][1] = j;
      }

      ++j;
    }
  }
}

bool Interpreter::is_instruction(char ch) {
  return (instructions.find(ch) != std::string::npos);
}

void Interpreter::interpret_char() {
  switch (this_ch) {
    case INCREMENT:  interpret_increment();  break;
    case DECREMENT:  interpret_decrement();  break;
    case IDX_RIGHT:  interpret_idx_right();  break;
    case IDX_LEFT:   interpret_idx_left();   break;
    case PRINT_CHAR: interpret_print_char(); break;
    case INPUT_CHAR: interpret_input_char(); break;
    case INPUT_LINE: interpret_input_line(); break;
    case LOOP_BEGIN: interpret_loop_begin(); break;
    case LOOP_END:   interpret_loop_end();   break;
    case STACK_PUSH: interpret_stack_push(); break;
    case STACK_POP:  interpret_stack_pop();  break;
    case JUMP_TO:    interpret_jump_to();    break;
    case JUMP_ZERO:  interpret_jump_zero();  break;
    case JUMP_NZERO: interpret_jump_nzero(); break;
    case JUMP_POS:   interpret_jump_pos();   break;
    case JUMP_NEG:   interpret_jump_neg();   break;
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
  if (buf[idx] != 0) {
    this_ch_num = loop_map[loop_id][1];
  }
}

void Interpreter::interpret_loop_end() {
  if (buf[idx] != 0) {
    this_ch_num = loop_map[loop_id][0];
  }
}

void Interpreter::interpret_stack_push() {
  prog_stack.push(buf[idx]);
}

void Interpreter::interpret_stack_pop() {
  buf[idx] = prog_stack.top();
  prog_stack.pop();
}

void Interpreter::interpret_jump_to() {
  this_ch_num = jump_map[lexed_prog.at(this_ch_num + 1)];
}

void Interpreter::interpret_jump_zero() {
  if (buf[idx] == 0) {
    interpret_jump_to();
  }
}

void Interpreter::interpret_jump_nzero() {
  if (buf[idx] != 0) {
    interpret_jump_to();
  }
}

void Interpreter::interpret_jump_pos() {
  if (buf[idx] > 0) {
    interpret_jump_to();
  }
}

void Interpreter::interpret_jump_neg() {
  if (buf[idx] < 0) {
    interpret_jump_to();
  }
}
