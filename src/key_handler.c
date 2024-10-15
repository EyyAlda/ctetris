#include "../include/key_handler.h"
#include <pthread.h>
#include <gdk/gdk.h>

static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data){
    Tetromino *tetrominoPtr = (Tetromino *)data;
    
    pthread_mutex_lock(&tetrominoPtr->lock);

    switch (event->keyval)

}
