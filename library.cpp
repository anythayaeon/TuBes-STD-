/*
 * File: library.cpp
 * Description: Library management functions
 */

#include "music.h"

// ----- LIBRARY MANAGEMENT -----

void printLibrary(Song lib[], int libCount) {
    printf("\n=== LIBRARY (%d songs) ===\n", libCount);
    printf("%-5s %-30s %-20s %-20s %-6s %-8s %-6s\n", 
           "ID", "Title", "Artist", "Album", "Year", "Plays", "Liked");
    printf("------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < libCount; i++) {
        printf("%-5d %-30s %-20s %-20s %-6d %-8d %s\n",
               lib[i].id,
               lib[i].title,
               lib[i].artist,
               lib[i].album,
               lib[i].year,
               lib[i].playCount,
               lib[i].isLiked ? "<3" : "  ");
    }
    printf("\n");
}

void printLibraryDetailed(Song lib[], int libCount) {
    printLibrary(lib, libCount);
}

void addSongToLibrary(Song lib[], int* libCount, Song* newSong, int role) {
    if (role != ROLE_ADMIN) {
        printf("[ERROR] Permission Denied! Only Admin can add songs.\n");
        return;
    }
    
    if (*libCount >= 100) {
        printf("[ERROR] Library is full!\n");
        return;
    }
    
    lib[*libCount] = *newSong;
    lib[*libCount].id = *libCount + 1;
    (*libCount)++;
    printf("[OK] Song added successfully! Total songs: %d\n", *libCount);
}

void editSongInLibrary(Song lib[], int libCount, int id, int role) {
    if (role != ROLE_ADMIN) {
        printf("[ERROR] Permission Denied! Only Admin can edit songs.\n");
        return;
    }
    
    Song* song = findSongById(lib, libCount, id);
    if (song == NULL) {
        printf("[ERROR] Song with ID %d not found!\n", id);
        return;
    }
    
    printf("\n=== EDIT SONG (ID: %d) ===\n", id);
    printf("Current: %s - %s (%s, %d)\n", song->title, song->artist, song->album, song->year);
    printf("\nEnter new details (press Enter to keep current value):\n");
    
    char buffer[100];
    getchar(); // consume newline
    
    printf("Title [%s]: ", song->title);
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(song->title, buffer);
    }
    
    printf("Artist [%s]: ", song->artist);
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(song->artist, buffer);
    }
    
    printf("Album [%s]: ", song->album);
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(song->album, buffer);
    }
    
    printf("Year [%d]: ", song->year);
    fgets(buffer, 100, stdin);
    if (buffer[0] != '\n') {
        song->year = atoi(buffer);
    }
    
    printf("[OK] Song updated successfully!\n");
}

void deleteSongFromLibrary(Song lib[], int* libCount, int id, int role) {
    if (role != ROLE_ADMIN) {
        printf("[ERROR] Permission Denied! Only Admin can delete songs.\n");
        return;
    }
    
    int found = -1;
    for (int i = 0; i < *libCount; i++) {
        if (lib[i].id == id) {
            found = i;
            break;
        }
    }
    
    if (found == -1) {
        printf("[ERROR] Song with ID %d not found!\n", id);
        return;
    }
    
    for (int i = found; i < *libCount - 1; i++) {
        lib[i] = lib[i + 1];
    }
    
    (*libCount)--;
    printf("[OK] Song deleted successfully! Total songs: %d\n", *libCount);
}

void likeSong(Song* libEntry, int* dummy) {
    if (libEntry != NULL) {
        libEntry->isLiked = 1;
        printf("[OK] Song liked: %s\n", libEntry->title);
    }
}

void unlikeSong(Song* libEntry, int* dummy) {
    if (libEntry != NULL) {
        libEntry->isLiked = 0;
        printf("[OK] Song unliked: %s\n", libEntry->title);
    }
}

Song* findSongById(Song lib[], int libCount, int id) {
    for (int i = 0; i < libCount; i++) {
        if (lib[i].id == id) {
            return &lib[i];
        }
    }
    return NULL;
}

// ----- SORTING -----

