#include "../Inc/consigne.h"

float consigne(float thermostatPrec_f){

   float thermostat_f=0;

   if(access(".verrouConsigne", F_OK) != 0){
      
      FILE* consigne = fopen("consigne.txt", "r");
   
      if(!consigne){
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      FILE* verrouConsigne = fopen(".verrouConsigne", "w");

      if(!verrouConsigne){
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      fscanf(consigne, "%f", &thermostat_f);
      fclose(consigne);

      remove(".verrouConsigne");
   }else{
      thermostat_f = thermostatPrec_f;
   }

   return thermostat_f;
}
