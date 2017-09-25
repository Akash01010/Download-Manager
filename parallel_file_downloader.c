#include <pthread.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include<fcntl.h>

int main(int argc, char const *argv[])
{
	char snum[1000],snum1[1000],snum2[1000];
	//./a.out(0) http://10.8.19.24/ProxyData/access.log-20161108.gz(1) file3.gz(4)
	//--range 0-19999999 -o part1 http://10.8.19.24/ProxyData/access.log-20161108.gz
	//itoa(num, snum, 10);
	int fork_count,i,file_size,part_size;
	sscanf(argv[3],"%d",&fork_count);
	sscanf(argv[2],"%d",&file_size);
	part_size=file_size/fork_count;
	printf("%d\n", part_size);
	/*char str1[1000]={" --range 0-"};//19999999 -o part1 "};
	//char str2[1000]={" --range 20000000- -o part2 "};

	strcat(str1,argv[1]);
	strcat(str1,argv[1]);
	strcat(str1,argv[1]);
	strcat(str2,argv[1]);
	
	long int parts=atoi(argv[2])/atoi(argv[3]);
	//fork_count=2;
	printf("%d\n", fork_count);*/
	//fork_count=2;
	pid_t processes[fork_count];
	//clock_t start =clock();
	for (i = 0; i < fork_count; ++i)
	{
		processes[i]=fork();
		if (processes[i]==-1)
		{
			printf("Process %d not created\n", i);
			_exit(1);
		}
		else if (processes[i]==0)
		{
			if (i==(fork_count-1))
			{
				char snum3[]={"otpt/part"};
				sprintf(snum2, "%d", i+1);
				strcat(snum3,snum2);
				printf("%d\n", file_size-part_size*i);
				sprintf(snum, "%d", part_size*i);
				strcat(snum,"-");
				//sprintf(snum1, "%d", part_size*(i+1)-1);
				//strcat(snum,snum1);

				char *ak[]={"curl","--range", snum, "-o",snum3, "http://10.8.19.24/ProxyData/access.log-20161108.gz",NULL};
				if(execvp(ak[0],ak) < 0){
					_exit(EXIT_FAILURE);
				}
				else{
					//printf("good 2\n");
					//waitpid(processes[i], NULL, 0);
					//_exit(EXIT_SUCCESS);
				}
			}
			else{
				char snum3[]={"otpt/part"};
				sprintf(snum2, "%d", i+1);
				strcat(snum3,snum2);
				printf("%d\n", part_size*(i+1)-1-part_size*i);
				sprintf(snum, "%d", part_size*i);
				strcat(snum,"-");
				sprintf(snum1, "%d", part_size*(i+1));
				strcat(snum,snum1);
				
				char *ak[]={"curl","--range", snum, "-o", snum3, "http://10.8.19.24/ProxyData/access.log-20161108.gz",NULL};
				if(execvp(ak[0],ak) < 0){
					_exit(EXIT_FAILURE);
				}
				else{
					//waitpid(processes[i], NULL, 0);
					//_exit(EXIT_SUCCESS);
				}
			}
		}
		else{
			continue;
		}
	}
	//middle =clock();

	for (i = 0; i < fork_count; ++i)
	{
		int   result;
        waitpid(processes[i], &result, 0);
	}

	
	/*if(execvp(ak[0],ak) < 0){
		_exit(EXIT_FAILURE);
	}*/

	int file_desc = open(argv[4], O_CREAT | O_RDWR);
	//int file_desc1 = open("part1",O_WRONLY | O_APPEND);

    
    // here the newfd is the file descriptor of stdout (i.e. 1)
    dup2(file_desc, 1) ;

    DIR *directory;
	struct dirent* file;
	directory=opendir("/mnt/d/Sem 5/CS 310/Assign3_B15303/otpt");
	if (directory==NULL)
	{
		printf("Not a directory\n");
		return 0;
	}
	else
		printf("Good till here\n");
	char filename[1000]={};
	i=0;
	while ((file=readdir(directory)) != NULL) {
		//printf("good1\n");
			processes[i]=fork();
			if (processes[i]==-1)
			{
				printf("Process %d not created\n", i);
				_exit(1);
			}
			else if (processes[i]==0)
			{
				if( strstr(file->d_name, "file"))
				{
					i++;
					sprintf(filename,"%s", "output/");
					strcat(filename, file->d_name);
					char *ak[]={"cat",filename,NULL};
					if(execvp(ak[0],ak)<0){
						printf("No way\n");
					}
					else
						printf("Yes Way\n");
				}
				else
					printf("file is error\n");

			}


			else
				printf("Some other error\n");
	}
	for (i = 0; i < fork_count; ++i)
	{
		int   result;
        waitpid(processes[i], &result, 0);
	}
	
	return 0;
}