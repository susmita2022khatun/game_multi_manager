#include "game_com.h"

void play_game(const char *game_name) {
    // Define the mapping
    GameMap games[] = {
	
	{ "game_2", game_2 },

	{NULL, NULL} // Sentinel value to mark the end
    };

    for (int i = 0; games[i].name != NULL; i++) {
        if (strcmp(games[i].name, game_name) == 0) {
            games[i].func();
            return;
        }
    }

    printf("Error: Unknown game '%s'\n", game_name);
}






void game_2() {
    char in[100];  // Fixed-size array to store input

    while (1) {
        printf("Enter (type '0' to quit):\n");
        scanf("%99s", in);  // Use a size specifier to avoid buffer overflow
        if (strcmp(in, "0") == 0) {
            break;
        }
        printf("Echo: %s\n", in);
    }
}
