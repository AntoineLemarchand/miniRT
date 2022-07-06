#!/bin/sh
basics=$(ls -1 examples/basic)
bonuses=$(ls -1 examples/bonus)
err=$(ls -1 examples/errors)

if [ -z "$1" ]
then
	echo basic: only basic test
	echo bonus: bonus tests
	echo error: errors test
	echo all   : all tests
elif [ $1 = "basic" ]
then
	make
	echo ┏━━━━━━┓
	echo ┃BASICS┃
	echo ┗━━━━━━┛
	for basic in $basics
	do
		./miniRT examples/basic/$basic
	done
elif [ $1 = "bonus" ]
then
	make bonus

	echo ┏━━━━━━┓
	echo ┃BASICS┃
	echo ┗━━━━━━┛
	for basic in $basics
	do
		./miniRT_bonus examples/basic/$basic
	done

	echo ┏━━━━━━┓
	echo ┃BONUS ┃
	echo ┗━━━━━━┛
	for bonus in $bonuses
	do
		./miniRT_bonus examples/bonus/$bonus
	done
elif [ $1 = "error" ]
then
	make
	make bonus

	echo ┏━━━━━━┓
	echo ┃ERRORS┃
	echo ┗━━━━━━┛
	for error in $err
	do
		./miniRT examples/errors/$error
		./miniRT_bonus examples/errors/$error
	done
elif [ $1 = "all" ]
then
	make
	make bonus

	echo ┏━━━━━━┓
	echo ┃BASICS┃
	echo ┗━━━━━━┛
	for basic in $basics
	do
		./miniRT examples/basic/$basic
		./miniRT_bonus examples/basic/$basic
	done

	echo ┏━━━━━━┓
	echo ┃BONUS ┃
	echo ┗━━━━━━┛
	for bonus in $bonuses
	do
		./miniRT_bonus examples/bonus/$bonus
	done

	echo ┏━━━━━━┓
	echo ┃ERRORS┃
	echo ┗━━━━━━┛
	for error in $err
	do
		./miniRT examples/errors/$error
		./miniRT_bonus examples/errors/$error
	done
fi
