#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "interpreter.hpp"

std::string convert_to_string(std::ifstream& ifs);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "\nInvalid argument count.\n\tUsage: ./main <bf_file>\n\n";
  }
  else {
    std::ifstream file;
    file.open(argv[1]);

    if (!file) {
      std::cout << "\nError while trying to open file.\n\n";
    }
    else {
      std::cout << "\n";

      std::string prog_as_string = convert_to_string(file);
      Interpreter i(prog_as_string);
      int result = i.interpret_program();

      if (result == 0) {
        std::cout << "Program exited successfully.\n";
      }
      else {
        std::cout << "Program exited abnormally.\n";
        std::cout << "Error code: " << std::to_string(result) << "\n";
      }
    }
  }

  return 0;
}

std::string convert_to_string(std::ifstream& ifs) {
  std::stringstream ss;
  ss << ifs.rdbuf();
  return ss.str();
}
