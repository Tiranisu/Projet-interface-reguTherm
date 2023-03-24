#include "../Inc/consigne.h"

float consigne(float thermostatPrec_f){

   float thermostat_f=0;

   if(access(".verrouConsigne", F_OK) != 0){
      
      FILE* consigne = fopen("consigne.txt", "r");
   
      if(!consigne){
         perror("Un problème est survenu pendant l'ouverture du fichier consigne.txt, le fichier n'est pas présent création du fichier....");
         consigne = fopen("consigne.txt", "w");
         fclose(consigne);
         return thermostatPrec_f;
      }

      FILE* verrouConsigne = fopen(".verrouConsigne", "w");

      if(!verrouConsigne){
         perror("Un problème est survenu pendant la creation du fichier .verrouConsigne .");
         return thermostatPrec_f;
      }

      fscanf(consigne, "%f", &thermostat_f);
      fclose(consigne);
      fclose(verrouConsigne);

      remove(".verrouConsigne");
   }else{
      thermostat_f = thermostatPrec_f;
   }

   return thermostat_f;
}
