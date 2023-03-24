#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "../Inc/visualisationC.h"


/**
 * @brief Envoie l'état si le chauffage est en route dans le fichier data.txt en le sécurisant
 * grace à .verrouData pour ne pas avoir de conflit entre le python et le C 
 * 
 * @param puissance_f La commande de puissance
 */
void visualisationC(float puissance_f)
{
   if(access(".verrouData", F_OK) != 0){ // si le fichier .verrouData n'existe pas alors rentrer dans le if
      char temp[8];
      float temp_int = 0, temp_ext = 0; 

      FILE* verrouData = fopen(".verrouData", "w"); // création du fichier .verrouData
      if(!verrouData){ // s'il n'arrive pas à créer le verrou, alors retourner une erreur
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }
      fclose(verrouData); // fermer le fichier .verrouData
      

      FILE* data = fopen("data.txt", "r"); // lecture des données dans data.txt
      if(!data){ // s'il n'arrive pas à lire le fichier data, alors retourner une erreur
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      fscanf(data, "%s\n", temp); // recupération de l'état de chauffe dans le fichier data.txt
      fscanf(data, "%f\n", &temp_int); // récuparation de la température intérieur dans le fichier data.txt
      fscanf(data, "%f", &temp_ext); // récupération de la température extérieur dans le fichier data.txt
      fclose(data); // fermeture du fichier data.txt

      
      data = fopen("data.txt", "w"); // Recrée le fichier data.txt 
      if(!data){ // s'il n'arrive pas à créer data.txt, alors retourner une erreur
         perror("Un problème est survenu pendant la création/ouverture du fichier.");
         return;
      }

      if(puissance_f > 0){ // si la puissance est supérieur à 0 alors l'indicateur de chauffe est à true
         fputs("true\n", data);
      }else{ // sinon à false
         fputs("false\n", data);
      }
      fprintf(data, "%.2f\n%.2f", temp_int, temp_ext); // écrir dans data.txt 
      fclose(data); // fermer le fichier data.txt
   
      
      remove(".verrouData"); // supprime le verrou pour rendre l'accès à data.txt accessible 
   }
}
