#include "Loteria.h"
#include "crear.h" 
char *filename;	
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

