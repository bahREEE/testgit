#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>

void changedir(char* directory)
	{
	    chdir(directory);
    	}

int main(void){



	system("clear"); 
    	printf("\n\n\n\t****OUR TERMINAL****\n"); 

	printf("user ID is %d\n\n", getuid());
	printf("username is %s \n\n",getlogin());
	
	char cwd[256];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
	        	printf("current working directory is: %s\n\n", cwd);
    		}	
	
	printf("Reading environment variables from profile ...\n\n");
	FILE *fptr;
	fptr =	fopen("/home/bahreee/Desktop/profile","r");
		
		if (fptr == NULL)
    		{
        		printf("Can't open file.\n\n");
        		exit(EXIT_FAILURE);
    		}
	
	char *str1 = "HOME";
    	char *str2 = "PATH";
	char *find;
	char ligne[100] ;		

		while( fgets (ligne, 100, fptr)!=NULL )
    		{
       			if (find = strstr(ligne,str1)) 
          		{
              			printf("HOME variable found!\n\n");
          		}

			if (find = strstr(ligne,str2))
          		{
              			printf("PATH variable found!\n\n");
          		}
    		}		
	
	char *buf= (char *)malloc(10*sizeof(char));
	buf = getlogin();	
	
	char *udir = (char *)malloc(10*sizeof(char));
	strcpy(udir,"/home/");
	strcat(udir,buf);

	printf("user directory is : %s \n",udir);
	changedir(udir);
	printf("Moved to directory %s successfully! \n\n", udir);
	
	const char *envname="PATH";
	const char *envval="/bin:/usr/bin:/usr/local/bin";
	if (setenv(envname,envval,1))
		{
			printf("PATH variable set successfully!\n\n");
		}
	
	while(1){
	char* file=(char*)malloc(10*sizeof(char));
	char* param=(char*)malloc(10*sizeof(char));
	char* filec=(char*)malloc(10*sizeof(char));
	char* filecr=(char*)malloc(10*sizeof(char));
	char* filey=(char*)malloc(10*sizeof(char));
	char* newdirect=(char*)malloc(10*sizeof(char));
	char* direct=(char*)malloc(10*sizeof(char));
	char* directt=(char*)malloc(10*sizeof(char));
	char* dirname=(char*)malloc(10*sizeof(char));
	FILE *fp;
	DIR *p;
	struct dirent *d;
	struct stat st ={0};
	struct stat stp ={0};
	char *message;
	char* path=(char*)malloc(10*sizeof(char));
	


	printf("\n*******************AVAILABLE COMMANDS*******************\n");
	
	printf("\n'curr' to show current directory\n");
	printf("'goto' to move to a directory\n");
	printf("'list' to list directory content\n");
	printf("'clr' to clear terminal\n");
	printf("'crefile' to create a new file\n");
	printf("'credir' to create a new directory\n");
	printf("'execf' to execute a list of commands from a file\n");
	printf("use '>' to redirect output to a file\n");
	printf("use '|' to redirect output from a command to another\n");
	
	char* cmnd=(char*)malloc(100*sizeof(char)); 
    	cmnd = readline("\n>>> "); 
	
	if(strstr(cmnd,">")==NULL)
	{	
	
		if(strstr(cmnd,"curr"))
		{
			char cwd[256];
			if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
	        			printf("current working directory is: %s\n\n", cwd);
    				}
		}
		else if (strstr(cmnd,"list"))
		{
			DIR *folder;
			char* direct=(char*)malloc(100*sizeof(char));
			char cwd[256];			
			direct = getcwd(cwd, sizeof(cwd));
	    		folder = opendir(direct);
	    		if(folder == NULL)
	    			{
					puts("Unable to read directory\n");
					return(1);
	    			}
		    
		         	struct dirent *dir;
		          	while ((dir = readdir(folder)) != NULL)
		            	{
		                	printf("%s \n", dir->d_name);
		            	}
		}
		
		else if(strstr(cmnd,"clr"))
    			{
        			system("clear");
    			}		
		
		else if (strstr(cmnd,"goto"))
			{
			char* path=(char*)malloc(100*sizeof(char));
			path=strndup(cmnd+strlen("goto")+1,500);	
			changedir(path);
			printf("Changed path successfully!\n");
			}
		
		else if(strstr(cmnd,"crefile")!=NULL)
		{
		filec=strndup(cmnd+strlen("crefile")+1,500);
		fp=fopen(filec,"w");
		fclose(fp);
		}		
		
		else if(strstr(cmnd,"credir")!=NULL && strstr(cmnd,"|")==NULL)
		{
			newdirect=strndup(cmnd+strlen("credir")+1,500);
			if (stat(newdirect, &st) == -1) 
			{
			mkdir(newdirect, 0777);
		    	}
		    	else
			{
			printf("Directory already exists !!!\n");
		    	}
		}		

		else if(strstr(cmnd,"|")!=NULL )
		{
    			if (strstr(cmnd,"credir")!=NULL){
        		newdirect=strndup(cmnd+strlen("credir")+1,1);
                	int i=1;
                	while (strstr(newdirect,"|")==NULL)
                	{
		            	newdirect=strndup(cmnd+strlen("credir")+1,1+i);
		            	i++;
                	}
                newdirect=strndup(cmnd+strlen("credir")+1,i-2);
                if (stat(newdirect, &st) == -1) 
		{
                    mkdir(newdirect, 0777);
                }
                else
		{
                    printf("Directory already exists !!!\n");
                }
                param=strndup(cmnd+strlen("credir")+1+i+1,500);
                if (strstr(param,"go")!=NULL)
                {
                    getcwd(cwd, sizeof(cwd));
                    strcat(cwd,"/");
                    strcat(cwd,newdirect);
                    changedir(cwd);
                }
                else
                {
                    printf("Parameter not valid !!!\n");
                }
                
    }         
    }
			
	else if(strstr(cmnd,"execf")!=NULL)
	{
    	file=strndup(cmnd+strlen("execf")+1,500);
    	fp = fopen(file, "r");
    	struct stat stp = { 0 };
	stat(file, &stp);
	int filesize = stp.st_size;
	message = (char *) malloc(sizeof(char) * filesize);
	if (fread(message, 1, filesize - 1, fp) == -1) 
	{
        printf("error reading file\n");
        fclose(fp);
        free(message);
    	}
	
	strcpy(message, strtok(message , ";"));
	
	if(strstr(message,"goto")!=NULL)
	{
	path=strndup(message+strlen("goto")+1,500);
	changedir(path);
	}
	for (int i = 0; i < 2; i++)
	{
        	strcpy(message, strtok(NULL , ";"));
        	if(strstr(message,"goto")!=NULL)
		{
        	path=strndup(message+strlen("goto")+1,500);
        	changedir(path);
		}

        	else if(strstr(message,"crefile")!=NULL)
		{
		filecr=strndup(message+strlen("crefile")+1,500);
		fp=fopen(filecr,"w");
		fclose(fp);
		}

		else if(strstr(message,"list")!=NULL && strstr(message,">")==NULL)
		{
		direct=strndup(message+strlen("list")+1,500);
		p=opendir(direct);
		if(p==NULL)
		{
		printf("Couldn't find directory !!!");
		}
		else
		{
			while(d=readdir(p))
			printf("%s\n",d->d_name);
			}
		}
		else if(strstr(message,">")!=NULL)
		{
		if (strstr(message,"list")!=NULL)
		{
            	directt=strndup(message+strlen("list")+1,1);
                    int i=1;
                    while (strstr(directt,">")==NULL)
                    {
                        dirname=strndup(message+strlen("list")+1,1+i);
                        i++;
                    }
                    dirname=strndup(message+strlen("list")+1,i-2);
                    filey=strndup(message+strlen("list")+1+i+1,500);
                    fp = fopen(filey, "w");
                    p=opendir(dirname);
                    if(p==NULL)
                    {
                        printf("Cannot find directory !!!\n");
                    }
                    else
		    {
			while(d=readdir(p))
			{
                    	fprintf(fp,"%s\n",d->d_name);
			}                    
		    }
                    fclose(fp);
                    printf("Output redirected to %s \n",filey);
        	}         
	}
    }    
    
}
		
		else
		{
			printf("None of these commands typed !!!\n");
		}
	}
	else if(strstr(cmnd,">")!=NULL)
	{
		if (strstr(cmnd,"list")!=NULL){
		char* dir=(char*)malloc(100*sizeof(char));
        	dir=strndup(cmnd+strlen("list")+1,1);
                int i=1;
                while (strstr(dir,">")==NULL)
                {
                    dir=strndup(cmnd+strlen("list")+1,1+i);
                    i++;
                }
                dir=strndup(cmnd+strlen("list")+1,i-2);
		char* filex=(char*)malloc(100*sizeof(char));
                filex=strndup(cmnd+strlen("list")+1+i+1,500);
		FILE *fp;
                fp = fopen(filex, "w");
		DIR *p;
                p=opendir(dir);
                if(p==NULL)
                {
                    printf("Couldn't open directory !!!\n");
		}
                else
		{
			struct dirent *d;		
			while(d=readdir(p))
		        fprintf(fp,"%s\n",d->d_name);
                }
                fclose(fp);
                printf("output redirected to %s\n",filex);
    		
    	}    	  
	}
}
return 0;
}
