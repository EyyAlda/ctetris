#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/game.h"
#include "../include/ui.h"

int prepared = 0;
// pointer to the tetris playing field
GtkWidget *area;
// pointer to the app window
GtkWidget *window;
// pointer to the stack containing all screens
GtkWidget *app_stack;
// event listener for key presses in game
GtkEventController *key_controller;
// button on the pause screen to return to the main menu
GtkWidget *end_button;
// label to show paused or game over on the paused screen
GtkWidget *paused_label;

int is_paused = 0;
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

static guint game_loop_id;
static guint drawing_area_update_id;
gulong key_handler_id;

// draw a certain block of the tetromino playing field
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

// update the playing field
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

gboolean on_tick_callback(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer user_data) {
    gtk_widget_queue_draw(GTK_WIDGET(area));
    return TRUE;
}

void end_game(){
    if (game_loop_id != 0 && drawing_area_update_id != 0){
        g_source_remove(game_loop_id);
        prepare();
        g_source_remove(drawing_area_update_id);
        g_signal_handler_disconnect(key_controller, key_handler_id);
        game_loop_id = 0;
        drawing_area_update_id = 0;
        prepared = 0;
    }
}

void show_game_over_screen(){
    gtk_label_set_text(GTK_LABEL(paused_label), "GAME OVER!");
    gtk_button_set_label(GTK_BUTTON(end_button), "To Main Menu");
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "pause_screen");
}

// game loop
gboolean update_grid(gpointer user_data){
    if (!prepared) {
        prepare();
        prepared = 1;
    }
    if (game_over) {
        end_game();
        show_game_over_screen();
    } else {
        if (!is_paused){
            settle_tetromino();
            moveDown();
        }
    }
    return TRUE;
}

void show_pause_screen(){
    if (is_paused){
        gtk_label_set_text(GTK_LABEL(paused_label), "PAUSED");
        gtk_button_set_label(GTK_BUTTON(end_button), "End Game");
        gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "pause_screen");
    } else {
        gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "game_screen");
    }
}

gboolean in_game_key_press(GtkEventController *controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data){
    switch (keyval){
        case GDK_KEY_w:
        case GDK_KEY_W:
            if (!is_paused){
                printf("rotating\n");
                rotate_tetromino();
            }
            break;
        case GDK_KEY_a:
        case GDK_KEY_A:
            if (!is_paused){            
                printf("moving Left\n");
                moveLeft();
            }
            break;
        case GDK_KEY_s:
        case GDK_KEY_S:
            if (!is_paused){            
                printf("moving down\n");
                moveDown();
            }
            break;
        case GDK_KEY_d:
        case GDK_KEY_D:
            if (!is_paused){            
                printf("moving right\n");
                moveRight();
            }
            break;
        case GDK_KEY_space:
            if (!is_paused){
                printf("dropping\n");
                drop();
            }
            break;
        case GDK_KEY_Escape:
            printf("pausing\n");
            is_paused = !is_paused;
            show_pause_screen();
            break;
        default:
            printf("nothing\n");
            break;
    }
    return TRUE;
}

void start_game(){ 
    if (game_loop_id == 0 && drawing_area_update_id == 0){
        game_loop_id = g_timeout_add(1000, update_grid, NULL);
        drawing_area_update_id = gtk_widget_add_tick_callback(window, on_tick_callback, NULL, NULL);
        key_handler_id = g_signal_connect(key_controller, "key-pressed", G_CALLBACK(in_game_key_press), NULL);
        game_over = 0;
    } 
    is_paused = 0;
        
}



gboolean on_window_destroy(GtkWidget *widget, gpointer app){
    free_pointer();
    g_print("freed pointer\n");
    g_print("Quitting...\n");
    return TRUE;
}

void on_start_button_clicked(GtkWidget *widget, gpointer data){
    start_game();
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "game_screen");
}

void on_end_button_clicked(GtkWidget *widget, gpointer data){
    end_game();
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main_menu");
}

GtkWidget* create_pause_screen(){
    GtkWidget *pause_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    paused_label = gtk_label_new("PAUSED");
    end_button = gtk_button_new_with_label("End Game");
    gtk_widget_add_css_class(paused_label, "paused_label");
    gtk_widget_add_css_class(end_button, "end_button");

    gtk_box_append(GTK_BOX(pause_box), paused_label);
    gtk_box_append(GTK_BOX(pause_box), end_button);

    g_signal_connect(end_button, "clicked", G_CALLBACK(on_end_button_clicked), NULL);

    return pause_box;
}

