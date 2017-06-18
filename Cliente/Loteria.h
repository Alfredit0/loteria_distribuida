#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h> 
#include <stdlib.h>
#include "crear.h"

void Principal();
void Desarrolladores();
void destroy( GtkWidget *widget,gpointer   data );
int main( int argc,char *argv[] );
void OnButton(GtkWidget *pWidget);

void Ayuda();
void Instrucciones();
static void link_hook( GtkLinkButton *button,const gchar   *link,gpointer       data );

GtkWidget *window,*vent,*contenedor,*b1,*b2,*b3, *conte,*b1_jugar,*contenedor_jugar,*window_jugar;


PangoFontDescription *font;
GtkWidget  *swin, *viewport, *table1, *table2,*imagen, *hpaned,*button,*button2,*textview,*imgzoom;
GtkTextBuffer *buffer;
char cadena[100];
GtkTextMark *mark;
GtkTextIter iter;
const gchar *text;

             
