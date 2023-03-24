#include <stdio.h>
#include <stdlib.h>
#include "../Inc/autotests.h"
#include "../Inc/visualisationT.h"
#include "../Inc/visualisationC.h"
#include "../Inc/regulation.h"
#include "../Inc/simulateur.h"
#include "../Inc/consigne.h"

#define REGUL_TYPE 2 // TOR : 1 | PID : 2

/**
 * @brief 
 * 
 * 
 */
int main(){
    temp_t temperature;
    temperature.exterieure = 10.0;
    temperature.interieure = 15.0;
    struct simParam_s*  monSimulateur_ps = simConstruct(temperature); // creation du simulateur, puissance intialisee à 0%
    float consi = 20;
    float consigne_prev = 20;
    float puissance = 70;
    float prev_error = 0;
    float sum_error = 0;
    while(consi >=5){
        consi = consigne(consigne_prev);
        switch (REGUL_TYPE) // le choix du type du régulateur ce fait plus haut dans les #define
        {
        case 1:
            puissance = TOR(consi, temperature.interieure); // la régulation du type tout ou rien
            break;
        
        case 2:
            puissance = PID((consi - temperature.interieure), prev_error, &sum_error); // la régulation avec le PID
        break;
        default:
            break;
        }
        temperature = simCalc(puissance,monSimulateur_ps); // simulation de l'environnement
        visualisationT(temperature); // envoie des températures pour l'affichage python
        visualisationC(puissance); // envoie de l'état de chauffe pour l'affichage python
        consigne_prev = consi; 
        prev_error = (consi - temperature.interieure);
    }
    simDestruct(monSimulateur_ps); // destruction de simulateur
    return 0;
}
