/*
 * File: menus.cpp
 * Description: Menu handler functions
 */

#include "music.h"

// ----- MENU HANDLERS -----

void displayMainMenu(int role, int* dummy) {
    printf("\n");
    if (role == ROLE_ADMIN) {
        printf("========================================\n");
        printf("           ADMIN MENU\n");
        printf("========================================\n");
        printf("1. [VIEW]   View Library\n");
        printf("2. [ADD]    Add New Song (ADMIN ONLY)\n");
        printf("3. [DELETE] Delete Song (ADMIN ONLY)\n");
        printf("4. [SORT]   Sort Library A-Z\n");
        printf("5. [SEARCH] Search Songs\n");
        printf("6. [PLAY]   Now Playing\n");
        printf("7. [QUEUE]  Queue System\n");
        printf("8. [LOGOUT] Logout\n");
        printf("0. [EXIT]   Exit\n");
        printf("========================================\n");
    } else {
        printf("========================================\n");
        printf("            USER MENU\n");
        printf("========================================\n");
        printf("1. [VIEW]  View Library (Read-Only)\n");
        printf("2. [PLAY]  Now Playing\n");
        printf("3. [QUEUE] Queue System\n");
        printf("4. [LIST]  My Playlists\n");
        printf("5. [LIKED] Liked Songs\n");
        printf("6. [SEARCH] Search Songs\n");
        printf("7. [RECOM] Recommendations\n");
        printf("8. [LOGOUT] Logout\n");
        printf("0. [EXIT]  Exit\n");
        printf("========================================\n");
    }
}

