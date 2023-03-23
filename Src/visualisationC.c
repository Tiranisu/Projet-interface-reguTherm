#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "../Inc/visualisationC.h"


void visualisationC(float puissance_f)
{
   if(access(".verrouData", F_OK) != 0){
      
      char temp[8];
      float temp_int = 0, temp_ext = 0; 

      FILE* verrouData = fopen(".verrouData", "w");
      fclose(verrouData);
      if(!verrouData){
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }
      
      FILE* data = fopen("data.txt", "r");

      if(!data){
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      fscanf(data, "%s\n", temp);
      fscanf(data, "%f\n", &temp_int);
      fscanf(data, "%f", &temp_ext);
      fclose(data);

      

      data = fopen("data.txt", "w");

      if(!data){
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      if(puissance_f > 0){
         fputs("true\n", data);
      }else{
         fputs("false\n", data);
      }
      fprintf(data, "%.2f\n%.2f", temp_int, temp_ext);
      fclose(data);
   
      
      remove(".verrouData");
   }
}
