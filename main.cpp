#include "list.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

template <class T>
void	print(ft::list<T>& lst)
{
	for (typename ft::list<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << " ";
	std::cout << '\n';
}

int main(int argc, char * argv[], char * envp[]){
	pid_t	pid = fork();
	int		status;

	(void)argc;
	if (pid == -1)
		return(EXIT_FAILURE);
	else if (pid == 0)
		execve("./tests/test.sh", argv + 1, envp);
	else
		waitpid(pid, &status, 0);
	return 0;
}