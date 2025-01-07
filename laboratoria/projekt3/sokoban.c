#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26  // Number of letters from 'a' to 'z'
#define INITIAL_MEM 10
#define INITIAL_BUFFER_SIZE 128

typedef enum {
    WALL,
    GOAL,
    NORMAL
} CellType;

typedef struct {
    CellType **cells; // 2D array of cells
    int *colsPerRow;  // Array of column counts
    int rowCount;     // Number of rows
} Board;

typedef struct {
    int row; // Row number
    int col; // Column number
} Position;

typedef struct {
    bool **boxMap;                     // 2D Map with the size of board, representing where boxes are placed
    Position boxLookup[ALPHABET_SIZE]; // Array of positions for each box
} BoxManager;

typedef struct {
    Position *player;                     // Array of previous player positions
    Position (*boxLookup)[ALPHABET_SIZE]; // Array of pointers to box states
    int count;                            // Number of saved states
    int capacity;                         // Maximum number of states currently supported
} Memory;

typedef struct {
    Board *board;           // Pointer to the Board struct, representing the game board's properties
    Position player;        // Player position
    BoxManager *boxManager; // BoxManager struct, responsible for tracking box locations
    Memory *memory;
} Game;

typedef enum {
    DOWN,
    LEFT,
    RIGHT,
    UP
} Direction;

typedef struct {
    char boxName;    // Name of the box
    char direction;  // Direction of the move
} Command;

typedef struct {
    int row[4];
    int col[4];
} Directions;

Board *initializeBoard() {
    Board *board = malloc(sizeof(Board));
    if (board == NULL) {
        return NULL;
    }

    // Initialize all fields
    board->cells = NULL;
    board->colsPerRow = NULL;
    board->rowCount = 0;

    return board;
}

BoxManager *initializeBoxManager() {
    BoxManager *boxManager = malloc(sizeof(BoxManager));
    if (boxManager == NULL) {
        return NULL;
    }

    // Initialize all fields
    boxManager->boxMap = NULL;

    // Initialize each box with (-1, -1) for not existing boxes
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        boxManager->boxLookup[i].row = -1;
        boxManager->boxLookup[i].col = -1;
    }

    return boxManager;
}

Memory *initializeMemory(int initialCapacity) {
    Memory *memory = malloc(sizeof(Memory));
    if (memory == NULL) {
        return NULL;
    }

    memory->player = malloc((size_t)initialCapacity * sizeof(Position));
    if (memory->player == NULL) {
        return NULL;
    }

    memory->boxLookup = malloc((size_t)initialCapacity * sizeof(Position[ALPHABET_SIZE]));
    if (memory->boxLookup == NULL) {
        free(memory->player);
        free(memory);
        return NULL;
    }

    memory->count = 0;
    memory->capacity = initialCapacity;

    return memory;
}


// Function to initialize the game
int initGame(Game *game) {
    // Initialize the board
    game->board = initializeBoard();
    if (!game->board) {
        return 1;
    }

    // Initialize player position at (-1, -1) for not existing
    game->player.row = -1;
    game->player.col = -1;

    // Initialize the BoxManager
    game->boxManager = initializeBoxManager();
    if (!game->boxManager) {
        return 1;
    }

    // Initialize the Memory
    game->memory = initializeMemory(INITIAL_MEM);
    if (!game->memory) {
        return 1;
    }

    return 0;
}

// Function to add a player to the game
void addPlayer(Game *game, int row, int col) {
    game->player.row = row;
    game->player.col = col;
}

// Function to add a box to the box manager
void addBox(BoxManager *boxManager, int row, int col, char name) {
    int index = name - 'a';
    boxManager->boxMap[row][col] = true;
    boxManager->boxLookup[index].row = row;
    boxManager->boxLookup[index].col = col;
}

void setCellType(const Game *game, int row, int col, char type) {
    if (type == '-' || type == '@' || islower(type)) {
        game->board->cells[row][col] = NORMAL;
    } else if (type == '+' || type == '*' || isupper(type)) {
        game->board->cells[row][col] = GOAL;
    } else if (type == '#') {
        game->board->cells[row][col] = WALL;
    }
}

