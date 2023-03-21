#include <stdio.h>
#include <stdlib.h>
#include "../Inc/regulation.h"
#define KP 1.1
#define KI 0.2
#define KD 0.15


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
		float erreur = consigne - tabT[nT-1];
		float dt = nT;
		float sum_error=tabT[nT-1] + tabT[nT-2];

		float P = KP * erreur * dt;	

		float I = KI * sum_error * dt;

		float D = KD * (erreur - (consigne - tabT[nT-2])) / dt;

		cmd = P + I + D;
		printf("%f\n", cmd);
		if(cmd > 100){
			cmd = 100;
		}
		if(cmd <= 0){
			cmd = 0;
		}
	}

	return cmd;
}