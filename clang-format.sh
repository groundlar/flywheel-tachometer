#! /bin/bash

clang-format -i $(find . -type f -name "*.cc" -o -name "*.h")
