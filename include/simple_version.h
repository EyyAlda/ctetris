#ifndef SIMPLE_VERSION_H
#define SIMPLE_VERSION_H

#include <gtk-4.0/gtk/gtk.h>

void draw_block_with_border(cairo_t *cr, int x, int y, int block_size);

GtkWidget* create_game_screen();

#endif
