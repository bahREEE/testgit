#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {

	int choix;

while(1)
{

	printf("\nTapez 1 pour executer l'interpreteur de commandes \n");
	printf("\nTapez 2 pour executer le simulateur d'ordonnancement \n");

	scanf("%d",&choix);
	
	if (choix==1)
		{
			system("/home/bahreee/Desktop/v3");
		}	
	else if (choix==2)
		{
			char *path= (char *)malloc(100*sizeof(char));
			path="/home/bahreee/Desktop/procs";
			chdir(path);
			system("java Main");
		}
		else {printf ("Verifiez votre choix !!!\n");}
}

}
