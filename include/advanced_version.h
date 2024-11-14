#ifndef ADVANCED_VERSION_H
#define ADVANCED_VERSION_H

#include <gtk-4.0/gtk/gtk.h>

// Structure to hold texture atlas information
typedef struct {
    cairo_surface_t* surface;
    cairo_pattern_t* pattern;
    int block_size;
    int atlas_width;
    int atlas_height;
} TextureAtlas;


typedef struct {
    cairo_t* cr;
    TextureAtlas* atlas;
    const char (*field)[10];  // Pointer to 2D array [20][10]
} RenderState;

GtkWidget* create_game_screen_advanced();

TextureAtlas* create_texture_atlas(GdkPaintable** icons, int initial_block_size);

RenderState* create_render_state(const char field[20][10]);

GtkWidget *get_game_area();

void cleanup_texture_atlas(TextureAtlas* atlas);

void cleanup_render_state(RenderState* state);

void render_field_batch(RenderState* state);

int update_window_size(int width, int height);

#endif
