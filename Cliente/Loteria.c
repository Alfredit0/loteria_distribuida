#include "Loteria.h"
#include "crear.h" 
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LINE 10
extern int errno;
char filename[23];	

char filenameM[23];	
static GtkItemFactoryEntry menu_items[] = {
  
  { "/_Instrucciones",      NULL,         NULL, 0, "<LastBranch>" },
  { "/Instrucciones/Instrucciones",  NULL,Instrucciones, 0, NULL },
  { "/Instrucciones/Ayuda","F1",Ayuda,0, NULL },
  { "/_Acerca de",         NULL,         NULL, 0, "<LastBranch>" },
  { "/_Acerca de/Desarrolladores",   NULL, Desarrolladores, 0, NULL },
};
void get_main_menu( GtkWidget  *window,
                    GtkWidget **menubar )
{
  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;
  gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);
  accel_group = gtk_accel_group_new ();
  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>", 
                                       accel_group);

  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);

  /* Attach the new accelerator group to the window. */
  gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);

  if (menubar)
    /* Finally, return the actual menu bar created by the item factory. */ 
    *menubar = gtk_item_factory_get_widget (item_factory, "<main>");
}

  GtkWidget *main_vbox;

int main( int argc,char *argv[] )
{
    GtkWidget *menubar;
    gtk_init (&argc, &argv);
	//Inicializamos la variable window
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_icon(GTK_WINDOW(window), create_pixbuf("icon.png"));//coloca el icono del programa
	gtk_signal_connect (GTK_OBJECT (window), "destroy",GTK_SIGNAL_FUNC (gtk_main_quit), "WM destroy");
	//Ponemos nombre en la ventana
	gtk_window_set_title (GTK_WINDOW (window), "Loteria");
	//Definimos el tamaño de la ventana
	gtk_widget_set_size_request (window, 1063, 768);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	
  main_vbox = gtk_vbox_new (FALSE, 1);
  gtk_container_border_width (GTK_CONTAINER (main_vbox), 1);
  gtk_container_add (GTK_CONTAINER (window), main_vbox);
  gtk_widget_show (main_vbox); 
  get_main_menu (window, &menubar);
  gtk_box_pack_start (GTK_BOX (main_vbox), menubar, FALSE, TRUE, 0);
  gtk_widget_show (menubar);
  gtk_widget_show (window);
  Principal();
  gtk_main ();
  return(0);
}


void Principal()
{	
	gdk_threads_enter (); 
	contenedor=gtk_fixed_new(); 
	b1 = gtk_button_new_with_label("Jugar");//crear
	b2 = gtk_button_new_with_label("Reglas del juego");//cargar
	gtk_widget_set_size_request(b1,200,70);
	gtk_widget_set_size_request(b2,210,70);
	gtk_fixed_put (GTK_FIXED(contenedor),b1,420,650);
	gtk_fixed_put (GTK_FIXED(contenedor),b2,130,650);
	botoncerrar=gtk_button_new_with_label("salir");//salir
	gtk_widget_set_size_request(botoncerrar,200, 70);
	gtk_fixed_put(GTK_FIXED(contenedor),botoncerrar,710,650);	
	imagen=gtk_image_new_from_file("inicio.jpg");	
	gtk_fixed_put(GTK_FIXED(contenedor),imagen,0,0);
	g_signal_connect_swapped (G_OBJECT (botoncerrar), "clicked",
                                  G_CALLBACK (gtk_widget_destroy),
                                  G_OBJECT (GTK_WIDGET(window)));
	  gtk_signal_connect (GTK_OBJECT (window), "destroy", GTK_SIGNAL_FUNC (gtk_main_quit),"WM destroy"); 
	g_signal_connect(b1, "clicked", G_CALLBACK (Jugar),NULL);
	g_signal_connect(b2, "clicked", G_CALLBACK (Reglas_Juego),NULL);
	gtk_box_pack_start (GTK_BOX (main_vbox), contenedor, FALSE, FALSE, 0);
	//~Mostramos todo en la ventana principal
	gtk_widget_show_all(window);
	gdk_threads_leave();		
}

