#ifndef UI_H
#define UI_H

#include <gtk-4.0/gtk/gtk.h>

int create_gui(int argc, char *argv[], int download_new);

void show(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data);

void show_advanced(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data);

#endif
