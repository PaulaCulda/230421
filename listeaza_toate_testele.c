#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
    FILE *fisierIncaperi, *fisierNrRetestari, *fisierToateTestele;
    char incapere[100];
    int nr;

	

    fisierNrRetestari = fopen("nr_retestari.txt", "r");
    if (fisierNrRetestari == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", "nr_retestari.txt", errno, strerror(errno));
        return EXIT_FAILURE;
    }

   fscanf(fisierNrRetestari,"%d",&nr);	

  
    fisierIncaperi = fopen("incaperi.txt", "r");
    if (fisierIncaperi == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", "incaperi.txt", errno, strerror(errno));
        return EXIT_FAILURE;
    }
    
    
    //pentru a nu face append peste un fisier folosit in alta sesiune de testare
    if (remove("toate_testele.txt") == 0 )
    	printf("Reinitializare fisier cu SUCCES!");

    	

    fisierToateTestele = fopen("toate_testele.txt", "a");
    if (fisierToateTestele == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", "toate_testele.txt", errno, strerror(errno));
        return EXIT_FAILURE;
    }


    	char test1[100],test2[100],test3[100];

	strcpy(test1,"_test1");
	strcpy(test2,"_test2");
	strcpy(test3,"_test3");

      while ((fgets(incapere, 100, fisierIncaperi)) != NULL)
	{
       // printf("\n\n\n%s INCAPERE \n\n\n\n",incapere);
	char nume_incapere[100];

	strtok(incapere, "\n"); //elimin \n

	strcpy(nume_incapere,"");
	
	if (strcmp(incapere,"\n")!=0)
	
	{
	if(nr == 1)  //daca se face doar o testare/incapere
	{
		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test1);
  		fprintf(fisierToateTestele,"%s\n",nume_incapere);
	}
	
	if(nr == 2)  //daca se fac 2 teste/incapere
	{
		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test1);
		fprintf(fisierToateTestele,"%s\n",nume_incapere);

		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test2);
		fprintf(fisierToateTestele,"%s\n",nume_incapere);
	}

	if(nr == 3) //daca se fac 3 teste/incapere
	{
		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test1);
		fprintf(fisierToateTestele,"%s\n",nume_incapere);


		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test2);
		fprintf(fisierToateTestele,"%s\n",nume_incapere);

		strcpy(nume_incapere,"");
		strcpy(nume_incapere,incapere);
		strcat(nume_incapere,test3);
		fprintf(fisierToateTestele,"%s\n",nume_incapere);
	}

	}
	}


}
