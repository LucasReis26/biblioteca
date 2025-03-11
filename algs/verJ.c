#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getClass(char *sFile){
	for(int i = 0; i < strlen(sFile); i++){
		if(sFile[i] == '.')
			sFile[i] = '\0';
	}
	return;
}

int main(){
	FILE *file;
	char sFile[255];
	char dir[255];
	char cmd[255];

	fgets(dir, 255, stdin);
	dir[strlen(dir) - 1] = '\0';

	sprintf(cmd,"ls %s | grep '\\.java$'", dir);

	file = popen(cmd,"r");
	if (file == NULL){
		perror("Failed to run command");
		return 1;
	}

	fgets(sFile, 255, file);
	sFile[strlen(sFile) - 1] = '\0';

	sprintf(cmd,"javac %s/%s", dir, sFile);
	system(cmd);

	getClass(sFile);

	sprintf(cmd,"java %s.%s < %s/pubs/pub.in > %s/program.out",dir,sFile,dir,dir);
	system(cmd);
	
	sprintf(cmd,"nvim -d %s/program.out %s/pubs/pub.out",dir,dir);
	system(cmd);

	return 0;
}
