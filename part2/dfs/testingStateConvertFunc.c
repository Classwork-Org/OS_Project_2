#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* convertStateToString(long state){
	
	int i = 0;
	long temp = 0;
	char* result;

	if(state == 0){
		return "running";
	}
	else{
		result = (char*)malloc(sizeof(char)*250);
	}

	strcpy(result, "");
	for(i = 0; i<=10; i++){
		temp = state & (1<<i);
		switch(temp){
			case 1:
				strcat(result,  "interruptable ");
				break;
			case 2:
				strcat(result,  "uninterruptable ");
				break;
			case 4:
				strcat(result,  "stopped ");
				break;
			case 8:
				strcat(result,  "traced ");
				break;
			case 16:
				strcat(result,  "exit dead ");
				break;
			case 32:
				strcat(result,  "exit zombie ");
				break;
			case 64:
				strcat(result,  "dead ");
				break;
			case 128:
				strcat(result,  "wakekill ");
				break;
			case 256:
				strcat(result,  "waking ");
				break;
			case 512:
				strcat(result,  "parked ");
				break;
			case 1024:
				strcat(result,  "state_max ");
				break;
			default:
				strcat(result,  "");
				break;
		}
	}
	return result;
}

int main(){
	char* result = convertStateToString(0);
	printf("%s\n", result);
	return 0;
}