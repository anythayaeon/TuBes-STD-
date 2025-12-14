/*
 * File: menus.cpp
 * Description: Menu handler functions - UPDATED WITH NEW FEATURES
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
        printf("4. [EDIT]   Edit Song (ADMIN ONLY)\n");
        printf("5. [SORT]   Sort Library A-Z\n");
        printf("6. [SEARCH] Search Songs\n");
        printf("7. [PLAY]   Now Playing\n");
        printf("8. [QUEUE]  Queue System\n");
        printf("9. [LOGOUT] Logout\n");
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
            printf("4. [EDIT] Edit Song\n");
            printf("5. [DEL]  Delete Song\n");
            printf("6. [LIKE] Like/Unlike Song\n");
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
            printf("Enter song ID to edit: ");
            scanf("%d", &id);
            editSongInLibrary(lib, *libCount, id, role);
            pauseScreen(&dummy);
        } else if (choice == 5 && role == ROLE_ADMIN) {
            int id;
            printf("Enter song ID to delete: ");
            scanf("%d", &id);
            deleteSongFromLibrary(lib, libCount, id, role);
        } else if (choice == 6 && role == ROLE_ADMIN) {
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

void handleNowPlayingMenu(Song** current, int* isPlaying, Queue* q, History* hist, 
                          Song lib[], int libCount, Playlist* contextPlaylist, addressPlaylist* currentNode) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        displayNowPlaying(*current, isPlaying);
        printf("\n1. [PLAY] Play/Pause\n");
        printf("2. [NEXT] Next Song\n");
        printf("3. [PREV] Previous Song (from History)\n");
        printf("4. [LIKE] Like/Unlike Current Song\n");
        printf("5. [VIEW] Show Queue\n");
        printf("6. [ADD]  Add Song to Queue\n");
        printf("7. [SELECT] Select Song from Library to Play\n");
        printf("0. [BACK] Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            playSong(*current, isPlaying);
        } else if (choice == 2) {
            nextSong(q, current, hist, contextPlaylist, currentNode);
        } else if (choice == 3) {
            previousSong(hist, current);
        } else if (choice == 4) {
            // Like/Unlike current song
            if (*current != NULL) {
                if ((*current)->isLiked) {
                    unlikeSong(*current, &dummy);
                } else {
                    likeSong(*current, &dummy);
                }
                pauseScreen(&dummy);
            } else {
                printf("[ERROR] No song is currently playing!\n");
                pauseScreen(&dummy);
            }
        } else if (choice == 5) {
            printQueue(q, &dummy);
            pauseScreen(&dummy);
        } else if (choice == 6) {
            int id;
            printf("Enter song ID to add to queue: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL) {
                enqueueSong(q, song);
                printf("[OK] Song added to queue!\n");
            } else {
                printf("[ERROR] Song not found!\n");
            }
        } else if (choice == 7) {
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
                
                // Reset context karena play dari library
                contextPlaylist->head = NULL;
                contextPlaylist->tail = NULL;
                contextPlaylist->songCount = 0;
                *currentNode = NULL;
                
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

void handlePlaylistMenu(Playlist playlists[], int* playlistCount, int* activePlaylistIndex, 
                        Song lib[], int libCount, Song** currentSong, 
                        int* isPlaying, Playlist* contextPlaylist, addressPlaylist* currentNode) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== MY PLAYLISTS ===\n");
        printf("Total Playlists: %d/20\n", *playlistCount);
        printf("\n");
        printf("1. [CREATE]  Create New Playlist\n");
        printf("2. [VIEW]    View a Playlist\n");
        printf("3. [ADD]     Add Song to Playlist\n");
        printf("4. [PLAY]    Play Song from Playlist\n");
        printf("5. [REMOVE]  Remove Song from Playlist\n");
        printf("6. [DELETE]  Delete a Playlist\n");
        printf("0. [BACK]    Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            // Create new playlist
            if (*playlistCount >= 20) {
                printf("[ERROR] Maximum playlists (20) reached!\n");
                pauseScreen(&dummy);
            } else {
                char name[100];
                printf("Enter playlist name: ");
                getchar();
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = 0;
                
                initPlaylist(&playlists[*playlistCount], name);
                (*playlistCount)++;
                printf("[OK] Playlist '%s' created! (Total: %d)\n", name, *playlistCount);
                pauseScreen(&dummy);
            }
        } else if (choice == 2) {
            // View a playlist
            if (*playlistCount == 0) {
                printf("[INFO] No playlists created yet!\n");
                pauseScreen(&dummy);
            } else {
                printf("\n=== SELECT PLAYLIST TO VIEW ===\n");
                for (int i = 0; i < *playlistCount; i++) {
                    printf("%d. %s (%d songs)\n", i + 1, playlists[i].name, playlists[i].songCount);
                }
                int idx;
                printf("Enter playlist number (1-%d): ", *playlistCount);
                scanf("%d", &idx);
                if (idx >= 1 && idx <= *playlistCount) {
                    printPlaylist(&playlists[idx - 1], &dummy);
                } else {
                    printf("[ERROR] Invalid playlist number!\n");
                }
                pauseScreen(&dummy);
            }
        } else if (choice == 3) {
            // Add song to playlist
            if (*playlistCount == 0) {
                printf("[INFO] No playlists created yet! Create one first.\n");
                pauseScreen(&dummy);
            } else {
                printf("\n=== SELECT PLAYLIST ===\n");
                for (int i = 0; i < *playlistCount; i++) {
                    printf("%d. %s (%d songs)\n", i + 1, playlists[i].name, playlists[i].songCount);
                }
                int idx;
                printf("Enter playlist number (1-%d): ", *playlistCount);
                scanf("%d", &idx);
                if (idx >= 1 && idx <= *playlistCount) {
                    printLibrary(lib, libCount);
                    int id;
                    printf("\nEnter song ID to add: ");
                    scanf("%d", &id);
                    Song* song = findSongById(lib, libCount, id);
                    if (song != NULL) {
                        addSongToPlaylist(&playlists[idx - 1], song);
                        pauseScreen(&dummy);
                    } else {
                        printf("[ERROR] Song not found!\n");
                        pauseScreen(&dummy);
                    }
                } else {
                    printf("[ERROR] Invalid playlist number!\n");
                    pauseScreen(&dummy);
                }
            }
        } else if (choice == 4) {
            // Play from playlist
            if (*playlistCount == 0) {
                printf("[INFO] No playlists created yet!\n");
                pauseScreen(&dummy);
            } else {
                printf("\n=== SELECT PLAYLIST TO PLAY FROM ===\n");
                for (int i = 0; i < *playlistCount; i++) {
                    printf("%d. %s (%d songs)\n", i + 1, playlists[i].name, playlists[i].songCount);
                }
                int idx;
                printf("Enter playlist number (1-%d): ", *playlistCount);
                scanf("%d", &idx);
                if (idx >= 1 && idx <= *playlistCount) {
                    if (playlists[idx - 1].head == NULL) {
                        printf("[ERROR] Playlist is empty!\n");
                        pauseScreen(&dummy);
                    } else {
                        printPlaylistWithNumbers(&playlists[idx - 1]);
                        int songNum;
                        printf("Enter song number to play (1-%d): ", playlists[idx - 1].songCount);
                        scanf("%d", &songNum);
                        Song* song = getPlaylistSongByIndex(&playlists[idx - 1], songNum);
                        if (song != NULL) {
                            *currentSong = song;
                            *isPlaying = 1;
                            song->playCount++;
                            
                            // Set context untuk next/prev
                            *contextPlaylist = playlists[idx - 1];
                            *currentNode = findPlaylistNodeBySong(&playlists[idx - 1], song);
                            
                            printf("[OK] Now playing from playlist '%s': %s - %s\n", 
                                   playlists[idx - 1].name, song->title, song->artist);
                            pauseScreen(&dummy);
                        } else {
                            printf("[ERROR] Invalid song number!\n");
                            pauseScreen(&dummy);
                        }
                    }
                } else {
                    printf("[ERROR] Invalid playlist number!\n");
                    pauseScreen(&dummy);
                }
            }
        } else if (choice == 5) {
            // Remove song from playlist
            if (*playlistCount == 0) {
                printf("[INFO] No playlists available!\n");
                pauseScreen(&dummy);
            } else {
                printf("\n=== SELECT PLAYLIST ===\n");
                for (int i = 0; i < *playlistCount; i++) {
                    printf("%d. %s (%d songs)\n", i + 1, playlists[i].name, playlists[i].songCount);
                }
                int idx;
                printf("Enter playlist number (1-%d): ", *playlistCount);
                scanf("%d", &idx);
                if (idx >= 1 && idx <= *playlistCount) {
                    printPlaylist(&playlists[idx - 1], &dummy);
                    int id;
                    printf("Enter song ID to remove: ");
                    scanf("%d", &id);
                    removeSongFromPlaylist(&playlists[idx - 1], id);
                } else {
                    printf("[ERROR] Invalid playlist number!\n");
                }
                pauseScreen(&dummy);
            }
        } else if (choice == 6) {
            // Delete playlist
            if (*playlistCount == 0) {
                printf("[INFO] No playlists available!\n");
                pauseScreen(&dummy);
            } else {
                printf("\n=== SELECT PLAYLIST TO DELETE ===\n");
                for (int i = 0; i < *playlistCount; i++) {
                    printf("%d. %s (%d songs)\n", i + 1, playlists[i].name, playlists[i].songCount);
                }
                int idx;
                printf("Enter playlist number (1-%d): ", *playlistCount);
                scanf("%d", &idx);
                if (idx >= 1 && idx <= *playlistCount) {
                    printf("[WARNING] Delete playlist '%s'? This cannot be undone!\n", 
                           playlists[idx - 1].name);
                    printf("Type 'YES' to confirm: ");
                    char confirm[10];
                    scanf("%s", confirm);
                    if (strcmp(confirm, "YES") == 0) {
                        deletePlaylist(&playlists[idx - 1], &dummy);
                        
                        // Shift remaining playlists
                        for (int i = idx - 1; i < *playlistCount - 1; i++) {
                            playlists[i] = playlists[i + 1];
                        }
                        (*playlistCount)--;
                        
                        printf("[OK] Playlist deleted! Remaining: %d\n", *playlistCount);
                    } else {
                        printf("[CANCELLED] Playlist not deleted.\n");
                    }
                } else {
                    printf("[ERROR] Invalid playlist number!\n");
                }
                pauseScreen(&dummy);
            }
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

void handleLikedMenu(Song lib[], int libCount, Song** currentSong, int* isPlaying) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== LIKED SONGS ===\n");
        printf("1. [VIEW]   View All Liked\n");
        printf("2. [PLAY]   Play Liked Song\n");
        printf("3. [UNLIKE] Unlike a Song\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printLikedSongs(lib, libCount);
            pauseScreen(&dummy);
        } else if (choice == 2) {
            // Play from liked songs
            printLikedSongs(lib, libCount);
            int id;
            printf("Enter song ID to play: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL && song->isLiked) {
                *currentSong = song;
                *isPlaying = 1;
                song->playCount++;
                printf("[OK] Now playing: %s - %s\n", song->title, song->artist);
                printf("[INFO] Go to 'Now Playing' menu to control playback.\n");
                pauseScreen(&dummy);
            } else {
                printf("[ERROR] Song not found in liked songs!\n");
                pauseScreen(&dummy);
            }
        } else if (choice == 3) {
            int id;
            printf("Enter song ID to unlike: ");
            scanf("%d", &id);
            unlikeFromList(lib, libCount, id);
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void handleRecommendationMenu(Song lib[], int libCount, History* hist, Song** currentSong, int* isPlaying) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== RECOMMENDATIONS ===\n");
        printf("1. [MOST]   Most Played (Top 10)\n");
        printf("2. [RECENT] Recently Played\n");
        printf("3. [PLAY]   Play from Recommendations\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            showMostPlayed(lib, libCount, 10);
            pauseScreen(&dummy);
        } else if (choice == 2) {
            showRecentlyPlayed(hist, 10);
            pauseScreen(&dummy);
        } else if (choice == 3) {
            // Play from recommendations
            showMostPlayed(lib, libCount, 10);
            int id;
            printf("Enter song ID to play: ");
            scanf("%d", &id);
            Song* song = findSongById(lib, libCount, id);
            if (song != NULL) {
                *currentSong = song;
                *isPlaying = 1;
                song->playCount++;
                printf("[OK] Now playing: %s - %s\n", song->title, song->artist);
                printf("[INFO] Go to 'Now Playing' menu to control playback.\n");
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

void handleQueueMenu(Queue* q) {
    int choice = 0;
    int dummy = 0;
    
    while (true) {
        printf("\n=== QUEUE SYSTEM ===\n");
        printQueue(q, &dummy);
        printf("1. [VIEW]   View Queue\n");
        printf("2. [REMOVE] Remove Next\n");
        printf("3. [CLEAR]  Clear Queue\n");
        printf("0. [BACK]   Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printQueue(q, &dummy);
            pauseScreen(&dummy);
        } else if (choice == 2) {
            Song* removed = NULL;
            dequeueSong(q, &removed);
            if (removed != NULL) {
                printf("[OK] Removed: %s\n", removed->title);
            }
        } else if (choice == 3) {
            clearQueue(q, &dummy);
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
