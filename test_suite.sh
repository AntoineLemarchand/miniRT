#!/bin/sh
basics=$(ls -1 examples/basic)
err=$(ls -1 examples/errors)

echo "BASICS"
for file in $basics
do
	./miniRT examples/basic/$file
done
echo "ERRORS"
for error in $err
do
	./miniRT examples/errors/$error
done
