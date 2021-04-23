#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>

#define tofind    "[0-9]*#[0-9]*"

int main(int argc, char **argv)
{
    FILE *fp, *finalFile,*nr_deja_reluate,*se_testeaza_acum,*duplicate;
    FILE *frate, *fpower;
    int count = 0;
    char line[1024];
    int retval = 0;
    regex_t re;
    regmatch_t rm[2];
    const char *filename;
    float rate=0, partial_rate=0;

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

    char nume_fisier_duplicate[100];
    char string_nr[10];

    strcpy(nume_fisier_duplicate,incapere);
    strcat(nume_fisier_duplicate,"_");
    strcat(nume_fisier_duplicate,"dup_test");
    sprintf(string_nr, "%d", nr);
    strcat(nume_fisier_duplicate,string_nr);
    strcat(nume_fisier_duplicate,".txt");
    //in final voi avea denumirea fisierului de forma: numeleincaperii_dup_testX.txt


    ///pentru a nu face append peste un fisier folosit in alta sesiune de testare
    if (remove(nume_fisier_duplicate) == 0 )
    	printf("Reinitializare fisier cu SUCCES!");


   // nr_deja_reluate = fopen("nr_deja_reluate.txt", "r");
 //   if (nr_deja_reluate == 0)
 //   {
   //     fprintf(stderr, "Failed to open file %s (%d: %s)\n", "nr_deja_reluate.txt", errno, strerror(errno));
  //      return EXIT_FAILURE;
  //  }

  //  nr_deja_reluate = fopen("nr_deja_reluate.txt", "r");
  //  if (nr_deja_reluate == 0)
   // {
  //      fprintf(stderr, "Failed to open file %s (%d: %s)\n", "nr_deja_reluate.txt", errno, strerror(errno));
  //     return EXIT_FAILURE;
 //   }


    char myline[1024];
    int sequence[1000000]={0}; //vectorul de frecventa in care pun de cate ori apare fiecare sevcenta ca fiind duplicata
    int k=0;
    int value;
    int  noOfDifferentDUP = 0;
    int noOfTotalDUP = 0;
    int noOfTotalPackets = 0;


    while ((fgets(line, 1024, fp)) != NULL)
    {
       noOfTotalPackets++; //nr total de pachete=nr total de linii

       line[strlen(line)-1] = '\0';
       if ((retval = regexec(&re, line, 2, rm, 0)) == 0){
	   strcpy(myline,line);	//retin in variabila myline linia care ma intereseaza (cea cu DUP)
	   noOfTotalDUP++; //numar totalul de duplicate, chiar si pe cele care se repeta

         //sparg linia in cuvinte pentru a delimita ce ma intereseaza	
	//sparg initial dupa simbolul # si raman, initial, cu ce e inainte de #, deci ultimul "cuvant" va fi chiar secventa cautata
	 char *dup= strtok(myline,"#");
	// printf("%s \n\n",dup);
         
	//apoi tot sparg dupa spatii pana cand raman doar cu secventa
	dup = strtok(dup," ");
	char myseq[1024];

  	 while(dup!=NULL)
               {
		//printf("%s \n",dup);
		strcpy(myseq,dup);
 		dup=strtok(NULL," ");
	       }

	//printf("My sequence is %s\n",myseq);
              

	//convertesc nr de secventa ce ma intereseaza(myseq) in integer pentru a-l putea compara cu ce am in vectorul de frecventa care e int
	
	int assigned = sscanf(myseq, "%d", &value);
	//printf("%d \n",value);

	//construiesc vectorul de frecventa
	if(sequence[value]!=0)
		{
		 sequence[value]++;	//daca am deja ceva pus in vector la pozitia respectiva, incrementez
		}
	else   {
		sequence[value]=1; //daca nu am deja in vector la pozitia respectiva nimic, incep de la 1
		}
        }

    }


     if ( (duplicate = fopen(nume_fisier_duplicate, "a") ) == NULL ) //deschid fisierul pentru append 
  	      {
    	      printf("Error: can't open file") ;
    	      exit(1);
 	      }



   //in final, merg pana la value, value fiind ultimul nr de secventa, deci cel maxim, caci ele apar in ordine crescatoare
   int aux;

   for( aux=0;aux<=value;aux++)
         {
	   if(sequence[aux]>0){	//daca am ceva la pozitia respectiva, afisez

	      if (noOfTotalPackets != 0 ) //ma asigur ca nu impart la 0	
		{
   	          partial_rate = ( noOfDifferentDUP * 100 ) / (float)noOfTotalPackets;
		  fprintf(duplicate,"%f\n",partial_rate);
		} //trec in fisier ratele partiale 
	      printf("DUP no %d appears %d times. \n", aux, sequence[aux]);
	      noOfDifferentDUP++;
	     }
	 }

   //dupa ce am scris in fisierul de duplicate, il mut in folderul cu sesiunea corespunzatoare
   
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
   
   printf("%s",nume_fisier_duplicate);
   
    char comanda[50];
    strcpy(comanda,nume_fisier_duplicate);
    strcat(comanda," ");
    strcat(comanda,sesiune);
    
    snprintf(command,sizeof(command),"sudo cp -r %s",comanda);
    system(command);
   
    //for( aux=0;aux<=value;aux++)
    //     {

	//   if(sequence[aux]>3){	//daca un duplicat apare de mai mult de 3 ori, abia atunci e o problema
	    //  printf("DUP no %d appears %d times. \n", aux, sequence[aux]);
	 //     noOfDifferentDUP++;
	    // }
	// }

     if (noOfTotalPackets != 0 ) //ma asigur ca nu impart la 0	
   	  rate = ( noOfDifferentDUP * 100 ) / (float)noOfTotalPackets;
     //altfel, rata va ramane 0, fiind si cazul ideal

   printf("\nNo of total packets = %d.\n", noOfTotalPackets);
   printf("No of total DUPs = %d.\n", noOfTotalDUP);
   printf("No of different DUPs = %d.\n", noOfDifferentDUP);
   printf("DUP rate = %f.\n", rate);

 
    	

	  if ( (finalFile = fopen("rezultate_partiale.txt", "a") ) == NULL ) //deschid fisierul pentru append 
  	      {
    	      printf("Error: can't open file") ;
    	      exit(1);
 	      }
	fprintf(finalFile,"%f\n",rate);
   
  // printf ("Found %d retransmissions.", count);
   return EXIT_SUCCESS;
}