GtkWidget* create_game_screen(){
    //GtkWidget *game_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), show, NULL, NULL);

    //gtk_box_append(GTK_BOX(game_box), area);
    return area;
}
/*static void on_window_size_allocate(GtkWidget *window, GtkAllocation *allocation, GtkPicture *picture)
{
    // Get the original image dimensions
    GdkPaintable *pixbuf = gtk_picture_get_paintable(picture);
    int orig_width = gdk_paintable_get_intrinsic_width(pixbuf);
    int orig_height = gdk_paintable_get_intrinsic_height(pixbuf);

    // Get the current window height
    int window_height = gtk_widget_get_height(window);

    // Calculate new width maintaining aspect ratio
    double aspect_ratio = (double)orig_width / orig_height;
    int new_width = window_height * aspect_ratio;

    // Set the new size request for the picture
    gtk_widget_set_size_request(GTK_WIDGET(picture), new_width, window_height);
}*/
GtkWidget* create_main_menu(){
    // Create the main menu container
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *main_menu_overlay = gtk_overlay_new();
    GtkWidget *background = gtk_scrolled_window_new();
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *start_button = gtk_button_new_with_label("Start Game");
    GtkWidget *background_picture = gtk_picture_new_for_filename("/home/lennard/Documents/myGames/Jtetris/textures/background.png");

    //create Layout
    gtk_overlay_set_child(GTK_OVERLAY(main_menu_overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(main_menu_overlay), button_container);
    gtk_box_append(GTK_BOX(button_container), start_button);
    gtk_box_append(GTK_BOX(main_box), main_menu_overlay);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(background), background_picture);
    
    // edit properties of the overlay
    gtk_widget_set_halign(GTK_WIDGET(main_menu_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_overlay), TRUE); // Allow box to expand vertically
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_overlay), TRUE); // Allow box to expand vertically

    //edit properties of the main menu container
    gtk_widget_set_halign(GTK_WIDGET(main_box), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(main_box), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_box), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_box), TRUE); // Allow box to expand horizontally
    gtk_widget_set_size_request(main_box, 800, 600);

    //center the button
    gtk_widget_set_halign(GTK_WIDGET(button_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(button_container), GTK_ALIGN_CENTER);
    gtk_button_set_has_frame(GTK_BUTTON(start_button), TRUE);

    // edit properties of the background_picture
    gtk_picture_set_can_shrink(GTK_PICTURE(background_picture), TRUE);
    gtk_widget_set_vexpand(background_picture, TRUE);
    gtk_picture_set_content_fit(GTK_PICTURE(background_picture), GTK_CONTENT_FIT_FILL);

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "../src/style.css");
    //gtk_widget_add_css_class(background, "main_menu");

    // Add title and start button
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_clicked), NULL);
    gtk_widget_add_css_class(start_button, "button-style");


    return main_box;
}


void on_activate(GtkApplication *app, gpointer user_data){
    window = gtk_application_window_new(app);
    app_stack = gtk_stack_new();

    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    //set minimum size
    gtk_widget_set_size_request(GTK_WIDGET(window), 400, 200);
    gtk_window_set_title(GTK_WINDOW(window), "Tetris");

    gtk_stack_set_transition_type(GTK_STACK(app_stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(app_stack), 100);
    gtk_widget_set_hexpand(app_stack, TRUE);
    gtk_widget_set_vexpand(app_stack, TRUE);
    gtk_widget_set_size_request(app_stack, 400, 200);
    gtk_widget_add_css_class(app_stack, "stack");

    // create main menu, game screen and pause screen
    GtkWidget *main_menu = create_main_menu();
    GtkWidget *game_screen = create_game_screen();
    GtkWidget *pause_screen = create_pause_screen();

    // add main menu and game screen to the application stack
    gtk_stack_add_named(GTK_STACK(app_stack), main_menu, "main_menu");
    gtk_stack_add_named(GTK_STACK(app_stack), game_screen, "game_screen");
    gtk_stack_add_named(GTK_STACK(app_stack), pause_screen, "pause_screen");

    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "../src/style.css");
    gtk_widget_add_css_class(main_menu, "main_menu");
    GdkDisplay *display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_widget_set_hexpand(main_menu, TRUE);
    gtk_widget_set_vexpand(main_menu, TRUE);

    gtk_widget_set_valign(pause_screen, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(pause_screen, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(pause_screen, TRUE);
    gtk_widget_set_vexpand(pause_screen, TRUE);

    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main_menu");

    key_controller = gtk_event_controller_key_new();
    gtk_widget_add_controller(GTK_WIDGET(window), key_controller);

    gtk_window_set_child(GTK_WINDOW(window), app_stack);


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
