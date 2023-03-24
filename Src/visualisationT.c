#include "../Inc/visualisationT.h"

/**
 * @brief Envoie les températures (Tint et Text) dans le fichier data.txt en le sécurisant
 * grace à .verrouData pour ne pas avoir de conflit entre le python et le C 
 * @param myTemp Prend en entrer un structure de température (température interne et externe)
 */
void visualisationT(temp_t myTemp)
{
    if(access(".verrouData", F_OK) != 0){ // si le fichier .verrouData n'existe pas alors rentrer dans le if
        char temoinChauffe[8];

        FILE* verrouData = fopen(".verrouData", "w"); // création du fichier .verrouData
        if(!verrouData){ // s'il n'arrive pas à créer le verrou, alors retourner une erreur
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }
        fclose(verrouData); // fermer le fichier .verrouData

        FILE* data = fopen("data.txt", "r"); // lecture des données dans data.txt
        if(!data){ // s'il n'arrive pas à créer data.txt, alors retourner une erreur
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }

        fscanf(data, "%s\n", temoinChauffe); // récuperer l'état du témoin de chauffe dans le fichier data.txt
        fclose(data); // fermer le fichier data.txt

        data = fopen("data.txt", "w"); // Recrée le fichier data.txt
        if(!data){ // s'il n'arrive pas à créer data.txt, alors retourner une erreur
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }

        fprintf(data, "%s\n%.2f\n%.2f", temoinChauffe, myTemp.interieure, myTemp.exterieure); // Insertion des données dans le data.txt
        fclose(data); // fermer le fichier data.txt
        

        remove(".verrouData"); // supprime le verrou pour rendre l'accès à data.txt accessible 
    }
}