void Jugar()
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
   printf("Arranca Ventana de Jugar\n");
   strcpy(mensaje,"conectame");
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
      		
        window_c = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));//Crea la ventana principal
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("icon.png"));//coloca el icono del programa
        //Definimos el tamaño de la ventana
         gtk_window_set_default_size(GTK_WINDOW(window_c), 1063,768);
	//gtk_widget_set_size_request(window_c,1063,768);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window_c),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window_c), GTK_WIN_POS_CENTER);

        frame=gtk_fixed_new();// Se crea un marco
        gtk_container_add(GTK_CONTAINER(window_c), frame);//se agrega el marco al contenedor

	//se asigna la iimagen de fondo
	imagen=gtk_image_new_from_file("tablero2.jpg");
  	gtk_fixed_put(GTK_FIXED(frame),imagen,0,0); 
	//Creacion del boton de cerrar
        botoncerrar=gtk_button_new_with_label("salir");
        gtk_widget_set_size_request(botoncerrar,180,70);
        gtk_fixed_put (GTK_FIXED(frame),botoncerrar,840,600);
	g_signal_connect(botoncerrar, "clicked", G_CALLBACK (destroy),NULL);	
	//Creacion del boton de menu
	boton1=gtk_button_new_with_label("menu");
        gtk_widget_set_size_request(boton1,180,70);
        gtk_fixed_put (GTK_FIXED(frame),boton1,600,600);
        
	g_signal_connect_swapped (G_OBJECT (boton1), "clicked",G_CALLBACK (gtk_widget_destroy),G_OBJECT (GTK_WIDGET(window_c)));
        //g_signal_connect_swapped (G_OBJECT (boton1), "clicked",G_CALLBACK (gtk_widget_show),G_OBJECT (GTK_WIDGET(window)));
        g_signal_connect(botoncerrar, "clicked", G_CALLBACK (destroy),NULL);
		
        if(strcmp(buf,"RECHAZADO")!=0){//
		int cont=0;	
    
        //tablero asignado 
        strcpy(filename,"Imagenes/tablero");
        strcat(filename,buf);
        strcat(filename,".jpg");
		pixbuf= gdk_pixbuf_new_from_file_at_scale(filename,500,700,TRUE,NULL);
		tablero=gtk_image_new_from_pixbuf(pixbuf);			
		gtk_fixed_put(GTK_FIXED(frame),tablero,50,50); 		
		
        //Mostramos todos los elementos
		gtk_widget_show_all(GTK_WIDGET(window_c));
		
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
		   
		   gtk_widget_show_all(GTK_WIDGET(window_c));
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
					while(gtk_events_pending()) gtk_main_iteration();
					buf[len] = '\0';
					printf("Carta lanzada..: %s\n\n",buf);	
					//Carta Lanzada 
					strcpy(filename,"Imagenes/");
					strcat(filename,buf);
					strcat(filename,".jpg");
					
					strcpy(filenameM,"Sonidos/");
					strcat(filenameM,buf);
					strcat(filenameM,".mp3");
					
					
					pid_t x;      // a special kind of int
					char kil[20] = "kill -s 9 ";
			 
					x = fork();   /* now there's actually two "x"s:
					if fork succeeds, "x" to the CHILD PROCESS is the return value of fork (0)
					and "x" to the PARENT PROCESS is the actual system pid of the child process.*/
							 
					if (x < 0) {  // just in case fork fails 
							puts("fork failure");
							exit(-1);
					}   
					
					else if (x == 0) { // therefore this block will be the child process 
							execlp("mpg123", "mpg123", "-q", filenameM, NULL); 
					}
					                   // see GNU docs, "system" also works                
				/*	else {  printf("from parent: mpg123 is pid %d\nENTER to quit\n", x);
							sprintf(kil,"%s%d",kil,x);
							getchar();// wait for user input
							system(kil);
							printf("All ");
					}  
					*/
					
					
					
					
					pixbuf= gdk_pixbuf_new_from_file_at_scale(filename,174,276,TRUE,NULL);
					carta=gtk_image_new_from_pixbuf(pixbuf);			
					gtk_fixed_put(GTK_FIXED(frame),carta,600,280);					
					gtk_widget_show (carta);
					sleep(6);					
					if(strcmp(buf,"YAGANARON")==0){//   
						break;
					}						
				}
			}else{								
				while(gtk_events_pending()) gtk_main_iteration();
				//Esperando a los jugadores
					strcpy(filename,"Imagenes/");					
					strcat(filename,"loading.gif");
					pixbuf= gdk_pixbuf_new_from_file_at_scale(filename,174,276,TRUE,NULL);
					carta=gtk_image_new_from_pixbuf(pixbuf);			
					gtk_fixed_put(GTK_FIXED(frame),carta,600,280);
					gtk_widget_show (carta);
				}
		   if(strcmp(buf,"NINGUNAOP")==0){//   
			break;
			}		
			cont++;
	   }	
	   
		}else{
		printf("Jugador Rechazado!! Intente mas tarde\n\n");	
		}	
}

