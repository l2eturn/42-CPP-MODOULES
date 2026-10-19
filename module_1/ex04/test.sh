#!/bin/sh
# run after `make`
printf "hello world\nhello 42\nhellohello\n" > sample.txt

echo "--- normal: hello -> bye ---"
./sedislame sample.txt hello bye && cat sample.txt.replace

echo "--- s2 empty: remove 'hello' ---"
./sedislame sample.txt hello "" && cat sample.txt.replace

echo "--- s1 not found ---"
./sedislame sample.txt xyz abc && cat sample.txt.replace

echo "--- s1 empty (should error) ---"
./sedislame sample.txt "" abc

echo "--- missing file (should error) ---"
./sedislame nofile.txt a b

echo "--- wrong arg count (should error) ---"
./sedislame sample.txt

rm -f sample.txt sample.txt.replace
