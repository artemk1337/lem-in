#!/bin/sh

make
rm test
./generator --big > test
cat test | ./lem-in
