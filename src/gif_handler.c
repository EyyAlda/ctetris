#include <gtk-4.0/gtk/gtk.h>
#include <gdk-pixbuf-2.0/gdk-pixbuf/gdk-pixbuf.h>
#include "../include/gif_handler.h"


typedef struct {
    GtkPicture *picture;
    GdkPixbufAnimation *animation;
    GdkPixbufAnimationIter *iter;
    guint timeout_id;
    int original_width;
    int original_height;
} GifPlayer;

static void on_size_allocate(GtkWidget *widget, int width, int height, gpointer user_data) {
    GifPlayer *player = (GifPlayer *)user_data;
    
    if (width <= 1 || height <= 1) return;  // Ignore invalid sizes
    
    // Calculate scaling factors to fill the entire space
    double scale_x = (double)width / player->original_width;
    double scale_y = (double)height / player->original_height;
    double scale = MAX(scale_x, scale_y);  // Use the larger scale to fill the space completely
    
    // Set the size request to fill the entire space
    gtk_widget_set_size_request(GTK_WIDGET(player->picture), width, height);
}

static gboolean advance_animation(gpointer user_data) {
    GifPlayer *player = (GifPlayer *)user_data;
    
    // Get the current frame as pixbuf
    GdkPixbuf *pixbuf = gdk_pixbuf_animation_iter_get_pixbuf(player->iter);
    
    // Set the current frame to the picture widget
    gtk_picture_set_pixbuf(player->picture, pixbuf);
    
    // Advance to next frame
    gdk_pixbuf_animation_iter_advance(player->iter, NULL);
    
    // Get delay time for next frame (in milliseconds)
    int delay = gdk_pixbuf_animation_iter_get_delay_time(player->iter);
    if (delay < 20) delay = 20; // Minimum delay to prevent excessive CPU usage
    
    // Remove current timeout and set new one with updated delay
    if (player->timeout_id) {
        g_source_remove(player->timeout_id);
    }
    player->timeout_id = g_timeout_add(delay, advance_animation, player);
    
    return G_SOURCE_REMOVE;
}

void cleanup_gif_player(GtkWidget *widget) {
    GifPlayer *player = g_object_get_data(G_OBJECT(widget), "gif-player");
    if (player) {
        if (player->timeout_id) {
            g_source_remove(player->timeout_id);
        }
        if (player->animation) {
            g_object_unref(player->animation);
        }
        if (player->iter) {
            g_object_unref(player->iter);
        }
        g_free(player);
    }
}

GtkWidget* create_gif_player(const char *gif_path) {
    GifPlayer *player = g_new0(GifPlayer, 1);
    
    // Create picture widget
    player->picture = GTK_PICTURE(gtk_picture_new());
    
    // Enable scaling and filling
    gtk_widget_set_hexpand(GTK_WIDGET(player->picture), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(player->picture), TRUE);
    gtk_picture_set_can_shrink(player->picture, TRUE);
    
    // Set content fit to fill the entire space
    gtk_picture_set_content_fit(player->picture, GTK_CONTENT_FIT_COVER);
    
    // Load the GIF animation
    GError *error = NULL;
    player->animation = gdk_pixbuf_animation_new_from_file(gif_path, &error);
    
    if (error != NULL) {
        g_warning("Error loading GIF: %s", error->message);
        g_error_free(error);
        g_free(player);
        return NULL;
    }
    
    // Store original dimensions
    player->original_width = gdk_pixbuf_animation_get_width(player->animation);
    player->original_height = gdk_pixbuf_animation_get_height(player->animation);
    
    // Get animation iterator
    player->iter = gdk_pixbuf_animation_get_iter(player->animation, NULL);
    
    // Set initial frame
    GdkPixbuf *first_frame = gdk_pixbuf_animation_iter_get_pixbuf(player->iter);
    gtk_picture_set_pixbuf(player->picture, first_frame);
    
    // Connect size allocation signal for scaling
    g_signal_connect(player->picture, "resize", G_CALLBACK(on_size_allocate), player);
    
    // Store player data in widget
    g_object_set_data(G_OBJECT(player->picture), "gif-player", player);
    
    // Start animation
    int delay = gdk_pixbuf_animation_iter_get_delay_time(player->iter);
    player->timeout_id = g_timeout_add(delay, advance_animation, player);
    
    // Connect destroy signal to cleanup
    g_signal_connect_swapped(player->picture, "destroy", G_CALLBACK(cleanup_gif_player), player);
    
    return GTK_WIDGET(player->picture);
}

void stop_gif_animation(GtkWidget *widget) {
    GifPlayer *player = g_object_get_data(G_OBJECT(widget), "gif-player");
    if (player && player->timeout_id) {
        g_source_remove(player->timeout_id);
        player->timeout_id = 0;
    }
}

void resume_gif_animation(GtkWidget *widget) {
    GifPlayer *player = g_object_get_data(G_OBJECT(widget), "gif-player");
    if (player && !player->timeout_id) {
        int delay = gdk_pixbuf_animation_iter_get_delay_time(player->iter);
        player->timeout_id = g_timeout_add(delay, advance_animation, player);
    }
}


