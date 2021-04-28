#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// inet_ntoa
#include <time.h> 			// time

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"
//======================================================================
static void 
dieIfFaultOccurred (xmlrpc_env * const envP) {
    if (envP->fault_occurred) {
        fprintf( stderr, "ERROR: %s (%d)\n", envP->fault_string, envP->fault_code );
        exit(1);
    }
}
//======================================================================


//======================================================================
int error( int ern, const char *msg ){
    perror( msg );
    return ern;
}
//======================================================================

void sned(char * buffer){
    /* zmienne predefiniowane *****************************************/
    const char * const serverUrl = "http://localhost:11111/RPC2";
    const char * const methodName = "sample.add";
	
	/* zmienne niezainicjowane ****************************************/
    xmlrpc_env env;
    xmlrpc_value * resultP;
    xmlrpc_int32 sum;
    char *ret;
    
    /* inicjujemy srodowisko ******************************************/
    xmlrpc_env_init(&env);

    /* inicjujemy xml-rpc po stronie klienta **************************/
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFaultOccurred(&env);	// sprawdzamy, czy wystapil blad 

    /* wywolujemy zdalna procedure ************************************/
    /* ("ii") oznacza format danych, tutaj: 2 x int *******************/
    resultP = xmlrpc_client_call(&env, serverUrl, methodName, "(s)", buffer);
    dieIfFaultOccurred(&env);
    
    /* pobieramy wynik ************************************************/
    xmlrpc_read_string(&env, resultP, &ret);
    dieIfFaultOccurred(&env);
    
    /* wypisujemy wynik *****************************************S******/
    //printf("Wysyłam wiadomość na port 11111: %s\n", ret);
    
    /* dekrementujemy licznik referencji ******************************/
    xmlrpc_DECREF(resultP);

    /* czyscimy srodowisko ********************************************/
    xmlrpc_env_clean(&env);
    
    /* konczymy prace klienta *****************************************/
    xmlrpc_client_cleanup();
}

int main( void ) {
	
	/* zmienne predefiniowane *****************************************/
	int  port   = 12343;
	
	/* zmienne niezainicjowane ****************************************/		
	int 		fd;
	char 		buffer[256];
	socklen_t 	socklen;
	char 		hex[200];
	
	struct 	sockaddr_in serv_addr, cli_addr;
	
	/* tworzymy gniazdo ***********************************************/
	fd = socket( AF_INET, SOCK_DGRAM, 0 );		// tworzymy nowe gniazdo
	if (fd < 0) 
        return error( 1, "socket()" );
        
    /* zapelniamy strukture zerami (inicjujemy) ***********************/
	bzero( ( char * )&serv_addr, sizeof(serv_addr));	// zapelniamy strukture zerami
	
	/* przypisujemy parametry *****************************************/
	serv_addr.sin_family 	  	= AF_INET;			// typ gniazda 
	serv_addr.sin_addr.s_addr 	= INADDR_ANY;		// oczekujemy polaczen na kazdym adresie
	serv_addr.sin_port 			= htons(port);		// port, na ktorym nasluchujemy
	
	/* mapujemy gniazdo ***********************************************/
	if( bind(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
		return error( 2, "bind()" );
	
	/* rozpoczynamy nasluchiwanie na gniezdzie ************************/
	listen( fd, 5 );
	
	/* kod obslugujacy nowe polaczenia ********************************/
	socklen = sizeof(cli_addr);
	
	while(1) 
	{
			
			bzero(buffer, 256);

			/* wypisujemy informacje o polaczeniu *********************/
			
			recvfrom(fd, (char *)buffer, 255, MSG_WAITALL, (struct sockaddr *)&cli_addr, &socklen);
            
            sned(buffer);

            printf("Wynik otrzymany z portu 12344: %s\n", buffer);
            
					
	}
	 /* zamykamy gniazdo **********************************************/
	close(fd);
	
	//------------------------------------------------------------------
	return 0; 
}
//======================================================================
