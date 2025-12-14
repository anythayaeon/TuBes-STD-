# Music Player - Aplikasi Pemutar Musik Berbasis Konsol
## Tugas Besar Struktur Data - Role-Based Music Player

## 🎯 FITUR YANG DIIMPLEMENTASIKAN

### ✅ FITUR ADMIN (Wajib + Lengkap)
1. **CRUD Library**
   - ✅ **View** - Lihat semua lagu dalam library
   - ✅ **Add** - Tambah lagu baru ke library
   - ✅ **Edit** - Edit data lagu (title, artist, album, year) 
   - ✅ **Delete** - Hapus lagu dari library
   - ✅ **Sort** - Sorting A-Z menggunakan Merge Sort
   
2. **Music Player**
   - ✅ Play/Pause/Stop lagu
   - ✅ Next/Previous song
   - ✅ Queue system (FIFO)
   - ✅ History stack (LIFO)
   
3. **Search & Management**
   - ✅ Search by title
   - ✅ Search by artist
   - ✅ Like/Unlike songs
   
### ✅ FITUR USER (Wajib + Tambahan)
1. **Music Player**
   - ✅ Play/Pause/Stop lagu
   - ✅ **Next/Prev dengan Context-Aware Navigation** !
     - Jika sedang play dari playlist → next/prev mengikuti urutan playlist
     - Jika sedang play biasa → next/prev dari queue
   - ✅ Queue management
   
2. **Playlist Management (Doubly Linked List)**
   - ✅ Create playlist
   - ✅ View playlist
   - ✅ Add lagu ke playlist dari Library
   - ✅ **Play lagu langsung dari playlist** 
   - ✅ Remove lagu dari playlist
   - ✅ Delete playlist
   
3. **Liked Songs (Favorit)**
   - ✅ View all liked songs
   - ✅ **Play lagu langsung dari liked songs** 
   - ✅ Unlike songs
   - ✅ Like songs dari library
   
4. **Recommendations**
   - ✅ Most played songs (Top 10)
   - ✅ Recently played (from history stack)
   - ✅ **Play lagu langsung dari recommendations** 
   
5. **Search**
   - ✅ Search by title
   - ✅ Search by artist

---

## 🔧 STRUKTUR DATA KLASIK

### 1. Song Library - Array dengan typedef
```cpp
struct infotypeSong {
    int id;
    char title[100];
    char artist[100];
    char album[100];
    int year;
    int playCount;
    int isLiked;
};
typedef infotypeSong Song;
```

### 2. Playlist - Doubly Linked List
```cpp
typedef struct elmPlaylist *addressPlaylist;
struct elmPlaylist {
    Song* song;
    addressPlaylist next;
    addressPlaylist prev;
};
```

### 3. Queue - Single Linked List dengan Head & Tail
```cpp
typedef struct elmQueue *addressQueue;
struct elmQueue {
    Song* song;
    addressQueue next;
};
```

### 4. History - Stack (Single Linked List)
```cpp
typedef struct elmHistory *addressHistory;
struct elmHistory {
    Song* song;
    addressHistory next;
};
```

---

## 🐛 BUG YANG DIPERBAIKI

1. **Playlist Linked List** ✅ FIXED
   - Sekarang bisa menambah banyak lagu
   - Pointer next/prev terhubung dengan benar
   - Head/tail update konsisten

2. **Next/Prev Navigation** ✅ FIXED
   - Context-aware: mengikuti playlist jika play dari playlist
   - Fallback to queue jika tidak ada playlist context

3. **Admin Edit Feature** ✅ ADDED
   - Function editSongInLibrary() dengan validasi role

4. **Play dari Berbagai Sumber** ✅ ADDED
   - Play dari playlist
   - Play dari liked songs
   - Play dari recommendations

---

## 📁 STRUKTUR FILE

```
music-player/
├── music.h              # Header & struct definitions
├── music.cpp            # Login system
├── library.cpp          # Library management + Edit
├── queue.cpp            # Queue & History (context-aware)
├── playlist.cpp         # Playlist management (enhanced)
├── menus.cpp            # All menu handlers (updated)
├── main.cpp             # Main program + 80+ songs
└── README.md            # This file
```