void Ayuda()
{
	//~Declaración de variables a utilizar en esta función
	GtkWidget *img,*reg,*clic,*manual;
	//~Inicializamos la variable window encima de la actual
	vent = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~Inicializamos el contenedor
	conte=gtk_fixed_new();
	
	
	
	manual =gtk_link_button_new_with_label( "manual.pdf","Manual de Usuario" );
	gtk_link_button_set_uri_hook( link_hook, NULL, NULL );
	
	//~Definimos el tamaño del boton b
	gtk_widget_set_size_request(manual,168,50);
	//~Poscicionamos b en el contenedor conte 
	gtk_fixed_put (GTK_FIXED(conte),manual,212,570);
	
	//~Dejamos la ventana de forma estática
	gtk_window_set_resizable(GTK_WINDOW(vent),FALSE);
	//~Ponemos nombre a la ventana
	gtk_window_set_title (GTK_WINDOW (vent), "Ayuda");
	//~Poscicionamos la ventana en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(vent), GTK_WIN_POS_CENTER);
	//~Definimos el tamaño d ela ventana
	gtk_widget_set_size_request (vent, 572, 650);
	clic=gtk_image_new_from_file ("clic.gif");
	gtk_fixed_put (GTK_FIXED(conte),clic,20,505);
//~ Ponemos la imegen de fondo.
	img=gtk_image_new_from_file ("ayuda.jpg");
	gtk_fixed_put (GTK_FIXED(conte),img,0,0);


	gtk_container_add (GTK_CONTAINER(vent),conte);
	gtk_widget_show_all(vent);
}

void Desarrolladores()
{
	//~Declaración de variables a utilizar en esta función
	GtkWidget *img,*reg,*clic,*manual;
	//~Inicializamos la variable window encima de la actual
	vent = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~Inicializamos el contenedor
	conte=gtk_fixed_new();
img=gtk_image_new_from_file ("desarrolladores.jpg");
	gtk_fixed_put (GTK_FIXED(conte),img,0,0);
	
//~Dejamos la ventana de forma estática
	gtk_window_set_resizable(GTK_WINDOW(vent),FALSE);
	//~Ponemos nombre a la ventana
	gtk_window_set_title (GTK_WINDOW (vent), "Desarrolladores");
	//~Poscicionamos la ventana en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(vent), GTK_WIN_POS_CENTER);
	//~Definimos el tamaño d ela ventana
	gtk_widget_set_size_request (vent, 572, 650);
	
	gtk_container_add (GTK_CONTAINER(vent),conte);
	gtk_widget_show_all(vent);
}

void Instrucciones()
{
	//~Declaración de variables a utilizar en esta función
	GtkWidget *img,*reg,*clic,*manual;
	//~Inicializamos la variable window encima de la actual
	vent = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//~Inicializamos el contenedor
	conte=gtk_fixed_new();
	//~Dejamos la ventana de forma estática
	gtk_window_set_resizable(GTK_WINDOW(vent),FALSE);
	//~Ponemos nombre a la ventana
	gtk_window_set_title (GTK_WINDOW (vent), "Instrucciones");
	//~Poscicionamos la ventana en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(vent), GTK_WIN_POS_CENTER);
	//~Definimos el tamaño d ela ventana
	gtk_widget_set_size_request (vent,572, 650);
	
	

	img=gtk_image_new_from_file ("instrucciones.jpg");
	gtk_fixed_put (GTK_FIXED(conte),img,0,0);

	gtk_container_add (GTK_CONTAINER(vent),conte);
	gtk_widget_show_all(vent);
}

static void link_hook( GtkLinkButton *button,const gchar   *link,gpointer       data )
{
   gchar *cmd = g_strconcat( "xdg-open ", link, NULL );

   g_spawn_command_line_async( cmd, NULL );
   g_free( cmd );
}

