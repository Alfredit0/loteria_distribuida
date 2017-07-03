#include "emergentes.h"
void mostrarGane(gpointer window)
{
/* Crea los widgets */
	PangoFontDescription *fuente;
	GtkWidget *dialog, *label, *Img;
	dialog = gtk_dialog_new_with_buttons ("Mensaje",
                                         GTK_WINDOW (window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_BUTTONS_CANCEL,
                                         NULL);
                                      gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
	 /////colores de la ventana del mensaje
     gdk_color_parse("#CCFBBF",&color);
     gtk_widget_modify_bg(GTK_WIDGET(dialog),GTK_STATE_NORMAL,&color);
	////color de la letra del mensaje
    label = gtk_label_new ("Felicidades has ganado");
    gdk_color_parse("BLACK",&color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL,&color);
    fuente = pango_font_description_new();							//creacion de la fuente.
	pango_font_description_set_family(fuente, "Times New Roman");	//Definición del tipo de fuente que trendrá.
	pango_font_description_set_size(fuente, 15* PANGO_SCALE);		//Definicion del tamaño de la fuente.
	gtk_widget_modify_font(GTK_WIDGET(label),fuente);			//Asignacion de la fuente a la etiqueta.
    Img=gtk_image_new_from_file ("No.png");//////imagen del mensaje.
  
	g_signal_connect_swapped (GTK_OBJECT (dialog),
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             GTK_OBJECT (dialog));
    /* Añadir la etiqueta, y mostrar todo lo que hemos añadido a la ventana de diálogo . */
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label);
	gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), Img);
    gtk_widget_show_all (dialog);
}

void mostrarGanaron(gpointer window)
{
/* Crea los widgets */
    PangoFontDescription *fuente;
    GtkWidget *dialog, *label, *Img;
    dialog = gtk_dialog_new_with_buttons ("Mensaje",
                                         GTK_WINDOW (window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_BUTTONS_CANCEL,
                                         NULL);
                                      gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
     /////colores de la ventana del mensaje
     gdk_color_parse("#CCFBBF",&color);
     gtk_widget_modify_bg(GTK_WIDGET(dialog),GTK_STATE_NORMAL,&color);
    ////color de la letra del mensaje
    label = gtk_label_new ("Lo sentimos otro jugador ha ganado");
    gdk_color_parse("BLACK",&color);
    gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL,&color);
    fuente = pango_font_description_new();                          //creacion de la fuente.
    pango_font_description_set_family(fuente, "Times New Roman");   //Definición del tipo de fuente que trendrá.
    pango_font_description_set_size(fuente, 15* PANGO_SCALE);       //Definicion del tamaño de la fuente.
    gtk_widget_modify_font(GTK_WIDGET(label),fuente);           //Asignacion de la fuente a la etiqueta.
    Img=gtk_image_new_from_file ("No.png");//////imagen del mensaje.
  
    g_signal_connect_swapped (GTK_OBJECT (dialog),
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             GTK_OBJECT (dialog));
    /* Añadir la etiqueta, y mostrar todo lo que hemos añadido a la ventana de diálogo . */
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), Img);
    gtk_widget_show_all (dialog);
}

void mostrarTerminado(gpointer window)
{
/* Crea los widgets */
    PangoFontDescription *fuente;
    GtkWidget *dialog, *label, *Img;
    dialog = gtk_dialog_new_with_buttons ("Mensaje",
                                         GTK_WINDOW (window),
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_BUTTONS_CANCEL,
                                         NULL);
                                      gtk_window_set_resizable(GTK_WINDOW(dialog),FALSE);
     /////colores de la ventana del mensaje
     gdk_color_parse("#CCFBBF",&color);
     gtk_widget_modify_bg(GTK_WIDGET(dialog),GTK_STATE_NORMAL,&color);
    ////color de la letra del mensaje
    label = gtk_label_new ("El Juego ha TERMINADO no existe Ningun Ganador");
    gdk_color_parse("BLACK",&color);
    gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL,&color);
    fuente = pango_font_description_new();                          //creacion de la fuente.
    pango_font_description_set_family(fuente, "Times New Roman");   //Definición del tipo de fuente que trendrá.
    pango_font_description_set_size(fuente, 15* PANGO_SCALE);       //Definicion del tamaño de la fuente.
    gtk_widget_modify_font(GTK_WIDGET(label),fuente);           //Asignacion de la fuente a la etiqueta.
    Img=gtk_image_new_from_file ("No.png");//////imagen del mensaje.
  
    g_signal_connect_swapped (GTK_OBJECT (dialog),
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             GTK_OBJECT (dialog));
    /* Añadir la etiqueta, y mostrar todo lo que hemos añadido a la ventana de diálogo . */
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), label);
    gtk_container_add (GTK_CONTAINER (GTK_DIALOG(dialog)->vbox), Img);
    gtk_widget_show_all (dialog);
}


