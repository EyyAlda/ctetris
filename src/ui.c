#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"

//GtkWidget *grid;
int prepared = 0;
//GtkWidget *boxes[200];
GtkWidget *area;
//GtkWidget *fps_label;
#define GRID_WIDTH 10
#define GRID_HEIGHT 20


static void draw_block_with_border(cairo_t *cr, int x, int y, int block_size) {
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

static void show(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data){
    int block_size_x = width / GRID_WIDTH;  // Calculate block size based on the new width
    int block_size_y = height / GRID_HEIGHT;  // Calculate block size based on the new height

    // Use the minimum block size to maintain square blocks
    int block_size = MIN(block_size_x, block_size_y);
    for (int y = 0; y < 20; y++){
        for (int x = 0; x < 10; x++){
           draw_block_with_border(cr, x, y, block_size); 
        }        
    }
}
gboolean in_game_key_press(GtkEventController *controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data){


    switch (keyval){
        case GDK_KEY_w:
        case GDK_KEY_W:
            printf("rotating\n");
            rotate_tetromino();
            break;
        case GDK_KEY_a:
        case GDK_KEY_A:
            printf("moving Left\n");
            moveLeft();
            break;
        case GDK_KEY_s:
        case GDK_KEY_S:
            printf("moving down\n");
            moveDown();
            break;
        case GDK_KEY_d:
        case GDK_KEY_D:
            printf("moving right\n");
            moveRight();
            break;
        default:
            printf("nothing\n");
            break;
    }
    return TRUE;
}
gboolean update_grid(gpointer user_data){
    if (!prepared) {
        prepare();
        prepared = 1;
    }
    //showPlayingField();
    settle_tetromino();
    moveDown();
    //showPlayingField();
    //showPlayingField();
    return TRUE;
}

gboolean on_tick_callback(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer user_data) {
    //gint64 frame_time = gdk_frame_clock_get_frame_time(frame_clock);
    //char fps[] = {"FPS: " + ((char[] )frame_time)};
    //gtk_label_set_text(GTK_LABEL(fps_label), fps);
    gtk_widget_queue_draw(GTK_WIDGET(area));
    return TRUE;
}

gboolean on_window_destroy(GtkWidget *widget, gpointer app){
    free_pointer();
    g_print("freed pointer\n");
    g_print("Quitting...\n");
    return TRUE;
}

void on_activate(GtkApplication *app, gpointer user_data){
    GtkWidget *window = gtk_application_window_new(app);

    area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), show, NULL, NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    //set minimum size
    gtk_widget_set_size_request(GTK_WIDGET(window), 400, 200);
    gtk_window_set_title(GTK_WINDOW(window), "Tetris");

    GtkEventController *key_controller = gtk_event_controller_key_new();
    g_signal_connect(key_controller, "key-pressed", G_CALLBACK(in_game_key_press), NULL);
    gtk_widget_add_controller(GTK_WIDGET(window), key_controller);

    g_timeout_add(1000, update_grid, NULL);

    gtk_widget_add_tick_callback(window, on_tick_callback, NULL, NULL);

    gtk_window_set_child(GTK_WINDOW(window), area);

    gtk_window_present(GTK_WINDOW(window));
    // Connect the "destroy" signal of the window to the callback
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), app);
}

int create_gui(int argc, char *argv[], int download_new){
    int status;
    GtkApplication *app = gtk_application_new("com.tetris", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);


    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
