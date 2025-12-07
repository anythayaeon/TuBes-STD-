/*
 * File: main.cpp
 * Description: Main program untuk Music Player dengan Role-Based Access System
 * Author: AI Generated
 * Constraints: Procedural, No OOP, Role-Based Access (int-based)
 * Date: December 7, 2025
 */

#include "music.h"

int main() {
    // ----- INITIALIZATION -----
    Song library[100];
    int libCount = 0;
    int role = 0;
    int dummy = 0;
    
    // Generate 100 dummy songs
    generateDummyData(library, &libCount);
    
    // Queue & History
    QueueNode* queueFront = NULL;
    QueueNode* queueRear = NULL;
    HistoryNode* historyTop = NULL;
    
    // Current playing song
    Song* currentSong = NULL;
    int isPlaying = 0;
    
    // Playlist
    Playlist myPlaylist;
    initPlaylist(&myPlaylist, "My Playlist");
    
    // ----- MAIN LOOP -----
    bool running = true;
    
    while (running) {
        // Login
        clearScreen(&dummy);
        role = loginSystem(&role);
        
        if (role == 0) {
            printf("\nThank you for using Music Player!\n");
            break;
        }
        
        // Main menu loop after login
        bool loggedIn = true;
        while (loggedIn) {
            clearScreen(&dummy);
            displayMainMenu(role, &dummy);
            
            int choice = 0;
            printf("Choice: ");
            scanf("%d", &choice);
            
            if (choice == 0) {
                printf("\nThank you for using Music Player!\n");
                running = false;
                loggedIn = false;
            } else if (choice == 8) {
                printf("[LOGOUT] Logging out...\n");
                loggedIn = false;
            } else if (choice == 1) {
                // View Library
                if (role == ROLE_ADMIN) {
                    handleLibraryMenu(library, &libCount, role);
                } else {
                    printLibrary(library, libCount);
                    pauseScreen(&dummy);
                }
            } else if (choice == 2) {
                if (role == ROLE_ADMIN) {
                    // Admin: Add New Song
                    Song newSong;
                    printf("Enter song title: ");
                    getchar();
                    fgets(newSong.title, 100, stdin);
                    newSong.title[strcspn(newSong.title, "\n")] = 0;
                    
                    printf("Enter artist: ");
                    fgets(newSong.artist, 100, stdin);
                    newSong.artist[strcspn(newSong.artist, "\n")] = 0;
                    
                    printf("Enter album: ");
                    fgets(newSong.album, 100, stdin);
                    newSong.album[strcspn(newSong.album, "\n")] = 0;
                    
                    printf("Enter year: ");
                    scanf("%d", &newSong.year);
                    
                    newSong.playCount = 0;
                    newSong.isLiked = 0;
                    
                    addSongToLibrary(library, &libCount, &newSong, role);
                    pauseScreen(&dummy);
                } else {
                    // User: Now Playing
                    handleNowPlayingMenu(&currentSong, &isPlaying, &queueFront, 
                                        &queueRear, &historyTop, library, libCount);
                }
            } else if (choice == 3) {
                if (role == ROLE_ADMIN) {
                    // Admin: Delete Song
                    int id;
                    printf("Enter song ID to delete: ");
                    scanf("%d", &id);
                    deleteSongFromLibrary(library, &libCount, id, role);
                    pauseScreen(&dummy);
                } else {
                    // User: Queue System
                    handleQueueMenu(&queueFront, &queueRear);
                }
            } else if (choice == 4) {
                if (role == ROLE_ADMIN) {
                    // Admin: Sort Library
                    Song temp[100];
                    mergeSortLibrary(library, temp, 0, libCount - 1);
                    printf("[OK] Library sorted A-Z!\n");
                    printLibrary(library, libCount);
                    pauseScreen(&dummy);
                } else {
                    // User: My Playlists
                    handlePlaylistMenu(&myPlaylist, library, libCount);
                }
            } else if (choice == 5) {
                if (role == ROLE_ADMIN) {
                    // Admin: Search Songs
                    handleSearchMenu(library, libCount);
                } else {
                    // User: Liked Songs
                    handleLikedMenu(library, libCount);
                }
            } else if (choice == 6) {
                if (role == ROLE_ADMIN) {
                    // Admin: Now Playing
                    handleNowPlayingMenu(&currentSong, &isPlaying, &queueFront, 
                                        &queueRear, &historyTop, library, libCount);
                } else {
                    // User: Search Songs
                    handleSearchMenu(library, libCount);
                }
            } else if (choice == 7) {
                if (role == ROLE_ADMIN) {
                    // Admin: Queue System
                    handleQueueMenu(&queueFront, &queueRear);
                } else {
                    // User: Recommendations
                    handleRecommendationMenu(library, libCount, historyTop);
                }
            } else {
                printf("[ERROR] Invalid choice!\n");
                pauseScreen(&dummy);
            }
        }
    }
    
    // ----- CLEANUP -----
    clearQueue(&queueFront, &queueRear, &dummy);
    deletePlaylist(&myPlaylist, &dummy);
    
    while (historyTop != NULL) {
        Song* temp = popHistory(&historyTop);
    }
    
    return 0;
}
