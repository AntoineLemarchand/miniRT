#!/bin/sh
array=$(ls -1 examples/basic)

for truc in $array
do
	./miniRT examples/basic/$truc
done
