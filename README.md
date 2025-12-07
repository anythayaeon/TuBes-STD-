# Music Player - C++ Procedural (Role System)

Music player dengan sistem role (Admin & User) menggunakan **procedural C++** murni tanpa OOP.

## Features
- Role-based access (Admin & User) dengan #define
- Library management (Admin only: add/delete songs)
- 60+ lagu populer (The Weeknd, SZA, Drake, Taylor Swift, dll)
- Playlist management (Doubly Linked List)
- Queue system (FIFO untuk upcoming songs)
- History stack (LIFO untuk previous songs)
- Search & Recommendations
- Like/Unlike system
- Merge Sort A-Z

## Login
**Admin**: Pilih 1, password: `admin` (atau Enter skip)  
**User**: Pilih 2, password: `user` (atau Enter skip)

## Struktur File

```
music-player/
├── music.h          # Header (structs, function declarations)
├── music.cpp        # Login system
├── library.cpp      # Library & search functions
├── queue.cpp        # Queue & History (Stack) functions
├── playlist.cpp     # Playlist management
├── menus.cpp        # All menu handlers & utility
├── main.cpp         # Main program + 60+ manual songs
└── README.md        # This file
```

## Compile & Run

### Windows (PowerShell)
```powershell
g++ -std=c++17 music.cpp library.cpp queue.cpp playlist.cpp menus.cpp main.cpp -o music.exe
.\music.exe
```

### Linux/Mac
```bash
g++ -std=c++17 music.cpp library.cpp queue.cpp playlist.cpp menus.cpp main.cpp -o music
./music
```

### Code::Blocks
1. Create new Console Application project
2. Add **ALL** .cpp files (music.cpp, library.cpp, queue.cpp, playlist.cpp, menus.cpp, main.cpp)
3. Add music.h header
4. Build & Run (F9)

## Lagu yang Tersedia

Library berisi 60+ lagu populer dari artis:
- **The Weeknd** - Blinding Lights, Starboy, Save Your Tears, Die For You, The Hills
- **SZA** - Kill Bill, Snooze, Good Days, All The Stars
- **Drake** - God's Plan, One Dance, Hotline Bling, In My Feelings
- **Taylor Swift** - Anti-Hero, Cruel Summer, Shake It Off, Blank Space
- **Ariana Grande** - 7 rings, Thank U Next, Positions
- **Ed Sheeran** - Shape of You, Perfect, Bad Habits, Shivers
- **Dua Lipa** - Levitating, Don't Start Now, New Rules
- **Bruno Mars** - Uptown Funk, 24K Magic, Leave The Door Open
- **Post Malone** - Circles, Sunflower, Rockstar, Congratulations
- **Billie Eilish** - Bad Guy, Happier Than Ever, Lovely
- **Harry Styles** - As It Was, Watermelon Sugar, Adore You
- **Olivia Rodrigo** - Drivers License, Good 4 U, Vampire
- **Justin Bieber** - Peaches, Sorry, Stay, Love Yourself
- **Dan banyak lagi...**

## Cara Menggunakan

### 1. Login
```
========================================
       MUSIC PLAYER LOGIN
========================================
1. [ADMIN] Login as Admin
2. [USER]  Login as User
0. [EXIT]  Exit
========================================
```

### 2. Admin Features
- **[VIEW]** View Library - Lihat semua lagu
- **[ADD]** Add New Song - Tambah lagu baru (ADMIN ONLY)
- **[DELETE]** Delete Song - Hapus lagu (ADMIN ONLY)
- **[SORT]** Sort Library A-Z - Sort alfabetis
- **[SEARCH]** Search Songs - Cari berdasarkan judul/artis
- **[PLAY]** Now Playing - Putar lagu, next/prev, queue
- **[QUEUE]** Queue System - Kelola antrian
- **[LOGOUT]** Logout - Ganti role

### 3. User Features
- **[VIEW]** View Library - Hanya lihat (read-only)
- **[PLAY]** Now Playing - Main lagu
- **[QUEUE]** Queue System - Lihat/kelola queue
- **[LIST]** My Playlists - Buat playlist sendiri
- **[LIKED]** Liked Songs - Lihat & unlike lagu favorit
- **[SEARCH]** Search Songs - Cari lagu
- **[RECOM]** Recommendations - Most played & recently played

