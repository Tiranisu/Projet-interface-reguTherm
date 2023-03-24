#include "../Inc/releve.h"

/**
 * @brief Permet la réception des informations de la carte sur l'ordinateur
 * @param carte Pointeur vers la carte créé avec l'ouverture de la liaison
 * @param temp Pointeur vers la structure des températures de l'habitat
*/
void releve(FT_HANDLE *carte, temp_t *temp){
    FT_STATUS status;
    
    char result[6];
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived;
    int SOT_ext = 0;
    int SOT_int = 0;

    //On vérifie si l'on a des octets qui ont été transférés et qui sont en attente.
    FT_GetStatus(*carte,&RxBytes,&TxBytes,&EventDWord);
    if(RxBytes > 0) {

        //On lit les données qui sont en attentes et on vérifie que tout c'est correctement passé
        status = FT_Read(*carte, result, RxBytes, &BytesReceived);
        if(status != FT_OK){
            perror("Probleme lors de la lecture de donnees 1!");
            return;
        }
        
        int ByteRead = 0; //Cela va nous permettre de vérifier que tous les octets ont bien été lu

        printf("Buffer :"); // on affiche le buffer afin de vérifier la vérification
        for(int i = 0; i < BytesReceived; i++){
            printf("%x", result[i]);
        }
        printf("\n");

        // on lit les octets reçu pour mettre les valeurs des SOT
        for(int i = 0; i < BytesReceived; i++){
            if((result[i] & 0xF0)>>4 == 0b0000){
                SOT_ext |= (result[i] & 0xF);                                                                                                                               
                ByteRead++;
            }
            if((result[i] & 0xF0)>>4 == 0b0001){
                SOT_ext |= (result[i] & 0xF)<<4;
                ByteRead++;
            }
            if((result[i] & 0xF0)>>4 == 0b0100){
                SOT_ext |= (result[i] & 0xF)<<8;
                ByteRead++;
            }
            if((result[i] & 0xF0)>>4 == 0b1000){
                SOT_int |= (result[i] & 0xF);
                ByteRead++;
            }
            if((result[i] & 0xF0)>>4 == 0b1001){
                SOT_int |= (result[i] & 0xF)<<4;
                ByteRead++;
            }
            if((result[i] & 0xF0)>>4 == 0b1100){
                SOT_int |= (result[i] & 0xF)<<8;
                ByteRead++;
            }
        }

        // on vérifie que l'on a bien des valeurs dans les SOT et qu'on a bien lu le bon nombre d'octet
        if(SOT_int != 0 && SOT_ext != 0 && ByteRead == 6){
            float temp_ext_absolu = -39.64 + 0.04 * (SOT_ext);
            float temp_int_absolu = -39.64 + 0.04 * (SOT_int);

            printf("temp-ext : %f*C || temp-int : %f*C\n", temp_ext_absolu, temp_int_absolu);
            temp->interieure = temp_int_absolu;
            temp->exterieure = temp_ext_absolu;
        }else{
            perror("Erreur de transmission : paquet manquant !");
        }
    }
    
}
