#!/bin/zsh

#color
output=$'\033[94m'
error=$'\033[31m'
warning=$'\033[93m'
success=$'\033[92m'
reset=$'\033[0;39m'

STANDAR_OUPUT_FILE=std.out
FT_OUPUT_FILE=ft.out
DEBUG=0

#			print_message(message, type)
function	print_message {
	type=$2
	if [ -z "$type" ]; then
		type=${output}
	fi
	echo -e "${type}$1${reset}"
}

#			print_error(message)
function	print_error {
	print_message "Error : "$1 $error
}

#			print_warning(message)
function	print_warning {
	print_message $1 $warning
}

#			print_warning(message)
function	print_success {
	print_message $1 $success
}

#			unit_test(path)
function	unit_test {
	IN=$1
	CONTAINER=$(echo "$IN" | cut -d/ -f 2)
	TEST_NAME=$(echo "$IN" | cut -d/ -f 3 | cut -d. -f 1)
	STD_LOG=./log/"$CONTAINER"_"$TEST_NAME"_std
	FT_LOG=./log/"$CONTAINER"_"$TEST_NAME"_ft
	print_message $TEST_NAME
	clang++ -Werror -Wextra -Wall -std=c++98 -I ../ -I./includes $file -o std.out &>> $STD_LOG || { print_warning "complilation with standar namespace fail, skip test"; return 1; }
	./std.out &>> $STD_LOG || { print_warning "exec with standar namespace fail, skip test"; return 1; }
	clang++ -Werror -Wextra -Wall -std=c++98 -I ../ -I./includes $file -D NAMESPACE=ft -o ft.out &>> $FT_LOG || { print_error "compilation fail"; return 1; }
	./ft.out &>> $FT_LOG || { print_error "exec fail"; return 1; }
	diff $STD_LOG $FT_LOG
	if [ $? -eq 0 ];then
		print_success "[OK]"
	else
		print_message "[K0]" $error
	fi
}

rm -rf log
mkdir -p log
for file in ./vector/*
do
	unit_test $file
done
