/*
 * File: playlist.cpp
 * Description: Playlist management functions
 */

#include "music.h"

// ----- PLAYLIST -----

void initPlaylist(Playlist* pl, const char name[]) {
    strcpy(pl->name, name);
    pl->head = NULL;
    pl->tail = NULL;
    pl->songCount = 0;
}

void addSongToPlaylist(Playlist* pl, Song* s) {
    PlaylistNode* newNode = new PlaylistNode;
    newNode->song = s;
    newNode->next = NULL;
    newNode->prev = NULL;
    
    if (pl->head == NULL) {
        pl->head = newNode;
        pl->tail = newNode;
    } else {
        newNode->prev = pl->tail;
        pl->tail->next = newNode;
        pl->tail = newNode;
    }
    
    pl->songCount++;
    printf("[OK] Song added to playlist '%s'\n", pl->name);
}

void removeSongFromPlaylist(Playlist* pl, int songId) {
    PlaylistNode* current = pl->head;
    
    while (current != NULL && current->song->id != songId) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("[ERROR] Song not found in playlist!\n");
        return;
    }
    
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        pl->head = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        pl->tail = current->prev;
    }
    
    delete current;
    pl->songCount--;
    printf("[OK] Song removed from playlist!\n");
}

void printPlaylist(Playlist* pl, int* dummy) {
    if (pl->head == NULL) {
        printf("[INFO] Playlist '%s' is empty!\n", pl->name);
        return;
    }
    
    printf("\n=== PLAYLIST: %s (%d songs) ===\n", pl->name, pl->songCount);
    int pos = 1;
    PlaylistNode* current = pl->head;
    
    while (current != NULL) {
        printf("%d. [ID:%d] %s - %s\n", pos, current->song->id, 
               current->song->title, current->song->artist);
        current = current->next;
        pos++;
    }
    printf("\n");
}

void deletePlaylist(Playlist* pl, int* dummy) {
    PlaylistNode* current = pl->head;
    
    while (current != NULL) {
        PlaylistNode* temp = current;
        current = current->next;
        delete temp;
    }
    
    pl->head = NULL;
    pl->tail = NULL;
    pl->songCount = 0;
    printf("[OK] Playlist '%s' deleted!\n", pl->name);
}
