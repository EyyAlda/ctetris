#include <gtk-4.0/gtk/gtk.h>
#include <gdk-pixbuf-2.0/gdk-pixbuf/gdk-pixbuf.h>
#include "../include/background_gif.h"

typedef struct {
    GdkPixbufAnimation *animation;
    GdkPixbufAnimationIter *iter;
    guint timer_id;
} GifData;

static gboolean on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer user_data) {
    GifData *gif_data = (GifData *)user_data;
    GdkPixbuf *pixbuf = gdk_pixbuf_animation_iter_get_pixbuf(gif_data->iter);

    if (pixbuf) {

        int pixbuf_width = gdk_pixbuf_get_width(pixbuf);
        int pixbuf_height = gdk_pixbuf_get_height(pixbuf);

        double scale_width = (double)width / pixbuf_width;
        double scale_height = (double)height / pixbuf_height;
        double scale_factor = scale_width < scale_height ? scale_width : scale_height;

        int new_width = pixbuf_width * scale_factor;
        int new_height = pixbuf_height * scale_factor;

        int x_offset = (width - new_width) / 2;
        int y_offset = (height -new_height) / 2;

        gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
        cairo_scale(cr, scale_factor, scale_factor);
        cairo_paint(cr);
    }
    return FALSE;
}

static gboolean update_frame(gpointer user_data) {
    GtkWidget *drawing_area = GTK_WIDGET(user_data);
    GifData *gif_data = g_object_get_data(G_OBJECT(drawing_area), "gif-data");

    if (gdk_pixbuf_animation_iter_advance(gif_data->iter, NULL)) {
        gtk_widget_queue_draw(drawing_area);
    }
    return G_SOURCE_CONTINUE;
}

static void on_resize(GtkWidget *widget, int width, int height, gpointer user_data) {
    int new_width = width;
    int new_height = (int)((double)width / 16.0 * 9.0);

    // Ensure the new height doesn't exceed window height
    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    if (new_height > allocation.height) {
        new_height = allocation.height;
        new_width = (int)((double)new_height * 16.0 / 9.0);
    }

    gtk_widget_set_size_request(widget, new_width, new_height);
}

GtkWidget* create_gif_animated_background(GtkWidget *window, const char *background_gif_path, int window_width, int window_height) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_drawing_area_set_content_width(GTK_DRAWING_AREA(drawing_area), window_width);
    gtk_drawing_area_set_content_height(GTK_DRAWING_AREA(drawing_area), window_height);

    GifData *gif_data = g_new0(GifData, 1);
    gif_data->animation = gdk_pixbuf_animation_new_from_file(background_gif_path, NULL);
    gif_data->iter = gdk_pixbuf_animation_get_iter(gif_data->animation, NULL);
    g_object_set_data_full(G_OBJECT(drawing_area), "gif-data", gif_data, (GDestroyNotify)g_free);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(on_draw), gif_data);
    
    g_signal_connect(window, "on-resize", G_CALLBACK(on_resize), drawing_area);
    gif_data->timer_id = g_timeout_add(100, update_frame, drawing_area);

    return drawing_area;
}
