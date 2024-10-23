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

//GtkWidget *fps_label;


/*static GtkWidget* create_colored_box(const char *color_name, int create_new) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkCssProvider *provider = gtk_css_provider_new();
    gchar *css = g_strdup_printf("box {background-color: %s; border: 1px solid gray;}", color_name);
    gtk_css_provider_load_from_data(provider, css, -1);
    g_free(css);

    GtkStyleContext *context = gtk_widget_get_style_context(box);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    gtk_widget_set_hexpand(box, TRUE);
    gtk_widget_set_vexpand(box, TRUE);

    return box;
}

void edit_colored_box(const char *color_name, GtkWidget *box) {
    GtkCssProvider *provider = gtk_css_provider_new();
    
    // Generate a unique CSS class name using the memory address of the box widget
    gchar *unique_class = g_strdup_printf("colored-box-%p", box);
    
    // Create the CSS rule with the unique class and specified color
    gchar *css = g_strdup_printf(".%s { background-color: %s; border: 1px solid gray; }", unique_class, color_name);
    gtk_css_provider_load_from_data(provider, css, -1);
    g_free(css);

    // Get the style context of the GtkBox
    GtkStyleContext *context = gtk_widget_get_style_context(box);

    // Add the CSS provider to the widget's style context
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Add the unique class to the box, so it uses the new CSS rule
    gtk_widget_add_css_class(box, unique_class);

    // Unreference the CSS provider as it's no longer needed
    g_object_unref(provider);
    
    // Free the unique class string
    g_free(unique_class);
}

void draw_tetrominos(){

}
*/

/*void free_playing_field(char** field){
    for (int i = 0; i < 20; i++){
        free(field[i]);
    }
    free(field);
}*/
/*
void edit_values(int y, int x, GtkWidget *box){
    switch(fieldValues[y][x]){
        case '0':
            edit_colored_box("black", box);
            break;
        case 'L':
        case '1':
            edit_colored_box("orange", box);
            break;
        case 'J':
        case '2':
            edit_colored_box("blue", box);
            break;
        case 'O':
        case '3':
            edit_colored_box("yellow", box);
            break;
        case 'I':
        case '4':
            edit_colored_box("rgb(0, 153, 255)", box);
            break;
        case 'S':
        case '5':
            edit_colored_box("green", box);
            break;
        case 'Z':
        case '6':
            edit_colored_box("red", box);
            break;
        case 'T':
        case '7':
            edit_colored_box("purple", box);
            break;
        default:
            edit_colored_box("black", box);
            break;
    }
    
}
*/
/*void init_Boxes(){
        for (int i = 0; i < 200; i++){
            boxes[i] = create_colored_box("black", 1);
        }
        int i = 0;
        for (int y = 0; y < 20; y++){
            for (int x = 0; x < 10; x++){
                gtk_grid_attach(GTK_GRID(grid), boxes[i], x, y, 1, 1);
                i++;
            }
        }
}
*/
void show(){
    int i = 0;
    for (int y = 0; y < 20; y++){
        for (int x = 0; x < 10; x++){
            edit_values(y, x, boxes[i]);
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
    if (!prepared) {
        prepare();
        init_Boxes();
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
    show();

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
                
                fps_label = gtk_label_new("FPS:");
                gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
                //set minimum size
                gtk_widget_set_size_request(GTK_WIDGET(window), 400, 200);
                gtk_window_set_title(GTK_WINDOW(window), "Tetris");

                GtkEventController *key_controller = gtk_event_controller_key_new();
                g_signal_connect(key_controller, "key-pressed", G_CALLBACK(in_game_key_press), NULL);
                gtk_widget_add_controller(GTK_WIDGET(window), key_controller);

                g_timeout_add(1000, update_grid, NULL);

                gtk_widget_add_tick_callback(window, on_tick_callback, NULL, NULL);
                
                grid = gtk_grid_new();
                gtk_widget_set_vexpand(grid, TRUE);
                gtk_widget_set_hexpand(grid, TRUE);
                
                GtkWidget *aspect_ratio = gtk_aspect_frame_new(0.5, 0.5, 0.5, FALSE);
                gtk_aspect_frame_set_child(GTK_ASPECT_FRAME(aspect_ratio), grid);
                
                gtk_window_set_child(GTK_WINDOW(window), aspect_ratio);

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
