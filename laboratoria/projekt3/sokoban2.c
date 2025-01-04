#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef enum {
    WALL,
    GOAL,
    NORMAL
} CellType;

typedef struct {
    CellType **cells;  // 2D array of cells
    int *cols_per_row; // Array of column counts
    int rows;          // Number of rows
} Board;

typedef struct {
    int row; // Row number
    int col; // Column number
} Position;

typedef struct {
    bool **box_map;                      // Map with the size of board
    Position *box_lookup[ALPHABET_SIZE]; //
} BoxManager;

typedef struct {
    Board *board;            //
    Position player;        // Player position
    BoxManager box_manager; //
} Game;

// Function to create a string representation of the board
char **create_string_board(const Board *board) {
    // Allocate an array of strings for each row
    char **string_board = (char **)malloc(board->rows * sizeof(char *));
    if (!string_board) {
        return NULL;
    }
    for (int i = 0; i < board->rows; i++) {
        // Allocate array for each row
        int cols = board->cols_per_row[i];
        string_board[i] = (char *)malloc(cols * sizeof(char));
        if (!string_board[i]) {
            for (int j = 0; j < i; j++) {
                free(string_board[j]);
            }
            free(string_board);
            return NULL;
        }

        // Fill the string with the board's cell representation
        for (int j = 0; j < cols; j++) {
            if (board->cells[i][j].can_pass && board->cells[i][j].is_goal) {
                string_board[i][j] = '+';
            } else if (board->cells[i][j].can_pass && !board->cells[i][j].is_goal) {
                string_board[i][j] = '-';
            } else if (!board->cells[i][j].can_pass && !board->cells[i][j].is_goal) {
                string_board[i][j] = '#';
            } else {
                string_board[i][j] = '$'; // Temporal symbol, will be replaced by box later
            }
        }
    }

    // Fill boxes
    for (int i = 0; i < board->box_count; i++) {
        char cell = string_board[board->boxes[i].pos.row][board->boxes[i].pos.col];
        if (cell == '#') {
            string_board[board->boxes[i].pos.row][board->boxes[i].pos.col] = board->boxes[i].name;
        } else if (cell == '$') {
            string_board[board->boxes[i].pos.row][board->boxes[i].pos.col] = (char)toupper(board->boxes[i].name);
        }
    }

    // Fill player
    char cell = string_board[board->player.row][board->player.col];
    if (cell == '+') {
        string_board[board->player.row][board->player.col] = '*';
    } else if (cell == '-') {
        string_board[board->player.row][board->player.col] = '@';
    }
    return string_board;
}

int display_board_2(const Board *board) {
    char **string_board = create_string_board(board);
    if (!string_board) {
        printf("Error creating string representation of the board!\n");
        return -1;
    }

    // Print each row of the string board
    for (int i = 0; i < board->rows; i++) {
        printf("%s\n", string_board[i]);
        free(string_board[i]); // Free each row after displaying
    }

    free(string_board); // Free the main array
    return 0;
}

int add_box(Board *board, int row, int col, char name) {
    Box *new_boxes = realloc(board->boxes, (board->box_count + 1) * sizeof(Box));
    if (new_boxes == NULL) {
        return 1;
    }
    board->boxes = new_boxes;
    board->boxes[board->box_count].name = name;
    board->boxes[board->box_count].pos.row = row;
    board->boxes[board->box_count].pos.col = col;
    board->box_count++;
    return 0;
}

int load_board(Board *board) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Mozliwe ze bedzie tzreba inaczej sprawdzic czy skonczylismy zczytywac plansze, tzn
        // Moze nie moge zalozyc ze po planszy zawsze bedzie pusta linia
        // Wtedy trzeba sprawdzac czy kazdy znak nalezy do (-, +, #, @, *, a..z, A..Z)
        // A;bo inaczej, przerwyam if isdigit
        // Jednak wtedy trzeba zwrocic te znaki do stdin
        // Trzeba napisac osobna funckje ktora sprawdzi poprawnosc buffera.
        if (strcmp(buffer, "\n") == 0) {
            break;
        }

        Cell **new_cells = realloc(board->cells, (board->rows + 1) * sizeof(Cell *));
        if (new_cells == NULL) {
            return 1;
        }
        board->cells = new_cells;

        size_t len = strlen(buffer);
        int col_count = 0;
        for (int i = 0; i < len; i++) {
            if (buffer[i] != ' ' && buffer[i] != '\n') {
                col_count++;
            }
        }

        board->cells[board->rows] = (Cell *)malloc(col_count * sizeof(Cell));
        if (board->cells[board->rows] == NULL) {
            return 1;
        }

        for (int i = 0; i < col_count; i++) {
            if (buffer[i] == '-') {
                board->cells[board->rows][i].can_pass = 1;
                board->cells[board->rows][i].is_goal = 0;
            } else if (buffer[i] == '+') {
                board->cells[board->rows][i].can_pass = 1;
                board->cells[board->rows][i].is_goal = 1;
            } else if (buffer[i] == '#') {
                board->cells[board->rows][i].can_pass = 0;
                board->cells[board->rows][i].is_goal = 0;
            } else if (buffer[i] == '@') {
                board->cells[board->rows][i].can_pass = 1;
                board->cells[board->rows][i].is_goal = 0;
                board->player.row = board->rows;
                board->player.col = i;
            } else if (buffer[i] == '*') {
                board->cells[board->rows][i].can_pass = 1;
                board->cells[board->rows][i].is_goal = 1;
                board->player.row = board->rows;
                board->player.col = i;
            } else if (islower(buffer[i])) {
                board->cells[board->rows][i].can_pass = 0;
                board->cells[board->rows][i].is_goal = 0;
                if (add_box(board, board->rows, i, buffer[i])) {
                    return 1;
                }
            } else if (isupper(buffer[i])) {
                board->cells[board->rows][i].can_pass = 0;
                board->cells[board->rows][i].is_goal = 1;
                if (add_box(board, board->rows, i, (char)tolower(buffer[i]))) {
                    return 1;
                }
            }
        }

        int *new_cols_per_row = realloc(board->cols_per_row, (board->rows + 1) * sizeof(int));
        if (new_cols_per_row == NULL) {
            return 1;
        }
        board->cols_per_row = new_cols_per_row;
        board->cols_per_row[board->rows] = col_count;

        board->rows++;
    }

    return 0;
}

void free_board(Board *board) {
    for (int i = 0; i < board->rows; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    free(board->boxes);
    free(board->cols_per_row);
    free(board);
}

Board *create_empty_board() {
    Board *board = (Board *)malloc(sizeof(Board));
    if (!board) {
        return NULL;
    }

    // Initialize all fields
    board->cells = NULL;
    board->cols_per_row = NULL;
    board->rows = 0;

    return board;
}

Game *init_game() {
    Game *game = (Game *)malloc(sizeof(Game));
    if (!game) {
        return NULL;
    }

    game->board = create_empty_board();

    game->player.row = 0;
    game->player.col = 0;

    game->box_manager.box_map = NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        game->box_manager.box_lookup[i] = NULL;
    }

    return game;
}

int main() {
    Game *game = init_game();
    if (!game || game->board) {

        return 1;
    }

    if (load_board(board)) {
        free_game(game);
        return 1;
    }
    display_board(board);
    display_board_2(board);
    free_board(board);
    return 0;
}
