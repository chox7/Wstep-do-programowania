#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef N
#define N 5
#endif

#define FACES 6

#define UP 0
#define LEFT 1
#define FRONT 2
#define RIGHT 3
#define BACK 4
#define DOWN 5

#define CLOCKWISE 1
#define COUNTERCLOCKWISE (-1)
#define ROTATE_180 2

typedef struct {
    int faces[FACES][N][N];
} RubikCube;

typedef struct {
    int LayerCount;
    int Side;
    int Angle;
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
void printSpaces(const int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

// Print a single row of a given face
void printRow(const RubikCube *cube, const int face, const int row) {
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

// Rotate a face 90 degrees in the given direction
void rotateFace(int face[N][N], const int direction) {
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
void rotateLayerUp(RubikCube *cube, const int layer, const int direction) {
    int temp[N];

    // Store the FRONT row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][layer][i];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // FRONT <- RIGHT
            cube->faces[FRONT][layer][i] = cube->faces[RIGHT][layer][i];
            // RIGHT <- BACK
            cube->faces[RIGHT][layer][i] = cube->faces[BACK][layer][i];
            // BACK <- LEFT
            cube->faces[BACK][layer][i] = cube->faces[LEFT][layer][i];
            // LEFT <- Stored FRONT
            cube->faces[LEFT][layer][i] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // FRONT <- LEFT
            cube->faces[FRONT][layer][i] = cube->faces[LEFT][layer][i];
            // LEFT <- BACK
            cube->faces[LEFT][layer][i] = cube->faces[BACK][layer][i];
            // BACK <- RIGHT
            cube->faces[BACK][layer][i] = cube->faces[RIGHT][layer][i];
            // RIGHT <- Stored FRONT
            cube->faces[RIGHT][layer][i] = temp[i];
        }
    }
}

// Rotate a layer around the LEFT face
void rotateLayerLeft(RubikCube *cube, const int layer, const int direction) {
    int temp[N];
    // Store the FRONT column at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][i][layer];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // FRONT <- UP
            cube->faces[FRONT][i][layer] = cube->faces[UP][i][layer];
            // UP <- BACK
            cube->faces[UP][i][layer] = cube->faces[BACK][N - 1 - i][N - 1 - layer];
            // BACK <- DOWN
            cube->faces[BACK][i][N - 1 - layer] = cube->faces[DOWN][N - 1 - i][layer];
            // DOWN <- Stored FRONT
            cube->faces[DOWN][i][layer] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // FRONT <- DOWN
            cube->faces[FRONT][i][layer] = cube->faces[DOWN][i][layer];
            // DOWN <- BACK
            cube->faces[DOWN][i][layer] = cube->faces[BACK][N - 1 - i][N - 1 - layer];
            // BACK <- UP
            cube->faces[BACK][i][N - 1 - layer] = cube->faces[UP][N - 1 - i][layer];
            // UP <- Stored FRONT
            cube->faces[UP][i][layer] = temp[i];
        }
    }
}

// Rotate a layer around the FRONT face
void rotateLayerFront(RubikCube *cube, const int layer, const int direction) {
    int temp[N];
    // Store the UP row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[UP][N - 1 - layer][i];
    }

    // Rotate a layer (clockwise or counterclockwise)
    if (direction == CLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // UP <- LEFT
            cube->faces[UP][N - 1 - layer][i] = cube->faces[LEFT][N - 1 - i][N - 1 - layer];
            // LEFT <- DOWN
            cube->faces[LEFT][i][N - 1 - layer] = cube->faces[DOWN][layer][i];
            // DOWN <- RIGHT
            cube->faces[DOWN][layer][i] = cube->faces[RIGHT][N - 1 - i][layer];
            // RIGHT <- Stored UP
            cube->faces[RIGHT][i][layer] = temp[i];
        }
    } else if (direction == COUNTERCLOCKWISE) {
        for (int i = 0; i < N; i++) {
            // UP <- RIGHT
            cube->faces[UP][N - 1 - layer][i] = cube->faces[RIGHT][i][layer];
            // RIGHT <- DOWN
            cube->faces[RIGHT][i][layer] = cube->faces[DOWN][layer][N - 1 - i];
            // DOWN <- LEFT
            cube->faces[DOWN][layer][i] = cube->faces[LEFT][i][N - 1 - layer];
            // LEFT <- Stored UP
            cube->faces[LEFT][i][N - 1 - layer] = temp[N - 1 - i];
        }
    }
}

// Rotate a layer around the DOWN face
void rotateLayerDown(RubikCube *cube, const int layer, const int direction) {
    rotateLayerUp(cube, N - layer - 1, direction * -1);
}

// Rotate a layer around the RIGHT face
void rotateLayerRight(RubikCube *cube, const int layer, const int direction) {
    rotateLayerLeft(cube, N - layer - 1, direction * -1);
}

