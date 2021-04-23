#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>


int main(int argc, char **argv)
{
    FILE *fp;
    FILE *finalFile;
    char line[1024], newLine[1024];
    const char *filename;
    int len = 0;
    double nr;
    char incaperi[1000][100];	//in acest vector voi avea toate incaperile
    char indici[1000][100];		//in acest vector voi avea toti indicii
    int i = 0;
    int j = 0;
    double max = 0.0, max_minus_1 = 0.0, max_minus_2 = 0.0;
    int pos = 0, pos_minus_1 = 0, pos_minus_2 = 0;
    int ok = 0;
    char *aux;
    

    if (argc > 1)
        filename = argv[1];
        
    fp = fopen(filename, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", filename, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    
    finalFile = fopen("top3.txt", "w");
    if (finalFile == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    
    //iau fiecare linie
    while ((fgets(line, 1024, fp)) != NULL)
    {
    	char *incapere = strtok(line," "); //iar numele incaperii
	
	strcpy(incaperi[i],incapere);	
	i++;

	len = strlen(incapere);
    	strcpy(indici[j],line + len + 1); 

	strcpy(indici[j],strtok(indici[j],"\n"));	//scap de \n

	nr = atof(indici[j]); //convertesc indicele in double

	
	if (ok == 0)
	{
		max = nr; 	
		pos = i;
		ok++;
	}
	
	else

	if (ok == 1)
	{
		if (nr > max)
		{
		   max_minus_1 = max;
		   pos_minus_1 = pos;
		   max = nr;
		   pos = i;
		   ok++;
		}
		else
		if(nr < max)
		{
		   max_minus_1 = nr;
		   pos_minus_1 = i;
		   ok++;			
		}
		
	}

	else

	if (ok == 2)
	{
		if (nr > max)
		{
		   max_minus_2 = max_minus_1;
		   pos_minus_2 = pos_minus_1;
		   max_minus_1 = max;
		   pos_minus_1 = pos;
		   max = nr;
		   pos = i;
		   ok++;
		}
		else
		if(nr > max_minus_1)
		{
		   max_minus_2 = max_minus_1;
		   pos_minus_2 = pos_minus_1;
		   max_minus_1 = nr;
		   pos_minus_1 = i;
		   ok++;			
		}
		else
		if(nr < max_minus_1)
		{
		   max_minus_2 = nr;
		   pos_minus_2 = i;
		   ok++;			
		}

	}

	else

	if (nr > max)	
	   {
		
		max_minus_2 = max_minus_1;
		pos_minus_2 = pos_minus_1;

		max_minus_1 = max;
		pos_minus_1 = pos;

		max = nr; //gasesc indicele maxim	
		pos = i; //retin si pozitia la care s-a gasit, pentru a putea lua si numele incaperii de la aceeasi pozitie din vectorul de incaperi
		
	   }
    	j++;	
    }

    fprintf(finalFile,"TOP 3: \n");
    fprintf(finalFile,"%s - %s\n", incaperi[pos-1],indici[pos-1]);
    fprintf(finalFile,"%s - %s\n", incaperi[pos_minus_1-1],indici[pos_minus_1-1]);
    fprintf(finalFile,"%s - %s\n", incaperi[pos_minus_2-1],indici[pos_minus_2-1]);
	


    fclose(fp);
    fclose(finalFile);
    return 0;
} 

