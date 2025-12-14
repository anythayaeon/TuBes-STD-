/*
 * File: music.h
 * Description: Header file untuk Music Player
 */

#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

// ----- ROLE CONSTANTS -----
#define ROLE_ADMIN 1
#define ROLE_USER 2

// ----- STRUCT DEFINITIONS (CLASSIC DATA STRUCTURE STYLE) -----

// =============================================================================
// SONG LIBRARY STRUCTURE (Single Linked List)
// =============================================================================

// InfoType untuk Song
struct infotypeSong {
    int id;
    char title[100];
    char artist[100];
    char album[100];
    int year;
    int playCount;
    int isLiked; // 0 = no, 1 = yes
};

// Node untuk Song (tidak digunakan dalam array, tapi konsisten dengan struktur)
typedef struct elmSong *addressSong;
struct elmSong {
    infotypeSong info;
    addressSong next;
};

// Library menggunakan array Song (bisa diperluas ke Linked List jika perlu)
typedef infotypeSong Song;

// =============================================================================
// PLAYLIST STRUCTURE (Doubly Linked List)
// =============================================================================

// Node untuk Playlist (self-referential)
typedef struct elmPlaylist *addressPlaylist;
struct elmPlaylist {
    Song* song;
    addressPlaylist next;
    addressPlaylist prev;
};

// Struktur utama Playlist
struct Playlist {
    char name[100];
    addressPlaylist head;
    addressPlaylist tail;
    int songCount;
};

// =============================================================================
// QUEUE STRUCTURE (Single Linked List dengan Head & Tail)
// =============================================================================

// Node untuk Queue (self-referential)
typedef struct elmQueue *addressQueue;
struct elmQueue {
    Song* song;
    addressQueue next;
};

// Struktur utama Queue
struct Queue {
    addressQueue head;
    addressQueue tail;
};

// =============================================================================
// HISTORY STRUCTURE (Stack - Single Linked List)
// =============================================================================

// Node untuk History/Stack (self-referential)
typedef struct elmHistory *addressHistory;
struct elmHistory {
    Song* song;
    addressHistory next;
};

// Struktur utama History (Stack)
struct History {
    addressHistory top;
};

// ----- LOGIN SYSTEM -----
int loginSystem(int* roleOutput);
void displayLoginMenu(int* dummy);

// ----- LIBRARY MANAGEMENT -----
void generateDummyData(Song lib[], int* libCount);
void printLibrary(Song lib[], int libCount);
void printLibraryDetailed(Song lib[], int libCount);
void addSongToLibrary(Song lib[], int* libCount, Song* newSong, int role);
void editSongInLibrary(Song lib[], int libCount, int id, int role);
void deleteSongFromLibrary(Song lib[], int* libCount, int id, int role);
void likeSong(Song* libEntry, int* dummy);
void unlikeSong(Song* libEntry, int* dummy);
Song* findSongById(Song lib[], int libCount, int id);

// ----- SORTING -----
void mergeSortLibrary(Song lib[], Song temp[], int left, int right);
void mergeLibrary(Song lib[], Song temp[], int left, int mid, int right);

// ----- SEARCH -----
int searchByTitle(Song lib[], int libCount, const char query[]);
void searchByArtist(Song lib[], int libCount, const char query[], int results[], int* resultCount);
void printSearchResults(Song lib[], int indices[], int resultCount);

// ----- NOW PLAYING (QUEUE + STACK) -----
void displayNowPlaying(Song* current, int* isPlaying);
void playSong(Song* current, int* isPlaying);
void nextSong(Queue* q, Song** current, History* hist, Playlist* contextPlaylist, addressPlaylist* currentNode);
void previousSong(History* hist, Song** current);
void enqueueSong(Queue* q, Song* s);
void dequeueSong(Queue* q, Song** output);
void printQueue(Queue* q, int* dummy);
void clearQueue(Queue* q, int* dummy);
void pushHistory(History* hist, Song* s);
Song* popHistory(History* hist);

// ----- PLAYLIST -----
void initPlaylist(Playlist* pl, const char name[]);
void addSongToPlaylist(Playlist* pl, Song* s);
void removeSongFromPlaylist(Playlist* pl, int songId);
void printPlaylist(Playlist* pl, int* dummy);
void printPlaylistWithNumbers(Playlist* pl);
void deletePlaylist(Playlist* pl, int* dummy);
Song* getPlaylistSongByIndex(Playlist* pl, int index);
addressPlaylist findPlaylistNodeBySong(Playlist* pl, Song* s);

// ----- LIKED SONGS -----
void printLikedSongs(Song lib[], int libCount);
void unlikeFromList(Song lib[], int libCount, int id);

// ----- RECOMMENDATIONS -----
void showMostPlayed(Song lib[], int libCount, int topN);
void showRecentlyPlayed(History* hist, int topN);

// ----- MENU HANDLERS -----
void displayMainMenu(int role, int* dummy);
void handleLibraryMenu(Song lib[], int* libCount, int role);
void handleNowPlayingMenu(Song** current, int* isPlaying, Queue* q, History* hist, Song lib[], int libCount, Playlist* contextPlaylist, addressPlaylist* currentNode);
void handlePlaylistMenu(Playlist playlists[], int* playlistCount, int* activePlaylistIndex, 
                        Song lib[], int libCount, Song** currentSong, 
                        int* isPlaying, Playlist* contextPlaylist, addressPlaylist* currentNode);
void handleSearchMenu(Song lib[], int libCount);
void handleLikedMenu(Song lib[], int libCount, Song** currentSong, int* isPlaying);
void handleRecommendationMenu(Song lib[], int libCount, History* hist, Song** currentSong, int* isPlaying);
void handleQueueMenu(Queue* q);

// ----- UTILITY -----
void clearScreen(int* dummy);
void pauseScreen(int* dummy);

#endif
