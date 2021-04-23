#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>

#define tofind    "[a-zA-Z]"

struct Test{

	char incapere[50];
        float dup;	//media dup pe incapere
	float power;	//media power pe incapere
	float rate;	//media rate pe incapere

};

int main(int argc, char **argv)
{
    FILE *fp;
    FILE *finalFile;
    int count = 0;
    char line[1024];
    int retval = 0;
    regex_t re;
    regmatch_t rm[2];
    const char *filename;
    char lineWithResults[500];
    float powerSum = 0, value2;
    float rateSum = 0, value1;
    float dupSum = 0, value3;
 

    struct Test teste[100]; 

    if (argc > 1)
        filename = argv[1];

    if (regcomp(&re, tofind, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", tofind);
        return EXIT_FAILURE;
    }

    fp = fopen(filename, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", filename, errno, strerror(errno));
        return EXIT_FAILURE;
    }

   
    int i = 0;
    int noOfTestsPerRoom;
    int len,len2,len3;
    char saveLine[1024];
    
    while ((fgets(line, 1024, fp)) != NULL)
    {
       line[strlen(line)-1] = '\0';
       len = 0;
       len2 = 0;
       len3 = 0;
       strcpy(saveLine,line);

           if ((retval = regexec(&re, line, 2, rm, 0)) == 0)
		{

		 strcpy(lineWithResults,"");

		  if (i >= 1)
			{ 
			    if (noOfTestsPerRoom != 0 )
   				{
   					teste[i-1].rate = rateSum / (float)noOfTestsPerRoom;
   					teste[i-1].power = powerSum / (float)noOfTestsPerRoom;
   					teste[i-1].dup = dupSum / (float)noOfTestsPerRoom;
 				 }
  
 			 else //daca s-a facut doar un test, atunci noOfTestsPerRoom = 0
 				 {
  					teste[i-1].rate = rateSum;
   					teste[i-1].power = powerSum;
   					teste[i-1].dup = dupSum;
 				 }
			  //printf("%s %f %f %f \n",teste[i-1].incapere, teste[i-1].rate, teste[i-1].power, teste[i-1].dup);
			}

		  strcpy(teste[i].incapere,line);
		  i++;

		  noOfTestsPerRoom = 0; //reinitializez nr de teste pentru incapere

	          //reinitializez si sumele pentru fiecare incapere
		  rateSum = 0;
		  powerSum = 0;
		  dupSum = 0;
		}
	   else
		{
	        //pun intr-un vector auxiliar toata linia cu numere (rata,putere,duplicate)
		noOfTestsPerRoom++; //numar cate retestari s-au facut pentru incaperea respectiva

		strcpy(lineWithResults,line);

	
		char *aux = strtok(lineWithResults," "); //initial voi avea in aux rata (e prima pe linie) 
		
		float assigned1 = sscanf(aux, "%f", &value1); //o convertesc in int pentru a  putea aduna
		rateSum += value1; printf("RATA = %f \n",value1);
	
		len = strlen(aux);
		strcpy(aux, saveLine + len + 1);
		
		float assigned2 = sscanf(aux, "%f", &value2); //dupa rata gasesc puterea si o convertesc in int
		powerSum += value2;printf("PUTEREA = %f \n",value2);

		len2 = strlen(aux);
		strcpy(aux, saveLine + len2 + 1);
		
		 float assigned3 = sscanf(aux, "%f", &value3); //in final gasesc rata de duplicate si o convertesc in int
	         dupSum += value3; printf("DUP =%f \n",value3);

	      //  len3 = strlen(aux);
		//strcpy(aux, saveLine + len2 + 1);
		
	
		//printf("%f \n %f \n %f \n",rateSum,powerSum,dupSum);

		}
    }

   //calculele pentru ultima linie
   if (noOfTestsPerRoom != 0 )
   {
   teste[i-1].rate = rateSum / (float)noOfTestsPerRoom;
   teste[i-1].power = powerSum / (float)noOfTestsPerRoom;
   teste[i-1].dup = dupSum / (float)noOfTestsPerRoom;
  }
  
  else //daca s-a facut doar un test, atunci noOfTestsPerRoom = 0
  {
   teste[i-1].rate = rateSum;
   teste[i-1].power = powerSum;
   teste[i-1].dup = dupSum;
  }



    finalFile = fopen("rezultate_finale.txt", "w");
    if (finalFile == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        return EXIT_FAILURE;
    }
 
   for (int j=0; j<i; j++)
     fprintf(finalFile,"%s %f %f %f \n",teste[j].incapere, teste[j].rate, teste[j].power, teste[j].dup);


   return EXIT_SUCCESS;
}
