#!/bin/bash

#gcc -fsanitize=address -g main.c
gcc -Wall -pedantic -Wno-long-long -O3 main.c
#gcc -O3 main.c

for i in 0 1 2
do
  echo "test "$i":"
  ./a.out < tests/000${i}_in.txt > tests/000${i}.out
  if diff tests/000${i}_out.txt tests/000${i}.out
  then
    echo ok
  fi
  echo "----------------------------------"
done
