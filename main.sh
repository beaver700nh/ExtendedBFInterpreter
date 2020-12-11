#!/bin/bash

read -p "Compile? [Y/n] " compile_y_n

if [[ $compile_y_n == "" || $compile_y_n == "y" || $compile_y_n == "Y" ]]; then
  echo "Compiling..."

  if clang++ -pthread -std=c++17 main.cpp interpreter.cpp -o main; then
    echo "SUCCESS!"

  else
    echo "FAILED!"

  fi
fi

echo "Running program..."
read -p "Enter the filename to run: " answer

if [[ $answer == "" ]]; then
  answer="test.bf"
fi

./main $answer