#include "person.h"
#include <stdio.h>
#include <stdlib.h>


struct person People[5];

int my_getnumber(char *str){
  int result;
  int puiss;
  result = 0;
  puiss = 1;
  while (('-' == (*str)) || ((*str) == '+')){
      if (*str == '-')
        puiss = puiss * -1;
      str++;
  }
  while ((*str >= '0') && (*str <= '9')){
      result = (result * 10) + ((*str) - '0');
      str++;
  }
  return (result * puiss);
}


const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
		
    }
    
    return NULL;
}

int myRead()
{
    FILE* stream = fopen("People.csv", "r");

    char line[1024];
    
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        char* tmp2 = strdup(line);
        char* tmp3 = strdup(line);
        const char* tmp3new = getfield(tmp3, 1);
        int idnum = my_getnumber(tmp3new);
        People[idnum].id = idnum;
        
		strcpy(People[idnum].name,getfield(tmp, 2));
		strcpy(People[idnum].surname,getfield(tmp2, 3));
        free(tmp);
        free(tmp2);
        free(tmp3);

    }
	return 0;
}

int main() {
	printf("\n Welcome to ozudb! \n");
	while(1){
		printf("\n Main menu: \n");
		char command;
		scanf(" %c", &command);

		if(command == 'C'){
			printf("\nCreating Table: \n");
			for(int i=0 ; i<5; i = i + 1 ){
				People[i].id = 0;
				strcpy( People[i].name , "" );
				strcpy( People[i].surname , "" );
			}
			printf("\nDone! \n");
		}
		
		else if (command == 'A'){
			int tmp1;
			printf("\nEnter Id: \n");
			scanf("%d",&tmp1);
			if (People[tmp1].id != 0)
				printf("\nCare OVERWRITING!! \n");				
			People[tmp1].id = tmp1;
			printf("\nEnter Name: \n");
			char temp[10] ;
		    scanf("%s",&temp);
			strcpy(People[tmp1].name,temp);
			printf("\nEnter Surname: \n");
			scanf("%s",&temp);
			strcpy(People[tmp1].surname,temp);
			
		//	for(int i=0 ; i<5; i= i+1){
		//		if(strcmp(People[i].name , "") == 0){
		//			printf("\nEnter Name: \n");
		//			char temp[10] ;
		//		    scanf("%s",&temp);
		//			strcpy(People[i].name,temp);
		//			printf("\nEnter Surname: \n");
		//			scanf("%s",&temp);
		//			strcpy(People[i].surname,temp);
		//			break;
		//		}
		//	}
		}
		
		else if (command == 'D'){
			printf("\nId to be deleted: \n");
			int temp;
			scanf("%d", &temp);
			//temp = temp - 1;
			if(temp < 0 || temp > 4){
				printf("\n Not valid id. Enter between 0 and 4. Getting back to menu.\n");
				break;
			}
			//for( ; temp<4; temp= temp+1){
				//strcpy(People[temp].name , People[temp+1].name);
				//strcpy(People[temp].surname , People[temp+1].surname);
			//}
			strcpy(People[temp].name , "");
			strcpy(People[temp].surname , "");
			People[temp].id = 0;
			printf("\n Done! \n");
		}
		
		else if (command == 'P'){
			
			if (strcmp(People[0].name , "empty") == 0)
				printf("\n Table is empty \n");
			    
			for(int i=0 ; i<5; i= i+1){
				char name[20],surname[20];
				strcpy(name,People[i].name);
			    strcpy(surname,People[i].surname);
			    //if (strcmp(name , "empty") == 0)
					//break;
				printf("\n %d  %s  %s \n", People[i].id , name , surname);
			}
		}	
		
		else if (command == 'R'){
			printf("\n Reading data from People.csv file \n");
			myRead();
		}
		
		else if (command == 'E'){
			printf("\n Exiting.. \n");
			return 0;
		}
	}

}



	

