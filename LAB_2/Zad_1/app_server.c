/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "app.h"

wyjscie *
obliczenia_1_svc(wejscie *argp, struct svc_req *rqstp)
{
	static wyjscie  result;

    printf("Przesłane dane do zsumowania: %d %d\n", argp->x1, argp->x2);
    
	result.suma = argp->x1 + argp->x2;

	return &result;
}
