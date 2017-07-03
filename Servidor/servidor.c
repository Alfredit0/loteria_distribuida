// Recibe una cadena del Cliente y se la devuelve en mayusculas
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h> /* mmap() is defined in this header */
#include <fcntl.h>
#include <time.h>
#include <sys/shm.h>

#define MAX_LINE 10
extern int errno;
//declaracion de las funciones
void inicializarJuego (int cartas[]);
int validarInsertarTablero (int jugadorNo, int *tabJugador1, int *tabJugador2, int *tabJugador3, int *tabJugador4, int *tabJugador5);
int main()
{
   struct sockaddr_in lsock,fsock, sname;
   int s, ss;
   int len;
   char buf[MAX_LINE], resp[MAX_LINE];
   //Numero de jugadores conectados
   int *numJugadores= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);   
   int *bandGanador= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);   

	//Tableros de los jugadores
   int *tabJugador1= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);   
   int *tabJugador2= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);   
   int *tabJugador3= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);     
   int *tabJugador4= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0); 
   int *tabJugador5= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
      MAP_SHARED | MAP_ANONYMOUS, -1, 0);                                                 
    //Nombres de los jugadores
   char nombres[5][30];
   //Arreglo de las cartas. Utilizadas para validar las cartas mostradas   
   int cartas[54];   
   *tabJugador1=0;
   *tabJugador2=0;
   *tabJugador3=0;
   *tabJugador4=0;
   *tabJugador5=0;
   //Se inicializa el juego
   inicializarJuego(cartas);
   //Numero de carta (Se generara aleaotrio)
   int numCarta, bandTiempo;
   //Incializa contador de numero de carta y bandera
   numCarta=0;
   bandTiempo=0;
   //Numero de tablero
   int tablero=0;
   int numeroJugador=0;
   //Declaracion de variables para estado General del Juego

   key_t Clave;
   int Id_Memoria;
   int *Memoria = NULL;
   int j;

   
   //Creación de socket | SOCK_NONBLOCK
   if((s=socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0)) < 0) {
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
   if(listen(s,2)<0){
      perror("LISTEN: ");
      exit(1);
   }

   while(1){ 
      ///printf("HOLA SOY EL SERVER ***\n");
      printf("Numero GLOBAL DE JUGADORES....:%d\n", *numJugadores);
      if(*numJugadores==1){ // 
               //
               // Igual que en p1.cc, obtenemos una clave para la memoria compartida
               //
               Clave = ftok ("/bin/ls", 33);
               if (Clave == -1)
               {
                  printf("No consigo clave para memoria compartida\n");
                  exit(0);
               }

               //
               // Igual que en p1.cc, obtenemos el id de la memoria. Al no poner
               // el flag IPC_CREAT, estamos suponiendo que dicha memoria ya está
               // creada.
               //
               Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 );
               if (Id_Memoria == -1)
               {
                  printf("No consigo Id para memoria compartida\n");
                  exit (0);
               }

               //
               // Igual que en p1.cc, obtenemos un puntero a la memoria compartida
               //
               Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
               if (Memoria == NULL)
               {
                  printf("No consigo memoria compartida\n");
                  exit (0);
               }

               //
               // Vamos leyendo el valor de la memoria con esperas de un segundo
               // y mostramos en pantalla dicho valor. Debería ir cambiando según
               // p1 lo va modificando.
               //
               for (j=0; j<16; j++)
               {
                  printf("Leido %d\n",Memoria[j]);
               }

               sleep(3);
               //
               // Desasociamos nuestro puntero de la memoria compartida. Suponemos
               // que p1 (el proceso que la ha creado), la liberará.
               //
               if (Id_Memoria != -1)
               {
                  shmdt ((char *)Memoria);
               }

           }      
      len = sizeof(struct sockaddr_in); /* &len: entra y sale el tamano del socket esperado */
      //La llamada al sistema accept() 
      if((ss=accept(s,(struct sockaddr *)&fsock, &len)) < 0){
         perror("ACCEPT: ");
         continue;
      }  
      if (*numJugadores==0)
          {
            //Se inicializa el juego
            inicializarJuego(cartas);
               //Se intenta eliminar la memoria compartida
               //
               shmdt ((char *)Memoria);
               shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);            

                  //Se crea memoria compartida
                  //
                  // Conseguimos una clave para la memoria compartida. Todos los
                  // procesos que quieran compartir la memoria, deben obtener la misma
                  // clave. Esta se puede conseguir por medio de la función ftok.
                  // A esta función se le pasa un fichero cualquiera que exista y esté
                  // accesible (todos los procesos deben pasar el mismo fichero) y un
                  // entero cualquiera (todos los procesos el mismo entero).
                  //
                  Clave = ftok ("/bin/ls", 33);
                  if (Clave == -1)
                  {
                     printf("No consigo clave para memoria compartida\n");
                     exit(0);
                  }

                  //
                  // Creamos la memoria con la clave recién conseguida. Para ello llamamos
                  // a la función shmget pasándole la clave, el tamaño de memoria que
                  // queremos reservar (100 enteros en nuestro caso) y unos flags.
                  // Los flags son  los permisos de lectura/escritura/ejecucion 
                  // para propietario, grupo y otros (es el 777 en octal) y el 
                  // flag IPC_CREAT para indicar que cree la memoria.
                  // La función nos devuelve un identificador para la memoria recién
                  // creada.
                  //  
                  Id_Memoria = shmget (Clave, sizeof(int)*100, 0777 | IPC_CREAT);
                  if (Id_Memoria == -1)
                  {
                     printf("No consigo Id para memoria compartida\n");
                     exit (0);
                  }            
          }             
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
            buf[len] = '\0';
            //Aqui imprimo la direccion IP del cliente y el puerto al que esta conectado (el plus)
           // printf("La dirección IP que tiene el cliente es: %s \n",inet_ntoa(fsock.sin_addr));
            char subbuff[8];
            subbuff[0]=buf[0];
            subbuff[1]=buf[1];
            subbuff[2]=buf[2];
            subbuff[3]=buf[3];
            subbuff[4]=buf[4];
            subbuff[5]=buf[5];
            subbuff[6]=buf[6];
            subbuff[7] = '\0';

            char subbuffPos[3];
            subbuffPos[0]=buf[7];
            subbuffPos[1]=buf[8];
            subbuffPos[2] = '\0';

            //printf("CADENA ... : %s SUB Cadena Recibida: %s\n numero Final pos....:",buf, subbuffPos);
            if(strcmp(buf,"Salir")==0){
               printf("Termina el servicio por decision del Cliente\n");
               close(ss); //Cerrar la conexión
               exit(0); /* el proceso hijo se mata */
            }
            else if(strcmp(buf,"ganejuego")==0){// Se recibe el mensaje de Juego Finalizado de alguno de de los cliente
            printf("YA HAY UN GANADOR -> INDICAR A TODOS LOS NODOS\n");
            *bandGanador=99;
            strcpy(resp,"YAGANARON");
             }
            else if(strcmp(subbuff,"posicio")==0){// Se recibe el mensaje de
            printf("GUARDANDO ESTADO DE JUEGO\n");
                  //
                  // Una vez creada la memoria, hacemos que uno de nuestros punteros
                  // apunte a la zona de memoria recién creada. Para ello llamamos a
                  // shmat, pasándole el identificador obtenido anteriormente y un
                  // par de parámetros
                  //
                  Memoria = (int *)shmat (Id_Memoria, (char *)0, 0);
                  if (Memoria == NULL)
                  {
                     printf("No consigo memoria compartida\n");
                     exit (0);
                  } 
                  int posClient;
                  posClient=atoi(subbuffPos);
                  int positition=(numeroJugador-1)*16+posClient;
                 Memoria[positition] = 1;
                 printf("VALOR DE POSICION GUARDADA EN MEMORIA........: %d\n", Memoria[positition]);
            strcpy(resp,"GUARDADO");
             }         
           else if(strcmp(buf,"damecarta")==0){// Se recibe solicitud de carta por parte del cliente ya conectado			   

              if (*bandGanador==99)
              {
               printf("YA HAY UN GANADOR DEL JUEGO\n");               
               strcpy(resp,"YAGANARON");
            }else{
               if (numCarta==16)
               {
                  strcpy(resp,"TERMINADO");
                  bandTiempo=2;

                     //
                     // Terminada de usar la memoria compartida, la liberamos.
                     //
                     shmdt ((char *)Memoria);
                     shmctl (Id_Memoria, IPC_RMID, (struct shmid_ds *)NULL);
                  }else{
                 printf("Resolviendo carta para el usuario\n");
                 printf("Numero de carta en el arreglo....: %d Valor de contador de cartas...:%d\n", cartas[numCarta],numCarta);             
                 sprintf(resp, "%d",cartas[numCarta]);                 
                 numCarta=numCarta+1; 
                 bandTiempo=1;                 
              }
           }
        }  
            else if(strcmp(buf,"conectame")==0){//       
             *numJugadores=*numJugadores+1;		                     				
					if(*numJugadores<=3){ //	
						printf("Un jugador conectado\n");						
						printf("El numero de jugadores conectados es %d\n", *numJugadores);				
						printf("Jugador aceptado!!\n\n");
                  numeroJugador=*numJugadores;
						tablero = validarInsertarTablero(*numJugadores, &*tabJugador1, &*tabJugador2, &*tabJugador3, &*tabJugador4, &*tabJugador5);				
						sprintf(resp, "%d",tablero);
						printf("Tablero asignado %s\n", buf);
						printf("Tablero del jugador 1..: %d\nTablero del jugador 2..: %d\nTablero del jugador 3..: %d\n", *tabJugador1, *tabJugador2, *tabJugador3);                 
					}else{								
                  printf("El numero de jugadores conectados es %d\n", *numJugadores);				
                  printf("Jugador Rechazado!!\n\n");	
                  strcpy(resp, "RECHAZADO");
               }				
            }
            else if(strcmp(buf,"yaempiezo")==0){//                            				

					if(*numJugadores==1){ //						
						printf("COMIENZAN LOS CLIENTES A JUGAR\n");
						strcpy(nombres[*numJugadores],buf);
						strcpy(resp,"COMIENZAN");

					}else{		
						//printf("El numero de jugadores conectados es %d", *numJugadores);							
						strcpy(resp,"FALTANJUG");
               }				
            }else{
              strcpy(resp,"NINGUNAOP");
           }								
            // Transferencia de datos. 
            if(send(ss,resp,strlen(resp),0) < len) /* responde al cliente */
           perror("SEND: ");
           if (bandTiempo==1)
           {
              sleep(8); 
              bandTiempo=0;
           }
           if (bandTiempo==2)
           {
              *numJugadores=0;
           }
           
         } /*while */
      } /* if fork */
      else /* Aqui continua el proceso vigia para aceptar otra conexion */
         close(ss); /* el padre cierra el socket completo que dejo al hijo */            

   } /*while*/

           return 0;
        }

        void inicializarJuego (int cartas[]){          
          int aux = 0;
          int i=0;
          srand(time(0));

          for(i = 0; i < 54; i++){
           aux = (1 + rand() % 54);

           int aux2 = 0;

           while(aux2 < i){
            if(aux != cartas[aux2])
             aux2++;

          else{
           aux = (1 + rand() % 54);
           aux2 = 0;

        }
     }

     cartas[i] = aux;

  }


}

int validarInsertarTablero (int jugadorNo, int *tabJugador1, int *tabJugador2, int *tabJugador3, int *tabJugador4, int *tabJugador5){				
 int bandera=1;
 int tableroNo;
 while(bandera==1){
   srand (time(NULL));
   tableroNo= rand () % (10-1+1) + 1;
   if(tableroNo!=*tabJugador1&&tableroNo!=*tabJugador2&&tableroNo!=*tabJugador3&&tableroNo!=*tabJugador4&&tableroNo!=*tabJugador5){
     printf("Numero de tablero generado automaticamente...: %d\n", tableroNo);
     switch(jugadorNo)
     {
       case 1:
       *tabJugador1=tableroNo;
       break;
       case 2:
       *tabJugador2=tableroNo;
       break;

       case 3:
       *tabJugador3=tableroNo;
       break;
       case 4:
       *tabJugador4=tableroNo;
       break;
       case 5:
       *tabJugador5=tableroNo;
       break;
    }
    bandera=2;
 }
}
return tableroNo;
}
