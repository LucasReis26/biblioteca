#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char dir[255];
	char sFile[255];
	char cmd[255];
	FILE *file;

	fgets(dir, 255, stdin);
	dir[strlen(dir) - 1] = '\0';

	sprintf(cmd,"ls %s | grep '\\.c$'", dir);
	file = popen(cmd,"r");
	if(file == NULL){
		perror("Failed to run program");
		return 1;
	}

	fgets(sFile, 255, file);
	sFile[strlen(sFile) - 1] = '\0';
	printf("%s nome do arquivo\n",sFile);

	sprintf(cmd,"gcc %s/%s -o %s/exec",dir,sFile,dir);
	system(cmd);

	sprintf(cmd,"./%s/exec < %s/pubs/pub.in > %s/program.out",dir,dir,dir);
	system(cmd);

	sprintf(cmd,"nvim -d %s/program.out %s/pubs/pub.out",dir,dir);
	system(cmd);

	return 0;
}
