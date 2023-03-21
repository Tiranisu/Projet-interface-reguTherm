#include <stdio.h>
#include <stdlib.h>
#include "../Inc/regulation.h"
#define KP 1
#define KI 1
#define KD 1


/**
 * @brief 
 * 
 * @param regul Si 1 la regulation est en TOR, si 2 la régulation est en PID
 * @param consigne Température de consigne
 * @param tabT Tableau de température
 * @param nT Taille du tableau de température
 * @return float 
 */
float regulationTest(int regul,float consigne,float* tabT, int nT){
	float cmd=0; // <---

	if(regul == 1){
		if(tabT[nT-1] > consigne){
			return 0;
		}
		if(tabT[nT-1] <= consigne){
			return 50;
		}
	}
	if(regul == 2){
		int dt = nT*10;
		float erreur = tabT[nT-1];
		float P = KP * (consigne - erreur);
		float I = KI * erreur * dt;
		float D = KD * (erreur - tabT[nT - 1]) / dt;
		float PID = P + I + D; 
		//printf("%f", P);
	}

	return cmd;
}