// Rotate a layer around the BACK face
void rotateLayerBack(RubikCube *cube, const int layer, const int direction) {
    rotateLayerFront(cube, N - layer - 1, direction * -1);
}

// Rotates the Rubik's Cube around the UP face
void rotateCubeUp(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the UP face
    rotateFace(cube->faces[UP], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerUp(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the DOWN face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[DOWN], direction * -1);
    }
}

// Rotates the Rubik's Cube around the LEFT face
void rotateCubeLeft(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the LEFT face
    rotateFace(cube->faces[LEFT], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerLeft(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the RIGHT face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[RIGHT], direction * -1);
    }
}

// Rotates the Rubik's Cube around the FRONT face
void rotateCubeFront(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the FRONT face
    rotateFace(cube->faces[FRONT], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerFront(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the BACK face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[BACK], direction * -1);
    }
}

// Rotates the Rubik's Cube around the RIGHT face
void rotateCubeRight(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the RIGHT face
    rotateFace(cube->faces[RIGHT], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerRight(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the LEFT face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[LEFT], direction * -1);
    }
}

// Rotates the Rubik's Cube around the BACK face
void rotateCubeBack(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the BACK face
    rotateFace(cube->faces[BACK], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerBack(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the FRONT face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[FRONT], direction * -1);
    }
}

// Rotates the Rubik's Cube around the DOWN face
void rotateCubeDown(RubikCube *cube, const int layer_count, const int direction) {
    // Rotate the DOWN face
    rotateFace(cube->faces[DOWN], direction);

    // Rotate layers
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerDown(cube, layer, direction);
    }

    // If all entire cube is being rotated, rotate the UP face in opposite direction
    if (layer_count == N) {
        rotateFace(cube->faces[UP], direction * -1);
    }
}

void rotateCube(RubikCube *cube, const int face, const int layer_count, const int direction) {
    if (face == UP) {
        rotateCubeUp(cube, layer_count, direction);
    } else if (face == LEFT) {
        rotateCubeLeft(cube, layer_count, direction);
    } else if (face == FRONT) {
        rotateCubeFront(cube, layer_count, direction);
    } else if (face == RIGHT) {
        rotateCubeRight(cube, layer_count, direction);
    } else if (face == BACK) {
        rotateCubeBack(cube, layer_count, direction);
    } else if (face == DOWN) {
        rotateCubeDown(cube, layer_count, direction);
    }
}

void executeCommand(RubikCube *cube, const Command *command) {
    int rotations = (command->Angle == ROTATE_180) ? 2 : 1;
    int direction = (command->Angle == ROTATE_180) ? CLOCKWISE : command->Angle;

    for (int i = 0; i < rotations; i++) {
        rotateCube(cube, command->Side, command->LayerCount, direction);
    }
}

int parseLayerCount() {
    int input = getchar();

    if (isalpha(input)) {
        ungetc(input, stdin);
        return 1;
    }

    int layerCount = 0;
    while (isdigit(input)) {
        layerCount = layerCount * 10 + (input - '0');
        input = getchar();
    }
    ungetc(input, stdin);
    return layerCount;
}

int parseSide() {
    const int input = getchar();

    switch (input) {
        case 'u': return UP;
        case 'l': return LEFT;
        case 'f': return FRONT;
        case 'r': return RIGHT;
        case 'b': return BACK;
        case 'd': return DOWN;
        default:
            fprintf(stderr, "Invalid side\n");
        exit(1);
    }
}

int parseAngle() {
    const int input = getchar();
    if (input == '\'') {
        return COUNTERCLOCKWISE;
    }
    if (input == '"') {
        return ROTATE_180;
    }
    ungetc(input, stdin);
    return CLOCKWISE;

}
void parseCommand(Command *command) {
    command->LayerCount = parseLayerCount();
    command->Side = parseSide();
    command->Angle = parseAngle();
}

// Processes user input to interact with the Rubik's Cube
void processInput(RubikCube *cube) {
    int input;

    // Read user input until EOF or '.' is encountered
    while ((input = getchar()) != EOF) {
        if (input == '.') {
            break;
        }
        if (input == '\n') {
            // Print the current state of the cube after new line.
            printCube(cube);
            continue;
        }

        // Push the character back to stdin
        ungetc(input, stdin);

        // Parse user command
        Command command = {0};
        parseCommand(&command);

        //
        executeCommand(cube, &command);
    }
}

int main(void) {
    RubikCube cube = initializeCube();
    processInput(&cube);
    return 0;
}





// void (*rotateFunctions[])(RubikCube*, int, int) = {
//     rotateCubeUp,
//     rotateCubeLeft,
//     rotateCubeFront,
//     rotateCubeRight,
//     rotateCubeBack,
//     rotateCubeDown
// };
//
// void rotateCube(RubikCube *cube, const int face, const int layer_count, const int direction) {
//     rotateFunctions[face](cube, layer_count, direction);
// }