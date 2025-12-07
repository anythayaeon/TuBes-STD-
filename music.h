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

// ----- STRUCT DEFINITIONS -----

struct Song {
    int id;
    char title[100];
    char artist[100];
    char album[100];
    int year;
    int playCount;
    int isLiked; // 0 = no, 1 = yes
};

struct PlaylistNode {
    Song* song;
    PlaylistNode* next;
    PlaylistNode* prev;
};

struct Playlist {
    char name[100];
    PlaylistNode* head;
    PlaylistNode* tail;
    int songCount;
};

struct QueueNode {
    Song* song;
    QueueNode* next;
};

struct HistoryNode {
    Song* song;
    HistoryNode* next;
};

// ----- LOGIN SYSTEM -----
int loginSystem(int* roleOutput);
void displayLoginMenu(int* dummy);

// ----- LIBRARY MANAGEMENT -----
void generateDummyData(Song lib[], int* libCount);
void printLibrary(Song lib[], int libCount);
void printLibraryDetailed(Song lib[], int libCount);
void addSongToLibrary(Song lib[], int* libCount, Song* newSong, int role);
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
void nextSong(QueueNode** front, QueueNode** rear, Song** current, HistoryNode** histTop);
void previousSong(HistoryNode** histTop, Song** current);
void enqueueSong(QueueNode** front, QueueNode** rear, Song* s);
void dequeueSong(QueueNode** front, QueueNode** rear, Song** output);
void printQueue(QueueNode* front, int* dummy);
void clearQueue(QueueNode** front, QueueNode** rear, int* dummy);
void pushHistory(HistoryNode** histTop, Song* s);
Song* popHistory(HistoryNode** histTop);

// ----- PLAYLIST -----
void initPlaylist(Playlist* pl, const char name[]);
void addSongToPlaylist(Playlist* pl, Song* s);
void removeSongFromPlaylist(Playlist* pl, int songId);
void printPlaylist(Playlist* pl, int* dummy);
void deletePlaylist(Playlist* pl, int* dummy);

// ----- LIKED SONGS -----
void printLikedSongs(Song lib[], int libCount);
void unlikeFromList(Song lib[], int libCount, int id);

// ----- RECOMMENDATIONS -----
void showMostPlayed(Song lib[], int libCount, int topN);
void showRecentlyPlayed(HistoryNode* histTop, int topN);

// ----- MENU HANDLERS -----
void displayMainMenu(int role, int* dummy);
void handleLibraryMenu(Song lib[], int* libCount, int role);
void handleNowPlayingMenu(Song** current, int* isPlaying, QueueNode** front, QueueNode** rear, HistoryNode** histTop, Song lib[], int libCount);
void handlePlaylistMenu(Playlist* pl, Song lib[], int libCount);
void handleSearchMenu(Song lib[], int libCount);
void handleLikedMenu(Song lib[], int libCount);
void handleRecommendationMenu(Song lib[], int libCount, HistoryNode* histTop);
void handleQueueMenu(QueueNode** front, QueueNode** rear);

// ----- UTILITY -----
void clearScreen(int* dummy);
void pauseScreen(int* dummy);

#endif