// Function to process each character from buffer to the game board
void processBufferChar(Game *game, int row, int col, char type) {
    setCellType(game, row, col, type);

    if (type == '@' || type == '*') {
        addPlayer(game, row, col);
    } else if (isalpha(type)) {
        addBox(game->boxManager, row, col, (char)tolower(type));
    }
}

// Function to load the cells from the buffer
void loadCells(Game *game, char buffer[], int n) {
    for (int i = 0; i < n; i++) {
        processBufferChar(game, game->board->rowCount, i, buffer[i]);
    }
}

void initializeBoxMapRow(bool *boxMapRow, int colCount) {
    for (int i = 0; i < colCount; i++) {
        boxMapRow[i] = false;
    }
}

// Function to allocate memory for a new row in the board
int allocateBoardRow(const Game *game, int colCount) {
    // Allocate memory for cells
    game->board->cells[game->board->rowCount] = (CellType *)malloc((size_t)colCount * sizeof(CellType));
    if (game->board->cells[game->board->rowCount] == NULL) return 1;

    // Allocate memory for boxMap row
    game->boxManager->boxMap[game->board->rowCount] = (bool *)malloc((size_t)colCount * sizeof(bool));
    if (game->boxManager->boxMap[game->board->rowCount] == NULL) return 1;

    initializeBoxMapRow(game->boxManager->boxMap[game->board->rowCount], colCount);
    return 0;
}

// Function to add a new row to the board and allocate memory for it
int addRowToBoard(const Game *game, int colCount) {
    // Reallocate memory for board rows and columns
    CellType **newCells = realloc(game->board->cells, (size_t)(game->board->rowCount + 1) * sizeof(CellType *));
    if (newCells == NULL) return 1;

    bool **newBoxMap = realloc(game->boxManager->boxMap, (size_t)(game->board->rowCount + 1) * sizeof(bool *));
    if (newBoxMap == NULL) {
        free(newCells);
        return 1;
    }

    int *newColsPerRow = realloc(game->board->colsPerRow, (size_t)(game->board->rowCount + 1) * sizeof(int));
    if (newColsPerRow == NULL) {
        free(newCells);
        free(newBoxMap);
        return 1;
    }

    game->board->cells = newCells;
    game->boxManager->boxMap = newBoxMap;
    game->board->colsPerRow = newColsPerRow;
    game->board->colsPerRow[game->board->rowCount] = colCount;

    return allocateBoardRow(game, colCount);
}

// Function to process the input row from stdin
int processInputRow(Game *game, char buffer[]) {
    int colCount = (int)strlen(buffer); // Length of the row (excluding newline character)
    if (addRowToBoard(game, colCount) != 0) return 1;

    // Load the cells into the game board
    loadCells(game, buffer, colCount);

    game->board->rowCount++;

    return 0;
}

// Function to read a line from stdin and store it in a buffer
int readLine(char **buffer, size_t *buffer_size) {
    FILE *stream = stdin;

    size_t length = 0;
    int ch;
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= *buffer_size) {
            *buffer_size += INITIAL_BUFFER_SIZE;
            char *new_buffer = realloc(*buffer, *buffer_size * sizeof(char));
            if (!new_buffer) {
                return -1;
            }
            *buffer = new_buffer;
        }
        (*buffer)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return -1;
    }

    (*buffer)[length] = '\0';
    return 1;
}

// Function to check if the end of board input is reached
int isNewlineOnly(const char *buffer) {
    return strlen(buffer) == 0;
}

// Function to load the board from stdin
int loadBoard(Game *game) {
    size_t buffer_size = INITIAL_BUFFER_SIZE;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        return 1;
    }
    while (readLine(&buffer, &buffer_size) != -1) {
        // If there is a newline only, it means the board is finished
        if (isNewlineOnly(buffer)) {
            free(buffer);
            return 0;
        }
        if (processInputRow(game, buffer) != 0) {
            free(buffer);
            return 1;
        }
    }

    free(buffer);
    return 1;
}

// Function to check if the end of input is reached
int isEndOfInput() {
    int input = getchar();

    if (input == EOF || input == '.') {
        return 1;
    }

    // Push the character back to stdin if not EOF or '.'
    ungetc(input, stdin);

    return 0;
}

