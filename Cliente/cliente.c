// Cliente (Socket Stream)
// Envia una cadena al servidor y se la devuelve en mayusculas
// Victor Gómez


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <netdb.h>
#include <unistd.h>

#define MAX_LINE 10
extern int errno;

int main(int argc,char *argv[])
{
	char buf[MAX_LINE];
	struct sockaddr_in fsock, sname;
   	struct hostent *hent; /* estructura que guarda el llamado a gethostbyname */
	int s, len;
	char mensaje[MAX_LINE];
	char *sl="A1"; 
	hent = gethostbyname("localhost");
   //Creación de socket 
	if((s=socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("SOCKET: ");
		exit(0);
	}
	fsock.sin_family = AF_INET;
   fsock.sin_addr.s_addr = *(long *) hent->h_addr; /* direccion IP de Maq. Remota */
   fsock.sin_port = htons(4400); /* puerto de la maq. remota */
   //Estableciendo conexión 
	if(connect(s,(struct sockaddr *)&fsock, sizeof(struct sockaddr_in)) == -1){
		perror("CONNECT: ");
		close(s);
		exit(0);
	}
	printf("Arranca el Programa Cliente !!!... Pulse q para salir\n");
	strcpy(mensaje,"conectame");
   //printf("Escribe tu mensaje de Jugador ");
   //scanf("%s",mensaje);
   //printf("Tu mensaje es = %s\n",mensaje);
   //Transferencia de datos 
	if( send(s,mensaje,strlen(mensaje),0) < strlen(mensaje) ){
		perror("SEND: ");    
	}
    //printf("Me detengo a recibir la respuesta del servidor...\n");
    //Transferencia de datos 
	if( (len=recv(s,buf,MAX_LINE-1,0))<= 0 ){
		perror("RECV: ");
		close(s);
		exit(0);
	}
	buf[len] = '\0';
	printf("Respuesta..: %s\n\n",buf);   
   if(strcmp(buf,"RECHAZADO")!=0){//
   	while(1){
			//Asignacion de mensaje
   		strcpy(mensaje,"yaempiezo");  
		   //Envio de datos 
   		if( send(s,mensaje,strlen(mensaje),0) < strlen(mensaje) ){
   			perror("SEND: ");    
   		}			
			//Transferencia de datos 
   		if( (len=recv(s,buf,MAX_LINE-1,0))<= 0 ){
   			perror("RECV: ");
   			close(s);
   			exit(0);
   		}
   		buf[len] = '\0';
		   //printf("Respuesta..: %s\n\n",buf);
		   if(strcmp(buf,"COMIENZAN")==0){//   			   
		   	while(1){
					//Asignacion de mensaje
		   		strcpy(mensaje,"damecarta");  
					//Envio de datos 
		   		if( send(s,mensaje,strlen(mensaje),0) < strlen(mensaje) ){
		   			perror("SEND: ");    
		   		}			
					//Transferencia de datos 
		   		if( (len=recv(s,buf,MAX_LINE-1,0))<= 0 ){
		   			perror("RECV: ");
		   			close(s);
		   			exit(0);
		   		}
		   		buf[len] = '\0';
					if(strcmp(buf,"YAGANARON")==0){//   
						break;
					}
					if(strcmp(buf,"TERMINADO")==0){//  
						printf("El Juego ha TERMINADO no existe Ningun Ganador\n"); 
						break;
					}			   		
					printf("Carta lanzada..: %s\n\n",buf);			   		

				}
				break;
			}
		   if(strcmp(buf,"NINGUNAOP")==0){//   
		   	break;
		   }		
		}	
	}else{
		printf("Jugador Rechazado!! Intente mas tarde\n\n");	
	}

	return 0;
}

