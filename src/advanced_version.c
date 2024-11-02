#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include "../include/game.h"
#include "../include/ui.h"
#include "../include/get_files_path.h"
#include "../include/advanced_version.h"
#define GRID_WIDTH 10
#define GRID_HEIGHT 20

GtkWidget *game_area;

TextureAtlas* create_texture_atlas(GdkPaintable** icons, int block_size) {
    TextureAtlas* atlas = g_malloc(sizeof(TextureAtlas));
    atlas->block_size = block_size;
    atlas->atlas_width = block_size * 4;   // 4 icons per row
    atlas->atlas_height = block_size * 2;  // 2 rows for 8 icons
    
    atlas->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 
                                              atlas->atlas_width, 
                                              atlas->atlas_height);
    cairo_t* cr = cairo_create(atlas->surface);
    
    // Draw all icons into the atlas
    for (int i = 0; i < 8; i++) {
        int x = (i % 4) * block_size;
        int y = (i / 4) * block_size;
        
        GtkSnapshot* snapshot = gtk_snapshot_new();
        gdk_paintable_snapshot(GDK_PAINTABLE(icons[i]), snapshot, 
                             block_size, block_size);
        GskRenderNode* node = gtk_snapshot_free_to_node(snapshot);
        
        cairo_save(cr);
        cairo_translate(cr, x, y);
        gsk_render_node_draw(node, cr);
        cairo_restore(cr);
        
        gsk_render_node_unref(node);
    }
    
    cairo_destroy(cr);
    cairo_surface_flush(atlas->surface);
    
    atlas->pattern = cairo_pattern_create_for_surface(atlas->surface);
    cairo_pattern_set_extend(atlas->pattern, CAIRO_EXTEND_REPEAT);
    
    return atlas;
}

RenderState* create_render_state(const char field[20][10]) {
    RenderState* state = g_malloc(sizeof(RenderState));
    state->field = field;
    return state;
}

void render_field_batch(RenderState* state) {
    cairo_save(state->cr);
    
    const int bs = state->atlas->block_size;
    
    // Draw each tile individually
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            char tile = state->field[y][x];
            int atlas_idx;
            
            // Map tile to atlas index
            switch(tile) {
                case 'I': case '4': atlas_idx = 0; break;
                case 'J': case '2': atlas_idx = 3; break;
                case 'L': case '1': atlas_idx = 2; break;
                case '0':          atlas_idx = 1; break;
                case 'O': case '3': atlas_idx = 4; break;
                case 'S': case '5': atlas_idx = 5; break;
                case 'T': case '7': atlas_idx = 6; break;
                case 'Z': case '6': atlas_idx = 7; break;
                default:           atlas_idx = 1; break;
            }
            
            // Calculate source coordinates in atlas
            int atlas_x = (atlas_idx % 4) * bs;
            int atlas_y = (atlas_idx / 4) * bs;
            
            // Draw the tile
            cairo_save(state->cr);
            
            // Set up the pattern transform
            cairo_matrix_t matrix;
            cairo_matrix_init_identity(&matrix);
            cairo_matrix_translate(&matrix, -atlas_x, -atlas_y);
            cairo_pattern_set_matrix(state->atlas->pattern, &matrix);
            
            // Move to the correct position and draw
            cairo_translate(state->cr, x * bs, y * bs);
            cairo_set_source(state->cr, state->atlas->pattern);
            cairo_rectangle(state->cr, 0, 0, bs, bs);
            cairo_fill(state->cr);
            
            cairo_restore(state->cr);
        }
    }
    
    cairo_restore(state->cr);
}

// Cleanup functions remain the same
void cleanup_texture_atlas(TextureAtlas* atlas) {
    if (atlas) {
        cairo_pattern_destroy(atlas->pattern);
        cairo_surface_destroy(atlas->surface);
        g_free(atlas);
    }
}

void cleanup_render_state(RenderState* state) {
    if (state) {
        g_free(state);
    }
}



int update_window_size(int width, int height) {
    int block_size_x = width / GRID_WIDTH;  // Calculate block size based on the new width
    int block_size_y = height / GRID_HEIGHT;  // Calculate block size based on the new height
    
    // Use the minimum block size to maintain square blocks
    int block_size = MIN(block_size_x, block_size_y);
    return block_size;
}


GtkWidget* create_game_screen_advanced(){
    //GtkWidget *game_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    game_area = gtk_drawing_area_new();
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(game_area), show_advanced, NULL, NULL);
    printf("DEBUG: create game screen\n");

    //gtk_box_append(GTK_BOX(game_box), area);
    return game_area;
}