// Check if cube should be printed
int checkPrintCommand() {
    int input = getchar();

    if (input == '\n') {
        return 1;
    }

    // Push the character back to stdin if it's not a newline
    ungetc(input, stdin);

    return 0;
}

// Function to convert cell type to char representation
char cellToChar(CellType cell, bool isPlayer, bool isBox, char boxChar) {
    if (isPlayer) {
        switch (cell) {
            case GOAL: return '*';
            case NORMAL: return '@';
            default: return ' ';
        }
    }
    if (isBox) {
        switch (cell) {
            case GOAL: return (char)toupper(boxChar);
            case NORMAL: return boxChar;
            default: return ' ';
        }
    }
    switch (cell) {
        case WALL: return '#';
        case GOAL: return '+';
        case NORMAL: return '-';
        default: return ' ';
    }
}

// Function to create a string row based on the cells of the board
char *createStringRow(const Game *game, int rowIndex) {
    int colCount = game->board->colsPerRow[rowIndex];
    int bufferSize = colCount + 1;

    char *row = malloc((size_t)bufferSize * sizeof(char));
    if (row == NULL) {
        return NULL;
    }

    for (int j = 0; j < colCount; j++) {
        row[j] = cellToChar(game->board->cells[rowIndex][j],
                    false,
                    false,
                    '\0');
    }
    row[colCount] = '\0'; // Null-terminate of the string

    return row;
}

// Function to place the boxes on the string board
void placeBoxesOnBoard(const Game * game, char ** stringBoard) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int row = game->boxManager->boxLookup[i].row;
        int col = game->boxManager->boxLookup[i].col;
        if (row >= 0 && col >= 0) {
            char boxChar = (char) (i + 'a');
            stringBoard[row][col] = cellToChar(
                    game->board->cells[row][col],
                    false,
                    true,
                    boxChar
            );
        }
    }
}

// Function to place the player on the string board
void placePlayerOnBoard(const Game * game, char ** stringBoard) {
    int row = game->player.row;
    int col = game->player.col;
    stringBoard[row][col] = cellToChar(
            game->board->cells[row][col],
            true,
            false,
            '\0'
    );
}

// Function to create the string board
char **createStringBoard(const Game *game) {
    char **stringBoard = malloc((size_t)game->board->rowCount * sizeof(char *));
    if (stringBoard == NULL) {
        return NULL;
    }

    // Create a string row based on cells of the board
    for (int i = 0; i < game->board->rowCount; i++) {
        stringBoard[i] = createStringRow(game, i);
        if (stringBoard[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(stringBoard[j]);
            }
            free(stringBoard);
            return NULL;
        }
    }

    placeBoxesOnBoard(game, stringBoard);
    placePlayerOnBoard(game, stringBoard);

    return stringBoard;
}

void freeStringBoard(char ** stringBoard, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        free(stringBoard[i]);
    }
    free(stringBoard);
}

// Function to display the board as a string
int displayBoard(const Game *game) {
    // Create the string board based on the game state
    char **stringBoard = createStringBoard(game);
    if (stringBoard == NULL) {
        return 1;
    }
    
    // Print each row of the string board
    for (int i = 0; i < game->board->rowCount; i++) {
        printf("%s\n", stringBoard[i]);
    }
    freeStringBoard(stringBoard, game->board->rowCount);
    return 0;
}

// Function to check if there is an undo command
int checkUndoCommand() {
    int input = getchar();

    if (input == '0') {
        return 1;
    }

    // Push the character back to stdin if it's not a newline
    ungetc(input, stdin);

    return 0;
}

// Function to reset the box map
void resetBoxMap(const BoxManager *boxManager, const Board *board) {
    for (int i = 0; i < board->rowCount; i++) {
        initializeBoxMapRow(boxManager->boxMap[i], board->colsPerRow[i]);
    }
}

void reconstructBoxMap(const BoxManager *boxManager, const Board *board) {
    // Reset the box map
    resetBoxMap(boxManager, board);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        Position pos = boxManager->boxLookup[i];

        if (pos.row >= 0 && pos.row < board->rowCount &&
            pos.col >= 0 && pos.col < board->colsPerRow[pos.row]) {
            boxManager->boxMap[pos.row][pos.col] = true;
            }
    }
}

