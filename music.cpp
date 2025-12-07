/*
 * File: music.cpp
 * Description: Login system only
 * Author: AI Generated
 * Date: December 7, 2025
 */

#include "music.h"

// ----- LOGIN SYSTEM -----

int loginSystem(int* roleOutput) {
    int choice = 0;
    char password[50];
    
    while (true) {
        printf("\n");
        printf("========================================\n");
        printf("       MUSIC PLAYER LOGIN\n");
        printf("========================================\n");
        printf("1. [ADMIN] Login as Admin\n");
        printf("2. [USER]  Login as User\n");
        printf("0. [EXIT]  Exit\n");
        printf("========================================\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        if (choice == 1) {
            printf("Enter admin password (or press Enter to skip): ");
            fgets(password, 50, stdin);
            password[strcspn(password, "\n")] = 0;
            
            if (strlen(password) == 0 || strcmp(password, "admin") == 0) {
                *roleOutput = ROLE_ADMIN;
                printf("[OK] Login successful! Welcome Admin.\n");
                return ROLE_ADMIN;
            } else {
                printf("[ERROR] Wrong password!\n");
            }
        } else if (choice == 2) {
            printf("Enter user password (or press Enter to skip): ");
            fgets(password, 50, stdin);
            password[strcspn(password, "\n")] = 0;
            
            if (strlen(password) == 0 || strcmp(password, "user") == 0) {
                *roleOutput = ROLE_USER;
                printf("[OK] Login successful! Welcome User.\n");
                return ROLE_USER;
            } else {
                printf("[ERROR] Wrong password!\n");
            }
        } else if (choice == 0) {
            return 0;
        } else {
            printf("[ERROR] Invalid choice!\n");
        }
    }
}

void displayLoginMenu(int* dummy) {
    printf("\n");
    printf("========================================\n");
    printf("       MUSIC PLAYER LOGIN\n");
    printf("========================================\n");
    printf("1. [ADMIN] Login as Admin\n");
    printf("2. [USER]  Login as User\n");
    printf("0. [EXIT]  Exit\n");
    printf("========================================\n");
}
