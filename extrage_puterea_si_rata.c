#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>

#define findRate   ".*Bit Rate.*"
#define findSignalLevel    ".*Signal level.*"
#define findWlan0   "wlan0.*"

int main(int argc, char **argv)
{
    FILE *fp;
    FILE *finalFile;
    FILE *nr_deja_reluate,*se_testeaza_acum;
    FILE *rateFile,*powerFile;

    int count = 0;
    char line[1024];
    int retval = 0;
    regex_t re1,re2, re3;
    regmatch_t rm[2];
    const char *filename;
    int noOfIterations = 0;
    float rateValue, powerValue;
    int rateSum = 0;	//suma ratelor
    int powerSum = 0;	//suma puterilor
    float midRate = 0;
    float midPower = 0;

    if (argc > 1)
        filename = argv[1];

    if (regcomp(&re1, findRate, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", findRate);
        return EXIT_FAILURE;
    }

    if (regcomp(&re2, findSignalLevel, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", findSignalLevel);
        return EXIT_FAILURE;
    }

    if (regcomp(&re3, findWlan0, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", findWlan0);
        return EXIT_FAILURE;
    }

    fp = fopen(filename, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", filename, errno, strerror(errno));
        return EXIT_FAILURE;
    }


    nr_deja_reluate = fopen("nr_deja_reluate.txt", "r");
    if (nr_deja_reluate == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", "nr_deja_reluate.txt", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    se_testeaza_acum = fopen("se_testeaza_acum.txt", "r");
    if (se_testeaza_acum == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", "se_testeaza_acum.txt", errno, strerror(errno));
        return EXIT_FAILURE;
    }

    int nr;
    fscanf(nr_deja_reluate,"%d",&nr);	//al catalea test este
   // printf("\n\nDEJA RELUATEEE %d \n\n",nr); 

   char incapere[100];
   fscanf(se_testeaza_acum,"%s",&incapere);	//numele incaperii care se testeaza acum
  // printf("\n\nINCAPEREEE %s \n\n",incapere);

    char nume_fisier_rata[100];
    char string_nr[10];

    strcpy(nume_fisier_rata,incapere);
    strcat(nume_fisier_rata,"_");
    strcat(nume_fisier_rata,"rata_test");
    sprintf(string_nr, "%d", nr);
    strcat(nume_fisier_rata,string_nr);
    strcat(nume_fisier_rata,".txt");
    //in final voi avea denumirea fisierului de forma: numeleincaperii_rata_testX.txt

    ///pentru a nu face append peste un fisier folosit in alta sesiune de testare
    if (remove(nume_fisier_rata) == 0 )
    	printf("Reinitializare fisier cu SUCCES!");
    	
    char nume_fisier_putere[100];
    
    strcpy(nume_fisier_putere,incapere);
    strcat(nume_fisier_putere,"_");
    strcat(nume_fisier_putere,"putere_test");
    strcat(nume_fisier_putere,string_nr);
    strcat(nume_fisier_putere,".txt");
    //in final voi avea denumirea fisierului de forma: numeleincaperii_putere_testX.txt

   ///pentru a nu face append peste un fisier folosit in alta sesiune de testare
    if (remove(nume_fisier_putere) == 0 )
    	printf("Reinitializare fisier cu SUCCES!");

    	
    if ( (rateFile = fopen(nume_fisier_rata, "a") ) == NULL ) //deschid fisierul pentru append 
  	      {
    	      printf("Error: can't open file") ;
    	      exit(1);
 	      }


   if ( (powerFile = fopen(nume_fisier_putere, "a") ) == NULL ) //deschid fisierul pentru append 
  	      {
    	      printf("Error: can't open file") ;
    	      exit(1);
 	      }
 
    size_t len,len2;
    int k,m;
    int i;
    char rateLine[1024],  powerLine[1024];

    while ((fgets(line, 1024, fp)) != NULL)
    {
	char rate[50];
        char power[50];

	strcpy(rate,"");
	strcpy(power,"");

       line[strlen(line)-1] = '\0';
   
       if ((retval = regexec(&re3, line, 2, rm, 0)) == 0)	//numar de cate ori am preluat informatii despre putere si rata
          { noOfIterations++;
            printf("%d",noOfIterations);
	   }

       if ((retval = regexec(&re1, line, 2, rm, 0)) == 0)
	{

		k = 0;

		//printf("%s\n",line);
	        strcpy(rateLine,line); //salvez linia pentru a nu aduce modificari asupra a celei originale

		char *aux = strtok(rateLine,"Mb/s"); //am in aux ceva de genul: Bit Rate=6.5

		len =  strlen(aux); //nr de elemente din aux
	        i = 0;
		while (i != len && aux[i]!= '=') //sar peste ce e pana la "=" 
		{
			i++;
		}   
		
		i++; // ca sa trec de spatiul de dupa "="
		
		//pun in "rate" tot ce e dupa egal, adica rata de transfer
		while(i != len+1)
		{
		 rate[k] = aux[i];
		 k++;
	         i++;
		}   

                //rate = strtok(rate,"=");
		printf("Rata = %s\n", rate);
                int assigned = sscanf(rate, "%f", &rateValue);
		printf("rate value %f",rateValue);

		fprintf(rateFile,"%f\n",rateValue); ///pun in fisier rata partiala

                rateSum += rateValue;
	}
   
       if ((retval = regexec(&re2, line, 2, rm, 0)) == 0)
	{

		m = 0;	
		
		//printf("%s\n",line);
		int twoTimesEqual=0;

		strcpy(powerLine,line);

		char *aux2 = strtok(powerLine,"dBm"); 

		len2 =  strlen(aux2); //nr de elemente din aux 
		
	        i = 0;

		while (i != len2 && twoTimesEqual!=2) //sar peste ce cele doua "="
		{ 	
		 if(aux2[i]=='=')
		    twoTimesEqual++;
		  i++;
		}   

		//i++; // ca sa trec de spatiul de dupa "="
		
		//pun in "power" tot ce e dupa egal, adica puterea semnalului
		while(i != len2+1)
		{
		 
		    power[m] = aux2[i];
		    m++;
	            i++;
		  
		}   

		printf("Puterea = %s\n", power);
		int assigned = sscanf(power, "%f", &powerValue);
	
		fprintf(powerFile,"%f\n",powerValue); ///pun in fisier puterea partiala

		powerSum += powerValue;
	}

    }

    midRate = rateSum / (float)noOfIterations;
    midPower= powerSum / (float)noOfIterations;
    
   
   //iau numarul sesiunii curente din fisierul nr_sesiunii.txt
   
   FILE *nr_sesiunii;
   char * nr_ses;
   int nrSesiune;
   char sesiune[100];
   char command[100];
   
    nr_sesiunii = fopen("nr_sesiunii.txt", "r+");
        if (nr_sesiunii == 0)
        {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", nr_sesiunii, errno, strerror(errno));
        }
       
   while ((fgets(line, 1024, nr_sesiunii)) != NULL)
   	 {
    		nr_ses = strtok(line,"\n"); 
		nrSesiune = atof(nr_ses); //convertesc in double
	}
	
    snprintf(sesiune,sizeof(sesiune),"SESIUNE_NR_%d*",nrSesiune+1);
   
   printf("%s",nume_fisier_putere);
   
    //pun fisierul de putere
    char comanda[50];
    strcpy(comanda,nume_fisier_putere);
    strcat(comanda," ");
    strcat(comanda,sesiune);
    
    snprintf(command,sizeof(command),"sudo cp -r %s",comanda);
    system(command);	
    
    //pun fisierul de rata in folder
    char comanda2[50];
    strcpy(comanda2,nume_fisier_rata);
    strcat(comanda2," ");
    strcat(comanda2,sesiune);
    
    snprintf(command,sizeof(command),"sudo cp -r %s",comanda2);
    system(command);	
    

    finalFile = fopen("rezultate_partiale.txt", "a");
    if (finalFile == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        return EXIT_FAILURE;
    }
 
    fprintf(finalFile,"%f %f ",midRate,midPower); //scriu rata si puterea in fisierul final
    printf("\n MIDRATE = %f MIDPOWER = %f \n",midRate,midPower); //scriu rata si puterea in fisierul final
	
   pclose(fp);

   return EXIT_SUCCESS;
}
