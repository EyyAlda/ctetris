#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"

GtkWidget *grid;
int prepared = 0;



static GtkWidget* create_colored_box(const char *color_name) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkCssProvider *provider = gtk_css_provider_new();
    gchar *css = g_strdup_printf("box {background-color: %s;}", color_name);
    gtk_css_provider_load_from_data(provider, css, -1);
    g_free(css);

    GtkStyleContext *context = gtk_widget_get_style_context(box);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    gtk_widget_set_hexpand(box, TRUE);
    gtk_widget_set_vexpand(box, TRUE);

    return box;
}


/*void free_playing_field(char** field){
    for (int i = 0; i < 20; i++){
        free(field[i]);
    }
    free(field);
}*/

GtkWidget* create_new(int y, int x){
    GtkWidget *box;
    switch(fieldValues[y][x]){
        case '0':
            box = create_colored_box("gray");
            break;
        case 'L':
        case '1':
            box = create_colored_box("orange");
            break;
        case 'J':
        case '2':
            box = create_colored_box("blue");
            break;
        case 'O':
        case '3':
            box = create_colored_box("yellow");
            break;
        case 'I':
        case '4':
            box = create_colored_box("light-blue");
            break;
        case 'S':
        case '5':
            box = create_colored_box("green");
            break;
        case 'Z':
        case '6':
            box = create_colored_box("red");
            break;
        case 'T':
        case '7':
            box = create_colored_box("purple");
            break;
        default:
            box = create_colored_box("black");
            break;
    }

    GtkWidget *aspect_frame = gtk_aspect_frame_new(0.5, 0.5, 1.0, FALSE);
    
    gtk_widget_set_hexpand(aspect_frame, TRUE);
    gtk_widget_set_vexpand(aspect_frame, TRUE);
    gtk_widget_set_hexpand(box, TRUE);
    gtk_widget_set_vexpand(box, TRUE);
    gtk_aspect_frame_set_child(GTK_ASPECT_FRAME(aspect_frame), box);

    return aspect_frame;
}

void show(){
GtkWidget *boxes[200];
    int i = 0;
    for (int y = 0; y < 20; y++){
        for (int x = 0; x < 10; x++){
            boxes[i] = create_new(y, x);
            gtk_grid_attach(GTK_GRID(grid), boxes[i], x, y, 1, 1);
            i++;
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
    show();
    return TRUE;
}
gboolean update_grid(gpointer user_data){
    if (!prepared) prepare();
    moveDown();
    showPlayingField();
    show();    
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

                GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
                gtk_widget_set_hexpand(main_box, TRUE);
                gtk_widget_set_vexpand(main_box, TRUE);
                gtk_widget_set_halign(main_box, GTK_ALIGN_CENTER);
                gtk_widget_set_valign(main_box, GTK_ALIGN_FILL);

                grid = gtk_grid_new();
                gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
                gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
                gtk_widget_set_margin_start(grid, 0);
                gtk_widget_set_margin_end(grid, 0);
                gtk_widget_set_margin_top(grid, 0);
                gtk_widget_set_margin_bottom(grid, 0);
                gtk_widget_set_vexpand(grid, TRUE);
                gtk_widget_set_hexpand(grid, TRUE);
                
                gtk_box_append(GTK_BOX(main_box), grid);

                gtk_window_set_child(GTK_WINDOW(window), main_box);
                gtk_window_present(GTK_WINDOW(window));
}

int create_gui(int argc, char *argv[], int download_new){
    int status;
    GtkApplication *app = gtk_application_new("com.tetris", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    g_timeout_add(1000, update_grid, NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
