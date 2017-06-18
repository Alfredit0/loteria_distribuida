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
   char nombre[MAX_LINE];
   char *sl="A1"; 
   if (argc!=2){
      printf("USO: cliente nombreMaquina_del_Servidor\n");
      exit(1);
   }
   if(!(hent = gethostbyname(argv[1])) ){
      perror("GETHOSTBYNAME: ");
      exit(0);
   }
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
   strcpy(nombre,"conectame");
   //printf("Escribe tu nombre de Jugador ");
   //scanf("%s",nombre);
   //printf("Tu nombre es = %s\n",nombre);
   //Transferencia de datos 
   if( send(s,nombre,strlen(nombre),0) < strlen(nombre) ){
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
   if(strcmp(buf,"CONECTADO")==0){//   
	   while(1){
			//Asignacion de mensaje
		   strcpy(nombre,"yaempiezo");  
		   //Envio de datos 
		   if( send(s,nombre,strlen(nombre),0) < strlen(nombre) ){
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
					strcpy(nombre,"damecarta");  
					//Envio de datos 
					if( send(s,nombre,strlen(nombre),0) < strlen(nombre) ){
						perror("SEND: ");    
					}			
					//Transferencia de datos 
					if( (len=recv(s,buf,MAX_LINE-1,0))<= 0 ){
						perror("RECV: ");
						close(s);
						exit(0);
					}
					buf[len] = '\0';
					printf("Respuesta..: %s\n\n",buf);
					sleep(8);
					if(strcmp(buf,"YAGANARON")==0){//   
						break;
					}						
				}
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
