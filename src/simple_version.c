#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/ui.h"


GtkWidget *drawing_area;

void draw_block_with_border(cairo_t *cr, int x, int y, int block_size) {
        // Fill the block depending on whether it's taken or not
        switch(fieldValues[y][x]){
            case '0':
                cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Black color for empty block
                break;
            case 'L':
            case '1':
                cairo_set_source_rgb(cr, 1.0, 0.65, 0.0);  // Orange
                break;
            case 'J':
            case '2':
                cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);  // Blue
                break;
            case 'O':
            case '3':
                cairo_set_source_rgb(cr, 1.0, 1.0, 0.0);  // Yellow
                break;
            case 'I':
            case '4':
                cairo_set_source_rgb(cr, 0.0, 1.0, 1.0);  // Light-Blue
                break;
            case 'S':
            case '5':
                cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);  // Green
                break;
            case 'Z':
            case '6':
                cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);  // Red
                break;
            case 'T':
            case '7':
                cairo_set_source_rgb(cr, 0.5, 0.0, 0.5);  // Purple
                break;
            default:
                cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);  // Black color for empty block
                break;

        } 

        cairo_rectangle(cr, x * block_size, y * block_size, block_size, block_size);
        cairo_fill(cr);  // Fill the block

        // Draw the border
        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);  // White color for the border
        cairo_set_line_width(cr, 2);              // Set border width (2 pixels)
        cairo_rectangle(cr, x * block_size, y * block_size, block_size, block_size);
        cairo_stroke(cr);  // Draw the border
} 


GtkWidget* create_game_screen(){
    //GtkWidget *game_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    drawing_area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(drawing_area), show, NULL, NULL);
    printf("DEBUG: create game screen\n");

    //gtk_box_append(GTK_BOX(game_box), area);
    return drawing_area;
}

