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
 * @brief 
 * 
 * 
 */
int main(){
    FT_HANDLE* carte = malloc(sizeof(FT_HANDLE));
    //temp_t* temp = malloc(sizeof(temp_t));
    FT_STATUS status;
    status = ouvertLien(carte);
    /*if(status != FT_OK){
        perror("Probleme pendant la création du lien avec la carte!");
    }else{
        while(1){
            //releve(carte, temp);
            commande(carte, 60);
        }
    }*/

    
    /**
     * @brief 
     * 
     */
    temp_t temperature;
    temperature.exterieure = 10.0;
    temperature.interieure = 15.0;
    struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialis�e � 0%
    float consi = 0;
    float consigne_prev = 20;
    float puissance = 70;
    float prev_error = 0;
    float sum_error = 0;
    while(1){
        consi = consigne(consigne_prev);
        switch (REGUL_TYPE)
        {
        case 1:
            puissance = TOR(consi, temperature.interieure);
            break;
        
        case 2:
            puissance = PID(consi, (consi - temperature.interieure), prev_error, &sum_error);
        break;
        default:
            break;
        }
        printf("Text : %.2f, Tint : %.2f, Puis : %.2f , consigne : %.2f, erreur : %f\n",temperature.exterieure, temperature.interieure, puissance, consi, (consi - temperature.interieure));
        temperature = simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
        visualisationT(temperature);
        visualisationC(puissance);
        consigne_prev = consi;
        prev_error = (consi - temperature.interieure);
    }
    simDestruct(monSimulateur_ps); // destruction de simulateur
    return 0;
}
