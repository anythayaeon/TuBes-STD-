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

void enqueueSong(QueueNode** front, QueueNode** rear, Song* s) {
    QueueNode* newNode = new QueueNode;
    newNode->song = s;
    newNode->next = NULL;
    
    if (*rear == NULL) {
        *front = newNode;
        *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

void dequeueSong(QueueNode** front, QueueNode** rear, Song** output) {
    if (*front == NULL) {
        *output = NULL;
        return;
    }
    
    QueueNode* temp = *front;
    *output = temp->song;
    *front = (*front)->next;
    
    if (*front == NULL) {
        *rear = NULL;
    }
    
    delete temp;
}

void pushHistory(HistoryNode** histTop, Song* s) {
    HistoryNode* newNode = new HistoryNode;
    newNode->song = s;
    newNode->next = *histTop;
    *histTop = newNode;
}

Song* popHistory(HistoryNode** histTop) {
    if (*histTop == NULL) {
        return NULL;
    }
    
    HistoryNode* temp = *histTop;
    Song* s = temp->song;
    *histTop = (*histTop)->next;
    delete temp;
    
    return s;
}

void nextSong(QueueNode** front, QueueNode** rear, Song** current, HistoryNode** histTop) {
    if (*current != NULL) {
        pushHistory(histTop, *current);
    }
    
    Song* nextSongPtr = NULL;
    dequeueSong(front, rear, &nextSongPtr);
    
    if (nextSongPtr != NULL) {
        *current = nextSongPtr;
        (*current)->playCount++;
        printf("[NEXT] Next: %s\n", (*current)->title);
    } else {
        printf("[ERROR] Queue is empty!\n");
    }
}

void previousSong(HistoryNode** histTop, Song** current) {
    Song* prevSongPtr = popHistory(histTop);
    
    if (prevSongPtr != NULL) {
        *current = prevSongPtr;
        printf("[PREV] Previous: %s\n", (*current)->title);
    } else {
        printf("[ERROR] No previous song in history!\n");
    }
}

void printQueue(QueueNode* front, int* dummy) {
    if (front == NULL) {
        printf("[INFO] Queue is empty!\n");
        return;
    }
    
    printf("\n=== QUEUE ===\n");
    int pos = 1;
    QueueNode* temp = front;
    
    while (temp != NULL) {
        printf("%d. %s - %s\n", pos, temp->song->title, temp->song->artist);
        temp = temp->next;
        pos++;
    }
    printf("\n");
}

void clearQueue(QueueNode** front, QueueNode** rear, int* dummy) {
    while (*front != NULL) {
        QueueNode* temp = *front;
        *front = (*front)->next;
        delete temp;
    }
    *rear = NULL;
    printf("[OK] Queue cleared!\n");
}
