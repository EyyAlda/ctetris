#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"


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

void on_activate(GtkApplication *app, gpointer user_data){
                GtkWidget *window = gtk_application_window_new(app);

                gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
                //set minimum size
                gtk_widget_set_size_request(GTK_WIDGET(window), 400, 200);

                gtk_window_set_title(GTK_WINDOW(window), "Tetris");

                GtkEventController *key_controller = gtk_event_controller_key_new();

                g_signal_connect(key_controller, "key-pressed", G_CALLBACK(in_game_key_press), NULL);

                gtk_widget_add_controller(GTK_WIDGET(window), key_controller);

                gtk_window_present(GTK_WINDOW(window));
}


int create_gui(int argc, char *argv[], int download_new){
    int status;
    GtkApplication *app = gtk_application_new("com.tetris", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