---

## 🔨 COMPILE & RUN

### Windows
```powershell
g++ main.cpp library.cpp menus.cpp music.cpp playlist.cpp queue.cpp -o program.exe
.\program.exe
```

### Linux/Mac
```bash
g++ main.cpp library.cpp menus.cpp music.cpp playlist.cpp queue.cpp -o program
./program
```

---

## 🎮 CARA MENGGUNAKAN

### Login
- **Admin**: password `admin` (or press Enter)
- **User**: password `user` (or press Enter)

### Admin Menu
```
1. [VIEW]   View Library
2. [ADD]    Add New Song
3. [DELETE] Delete Song
4. [EDIT]   Edit Song ⭐ NEW!
5. [SORT]   Sort Library A-Z
6. [SEARCH] Search Songs
7. [PLAY]   Now Playing
8. [QUEUE]  Queue System
9. [LOGOUT] Logout
```

### User Menu
```
1. [VIEW]   View Library (Read-Only)
2. [PLAY]   Now Playing
3. [QUEUE]  Queue System
4. [LIST]   My Playlists ⭐ ENHANCED!
5. [LIKED]  Liked Songs ⭐ ENHANCED!
6. [SEARCH] Search Songs
7. [RECOM]  Recommendations ⭐ ENHANCED!
8. [LOGOUT] Logout
```

---

## 🆕 FITUR BARU

### 1. Edit Song (Admin)
Admin bisa edit title, artist, album, year dari lagu existing.

### 2. Play dari Playlist (User)
- Pilih lagu dari playlist by number
- Otomatis set context untuk next/prev
- Next/prev mengikuti urutan playlist

### 3. Play dari Liked Songs (User)
- Lihat semua liked songs
- Play langsung by ID

### 4. Play dari Recommendations (User)
- Lihat most played / recently played
- Play langsung by ID

### 5. Context-Aware Navigation
- Next/prev detect apakah user sedang play dari playlist
- Jika ya → follow playlist order
- Jika tidak → fallback to queue

---

## 🔬 KONSISTENSI STRUKTUR DATA

✅ **Format Klasik Dipertahankan:**
- `typedef struct *address` untuk abstraksi pointer
- `struct infotype` untuk data
- `struct node` yang self-referential
- Pemisahan: infotype → node → struktur utama

✅ **Tidak Menggunakan:**
- ❌ STL (vector, list, map)
- ❌ Modern C++ (class, template)
- ✅ Pure pointer-based manual implementation

---

## 📝 PENJELASAN TEKNIS

### Mengapa Doubly Linked List untuk Playlist?
- Navigasi dua arah (next/prev dalam playlist)
- Insert/delete O(1) di any position
- Konsisten dengan teori struktur data

### Mengapa Queue untuk Song Queue?
- FIFO: Song pertama masuk diplay pertama
- O(1) enqueue dan dequeue
- Real-world analogy: antrian

### Mengapa Stack untuk History?
- LIFO: Previous song = last played
- O(1) push dan pop
- Perfect untuk fitur "back"

### Context-Aware Navigation
- Detect apakah user play dari playlist
- Next/prev behavior sesuai context
- Implementasi: pointer ke playlist dan current node

---

## ✅ CHECKLIST TUGAS BESAR

- [x] **Admin: CRUD Library** (View, Add, Edit, Delete)
- [x] **Admin: Sort Library** (Merge Sort A-Z)
- [x] **User: Search Song** (by title, by artist)
- [x] **User: Play/Stop** (dengan play count)
- [x] **User: Next/Prev** (context-aware)
- [x] **User: Playlist Management** (Doubly Linked List)
- [x] **User: Play from Playlist** (context preservation)
- [x] **User: Liked Songs** (play langsung)
- [x] **User: Recommendations** (play langsung)
- [x] **Queue System** (FIFO)
- [x] **History Stack** (LIFO)
- [x] **Struktur Data Klasik** (typedef, address, self-referential)
- [x] **No STL** (pure manual)
- [x] **Bug Fixed** (playlist linked list valid)

**Version:** 2.0 - Enhanced Edition  
**Last Updated:** December 14, 2025  
**Status:** Production Ready 🚀

