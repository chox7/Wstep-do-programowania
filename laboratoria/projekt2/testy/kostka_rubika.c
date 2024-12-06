#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 5
#endif

#define FACES 6

typedef enum {
    UP,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN
} CubeFace;

typedef enum {
    CLOCKWISE ,
    COUNTERCLOCKWISE,
    ROTATE_180,
} RotationAngle;

typedef struct {
    int faces[FACES][N][N];
} RubikCube;

typedef struct {
    int LayerCount;
    CubeFace Side;
    RotationAngle Angle;
} Command;

// Initialize the cube with each face filled
RubikCube initializeCube() {
    RubikCube cube;
    for (int face = 0; face < FACES; face++) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                cube.faces[face][row][col] = face;
            }
        }
    }
    return cube;
}

// Print spaces for alignment
void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

// Print a single row of a given face
void printRow(const RubikCube *cube, CubeFace face, int row) {
    for (int col = 0; col < N; col++) {
        printf("%d", cube->faces[face][row][col]);
    }
}

// Print the entire cube
void printCube(const RubikCube *cube) {
    printf("\n");

    // Print the top layer (UP)
    for (int row = 0; row < N; row++) {
        printSpaces(N + 1);
        printRow(cube, UP, row);
        printf("\n");
    }

    // Print the middle layer (LEFT, FRONT, RIGHT, BACK)
    for (int row = 0; row < N; row++) {
        printRow(cube, LEFT, row);
        printf("|");
        printRow(cube, FRONT, row);
        printf("|");
        printRow(cube, RIGHT, row);
        printf("|");
        printRow(cube, BACK, row);
        printf("\n");
    }

    // Print the bottom layer (DOWN)
    for (int row = 0; row < N; row++) {
        printSpaces(N + 1);
        printRow(cube, DOWN, row);
        printf("\n");
    }
}

// Return the opposite face
CubeFace opposite(CubeFace face) {
    // Mapping each face to its opposite
    CubeFace opposites[] = {DOWN, RIGHT, BACK, LEFT, FRONT, UP};
    return opposites[face];
}

// Toggle the rotation direction between CLOCKWISE and COUNTERCLOCKWISE
RotationAngle toggleDirection(RotationAngle direction) {
    return (direction == CLOCKWISE) ? COUNTERCLOCKWISE : CLOCKWISE;
}

// Rotate a face 90 degrees in the given direction
void rotateFace(int face[N][N], RotationAngle direction) {
    int temp[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (direction == CLOCKWISE) {
                temp[j][N - 1 - i] = face[i][j];
            } else if (direction == COUNTERCLOCKWISE) {
                temp[N - 1 - j][i] = face[i][j];
            }
        }
    }

    // Copy back to the original face
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            face[i][j] = temp[i][j];
        }
    }
}

// Rotate a layer around the UP face
void rotateLayerUp(RubikCube *cube, int layer, RotationAngle direction) {
    int temp[N];

    // Store the FRONT row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][layer][i];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        // FRONT <- RIGHT
        for (int i = 0; i < N; i++) {
            cube->faces[FRONT][layer][i] = cube->faces[RIGHT][layer][i];
        }
        // RIGHT <- BACK
        for (int i = 0; i < N; i++) {
            cube->faces[RIGHT][layer][i] = cube->faces[BACK][layer][i];
        }
        // BACK <- LEFT
        for (int i = 0; i < N; i++) {
            cube->faces[BACK][layer][i] = cube->faces[LEFT][layer][i];
        }
        // LEFT <- Stored FRONT
        for (int i = 0; i < N; i++) {
            cube->faces[LEFT][layer][i] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        // FRONT <- LEFT
        for (int i = 0; i < N; i++) {
            cube->faces[FRONT][layer][i] = cube->faces[LEFT][layer][i];
        }
        // LEFT <- BACK
        for (int i = 0; i < N; i++) {
            cube->faces[LEFT][layer][i] = cube->faces[BACK][layer][i];
        }
        // BACK <- RIGHT
        for (int i = 0; i < N; i++) {
            cube->faces[BACK][layer][i] = cube->faces[RIGHT][layer][i];
        }
        // RIGHT <- Stored FRONT
        for (int i = 0; i < N; i++) {
            cube->faces[RIGHT][layer][i] = temp[i];
        }
    }
}

// Rotate a layer around the LEFT face
void rotateLayerLeft(RubikCube *cube, int layer, RotationAngle direction) {
    int temp[N];

    // Store the FRONT column at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][i][layer];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        // FRONT <- UP
        for (int i = 0; i < N; i++) {
            cube->faces[FRONT][i][layer] = cube->faces[UP][i][layer];
        }
        // UP <- BACK
        for (int i = 0; i < N; i++) {
            cube->faces[UP][i][layer] = cube->faces[BACK][N - 1 - i][N - 1 - layer];
        }
        // BACK <- DOWN
        for (int i = 0; i < N; i++) {
            cube->faces[BACK][i][N - 1 - layer] = cube->faces[DOWN][N - 1 - i][layer];
        }
        // DOWN <- Stored FRONT
        for (int i = 0; i < N; i++) {
            cube->faces[DOWN][i][layer] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        // FRONT <- DOWN
        for (int i = 0; i < N; i++) {
            cube->faces[FRONT][i][layer] = cube->faces[DOWN][i][layer];
        }
        // DOWN <- BACK
        for (int i = 0; i < N; i++) {
            cube->faces[DOWN][i][layer] = cube->faces[BACK][N - 1 - i][N - 1 - layer];
        }
        // BACK <- UP
        for (int i = 0; i < N; i++) {
            cube->faces[BACK][i][N - 1 - layer] = cube->faces[UP][N - 1 - i][layer];
        }
        // UP <- Stored FRONT
        for (int i = 0; i < N; i++) {
            cube->faces[UP][i][layer] = temp[i];
        }
    }
}

