#include "ab_menus.h"

#define FALSE 0
#define TRUE 1

static const char *options[] = {"Start Game", "Settings", "Exit"};
size_t options_size = sizeof(options) / sizeof(options[0]);
 
int main_menu(int *long_press, int *short_press) { 
    int choice = 0;
    while (1) {
        //Prints shall be replaced with display functions for i2c or spi
        printf("Main Menu\n");
        switch (choice) {
            case 0:
                printf("%s\n", options[choice]);
                if ( *short_press == TRUE ) {
                    choice = 1;
                    *short_press = FALSE;
                }
                if ( *long_press == TRUE ) {
                    *long_press = FALSE;
                    return choice;
                }
                break;

            case 1:
                printf("%s\n", options[choice]);
                if ( *short_press == TRUE ) {
                    choice = 2;
                    *short_press = FALSE;
                }
                if ( *long_press == TRUE ) {
                    *long_press = FALSE;
                    return choice;
                }
                break;

            case 3:
                printf("%s\n", options[choice]);
                if ( *short_press == TRUE ) {
                    choice = 0;
                    *short_press = FALSE;
                }
                if ( *long_press == TRUE ) {
                    *long_press = FALSE;
                    return choice;
                }
                break;

            default:
                printf("Invalid choice\n");
        }
    }
}