// Function to undo the last command
void executeUndoCommand(Game *game) {
    // Check if there is anything to undo
    if (game->memory->count <= 0) {
        return;
    }

    game->memory->count--;
    game->player = game->memory->player[game->memory->count];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        game->boxManager->boxLookup[i] = game->memory->boxLookup[game->memory->count][i];
    }

    // Based on BoxLookup reconstruct the BoxMap
    reconstructBoxMap(game->boxManager, game->board);
}

// Read direction from user input
Direction readDirection() {
    int input = getchar();
    switch (input) {
        case '2': return DOWN;
        case '8': return UP;
        case '4': return LEFT;
        case '6': return RIGHT;
        default:  return -1;
    }
}

// Read user command
void readCommand(Command *command) {
    command->boxName = (char)getchar();
    command->direction = readDirection();
}

// Function to check if the move to cell is valid
int isValidMove(const Game *game, int row, int col) {
    return row >= 0 && row < game->board->rowCount &&
           col >= 0 && col < game->board->colsPerRow[row] &&
           game->board->cells[row][col] != WALL && !game->boxManager->boxMap[row][col];
}

// Recursive depth-first search to find a path from the player to the box
int dfs(Game *game, bool **visited, int currRow, int currCol, int destRow, int destCol, Directions *directions) {
    if (currRow == destRow && currCol == destCol) {
        return 1;
    }

    visited[currRow][currCol] = true;

    for (int i = 0; i < 4; i++) {
        int newRow = currRow + directions->row[i];
        int newCol = currCol + directions->col[i];

        if (isValidMove(game, newRow, newCol) && !visited[newRow][newCol]) {
            if (dfs(game, visited, newRow, newCol, destRow, destCol, directions)) {
                return 1;
            }
        }
    }

    return 0;
}

// Update the position based on the direction and delta (1 for box, -1 for player)
Position updatePosition(Position pos, Direction direction, int delta) {
    if (direction == UP) {
        pos.row -= delta;
    } else if (direction == DOWN) {
        pos.row += delta;
    } else if (direction == LEFT) {
        pos.col -= delta;
    } else if (direction == RIGHT) {
        pos.col += delta;
    }
    return pos;
}

// Get the position of the box after being pushed
Position getPushedBoxPosition(const Game *game, const Command *command) {
    Position pos = game->boxManager->boxLookup[command->boxName - 'a'];
    return updatePosition(pos, command->direction, 1);
}

// Get the position of the player pushing the box
Position getPlayerPositionToPush(const Game *game, const Command *command) {
    Position pos = game->boxManager->boxLookup[command->boxName - 'a'];
    return updatePosition(pos, command->direction, -1);
}

int allocateVisitedArray(const Game *game, bool ***visited) {
    *visited = (bool **)malloc((size_t)game->board->rowCount * sizeof(bool *));
    if (!*visited) {
        return 1;
    }

    for (int i = 0; i < game->board->rowCount; i++) {
        (*visited)[i] = (bool *)calloc((size_t)game->board->colsPerRow[i], sizeof(bool));
        if (!(*visited)[i]) {
            for (int j = 0; j < i; j++) {
                free((*visited)[j]);
            }
            free(*visited);
            return 1;
        }
    }
    return 0;
}

void freeVisitedArray(const Game *game, bool **visited) {
    for (int i = 0; i < game->board->rowCount; i++) {
        free(visited[i]);
    }
    free(visited);
}

Directions initializeDirections() {
    // Initialize the directions
    Directions directions = {
        .row = {1, -1, 0, 0},
        .col = {0, 0, 1, -1}
    };
    return directions;
}

// Check if the command is executable
int isCommandExecutable(Game *game, const Command *command) {
    Position pushedBox = getPushedBoxPosition(game, command);
    Position playerPushing = getPlayerPositionToPush(game, command);

    // Check if the moves are valid
    if (!isValidMove(game, pushedBox.row, pushedBox.col) ||
        !isValidMove(game, playerPushing.row, playerPushing.col)) {
        return 0;
        }

    bool **visited;
    if (allocateVisitedArray(game, &visited)) {
        return 0;
    }

    // Check if there is a path from the player to the box
    Directions directions = initializeDirections();
    int pathExists = dfs(game, visited, game->player.row, game->player.col, playerPushing.row, playerPushing.col, &directions);

    freeVisitedArray(game, visited);
    return pathExists;
}

