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



	
void Jugar()
{    
  //gtk_widget_hide_all(window);

        window_c = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));//Crea la ventana principal
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("Imagenes/icono.jpg"));//coloca el icono del programa
        //Definimos el tamaño de la ventana
	gtk_widget_set_size_request (window_c,1063, 768);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window_c),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window_c), GTK_WIN_POS_CENTER);

        frame=gtk_fixed_new();// Se crea un marco
        gtk_container_add(GTK_CONTAINER(window_c), frame);//se agrega el marco al contenedor

	//se asigna la iimagen de fondo
	imagen=gtk_image_new_from_file("Imagenes/tablero2.jpg");
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
	/*Creacion del boton de ayuda
	boton2=gtk_button_new_with_label("Ayuda");
        gtk_widget_set_size_request(boton2,180,70);
        gtk_fixed_put (GTK_FIXED(frame),boton2,20,50);*/
        // g_signal_connect(b1, "clicked", G_CALLBACK (Jugar),NULL);
	g_signal_connect_swapped (G_OBJECT (boton1), "clicked",G_CALLBACK (gtk_widget_destroy),G_OBJECT (GTK_WIDGET(window_c)));
        //g_signal_connect_swapped (G_OBJECT (boton1), "clicked",G_CALLBACK (gtk_widget_show),G_OBJECT (GTK_WIDGET(window)));
        g_signal_connect(botoncerrar, "clicked", G_CALLBACK (destroy),NULL);
        //Mostramos todos los elementos
	  gtk_widget_show_all(GTK_WIDGET(window_c));
}


		
void Reglas_Juego()
{    

        window_c = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));//Crea la ventana principal
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("Imagenes/icono.jpg"));//coloca el icono del programa
        //Definimos el tamaño de la ventana
	gtk_widget_set_size_request (window_c,572, 650);
	//Deja la ventana estática
	gtk_window_set_resizable(GTK_WINDOW(window_c),FALSE);
	//Posciciona la venta en el centro de la pantalla
	gtk_window_set_position(GTK_WINDOW(window_c), GTK_WIN_POS_CENTER);
	frame=gtk_fixed_new();// Se crea un marco
	//se asigna la iimagen de fondo
	imagen=gtk_image_new_from_file("Imagenes/reglas.jpg");
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
        gtk_window_set_icon(GTK_WINDOW(window_c), create_pixbuf("Imagenes/icono.jpg"));//coloca el icono del programa
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

