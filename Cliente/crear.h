#include <gtk-2.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "ventanas_error.h"
GdkPixbuf *create_pixbuf(const gchar * filename);

void Ventana_Desarrolladores();
void Ventana_Instrucciones();
void Jugar( );
void AcercaDe();
void Reglas_Juego();


GtkWidget *label,*label2, *label3;	
	PangoFontDescription *fuente;

  GdkPixbuf *pixbuf;
  GtkWidget *imagen;
GtkWidget *imagen_jugar;
  GtkWidget *imagen2;
  GtkWidget *imagen3;
  GtkWidget *imagen4;
  GtkWidget *imagen5;
  GtkWidget *imgt1;
  GtkWidget *imgt2;
  GtkWidget *imgt3;
  GtkWidget *imgt4;
  GtkWidget *imgt5;
  GtkWidget *imgt6;
  GtkWidget *fondo_crear;
  GtkWidget *imagenbloqueo;
  GtkWidget *imagenf;
  GtkWidget *imagenT;
  GtkWidget *botonexpg;
  GtkWidget *botonexpi;

  GdkColor color;
  GtkWindow *window_c;
  GtkWidget *frame;
  GtkWidget *boton1;
  GtkWidget *boton2;
  GtkWidget *boton3;
  GtkWidget *boton4; 
  GtkWidget *boton5;
  GtkWidget *btntema1;
  GtkWidget *btntema2;
  GtkWidget *btntema3;
  GtkWidget *btntema4;
  GtkWidget *btntema5;
  GtkWidget *btntema6;
  GtkWidget *btn_crear_relacion;
  GtkWidget *btn_crear_grafo;
  GtkWidget *btn_editar_grafo;
  GtkWidget *botoncerrar;
  GtkWidget *botoncerrar_jugar;

  GtkWidget *botonbloqueo;
 
  GtkWidget *boton_desarrolladores;
  GtkWidget *boton_instrucciones;
  GtkWidget *boton_Tda;
  GdkScreen *screen;
  GtkWidget *imgcerrar;
  GtkWidget *ventana_d;
  GtkWidget *ventana_i;
  GtkWidget *ventana_T;
  GtkWidget *marco_d;
  GtkWidget *marco_i;
  GtkWidget *marco_T;
  GtkWidget *nodo1;
  GtkWidget *nodo2;
  GtkWidget *peso;

  GtkWidget *i1;
  GtkWidget *i2;
  GtkWidget *i3;
  GtkWidget *i4;
  GtkWidget *i5;
  GtkWidget *i6;
  GtkWidget *img_gra1;
  GtkWidget *img_gra2;
  GtkWidget *img_gra3;
  GtkWidget *img_gra4;


