#include <stdio.h>
#include <stdlib.h>
#include "../Inc/autotests.h"
#include "../Inc/releve.h"
#include "../Inc/commande.h"
#include "../Inc/visualisationT.h"
#include "../Inc/visualisationC.h"
#include "../Inc/regulation.h"
#include "../Inc/simulateur.h"
#include "../Inc/consigne.h"
//#include "../Inc/releve.h"

#define REGUL_TYPE 2 // TOR : 1 | PID : 2


/**
 * @brief Pour la siulation lorsque la carte STM32 est connectée
 * 
 * 
 */
int main(){
    FT_HANDLE* carte = malloc(sizeof(FT_HANDLE));
    FT_STATUS status;
    temp_t* temperature = malloc(sizeof(temp_t));
    status = ouvertLien(carte);
    if(status != FT_OK){
        perror("Probleme pendant la création du lien avec la carte!");
    }
    temperature->exterieure = 10.0;
    temperature->interieure = 15.0;
    struct simParam_s*  monSimulateur_ps = simConstruct(*temperature); // creation du simulateur, puissance intialis�e � 0%
    float consi = 0;
    float consigne_prev = 20;
    float puissance = 70;
    float prev_error = 0;
    float sum_error = 0;
    while(1){
        consi = consigne(consigne_prev);
        switch (REGUL_TYPE) // le choix du type du régulateur ce fait plus haut dans les #define
        {
        case 1:
            puissance = TOR(consi, temperature->interieure); // la régulation du type tout ou rien
            break;
        
        case 2:
            puissance = PID((consi - temperature->interieure), prev_error, &sum_error); // la régulation avec le PID
            break;

        default:
            break;
        }
        printf("Text : %.2f, Tint : %.2f, Puis : %.2f , consigne : %.2f, erreur : %f\n",temperature->exterieure, temperature->interieure, puissance, consi, (consi - temperature->interieure));
        /*(*temperature) = simCalc(puissance,monSimulateur_ps); // simulation de l'environnement*/
        releve(carte, temperature);
        visualisationT(*temperature);
        visualisationC(puissance);
        commande(carte, puissance);
        consigne_prev = consi;
        prev_error = (consi - temperature->interieure);
        msleep(40);
    }
    simDestruct(monSimulateur_ps); // destruction de simulateur
    return 0;
}
