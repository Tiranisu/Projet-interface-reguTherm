#include "usb.h"

FT_STATUS ouvertLien(FT_HANDLE *carte){
    FT_STATUS status;

    status = FT_Open(0, carte);
    if(status != FT_OK){
        perror("Problème lors de l'ouverture de la liaison avec la carte!");
        return status;
    }

    status = FT_SetBaudRate(*carte, 115200);
    if(status != FT_OK){
        perror("Le baudrate ne sait pas correctement initialiser!");
        return status;
    }

    status = FT_SetDataCharacteristics(*carte, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if(status != FT_OK){
        perror("Problème lors du choix des charactéristique de la liaison!");
        return status;
    }

    status = FT_SetFlowControl(*carte, FT_FLOW_NONE, 0, 0);
    if(status != FT_OK){
        perror("Problème lors la précision du flux de l'échange!");
        return status;
    }

    return status;
}

FT_STATUS fermerLien(FT_HANDLE *carte){
    return FT_Close(*carte);
}