### 4. Now Playing Menu
```
========================================
          NOW PLAYING
========================================
>> Blinding Lights - The Weeknd
Album: After Hours | Year: 2020
Plays: 95 | Status: [PLAYING]
========================================

1. [PLAY] Play/Pause
2. [NEXT] Next Song (from Queue)
3. [PREV] Previous Song (from History)
4. [VIEW] Show Queue
5. [ADD]  Add Song to Queue
6. [SELECT] Select Song from Library to Play
0. [BACK] Back
```

## Data Structures

- **Library**: Static Array (100 songs max)
- **Playlist**: Doubly Linked List (next & prev pointers)
- **Queue**: Single Linked List (FIFO - First In First Out)
- **History**: Stack Linked List (LIFO - Last In First Out)
- **Role**: Integer constant via #define (1=Admin, 2=User)

## Technical Details

### Permission System
```cpp
#define ROLE_ADMIN 1
#define ROLE_USER 2

void addSongToLibrary(Song lib[], int* libCount, Song* newSong, int role) {
    if (role != ROLE_ADMIN) {
        printf("[ERROR] Permission Denied! Only Admin can add songs.\n");
        return;
    }
    // ... implementation
}
```

### Manual Song Loading
```cpp
// Di main.cpp
addManualSong(library, &libCount, "Kill Bill", "SZA", "SOS", 2022, 94);
addManualSong(library, &libCount, "Blinding Lights", "The Weeknd", "After Hours", 2020, 95);
```

### Merge Sort (O(n log n))
```cpp
void mergeSortLibrary(Song lib[], Song temp[], int left, int right);
void mergeLibrary(Song lib[], Song temp[], int left, int mid, int right);
```

## Constraints

- Procedural only
- Struct untuk ADT
- Manual linked list implementation
- Library: `<iostream>`, `<cstring>`, `<cstdio>`, `<cstdlib>`, `<ctime>`

## Troubleshooting

### Compilation Error
```bash
# Pastikan semua file ada
ls music.h music.cpp library.cpp queue.cpp playlist.cpp menus.cpp main.cpp

# Compile ulang
g++ -std=c++17 music.cpp library.cpp queue.cpp playlist.cpp menus.cpp main.cpp -o music.exe
```

### Link Error
- Pastikan compile **semua .cpp files** (6 files)
- Jangan lupa: `music.cpp`, `library.cpp`, `queue.cpp`, `playlist.cpp`, `menus.cpp`, `main.cpp`

### Emoji Error (Karakter aneh)
- Sudah fixed! Semua emoji diganti ASCII:
  - Checkmark → `[OK]`
  - Cross → `[ERROR]`
  - Heart → `<3`
  - Music note → (removed/plain text)

## Example Session

```
[INFO] Loading music library...
[OK] Loaded 60 songs into library

========================================
       MUSIC PLAYER LOGIN
========================================
1. [ADMIN] Login as Admin
2. [USER]  Login as User
0. [EXIT]  Exit
========================================
Choice: 2
Enter user password (or press Enter to skip): [Enter]
[OK] Login successful! Welcome User.

========================================
            USER MENU
========================================
1. [VIEW]  View Library (Read-Only)
2. [PLAY]  Now Playing
3. [QUEUE] Queue System
4. [LIST]  My Playlists
5. [LIKED] Liked Songs
6. [SEARCH] Search Songs
7. [RECOM] Recommendations
8. [LOGOUT] Logout
0. [EXIT]  Exit
========================================
Choice: 1

=== LIBRARY (60 songs) ===
ID    Title                          Artist               Album                Year   Plays    Liked
------------------------------------------------------------------------------------
1     Blinding Lights                The Weeknd           After Hours          2020   95         
2     Starboy                        The Weeknd           Starboy              2016   88         
3     Save Your Tears                The Weeknd           After Hours          2020   82         
...
```

## License
Free to use for educational purposes
