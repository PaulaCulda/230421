#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <regex.h>


int main(int argc, char **argv)
{
    FILE *fp;
    FILE *finalFile, *plotFile;
    char line[1024], newLine[1024];
    const char *filename;
    int len = 0;
    double nr = 0.0;
    

    if (argc > 1)
        filename = argv[1];
        
    fp = fopen(filename, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", filename, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    
 
    	
    finalFile = fopen("rez_partiale.txt", "w");
    if (finalFile == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", finalFile, errno, strerror(errno));
        return EXIT_FAILURE;
    }

        ///pentru a nu face append peste un fisier folosit in alta sesiune de testare
    if (remove("plot_file.txt") == 0 )
    	printf("Reinitializare fisier cu SUCCES!");

    	
    	
    plotFile = fopen("plot_file.txt", "w");
    if (plotFile == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", plotFile, errno, strerror(errno));
        return EXIT_FAILURE;
    }
    
    //iau fiecare linie
    while ((fgets(line, 1024, fp)) != NULL)
    {
    	//iau primul cuvant de pe linie si il scriu in fisierul de iesire
    	char *aux = strtok(line," ");
    	fprintf(finalFile,"%s ", aux);
    	
    	//iau lungimea primului cuvant si sar peste ea, ca sa ma mut la cel de-al doilea
    	len = strlen(aux);
    	strcpy(newLine,line + len + 1); 
    	
    	//iau al doilea cuvant
    	char *aux1 = strtok(newLine," ");
    	nr = atof(aux1);
    	//printf("%f\n", nr);
    	
    	//iau lungimea celui de-al doilea cuvant si sar peste ea, ca sa ma mut la cel de-al treilea
    	len = strlen(aux1);
    	strcpy(line,newLine + len + 1); 
    	
    	//iau al treilea cuvant si fac suma cu primul
    	aux1 = strtok(line," ");
    	nr += atof(aux1);
    	//printf("%f\n", nr);
    	
    	//iau lungimea celui de-al treilea cuvant si sar peste ea, ca sa ma mut la cel de-al patrulea
    	len = strlen(aux1);
    	strcpy(newLine,line + len + 1); 
    	
    	//iau al patrulea cuvant si fac diferenta cu suma primelor doua
    	aux1 = strtok(newLine," ");
    	nr -= atof(aux1);
    	fprintf(finalFile,"%f\n", nr);
	
	fprintf(plotFile,"%f\n", nr);
    	
    }

    fclose(fp);
    fclose(finalFile);
    fclose(plotFile);
    return 0;
} 

