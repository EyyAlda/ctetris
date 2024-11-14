#ifndef BACKGROUND_GIF_H
#define BACKGROUND_GIF_H

#include <gtk-4.0/gtk/gtk.h>

GtkWidget* create_gif_animated_background(GtkWidget *window, const char *gif_background_path, int window_width, int window_height);

#endif
