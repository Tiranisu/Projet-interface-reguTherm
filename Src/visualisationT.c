#include "../Inc/visualisationT.h"

void visualisationT(temp_t myTemp)
{
    if(access(".verrouData", F_OK) != 0){

        char temoinChauffe[8];

        FILE* data = fopen("data.txt", "r");

        if(!data){
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }

        fscanf(data, "%s\n", temoinChauffe);
        fclose(data);

        FILE* verrouData = fopen(".verrouData", "w");
        fclose(verrouData);
        if(!verrouData){
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }

        data = fopen("data.txt", "w");

        if(!data){
            perror("Un problème est survenu pendant la création/ouverture du fichier.");
            return;
        }

        fprintf(data, "%s\n%.2f\n%.2f", temoinChauffe, myTemp.interieure, myTemp.exterieure);
        fclose(data);
        

        remove(".verrouData");
    }
}