// Rotate a layer around the FRONT face
void rotateLayerFront(RubikCube *cube, int layer, RotationAngle direction) {
    int temp[N];

    // Store the UP row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[UP][N - 1 - layer][i];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        // UP <- LEFT
        for (int i = 0; i < N; i++) {
            cube->faces[UP][N - 1 - layer][i] = cube->faces[LEFT][N - 1 - i][N - 1 - layer];
        }
        // LEFT <- DOWN
        for (int i = 0; i < N; i++) {
            cube->faces[LEFT][i][N - 1 - layer] = cube->faces[DOWN][layer][i];
        }
        // DOWN <- RIGHT
        for (int i = 0; i < N; i++) {
            cube->faces[DOWN][layer][i] = cube->faces[RIGHT][N - 1 - i][layer];
        }
        // RIGHT <- Stored UP
        for (int i = 0; i < N; i++) {
            cube->faces[RIGHT][i][layer] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        // UP <- RIGHT
        for (int i = 0; i < N; i++) {
            cube->faces[UP][N - 1 - layer][i] = cube->faces[RIGHT][i][layer];
        }
        // RIGHT <- DOWN
        for (int i = 0; i < N; i++) {
            cube->faces[RIGHT][i][layer] = cube->faces[DOWN][layer][N - 1 - i];
        }
        // DOWN <- LEFT
        for (int i = 0; i < N; i++) {
            cube->faces[DOWN][layer][i] = cube->faces[LEFT][i][N - 1 - layer];
        }
        // LEFT <- Stored UP
        for (int i = 0; i < N; i++) {
            cube->faces[LEFT][i][N - 1 - layer] = temp[N - 1 - i];
        }
    }
}

// Rotate a layer around the DOWN face
void rotateLayerDown(RubikCube *cube, int layer, RotationAngle direction) {
    // This is equivalent to rotating the (N - i - 1)th layer from the opposite direction
    rotateLayerUp(cube, N - layer - 1, toggleDirection(direction));
}

// Rotate a layer around the RIGHT face
void rotateLayerRight(RubikCube *cube, int layer, RotationAngle direction) {
    // This is equivalent to rotating the (N - i - 1)th layer from the opposite direction
    rotateLayerLeft(cube, N - layer - 1, toggleDirection(direction));
}

// Rotate a layer around the BACK face
void rotateLayerBack(RubikCube *cube, int layer, RotationAngle direction) {
    // This is equivalent to rotating the (N - i - 1)th layer from the opposite direction
    rotateLayerFront(cube, N - layer - 1, toggleDirection(direction));
}

// Array of functions to rotate a layer around each face
void (*rotateLayer[])(RubikCube*, int, RotationAngle) = {
    rotateLayerUp,
    rotateLayerLeft,
    rotateLayerFront,
    rotateLayerRight,
    rotateLayerBack,
    rotateLayerDown
};

// Rotate the entire cube, including the face and layers
void rotateCube(RubikCube *cube, CubeFace face, int layer_count, RotationAngle direction) {
    // Rotate the corresponding face
    rotateFace(cube->faces[face], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayer[face](cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the opposite face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[opposite(face)], toggleDirection(direction));
    }
}

// Execute user command
void executeCommand(RubikCube *cube, const Command *command) {
    // Convert 180-degree rotation into two 90-degree rotations
    int rotations = (command->Angle == ROTATE_180) ? 2 : 1;
    RotationAngle direction = (command->Angle == ROTATE_180) ? CLOCKWISE : command->Angle;

    for (int i = 0; i < rotations; i++) {
        rotateCube(cube, command->Side, command->LayerCount, direction);
    }
}

// Parse layer count
int parseLayerCount() {
    int input = getchar();

    int layerCount = 0;
    while (isdigit(input)) {
        layerCount = layerCount * 10 + (input - '0');
        input = getchar();
    }

    // Push the last non-digit character back to stdin
    ungetc(input, stdin);

    // If layer number no specified, default is 1
    if (layerCount == 0) {
        return 1;
    }

    return layerCount;
}

// Parse side of the cube
CubeFace parseSide() {
    int input = getchar();

    if (input == 'u') return UP;
    if (input == 'l') return LEFT;
    if (input == 'f') return FRONT;
    if (input == 'r') return RIGHT;
    if (input == 'b') return BACK;
    if (input == 'd') return DOWN;

    return -1;
}

// Parse rotation angle
RotationAngle parseAngle() {
    int input = getchar();

    if (input == '\'') return COUNTERCLOCKWISE;
    if (input == '"') return ROTATE_180;

    // Push the character back to stdin if rotation is clockwise
    ungetc(input, stdin);

    return CLOCKWISE;
}

// Parse user command
void parseCommand(Command *command) {
    command->LayerCount = parseLayerCount();
    command->Side = parseSide();
    command->Angle = parseAngle();
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

// Processes user input to interact with the Rubik's Cube
void processInput(RubikCube *cube) {
    while (!isEndOfInput()) {
        // Check if there is a newline and print the cube if so
        if (checkPrintCommand()) {
            printCube(cube);
            continue;
        }

        // Parse user command
        Command command;
        parseCommand(&command);

        // Execute command
        executeCommand(cube, &command);
    }
}

int main(void) {
    //  Initialize the cube
    RubikCube cube = initializeCube();

    // Process user input
    processInput(&cube);

    return 0;
}
