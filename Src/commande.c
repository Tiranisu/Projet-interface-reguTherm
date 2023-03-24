#include "../Inc/commande.h"

void commande(FT_HANDLE *carte, float puissance){
    FT_STATUS status;

    char data[1];
    DWORD BytesWritten;
    int PUIS = ((float) puissance / 100) * 127;

    data[0] = 0;

    if(puissance != 0){
        data[0] |= 1<<7;
    }else{
        data[0] &= ~(1<<7);
    }

    data[0] |= (PUIS & 0x7F);

    status = FT_Write(*carte, data, sizeof(data), &BytesWritten);
    if (status == FT_OK) {
        printf("L'ecriture s'est bien passe %d!\n", PUIS);
        printf("Buffer :");
        for(int i = 0; i < BytesWritten; i++){
            printf("%x", data[i]);
        }
        printf("\n");
    }
    else {
        perror("L'ecriture a eu une erreur!\n");
    }
}
 