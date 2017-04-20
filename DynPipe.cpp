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
	int childpid4;

	char *wc_args[] = {"wc", "-l", NULL};
	char *cat_args[] = {"ls", "-ltr", NULL};
	char *grep_args[] = {"grep", "3376", NULL};

	if(argc > 6 || argc < 3){
		std::cout << "Error: try a different number of arguments." << std::endl;
	}
	
	int pipes[2];
	int pipes2[2];
	int pipes3[2];
	int pipes4[2];
	pipe(pipes);
	pipe(pipes2);
	pipe(pipes3);
	pipe(pipes4);
	
	std::cout << "argc = " << argc << std::endl;

	if((childpid = fork())  == -1){
		perror("Error creating a child process");
		exit(1);
	}
	if(childpid == 0){
		
		//std::cout << "First child created." << std::endl;	
		
		dup2(pipes2[1], 1);
		close(pipes2[0]);
		close(pipes2[1]);

		system(argv[1]);
		exit(0);
	}
	else{
		if((childpid2 = fork()) == -1){
			perror("error creating second child process");
			exit(1);
		}
		if(childpid2 == 0){
			
			//std::cout << "Second child created." << std::endl;
			if(argc != 3){

				dup2(pipes[1], 1);
			}
			close(pipes[0]);
			close(pipes[1]);
			
			dup2(pipes2[0], 0);
			close(pipes2[1]);
			close(pipes2[0]);

			system(argv[2]);
			exit(0);
		}
		else{
			
			if((childpid3 = fork()) == -1){
				perror("error creating third child process");
				exit(1);
			}
			if((childpid3 == 0) && (argc > 3)){
				//std::cout << "Third child created." << std::endl;
				if(argc != 4){
					dup2(pipes3[1], 1);
				}
				dup2(pipes[0], 0);
				close(pipes[0]);
				close(pipes[1]);
				
				close(pipes2[0]);
				close(pipes2[1]);
				system(argv[3]);
				exit(0);
			}
			else{
				if((childpid4 = fork()) == -1){
					perror("error creating fourth child process");
					exit(1);
				}
				if((childpid4 == 0) && (argc > 4)){
					dup2(pipes3[0], 0);
					if(argc != 5){
						dup2(pipes4[1], 1);
					}
					close(pipes[0]);
					close(pipes[1]);
					close(pipes2[0]);
					close(pipes2[1]);
					close(pipes3[0]);
					close(pipes3[1]);
					system(argv[4]);
					exit(0);
				}
				else{
					//std::cout << "Exited child processes." << std::endl;
					if(argc == 6){
						dup2(pipes4[0], 0);
						close(pipes[0]);
						close(pipes[1]);
						close(pipes2[0]);
						close(pipes2[1]);
						close(pipes3[0]);
						close(pipes3[1]);
						close(pipes4[0]);
						close(pipes4[1]);
						system(argv[5]);
					}
				}
			}

		}
	}
	return(0);
}
	


