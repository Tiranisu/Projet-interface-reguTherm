#include "../Inc/commande.h"

/**
 * @brief Permet l'envoie des informations de la carte à partir l'ordinateur
 * @param carte Pointeur vers la carte créé avec l'ouverture de la liaison
 * @param puissance Puissance fournit par la régulation
*/
void commande(FT_HANDLE *carte, float puissance){
    FT_STATUS status;

    char data[1];
    DWORD BytesWritten;
    int PUIS = ((float) puissance / 100) * 127;

    data[0] = 0; // on initialise l'octet à envoyer à 0

    // on configure le bitde chauffage
    if(puissance != 0){
        data[0] |= 1<<7;
    }else{
        data[0] &= ~(1<<7);
    }

    // on ajoute la valeur de PUIS calculé à l'aide de la puissance
    data[0] |= (PUIS & 0x7F);

    // on envoie l'octet à la carte
    status = FT_Write(*carte, data, sizeof(data), &BytesWritten);
    if (status == FT_OK) {
        printf("L'ecriture s'est bien passe %d!\n", PUIS);
        printf("Buffer :"); // on vérifie l'octet envoyer
        for(int i = 0; i < BytesWritten; i++){
            printf("%x", data[i]);
        }
        printf("\n");
    }
    else {
        perror("L'ecriture a eu une erreur!\n");
    }
}
 