#include <gtk-4.0/gtk/css/gtkcss.h>
#include <gtk-4.0/gtk/gtk.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/get_files_path.h"
#include "../include/simple_version.h"
#include "../include/advanced_version.h"
#include "../include/gif_handler.h"
#include "../include/settings.h"

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

GtkWidget *ghost_tetromino_switch;

int is_initialized = 0;

int are_files_available;

int is_paused = 0;
#define GRID_WIDTH 10
#define GRID_HEIGHT 20


static guint game_loop_id;
static guint drawing_area_update_id;

gulong key_handler_id;

GdkPaintable* icons[9];

TextureAtlas* atlas;

RenderState* state;
//
void show_game_over_screen(){
    gtk_label_set_text(GTK_LABEL(paused_label), "GAME OVER!");
    gtk_button_set_label(GTK_BUTTON(end_button), "To Main Menu");
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "pause_screen");
}

void end_game(){
    if (game_loop_id != 0 && drawing_area_update_id != 0){ 
        g_source_remove(game_loop_id);
        prepare();
        g_source_remove(drawing_area_update_id);
        g_signal_handler_disconnect(key_controller, key_handler_id);
        if (atlas != NULL && state != NULL) {
            cleanup_texture_atlas(atlas);
            cleanup_render_state(state);
        }
        game_loop_id = 0;
        drawing_area_update_id = 0;
        prepared = 0;
        is_initialized = 0;
        free_pointer();
        fprintf(stdout, "end_game executed\n");
    }
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


// update the playing field
void show_advanced(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data){
    /*int block_size_x = width / GRID_WIDTH;  // Calculate block size based on the new width
    int block_size_y = height / GRID_HEIGHT;  // Calculate block size based on the new height
    
    // Use the minimum block size to maintain square blocks
    int block_size = MIN(block_size_x, block_size_y);
    g_print("%d\n", block_size);
*/
    if (!is_initialized){
        update_grid(NULL);
        atlas = create_texture_atlas(icons, 50);
        state = create_render_state(fieldValues);
        state->atlas = atlas;       
        is_initialized = 1;
    }


    state->cr = cr;
    render_field_batch(state); 
}

// update the playing field
void show(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data){
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
                drop(0);
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
    prepared = 0;
    is_initialized = 0;
    set_show_ghost(gtk_switch_get_state(GTK_SWITCH(ghost_tetromino_switch)));
    fprintf(stdout, "start_game executed\n");
        
}



gboolean on_window_destroy(GtkWidget *widget, gpointer app){
    end_game(); 
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

void on_quit_button_clicked(GtkWidget *widget, gpointer data){
    g_print("Quitting\n");
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

GtkWidget *create_game_panel(){
    //load background image
    errno = 0;
    char *base_path = return_folders_path();
    char add_path[] = "textures/background4.gif";
    char background_img_path[strlen(base_path) + strlen(add_path) + 1];
    
    perror("after background_img_path");
    strcpy(background_img_path, base_path);
    strcat(background_img_path, add_path);
    fprintf(stdout, "Background Image: %s\n", background_img_path);
    perror("after strcat");
    free_folders_ptr();

    int window_width = gtk_widget_get_width(GTK_WIDGET(window));
    int window_height = gtk_widget_get_height(GTK_WIDGET(window));
 
    GtkWidget *game_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *game_overlay = gtk_overlay_new();
    GtkWidget *background = create_gif_player(background_img_path);
    GtkWidget *game_screen;

    if (are_files_available){
        game_screen = create_game_screen_advanced();
        area = get_game_area();
    } else {
        game_screen = create_game_screen();
        area = game_screen;
    }

    gtk_widget_set_halign(GTK_WIDGET(game_container), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(game_container), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(GTK_WIDGET(game_container), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(game_container), TRUE);

    gtk_widget_set_halign(GTK_WIDGET(game_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(game_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(GTK_WIDGET(game_overlay), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(game_overlay), TRUE);

/*    gtk_widget_set_halign(GTK_WIDGET(background), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(background), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(GTK_WIDGET(background), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(background), TRUE);
*/
    gtk_widget_set_halign(GTK_WIDGET(game_screen), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(game_screen), GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(GTK_WIDGET(game_screen), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(game_screen), TRUE);

    gtk_box_append(GTK_BOX(game_container), game_overlay);

    gtk_overlay_set_child(GTK_OVERLAY(game_overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(game_overlay), game_screen);

    return game_container;
}

GtkWidget* create_main_menu(){
    char *base_path = return_folders_path(); 
    perror("after return_folders_path");
    char additional_path[] = "textures/background.png";
    char background_img_path[strlen(base_path) + strlen(additional_path) + 1];
    
    perror("after background_img_path");
    strcpy(background_img_path, base_path);
    strcat(background_img_path, additional_path);
    perror("after strcat");

    // Create the main menu container
    GtkWidget *main_menu_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *main_menu_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *main_menu_middle = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *main_menu_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *main_menu_overlay = gtk_overlay_new();
    GtkWidget *background = gtk_scrolled_window_new();
    GtkWidget *start_button = gtk_button_new_with_label("Start Game");
    GtkWidget *settings_button = gtk_button_new_with_label("Settings");
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    GtkWidget *background_picture = gtk_picture_new_for_filename(background_img_path);
    ghost_tetromino_switch = gtk_switch_new();
    GtkWidget *nothing_label = gtk_label_new(" ");
    GtkWidget *ghost_label = gtk_label_new("Show Ghost-Tetrominos");

    //edit properties of the main_menu_container
    gtk_widget_set_halign(GTK_WIDGET(main_menu_container), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_container), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_container), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_menu_container), TRUE); // Allow box to expand horizontially
    
    //edit properties of the switch
    gtk_widget_set_halign(GTK_WIDGET(ghost_tetromino_switch), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(ghost_tetromino_switch), GTK_ALIGN_START);
    gtk_widget_add_css_class(GTK_WIDGET(ghost_tetromino_switch), "ghost-switch");

    //edit properties of the ghost tetromino label
    gtk_widget_set_halign(GTK_WIDGET(ghost_label), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(ghost_label), GTK_ALIGN_START);
    gtk_widget_add_css_class(GTK_WIDGET(ghost_label), "ghost-label");

    //edit properties of the label
    gtk_widget_set_valign(GTK_WIDGET(nothing_label), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(nothing_label), GTK_ALIGN_END);
    gtk_widget_add_css_class(GTK_WIDGET(nothing_label), "nothing-label");

    //edit properties of the start button
    gtk_widget_set_halign(GTK_WIDGET(start_button), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(start_button), GTK_ALIGN_CENTER);



    //create overlay Layout
    gtk_overlay_set_child(GTK_OVERLAY(main_menu_overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(main_menu_overlay), main_menu_middle);
    gtk_overlay_add_overlay(GTK_OVERLAY(main_menu_overlay), main_menu_left);
    gtk_overlay_add_overlay(GTK_OVERLAY(main_menu_overlay), main_menu_right);


    //append items to the 3 vboxes
    gtk_box_append(GTK_BOX(button_container), start_button);
    gtk_box_append(GTK_BOX(button_container), settings_button);
    gtk_box_append(GTK_BOX(button_container), quit_button);
    gtk_box_append(GTK_BOX(main_menu_left), ghost_label);
    gtk_box_append(GTK_BOX(main_menu_left), ghost_tetromino_switch);
    gtk_box_append(GTK_BOX(main_menu_middle), button_container);
    gtk_box_append(GTK_BOX(main_menu_right), nothing_label);

    gtk_box_append(GTK_BOX(main_box), main_menu_overlay);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(background), background_picture);
    
    // edit properties of the overlay
    gtk_widget_set_halign(GTK_WIDGET(main_menu_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_overlay), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_overlay), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_menu_overlay), TRUE); // Allow box to expand vertically

    //edit properties of the main menu container
    gtk_widget_set_halign(GTK_WIDGET(main_box), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(main_box), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_box), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_box), TRUE); // Allow box to expand horizontially

    //edit properties of the box containing the start button
    gtk_widget_set_halign(GTK_WIDGET(button_container), GTK_ALIGN_BASELINE_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(button_container), GTK_ALIGN_BASELINE_CENTER);
    gtk_widget_add_css_class(GTK_WIDGET(button_container), "menu-box");


    //set properties of the middle vbox
    gtk_box_set_homogeneous(GTK_BOX(main_menu_middle), FALSE);
    gtk_widget_set_halign(GTK_WIDGET(main_menu_middle), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_middle), GTK_ALIGN_CENTER);
    gtk_button_set_has_frame(GTK_BUTTON(start_button), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_middle), TRUE); // Allow box to expand vertically
    gtk_widget_add_css_class(GTK_WIDGET(main_menu_middle), "menu-box");

    //set properties of the left vbox
    gtk_widget_set_halign(GTK_WIDGET(main_menu_left), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_left), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_left), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_menu_left), TRUE); // Allow box to expand horinzontially
    gtk_widget_add_css_class(GTK_WIDGET(main_menu_left), "menu-box");


    //set properties of the right vbox
    gtk_widget_set_halign(GTK_WIDGET(main_menu_right), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(main_menu_right), GTK_ALIGN_FILL);
    gtk_widget_set_vexpand(GTK_WIDGET(main_menu_right), TRUE); // Allow box to expand vertically
    gtk_widget_set_hexpand(GTK_WIDGET(main_menu_right), TRUE); // Allow box to expand horinzontially
    gtk_widget_add_css_class(GTK_WIDGET(main_menu_right), "menu-box");

    // edit properties of the background_picture
    gtk_picture_set_can_shrink(GTK_PICTURE(background_picture), TRUE);
    gtk_widget_set_vexpand(background_picture, TRUE);
    gtk_picture_set_content_fit(GTK_PICTURE(background_picture), GTK_CONTENT_FIT_COVER);

    // Load CSS
    GtkCssProvider *provider = gtk_css_provider_new();

    char stylesheet_path[strlen(base_path) + strlen("textures/style.css") + 1];
    
    strcpy(stylesheet_path, base_path);
    strcat(stylesheet_path, "textures/style.css");

    gtk_css_provider_load_from_path(provider, stylesheet_path);
    //gtk_widget_add_css_class(background, "main_menu");
    free_folders_ptr();

    g_object_unref(provider);
    
    perror("after free_folders_ptr");

    // Add title and start button
    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_clicked), NULL);
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit_button_clicked), NULL);
    gtk_widget_add_css_class(start_button, "button-style");
    gtk_widget_add_css_class(settings_button, "button-style");
    gtk_widget_add_css_class(quit_button, "button-style");


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

    g_set_application_name("com.eyyalda.tetris");
    g_set_prgname("Tetris");
     
    // create main menu, game screen and pause screen
    GtkWidget *main_menu = create_main_menu();

    GtkWidget *game_screen = create_game_panel();    

    GtkWidget *pause_screen = create_pause_screen();

    GtkWidget *settings_screen = create_settings_menu();

    // add main menu and game screen to the application stack
    gtk_stack_add_named(GTK_STACK(app_stack), main_menu, "main_menu");
    gtk_stack_add_named(GTK_STACK(app_stack), game_screen, "game_screen");
    gtk_stack_add_named(GTK_STACK(app_stack), pause_screen, "pause_screen");
    gtk_stack_add_named(GTK_STACK(app_stack), settings_screen, "settings_screen");

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

    
    if (are_files_available){
        char *path = return_folders_path();
        char tetromino_icons[][10] = {"i.png", "j.png", "l.png", "null.png", "o.png", "s.png", "t.png", "z.png", "ghost.png"};
        for (int i = 0; i < 9; i++){
            char textures_path[strlen(path) + strlen("textures/") + strlen(tetromino_icons[i]) + 1];
            strcpy(textures_path, path);
            strcat(textures_path, "textures/");
            strcat(textures_path, tetromino_icons[i]);
            GdkTexture *texture = gdk_texture_new_from_filename(textures_path, NULL);
            icons[i] = GDK_PAINTABLE(texture);
        } 
        fprintf(stdout, "Loaded Icons\n");
    }
    
}

int create_gui(int argc, char *argv[], int download_new){
    int status;
    are_files_available = download_new;
    GtkApplication *app = gtk_application_new("com.tetris", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
