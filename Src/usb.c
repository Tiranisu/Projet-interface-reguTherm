#include "../Inc/usb.h"


/**
 * @brief Configuration de la communication de la carte STM32 avec l'ordinateur et retour d'erreur
 * 
 * @param carte Pointeur vers l'USART pour communiquer la carte
 * @return FT_STATUS retour du code d'erreur
 */
FT_STATUS ouvertLien(FT_HANDLE *carte){ 
    FT_STATUS status;

    status = FT_Open(0, carte); // ouverture de la ligne de communication avec la carte
    if(status != FT_OK){ // si erreur avec l'ouverture retourner l'erreur
        perror("Problème lors de l'ouverture de la liaison avec la carte!");
        return status;
    }

    status = FT_SetBaudRate(*carte, 115200); // configuration de la vitesse de communication
    if(status != FT_OK){ // si erreur avec la configuration de la vitesse retourner erreur
        perror("Le baudrate ne sait pas correctement initialiser!");
        return status;
    }

    status = FT_SetDataCharacteristics(*carte, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE); // configuration des caractéristiques de la trame de communication
    if(status != FT_OK){ // si erreur avec cette configuration alors retourner une erreur
        perror("Problème lors du choix des charactéristique de la liaison!");
        return status;
    }

    status = FT_SetFlowControl(*carte, FT_FLOW_NONE, 0, 0); // contrôle du flux d'information
    if(status != FT_OK){ // si erreur alors retourner une erreur
        perror("Problème lors la précision du flux de l'échange!");
        return status;
    }

    return status;
}


/**
 * @brief Fonction qui permet la fermeture de la liaison avec la carte
 * 
 * @param carte  // Pointeur vers l'USART pour communiquer la carte
 * @return FT_STATUS 
 */
FT_STATUS fermerLien(FT_HANDLE *carte){
    return FT_Close(*carte); // fermeture du lien
}