#!/bin/bash

#color
output=$'\033[94m'
error=$'\033[31m'
warning=$'\033[93m'
success=$'\033[92m'
reset=$'\033[0;39m'

STANDAR_OUPUT_FILE=std.out
FT_OUPUT_FILE=ft.out
DEBUG=0
VERBOSE=1
LEAKS=1
newline=1



#			print_message(message, type)
function	print_message {
	type=$2
	if [ -z "$type" ]; then
		type=${output}
	fi
	if [ $newline -eq 0 ];then
		echo -n -e "${type}$1${reset}"
	else
		echo -e "${type}$1${reset}"
	fi
}

#			print_error(message)
function	print_error {
	print_message "[Error] : "$1 $error
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
	if [ "$DIRSCRIPT" != "." ];then
		IN=$(echo $1 | sed "s|$DIRSCRIPT||g")
	else
		IN=$1
	fi
	container_name=$(echo "$IN" | cut -d/ -f 2)
	test_name=$(echo "$IN" | cut -d/ -f 3 | cut -d. -f 1)
	STD_LOG=$DIRSCRIPT/log/"$container_name"_"$test_name"_std
	FT_LOG=$DIRSCRIPT/log/"$container_name"_"$test_name"_ft

	newline=0
	if [ $VERBOSE -eq 1 ];then
		print_message $test_name" : "
		newline=1
	fi;
	clang++ -Werror -Wextra -Wall -std=c++98 -I$DIRSCRIPT/includes $file -D NAMESPACE=std -o $DIRSCRIPT/std.out &>> $STD_LOG || { print_warning "complilation with standar namespace fail, skip test " ; return 1; }
	$DIRSCRIPT/std.out &>> $STD_LOG || { print_warning "exec with standar namespace fail, skip test "; return 1; }
	clang++ -Werror -Wextra -Wall -g -std=c++98 -I $DIRSCRIPT/../ -I$DIRSCRIPT/includes -include $DIRSCRIPT/includes/ft_utils.hpp $file -D NAMESPACE=ft -o $DIRSCRIPT/ft.out &>> $FT_LOG || { print_error "compilation_fail " ; return 1; }
	$DIRSCRIPT/ft.out &>> $FT_LOG || { print_error "SEGFAULT "; return 1; }
	diff $STD_LOG $FT_LOG &>> $FT_LOG
	if [ $? -eq 0 ];then
		print_success "[OK] "
		rm -rf $FT_LOG $STD_LOG
	else
		print_message "[K0] " $error
	fi
	newline=1
}

#			container_test(name, n=none)
function	container_test {
	print_message $1
	for file in $DIRSCRIPT/$1/$2*
	do
		unit_test $file
	done
	if [ "$2" != "" ];then
		if [ $LEAKS -eq 1 ];then
		valgrind --leak-check=full ./ft.out
		fi
	fi
}

containers=(vector list map)

if [ -n $BASH_SOURCE -a ! "$BASH_SOURCE" = "" ];then
	DIRSCRIPT=$(dirname -- "$BASH_SOURCE") > /dev/null
	SCRIPTPATH=$BASH_SOURCE
else
	DIRSCRIPT=$(dirname -- "$0") > /dev/null
	SCRIPTPATH=$0
fi

rm -rf $DIRSCRIPT/log
mkdir -p $DIRSCRIPT/log

if [ -z $1 ];then
	for container in ${containers[@]}; do
		container_test $container
	done
else
	container_test $1 $2
fi

