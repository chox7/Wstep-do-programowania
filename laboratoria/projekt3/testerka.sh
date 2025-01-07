#!/bin/bash

# Zakładając, że masz folder 'przyklady' z testami i oczekiwanymi wynikami

for i in {10..16}; do
  echo "Testowanie testu $i..."
  ./sokoban < przyklady/test$i.in | diff - przyklady/test$i.out
  if [ $? -eq 0 ]; then
    echo "Test $i zakończony pomyślnie!"
  else
    echo "Test $i nie przeszedł."
  fi
  echo "-------------------------"
done
