#include "../Inc/consigne.h"


/**
 * @brief recupère la consigne envoyé par la fichier consigne.txt
 * 
 * @param thermostatPrec_f consigne précedente au cas ou le lecture est impossible
 * @return float 
 */
float consigne(float thermostatPrec_f){

   float thermostat_f=0;

   if(access(".verrouConsigne", F_OK) != 0){ // si le fichier .verrouData n'existe pas alors rentrer dans le if
      
      FILE* consigne = fopen("consigne.txt", "r"); // lecture des données dans consigne.txt
   
      if(!consigne){ // s'il n'arrive pas à lire le fichier consigne, alors retourner une erreur
         perror("Un problème est survenu pendant l'ouverture du fichier consigne.txt, le fichier n'est pas présent création du fichier....");
         consigne = fopen("consigne.txt", "w");
         fclose(consigne);
         return thermostatPrec_f;
      }

      FILE* verrouConsigne = fopen(".verrouConsigne", "w"); // création du fichier .verrouConsigne

      if(!verrouConsigne){ // s'il n'arrive pas à lire le fichier consigne, alors retourner une erreur
         perror("Un problème est survenu pendant la creation du fichier .verrouConsigne .");
         return thermostatPrec_f;
      }

      fscanf(consigne, "%f", &thermostat_f); // récupération de la consigne ecrite dans le fichier
      fclose(consigne); // fermeture du fichier consigne.txt
      fclose(verrouConsigne); // fermeture du fichier .verrouConsigne

      remove(".verrouConsigne"); // supprime le verrou pour rendre l'accès à consigne.txt accessible
   }else{
      thermostat_f = thermostatPrec_f; // si fichier pas accessible alors prendre la valeur de consigne précedente
   }

   return thermostat_f; // retourne la valeur de consigne
}
