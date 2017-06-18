#include "Loteria.h"
#include <string.h>
 #include <ctype.h>
GdkPixbuf *create_pixbuf(const gchar * filename)
 {	 
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
       fprintf(stderr, "%s\n", error->message);
       g_error_free(error);
    }
    return pixbuf;
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
		
void Reglas_Juego()
{    

        window_c = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));//Crea la ventana principal
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("icono.jpg"));//coloca el icono del programa
        //Definimos el tamaño de la ventana
	gtk_widget_set_size_request (window_c,572, 650);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window_c),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window_c), GTK_WIN_POS_CENTER);
	frame=gtk_fixed_new();// Se crea un marco
	//se asigna la iimagen de fondo
	imagen=gtk_image_new_from_file("reglas.jpg");
  	gtk_fixed_put(GTK_FIXED(frame),imagen,0,0);
        gtk_container_add(GTK_CONTAINER(window_c), frame);//se agrega el marco al contenedor
  	 
	//g_signal_connect(boton2, "clicked", G_CALLBACK (Ayuda),NULL);            
        g_signal_connect_swapped (G_OBJECT (botoncerrar), "clicked",
                                  G_CALLBACK (gtk_widget_destroy),
                                  G_OBJECT (GTK_WIDGET(window_c)));
       //Mostramos todos los elementos
       gtk_widget_show_all(GTK_WIDGET(window_c));
}


void AcercaDe()
{    

        window_c = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));//Crea la ventana principal
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("icono.jpg"));//coloca el icono del programa
        //Definimos el tamaño de la ventana
	gtk_widget_set_size_request (window_c,572, 650);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window_c),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window_c), GTK_WIN_POS_CENTER);
        frame=gtk_fixed_new();// Se crea un marco
        gtk_container_add(GTK_CONTAINER(window_c), frame);//se agrega el marco al contenedor
        //imagen=gtk_image_new_from_file("tablero2.jpg");
  	//gtk_fixed_put(GTK_FIXED(frame),imagen,0,0); 
        botoncerrar=gtk_button_new_with_label("salir de hacerca de");
        gtk_widget_set_size_request(botoncerrar,180,70);
        gtk_fixed_put (GTK_FIXED(frame),botoncerrar,50,600);
 //g_signal_connect(boton2, "clicked", G_CALLBACK (Ayuda),NULL);            

        g_signal_connect_swapped (G_OBJECT (botoncerrar), "clicked",
                                  G_CALLBACK (gtk_widget_destroy),
                                  G_OBJECT (GTK_WIDGET(window_c)));
  //Mostramos todos los elementos
   gtk_widget_show_all(GTK_WIDGET(window_c));
}

void destroy( GtkWidget *widget,gpointer   data )
{
    gtk_main_quit();
}


static void link_hook( GtkLinkButton *button,const gchar   *link,gpointer       data )
{
   gchar *cmd = g_strconcat( "xdg-open ", link, NULL );

   g_spawn_command_line_async( cmd, NULL );
   g_free( cmd );
}	

