

#include "music.h"

// Helper function to add song manually
void addManualSong(Song lib[], int* libCount, const char* title, const char* artist, 
                   const char* album, int year, int playCount) {
    if (*libCount >= 100) return;
    
    lib[*libCount].id = *libCount + 1;
    strcpy(lib[*libCount].title, title);
    strcpy(lib[*libCount].artist, artist);
    strcpy(lib[*libCount].album, album);
    lib[*libCount].year = year;
    lib[*libCount].playCount = playCount;
    lib[*libCount].isLiked = 0;
    (*libCount)++;
}

int main() {
    // ----- INITIALIZATION -----
    Song library[100];
    int libCount = 0;
    int role = 0;
    int dummy = 0;
    
    // ----- POPULATE LIBRARY WITH REAL SONGS -----
    printf("[INFO] Loading music library...\n");
    
    // The Weeknd
    addManualSong(library, &libCount, "Blinding Lights", "The Weeknd", "After Hours", 2020, 95);
    addManualSong(library, &libCount, "Starboy", "The Weeknd", "Starboy", 2016, 88);
    addManualSong(library, &libCount, "Save Your Tears", "The Weeknd", "After Hours", 2020, 82);
    addManualSong(library, &libCount, "The Hills", "The Weeknd", "Beauty Behind the Madness", 2015, 79);
    addManualSong(library, &libCount, "Die For You", "The Weeknd", "Starboy", 2016, 91);
    
    // SZA
    addManualSong(library, &libCount, "Kill Bill", "SZA", "SOS", 2022, 94);
    addManualSong(library, &libCount, "Snooze", "SZA", "SOS", 2022, 89);
    addManualSong(library, &libCount, "Good Days", "SZA", "Good Days", 2020, 76);
    addManualSong(library, &libCount, "All The Stars", "SZA", "Black Panther", 2018, 72);
    
    // Drake
    addManualSong(library, &libCount, "God's Plan", "Drake", "Scorpion", 2018, 87);
    addManualSong(library, &libCount, "One Dance", "Drake", "Views", 2016, 90);
    addManualSong(library, &libCount, "Hotline Bling", "Drake", "Views", 2015, 85);
    addManualSong(library, &libCount, "In My Feelings", "Drake", "Scorpion", 2018, 81);
    addManualSong(library, &libCount, "Way 2 Sexy", "Drake", "Certified Lover Boy", 2021, 73);
    
    // Taylor Swift
    addManualSong(library, &libCount, "Anti-Hero", "Taylor Swift", "Midnights", 2022, 92);
    addManualSong(library, &libCount, "Cruel Summer", "Taylor Swift", "Lover", 2019, 88);
    addManualSong(library, &libCount, "Shake It Off", "Taylor Swift", "1989", 2014, 86);
    addManualSong(library, &libCount, "Blank Space", "Taylor Swift", "1989", 2014, 84);
    addManualSong(library, &libCount, "Lavender Haze", "Taylor Swift", "Midnights", 2022, 78);
    
    // Ariana Grande
    addManualSong(library, &libCount, "7 rings", "Ariana Grande", "Thank U, Next", 2019, 89);
    addManualSong(library, &libCount, "Thank U, Next", "Ariana Grande", "Thank U, Next", 2019, 87);
    addManualSong(library, &libCount, "Positions", "Ariana Grande", "Positions", 2020, 80);
    addManualSong(library, &libCount, "34+35", "Ariana Grande", "Positions", 2020, 75);
    
    // Ed Sheeran
    addManualSong(library, &libCount, "Shape of You", "Ed Sheeran", "Divide", 2017, 93);
    addManualSong(library, &libCount, "Perfect", "Ed Sheeran", "Divide", 2017, 90);
    addManualSong(library, &libCount, "Shivers", "Ed Sheeran", "Equals", 2021, 77);
    addManualSong(library, &libCount, "Bad Habits", "Ed Sheeran", "Equals", 2021, 82);
    
    // Dua Lipa
    addManualSong(library, &libCount, "Levitating", "Dua Lipa", "Future Nostalgia", 2020, 91);
    addManualSong(library, &libCount, "Don't Start Now", "Dua Lipa", "Future Nostalgia", 2019, 88);
    addManualSong(library, &libCount, "New Rules", "Dua Lipa", "Dua Lipa", 2017, 79);
    addManualSong(library, &libCount, "Break My Heart", "Dua Lipa", "Future Nostalgia", 2020, 74);
    
    // Bruno Mars
    addManualSong(library, &libCount, "Uptown Funk", "Bruno Mars", "Uptown Special", 2014, 96);
    addManualSong(library, &libCount, "24K Magic", "Bruno Mars", "24K Magic", 2016, 85);
    addManualSong(library, &libCount, "That's What I Like", "Bruno Mars", "24K Magic", 2017, 83);
    addManualSong(library, &libCount, "Leave The Door Open", "Bruno Mars", "An Evening with Silk Sonic", 2021, 86);
    
    // Post Malone
    addManualSong(library, &libCount, "Circles", "Post Malone", "Hollywood's Bleeding", 2019, 89);
    addManualSong(library, &libCount, "Sunflower", "Post Malone", "Spider-Man: Into the Spider-Verse", 2018, 92);
    addManualSong(library, &libCount, "Rockstar", "Post Malone", "Beerbongs & Bentleys", 2017, 87);
    addManualSong(library, &libCount, "Congratulations", "Post Malone", "Stoney", 2016, 81);
    
    // Billie Eilish
    addManualSong(library, &libCount, "Bad Guy", "Billie Eilish", "When We All Fall Asleep", 2019, 90);
    addManualSong(library, &libCount, "Happier Than Ever", "Billie Eilish", "Happier Than Ever", 2021, 84);
    addManualSong(library, &libCount, "Lovely", "Billie Eilish", "13 Reasons Why", 2018, 78);
    addManualSong(library, &libCount, "Everything I Wanted", "Billie Eilish", "Everything I Wanted", 2019, 76);
    
    // Harry Styles
    addManualSong(library, &libCount, "As It Was", "Harry Styles", "Harry's House", 2022, 95);
    addManualSong(library, &libCount, "Watermelon Sugar", "Harry Styles", "Fine Line", 2019, 88);
    addManualSong(library, &libCount, "Adore You", "Harry Styles", "Fine Line", 2019, 82);
    addManualSong(library, &libCount, "Sign of the Times", "Harry Styles", "Harry Styles", 2017, 80);
    
    // Olivia Rodrigo
    addManualSong(library, &libCount, "Drivers License", "Olivia Rodrigo", "SOUR", 2021, 93);
    addManualSong(library, &libCount, "Good 4 U", "Olivia Rodrigo", "SOUR", 2021, 91);
    addManualSong(library, &libCount, "Vampire", "Olivia Rodrigo", "GUTS", 2023, 87);
    addManualSong(library, &libCount, "Deja Vu", "Olivia Rodrigo", "SOUR", 2021, 79);
    
    // Justin Bieber
    addManualSong(library, &libCount, "Peaches", "Justin Bieber", "Justice", 2021, 86);
    addManualSong(library, &libCount, "Sorry", "Justin Bieber", "Purpose", 2015, 88);
    addManualSong(library, &libCount, "Love Yourself", "Justin Bieber", "Purpose", 2015, 85);
    addManualSong(library, &libCount, "Stay", "Justin Bieber", "Justice", 2021, 90);
    
    // More popular songs
    addManualSong(library, &libCount, "Flowers", "Miley Cyrus", "Endless Summer Vacation", 2023, 94);
    addManualSong(library, &libCount, "Unholy", "Sam Smith", "Unholy", 2022, 88);
    addManualSong(library, &libCount, "Heat Waves", "Glass Animals", "Dreamland", 2020, 86);
    addManualSong(library, &libCount, "Sweater Weather", "The Neighbourhood", "I Love You", 2013, 81);
    addManualSong(library, &libCount, "Someone You Loved", "Lewis Capaldi", "Divinely Uninspired", 2018, 83);
    addManualSong(library, &libCount, "Dance Monkey", "Tones and I", "The Kids Are Coming", 2019, 87);
    addManualSong(library, &libCount, "Believer", "Imagine Dragons", "Evolve", 2017, 85);
    addManualSong(library, &libCount, "Radioactive", "Imagine Dragons", "Night Visions", 2012, 82);
    addManualSong(library, &libCount, "Counting Stars", "OneRepublic", "Native", 2013, 80);
    addManualSong(library, &libCount, "Memories", "Maroon 5", "Jordi", 2019, 78);
    addManualSong(library, &libCount, "Sugar", "Maroon 5", "V", 2015, 84);
    addManualSong(library, &libCount, "Girls Like You", "Maroon 5", "Red Pill Blues", 2017, 86);
    addManualSong(library, &libCount, "Closer", "The Chainsmokers", "Collage", 2016, 89);
    addManualSong(library, &libCount, "Something Just Like This", "The Chainsmokers", "Memories...Do Not Open", 2017, 82);
    addManualSong(library, &libCount, "Despacito", "Luis Fonsi", "Vida", 2017, 97);
    addManualSong(library, &libCount, "Senorita", "Shawn Mendes", "Shawn Mendes", 2019, 88);
    addManualSong(library, &libCount, "Havana", "Camila Cabello", "Camila", 2017, 91);
    addManualSong(library, &libCount, "Dynamite", "BTS", "BE", 2020, 93);
    addManualSong(library, &libCount, "Butter", "BTS", "Butter", 2021, 90);
    addManualSong(library, &libCount, "Rolling in the Deep", "Adele", "21", 2011, 92);
    addManualSong(library, &libCount, "Hello", "Adele", "25", 2015, 90);
    addManualSong(library, &libCount, "Easy On Me", "Adele", "30", 2021, 87);
    addManualSong(library, &libCount, "Bohemian Rhapsody", "Queen", "A Night at the Opera", 1975, 98);
    
    printf("[OK] Loaded %d songs into library\n\n", libCount);
    
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

