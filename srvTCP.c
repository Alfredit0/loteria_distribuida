// Recibe una cadena del Cliente y se la devuelve en mayusculas
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 120
extern int errno;

main()
{
   struct sockaddr_in lsock,fsock, sname;
   int s, ss;
   int len,i;
   char buf[MAX_LINE], resp[MAX_LINE];
   //Creación de socket
   if((s=socket(AF_INET,SOCK_STREAM,0)) < 0) {
      perror("SOCKET: ");
      exit(0);
   }
   lsock.sin_family = AF_INET;
   lsock.sin_port = htons(4400); /* puerto para dar el servicio */
   lsock.sin_addr.s_addr =0; /* direccion IP de mi maquina servidora */
   //Asignación de dirección local 
   if(bind(s,(struct sockaddr *)&lsock, sizeof(struct sockaddr_in)) < 0 ){
      perror("BIND: ");
      exit(1);
   }
   //La llamada al sistema listen()  
   if(listen(s,3)<0){
      perror("LISTEN: ");
      exit(1);
   }
    
   while(1){ 
      len = sizeof(struct sockaddr_in); /* &len: entra y sale el tamano del socket esperado */
      //La llamada al sistema accept() 
      if((ss=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
         perror("ACCEPT: ");
         continue;
      }
      printf("Un cliente conectado\n");
      if (fork() == 0) {
         /* Aqui se ejecuta el proceso hijo */
         /* Cierra el socket incompleto */
         /* se dedica a atender la conexion con el socket completo */
         close(s);
         while(1){ // Transferencia de datos.
            if((len=recv(ss,buf,MAX_LINE-1,0))<=0){
               perror("RECV: "); /* Si len==0 entonces el cliente cerro la conexion */
               exit(1);
            }
            //Aqui imprimo la direccion IP del cliente y el puerto al que esta conectado (el plus)
            printf("La dirección IP que tiene el cliente es: %s \n",inet_ntoa(fsock.sin_addr));
            
            printf("Cadena Recibida: %s\n",buf);
            if(strcmp(buf,"Salir")==0){
               printf("Termina el servicio por decision del Cliente\n");
               close(ss); //Cerrar la conexión
               exit(0); /* el proceso hijo se mata */
            }
	    else{
            printf("Nuevo Usuario conectado\n");
            strcpy(resp,"Hola: ");
	    strcat( resp, buf);
	    strcat( resp, " Bienvenido al juego de loteria Distribuida");

             }
             
            // Transferencia de datos. 
            if(send(ss,resp,strlen(resp),0) < len) /* responde al cliente */
               perror("SEND: ");
         } /*while */
      } /* if fork */
      else /* Aqui continua el proceso vigia para aceptar otra conexion */
         close(ss); /* el padre cierra el socket completo que dejo al hijo */
   } /*while*/
}
