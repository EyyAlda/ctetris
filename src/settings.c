#include "../include/settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk-4.0/gtk/gtk.h>




GtkWidget *create_settings_menu(){
    GtkWidget *settings_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *settings_overview = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *settings_elements = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *save_exit_button_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *container = gtk_scrolled_window_new();
    GtkWidget *settings_media_grid = gtk_grid_new();
    GtkWidget *settings_keys_grid = gtk_grid_new();
    GtkWidget *settings_overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new();
    GtkWidget *media_label = gtk_label_new("Media Settings");
    GtkWidget *keybind_label = gtk_label_new("Keybinds");
    GtkWidget *header_label = gtk_label_new("Settings");

    gtk_box_append(GTK_BOX(settings_container), settings_overlay);

    gtk_box_append(GTK_BOX(settings_overview), header_label);
    gtk_box_append(GTK_BOX(settings_overview), container);
    gtk_box_append(GTK_BOX(settings_overview), save_exit_button_container);

    gtk_box_append(GTK_BOX(settings_elements), media_label);
    gtk_box_append(GTK_BOX(settings_elements), settings_media_grid);
    gtk_box_append(GTK_BOX(settings_elements), keybind_label);
    gtk_box_append(GTK_BOX(settings_elements), settings_keys_grid);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(container), settings_elements);

    gtk_overlay_set_child(GTK_OVERLAY(settings_overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(settings_overlay), settings_overview);

    return settings_container;
}
