    #include <stdio.h>
	#include <stdlib.h>
	#include "define.h" 
    
    // Pensez à bien proteger vos .h avec des ifndef
	float TOR(float consigne,float temp);
    float PID(float consigne, float now_error, float prev_error, float* sum_error);
    float regulationTest(int regul,float consigne,float* tabT, int nT);