void handleLibraryMenu(Song lib[], int* libCount, int role) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n");
        if (role == ROLE_ADMIN) {
            printf("=== LIBRARY (ADMIN) ===\n");
            printf("1. [VIEW] View All Songs\n");
            printf("2. [SORT] Sort Library A-Z\n");
            printf("3. [ADD]  Add New Song\n");
            printf("4. [DEL]  Delete Song\n");
            printf("5. [LIKE] Like/Unlike Song\n");
            printf("0. [BACK] Back\n");
        } else {
            printf("=== LIBRARY (USER) ===\n");
            printf("1. [VIEW] View All Songs (Read-Only)\n");
            printf("2. [LIKE] Like/Unlike Song\n");
            printf("0. [BACK] Back\n");
        }
        
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printLibrary(lib, *libCount);
            pauseScreen(&dummy);
        } else if (choice == 2 && role == ROLE_ADMIN) {
            Song temp[100];
            mergeSortLibrary(lib, temp, 0, *libCount - 1);
            printf("[OK] Library sorted A-Z!\n");
            printLibrary(lib, *libCount);
            pauseScreen(&dummy);
        } else if (choice == 2 && role == ROLE_USER) {
            int id;
            printf("Enter song ID to like/unlike: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, *libCount, id);
            if (song != NULL) {
                if (song->isLiked) {
                    unlikeSong(song, &dummy);
                } else {
                    likeSong(song, &dummy);
                }
            } else {
                printf("[ERROR] Song not found!\n");
            }
        } else if (choice == 3 && role == ROLE_ADMIN) {
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
            
            addSongToLibrary(lib, libCount, &newSong, role);
        } else if (choice == 4 && role == ROLE_ADMIN) {
            int id;
            printf("Enter song ID to delete: ");
            scanf("%d", &id);
            deleteSongFromLibrary(lib, libCount, id, role);
        } else if (choice == 5 && role == ROLE_ADMIN) {
            int id;
            printf("Enter song ID to like/unlike: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, *libCount, id);
            if (song != NULL) {
                if (song->isLiked) {
                    unlikeSong(song, &dummy);
                } else {
                    likeSong(song, &dummy);
                }
            } else {
                printf("[ERROR] Song not found!\n");
            }
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleNowPlayingMenu(Song** current, int* isPlaying, QueueNode** front, 
                          QueueNode** rear, HistoryNode** histTop, Song lib[], int libCount) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        displayNowPlaying(*current, isPlaying);
        printf("\n1. [PLAY] Play/Pause\n");
        printf("2. [NEXT] Next Song (from Queue)\n");
        printf("3. [PREV] Previous Song (from History)\n");
        printf("4. [VIEW] Show Queue\n");
        printf("5. [ADD]  Add Song to Queue\n");
        printf("6. [SELECT] Select Song from Library to Play\n");
        printf("0. [BACK] Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            playSong(*current, isPlaying);
        } else if (choice == 2) {
            nextSong(front, rear, current, histTop);
        } else if (choice == 3) {
            previousSong(histTop, current);
        } else if (choice == 4) {
            printQueue(*front, &dummy);
            pauseScreen(&dummy);
        } else if (choice == 5) {
            int id;
            printf("Enter song ID to add to queue: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL) {
                enqueueSong(front, rear, song);
                printf("[OK] Song added to queue!\n");
            } else {
                printf("[ERROR] Song not found!\n");
            }
        } else if (choice == 6) {
            // Show library first
            printLibrary(lib, libCount);
            printf("\n");
            
            int id;
            printf("Enter song ID to play: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL) {
                *current = song;
                *isPlaying = 1;
                song->playCount++;
                printf("[OK] Now playing: %s - %s\n", song->title, song->artist);
                pauseScreen(&dummy);
            } else {
                printf("[ERROR] Song not found!\n");
                pauseScreen(&dummy);
            }
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handlePlaylistMenu(Playlist* pl, Song lib[], int libCount) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== MY PLAYLISTS ===\n");
        printf("1. [CREATE] Create New Playlist\n");
        printf("2. [VIEW]   View Playlist\n");
        printf("3. [ADD]    Add Song to Playlist\n");
        printf("4. [REMOVE] Remove Song from Playlist\n");
        printf("5. [DELETE] Delete Playlist\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            char name[100];
            printf("Enter playlist name: ");
            getchar();
            fgets(name, 100, stdin);
            name[strcspn(name, "\n")] = 0;
            initPlaylist(pl, name);
            printf("[OK] Playlist '%s' created!\n", name);
        } else if (choice == 2) {
            printPlaylist(pl, &dummy);
            pauseScreen(&dummy);
        } else if (choice == 3) {
            int id;
            printf("Enter song ID to add: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL) {
                addSongToPlaylist(pl, song);
            } else {
                printf("[ERROR] Song not found!\n");
            }
        } else if (choice == 4) {
            int id;
            printf("Enter song ID to remove: ");
            scanf("%d", &id);
            removeSongFromPlaylist(pl, id);
        } else if (choice == 5) {
            deletePlaylist(pl, &dummy);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleSearchMenu(Song lib[], int libCount) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== SEARCH ===\n");
        printf("1. [TITLE]  Search by Title\n");
        printf("2. [ARTIST] Search by Artist\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            char query[100];
            printf("Enter title: ");
            getchar();
            fgets(query, 100, stdin);
            query[strcspn(query, "\n")] = 0;
            
            int idx = searchByTitle(lib, libCount, query);
            if (idx != -1) {
                int indices[1] = {idx};
                printSearchResults(lib, indices, 1);
            } else {
                printf("[ERROR] Song not found!\n");
            }
            pauseScreen(&dummy);
        } else if (choice == 2) {
            char query[100];
            printf("Enter artist name: ");
            getchar();
            fgets(query, 100, stdin);
            query[strcspn(query, "\n")] = 0;
            
            int results[100];
            int resultCount = 0;
            searchByArtist(lib, libCount, query, results, &resultCount);
            printSearchResults(lib, results, resultCount);
            pauseScreen(&dummy);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleLikedMenu(Song lib[], int libCount) {
    int choice = 0;
    
    while (true) {
        printf("\n=== LIKED SONGS ===\n");
        printf("1. [VIEW]   View All Liked\n");
        printf("2. [UNLIKE] Unlike a Song\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printLikedSongs(lib, libCount);
            int dummy = 0;
            pauseScreen(&dummy);
        } else if (choice == 2) {
            int id;
            printf("Enter song ID to unlike: ");
            scanf("%d", &id);
            unlikeFromList(lib, libCount, id);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleRecommendationMenu(Song lib[], int libCount, HistoryNode* histTop) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== RECOMMENDATIONS ===\n");
        printf("1. [MOST] Most Played (Top 10)\n");
        printf("2. [RECENT] Recently Played\n");
        printf("0. [BACK] Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            showMostPlayed(lib, libCount, 10);
            pauseScreen(&dummy);
        } else if (choice == 2) {
            showRecentlyPlayed(histTop, 10);
            pauseScreen(&dummy);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleQueueMenu(QueueNode** front, QueueNode** rear) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== QUEUE SYSTEM ===\n");
        printQueue(*front, &dummy);
        printf("1. [VIEW]   View Queue\n");
        printf("2. [REMOVE] Remove Next\n");
        printf("3. [CLEAR]  Clear Queue\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printQueue(*front, &dummy);
            pauseScreen(&dummy);
        } else if (choice == 2) {
            Song* removed = NULL;
            dequeueSong(front, rear, &removed);
            if (removed != NULL) {
                printf("[OK] Removed: %s\n", removed->title);
            }
        } else if (choice == 3) {
            clearQueue(front, rear, &dummy);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

// ----- UTILITY -----

void clearScreen(int* dummy) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen(int* dummy) {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}