// Function to save the current state
int saveCurrentState(const Game *game) {
    // Reallocate memory if needed
    if (game->memory->count >= game->memory->capacity) {
        Position *new_player = realloc(game->memory->player, (size_t)(game->memory->capacity + INITIAL_MEM) * sizeof(Position));
        if (new_player == NULL) {
            return 1;
        }

        Position (*new_boxLookup)[ALPHABET_SIZE] = realloc(game->memory->boxLookup, (size_t)(game->memory->capacity + INITIAL_MEM) * sizeof(Position[ALPHABET_SIZE]));
        if (new_boxLookup == NULL) {
            return 1;
        }

        game->memory->player = new_player;
        game->memory->boxLookup = new_boxLookup;
        game->memory->capacity += INITIAL_MEM;
    }

    // Save player position
    game->memory->player[game->memory->count] = game->player;

    // Save box positions
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        game->memory->boxLookup[game->memory->count][i] = game->boxManager->boxLookup[i];
    }

    game->memory->count++;

    return 0;
}

// Function to execute the command
void executeCommand(Game *game, const Command *command) {
    // Get the index of the box
    int boxIndex = command->boxName - 'a';

    Position oldPos = game->boxManager->boxLookup[boxIndex];
    Position newPos = getPushedBoxPosition(game, command);

    // Update box map
    game->boxManager->boxMap[oldPos.row][oldPos.col] = false;
    game->boxManager->boxMap[newPos.row][newPos.col] = true;

    // Update box position
    game->boxManager->boxLookup[boxIndex] = newPos;

    // Move player to the old position of the box
    game->player = oldPos;
}

// Function to process the input commands
int processInput(Game *game) {
    while (!isEndOfInput()) {
        // Check if there is a newline and print the board if so
        if (checkPrintCommand()) {
            if (displayBoard(game)) {
                return 1;
            }
            continue;
        }

        // Check if there is an undo command
        if (checkUndoCommand()) {
            executeUndoCommand(game);
            continue;
        }

        // Read user command
        Command command;
        readCommand(&command);

        // Check if the move is possible
        if (isCommandExecutable(game, &command)) {
            // Save current state in memory
            if (saveCurrentState(game)) {
                return 1;
            }
            // Execute command
            executeCommand(game, &command);
        }
    }
    return 0;
}

void freeBoard(Board *board) {
    if (board == NULL) return;
    if (board->cells) {
        for (int i = 0; i < board->rowCount; i++) {
            free(board->cells[i]);
        }
        free(board->cells);
    }
    if (board->colsPerRow) free(board->colsPerRow);
    free(board);
}

void freeBoxManager(BoxManager *boxManager, int rowCount) {
    if (boxManager == NULL) return;
    if (boxManager->boxMap != NULL) {
        for (int i = 0; i < rowCount; i++) {
            free(boxManager->boxMap[i]);
        }
        free(boxManager->boxMap);
    }
    free(boxManager);
}

void freeMemory(Memory *memory) {
    if (memory == NULL) return;
    if (memory->player != NULL ) free(memory->player);
    if (memory->boxLookup != NULL) free(memory->boxLookup);
    free(memory);
}

void freeGame(Game *game) {
    if (!game) return;
    freeMemory(game->memory);
    freeBoxManager(game->boxManager, game->board->rowCount);
    freeBoard(game->board);
    free(game);
}

int main() {
    // Memory allocation for the game
    Game *game = malloc(sizeof(Game));
    if (game == NULL) {
        return 1;
    }

    // Initialize the game
    if (initGame(game)) {
        freeGame(game);
        return 1;
    }

    // Load the board from stdin
    if (loadBoard(game)) {
        freeGame(game);
        return 1;
    }

    // The first command is always to print the board
    if (displayBoard(game)) {
        freeGame(game);
        return 1;
    }

    // Process the input commands
    if (processInput(game)) {
        freeGame(game);
        return 1;
    }

    // Free the game memory
    freeGame(game);
    return 0;
}