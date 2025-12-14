/*
 * File: queue.cpp
 * Description: Queue and History (Stack) management functions
 */

#include "music.h"

// ----- NOW PLAYING (QUEUE + STACK) -----

void displayNowPlaying(Song* current, int* isPlaying) {
    printf("\n");
    printf("========================================\n");
    printf("          NOW PLAYING\n");
    printf("========================================\n");
    
    if (current == NULL) {
        printf("No song is playing.\n");
    } else {
        printf(">> %s - %s\n", current->title, current->artist);
        printf("Album: %s | Year: %d\n", current->album, current->year);
        printf("Plays: %d | Status: %s\n", current->playCount, *isPlaying ? "[PLAYING]" : "[PAUSED]");
    }
    
    printf("========================================\n");
}

void playSong(Song* current, int* isPlaying) {
    if (current == NULL) {
        printf("[ERROR] No song to play!\n");
        return;
    }
    
    *isPlaying = !(*isPlaying);
    if (*isPlaying) {
        current->playCount++;
        printf("[PLAY] Playing: %s\n", current->title);
    } else {
        printf("[PAUSE] Paused: %s\n", current->title);
    }
}

void enqueueSong(Queue* q, Song* s) {
    addressQueue newNode = new elmQueue;
    newNode->song = s;
    newNode->next = NULL;
    
    if (q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

void dequeueSong(Queue* q, Song** output) {
    if (q->head == NULL) {
        *output = NULL;
        return;
    }
    
    addressQueue temp = q->head;
    *output = temp->song;
    q->head = q->head->next;
    
    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    delete temp;
}

void pushHistory(History* hist, Song* s) {
    addressHistory newNode = new elmHistory;
    newNode->song = s;
    newNode->next = hist->top;
    hist->top = newNode;
}

Song* popHistory(History* hist) {
    if (hist->top == NULL) {
        return NULL;
    }
    
    addressHistory temp = hist->top;
    Song* s = temp->song;
    hist->top = hist->top->next;
    delete temp;
    
    return s;
}

void nextSong(Queue* q, Song** current, History* hist, Playlist* contextPlaylist, addressPlaylist* currentNode) {
    // Save current to history
    if (*current != NULL) {
        pushHistory(hist, *current);
    }
    
    // Check if we're in playlist context
    if (contextPlaylist != NULL && contextPlaylist->head != NULL && *currentNode != NULL) {
        // Next in playlist
        if ((*currentNode)->next != NULL) {
            *currentNode = (*currentNode)->next;
            *current = (*currentNode)->song;
            (*current)->playCount++;
            printf("[NEXT] Next in playlist: %s\n", (*current)->title);
            return;
        } else {
            printf("[INFO] End of playlist reached.\n");
            // Fallback to queue
        }
    }
    
    // Try queue
    Song* nextSongPtr = NULL;
    dequeueSong(q, &nextSongPtr);
    
    if (nextSongPtr != NULL) {
        *current = nextSongPtr;
        (*current)->playCount++;
        printf("[NEXT] Next from queue: %s\n", (*current)->title);
    } else {
        printf("[ERROR] No next song available!\n");
    }
}

void previousSong(History* hist, Song** current) {
    Song* prevSongPtr = popHistory(hist);
    
    if (prevSongPtr != NULL) {
        *current = prevSongPtr;
        printf("[PREV] Previous: %s\n", (*current)->title);
    } else {
        printf("[ERROR] No previous song in history!\n");
    }
}

void printQueue(Queue* q, int* dummy) {
    if (q->head == NULL) {
        printf("[INFO] Queue is empty!\n");
        return;
    }
    
    printf("\n=== QUEUE ===\n");
    int pos = 1;
    addressQueue temp = q->head;
    
    while (temp != NULL) {
        printf("%d. %s - %s\n", pos, temp->song->title, temp->song->artist);
        temp = temp->next;
        pos++;
    }
    printf("\n");
}

void clearQueue(Queue* q, int* dummy) {
    while (q->head != NULL) {
        addressQueue temp = q->head;
        q->head = q->head->next;
        delete temp;
    }
    q->tail = NULL;
    printf("[OK] Queue cleared!\n");
}
