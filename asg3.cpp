#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char **argv){
	int status;
	int childpid;
	int childpid2;
	int childpid3;

	char *wc_args[] = {"wc", "-l", NULL};
	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};

	int pipes[2];
	int pipes2[2];
	pipe(pipes);
	pipe(pipes2);

	if((childpid = fork())  == -1){
		perror("Error creating a child process");
		exit(1);
	}
	if(childpid == 0){
		
		std::cout << "First child created." << std::endl;	
		
		dup2(pipes2[1], 1);
		close(pipes2[0]);
		close(pipes2[1]);
		//dup2(pipes2[0], 0);
		//close(pipes2[0]);
		//close(pipes2[1]);
		//dup2(pipes[0], 0);
		//close(pipes[1]);
		//close(pipes[0]);
		//dup2(pipes2[0], 0);
		//close(pipes2[0]);
		//close(pipes2[1]);
		
		execvp(*cat_args, cat_args);
		exit(0);
	}
	else{
		if((childpid2 = fork()) == -1){
			perror("error creating second child process");
			exit(1);
		}
		if(childpid2 == 0){
			
			std::cout << "Second child created." << std::endl;
			dup2(pipes[1], 1);
			close(pipes[0]);
			close(pipes[1]);
			//execvp(*wc_args, wc_args);
			dup2(pipes2[0], 0);
			close(pipes2[1]);
			close(pipes2[0]);
			//dup2(pipes2[0], 0);
			//close(pipes2[0]);
			//close(pipes2[1]);
			execvp(*grep_args, grep_args);
			exit(0);
		}
		else{
			
			if((childpid3 = fork()) == -1){
				
			}
			if(childpid3 == 0){
				std::cout << "Third child created." << std::endl;

				dup2(pipes[0], 0);
				close(pipes[0]);
				close(pipes[1]);
				//dup2(pipes2[1], 1);
				close(pipes2[0]);
				close(pipes2[1]);
				execvp(*wc_args, wc_args);
				exit(0);
			}
			else{
				
				std::cout << "Exited child processes." << std::endl;
				//dup2(pipes[1], 1);
				//close(pipes[1]);
				//close(pipes[0]);
				//execvp(*cat_args, cat_args);
				//dup2(pipes[0], 0);
				//close(pipes[1]);
				//close(pipes[0]);
				//dup2(pipes2[1], 1);
				//close(pipes2[1]);
				//close(pipes2[0]);
				//execvp(*grep_args, grep_args);
				//dup2(pipes2[0], 0);
				//close(pipes2[1]);
				//close(pipes2[0]);
				//dup2(1, pipes[0]);
				//execvp(*wc_args, wc_args);
			
				//dup2(pipes2[1], 1);
				//close(pipes2[0]);
				//close(pipes2[1]);
				//execvp(*cat_args, cat_args);
				//dup2(pipes[0], 0);
				//close(pipes[1]);
				//close(pipes[0]);
				//dup2(pipes2[1], 1);
				//execvp(*grep_args, grep_args);
				//return(0);
			}

		}
	}
	return(0);
}
	