void mergeLibrary(Song lib[], Song temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;
    
    while (i <= mid && j <= right) {
        if (strcmp(lib[i].title, lib[j].title) <= 0) {
            temp[k++] = lib[i++];
        } else {
            temp[k++] = lib[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = lib[i++];
    }
    
    while (j <= right) {
        temp[k++] = lib[j++];
    }
    
    for (i = left; i <= right; i++) {
        lib[i] = temp[i];
    }
}

void mergeSortLibrary(Song lib[], Song temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortLibrary(lib, temp, left, mid);
        mergeSortLibrary(lib, temp, mid + 1, right);
        mergeLibrary(lib, temp, left, mid, right);
    }
}

// ----- SEARCH -----

int searchByTitle(Song lib[], int libCount, const char query[]) {
    for (int i = 0; i < libCount; i++) {
        if (strstr(lib[i].title, query) != NULL) {
            return i;
        }
    }
    return -1;
}

void searchByArtist(Song lib[], int libCount, const char query[], int results[], int* resultCount) {
    *resultCount = 0;
    for (int i = 0; i < libCount; i++) {
        if (strstr(lib[i].artist, query) != NULL) {
            results[*resultCount] = i;
            (*resultCount)++;
        }
    }
}

void printSearchResults(Song lib[], int indices[], int resultCount) {
    if (resultCount == 0) {
        printf("[ERROR] No songs found!\n");
        return;
    }
    
    printf("\n=== SEARCH RESULTS (%d found) ===\n", resultCount);
    printf("%-5s %-30s %-20s %-20s %-6s\n", "ID", "Title", "Artist", "Album", "Year");
    printf("------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < resultCount; i++) {
        int idx = indices[i];
        printf("%-5d %-30s %-20s %-20s %-6d\n",
               lib[idx].id,
               lib[idx].title,
               lib[idx].artist,
               lib[idx].album,
               lib[idx].year);
    }
    printf("\n");
}

// ----- LIKED SONGS -----

void printLikedSongs(Song lib[], int libCount) {
    int count = 0;
    printf("\n=== LIKED SONGS ===\n");
    printf("%-5s %-30s %-20s\n", "ID", "Title", "Artist");
    printf("------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < libCount; i++) {
        if (lib[i].isLiked) {
            printf("%-5d %-30s %-20s\n", lib[i].id, lib[i].title, lib[i].artist);
            count++;
        }
    }
    
    if (count == 0) {
        printf("No liked songs yet.\n");
    } else {
        printf("\nTotal: %d liked songs\n", count);
    }
    printf("\n");
}

void unlikeFromList(Song lib[], int libCount, int id) {
    Song* song = findSongById(lib, libCount, id);
    if (song != NULL) {
        int dummy = 0;
        unlikeSong(song, &dummy);
    } else {
        printf("[ERROR] Song not found!\n");
    }
}

// ----- RECOMMENDATIONS -----

void showMostPlayed(Song lib[], int libCount, int topN) {
    Song sorted[100];
    for (int i = 0; i < libCount; i++) {
        sorted[i] = lib[i];
    }
    
    for (int i = 0; i < libCount - 1; i++) {
        for (int j = 0; j < libCount - i - 1; j++) {
            if (sorted[j].playCount < sorted[j + 1].playCount) {
                Song temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    printf("\n=== MOST PLAYED (Top %d) ===\n", topN);
    printf("%-5s %-30s %-20s %-8s\n", "Rank", "Title", "Artist", "Plays");
    printf("------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < topN && i < libCount; i++) {
        printf("%-5d %-30s %-20s %-8d\n", i + 1, sorted[i].title, 
               sorted[i].artist, sorted[i].playCount);
    }
    printf("\n");
}

void showRecentlyPlayed(History* hist, int topN) {
    printf("\n=== RECENTLY PLAYED ===\n");
    
    if (hist->top == NULL) {
        printf("No history yet.\n\n");
        return;
    }
    
    int count = 0;
    addressHistory current = hist->top;
    
    while (current != NULL && count < topN) {
        printf("%d. %s - %s\n", count + 1, current->song->title, current->song->artist);
        current = current->next;
        count++;
    }
    printf("\n");
}
