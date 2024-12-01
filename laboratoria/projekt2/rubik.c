#include <stdio.h>
#include <ctype.h>

#ifndef N
#define N 10
#endif

#define FACES 6

#define UP 0
#define LEFT 1
#define FRONT 2
#define RIGHT 3
#define BACK 4
#define DOWN 5

#define SIMPLE 0
#define MINUS_SIMPLE 1
#define SEMI_FULL 2

#define CLOCKWISE 1
#define COUNTERCLOCKWISE (-1)

typedef struct {
    int faces[FACES][N][N];
} RubikCube;

typedef struct {
    int LayerCount;
    int Side;
    char Angle;
} Command;

void initializeCube(RubikCube *cube) {
    for (int face = 0; face < FACES; face++) {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                cube->faces[face][row][col] = face;
            }
        }
    }
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printRow(const RubikCube *cube, int face, int row) {
    for (int col = 0; col < N; col++) {
        printf("%d", cube->faces[face][row][col]);
    }
}

void printCube(const RubikCube *cube) {
    printf("\n");
    for (int row = 0; row < N; row++) {
        printSpaces(N + 1);
        printRow(cube, UP, row);
        printf("\n");
    }

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

    for (int row = 0; row < N; row++) {
        printSpaces(N + 1);
        printRow(cube, DOWN, row);
        printf("\n");
    }
}

void rotateFace(int face[N][N], int direction) {
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

void rotateLayerUp(RubikCube *cube, int layer, int direction) {
    int temp[N];
    // Store the FRONT row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][layer][i];
    }

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

void rotateLayerLeft(RubikCube *cube, int layer, int direction) {
    int temp[N];
    // Store the FRONT column at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[FRONT][i][layer];
    }

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

void rotateLayerFront(RubikCube *cube, int layer, int direction) {
    int temp[N];
    // Store the UP row at the given layer
    for (int i = 0; i < N; i++) {
        temp[i] = cube->faces[UP][N - 1 - layer][i];
    }

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

void rotateLayerDown(RubikCube *cube, int layer, int direction) {
    rotateLayerUp(cube, N - layer - 1, direction * -1);
}

void rotateLayerRight(RubikCube *cube, int layer, int direction) {
    rotateLayerLeft(cube, N - layer - 1, direction * -1);
}

void rotateLayerBack(RubikCube *cube, int layer, int direction) {
    rotateLayerFront(cube, N - layer - 1, direction * -1);
}

void rotateCubeUp(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[UP], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerUp(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[DOWN], direction * -1);
    }
}

void rotateCubeLeft(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[LEFT], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerLeft(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[RIGHT], direction * -1);
    }
}

void rotateCubeFront(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[FRONT], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerFront(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[BACK], direction * -1);
    }
}

void rotateCubeRight(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[RIGHT], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerRight(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[LEFT], direction * -1);
    }
}

void rotateCubeBack(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[BACK], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerBack(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[FRONT], direction * -1);
    }
}

void rotateCubeDown(RubikCube *cube, int layer_count, int direction) {
    rotateFace(cube->faces[DOWN], direction);
    for (int layer = 0; layer < layer_count; layer++) {
        rotateLayerDown(cube, layer, direction);
    }
    if (layer_count == N) {
        rotateFace(cube->faces[UP], direction * -1);
    }
}

void rotateCube(RubikCube *cube, int face, int layer_count, int direction) {
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

void execute_command(RubikCube *cube, const Command *command) {
    if (command->Angle == SIMPLE) {
        rotateCube(cube, command->Side, command->LayerCount, CLOCKWISE);
    } else if (command->Angle == MINUS_SIMPLE) {
        rotateCube(cube, command->Side, command->LayerCount, COUNTERCLOCKWISE);
    } else if (command->Angle == SEMI_FULL) {
        rotateCube(cube, command->Side, command->LayerCount, CLOCKWISE);
        rotateCube(cube, command->Side, command->LayerCount, CLOCKWISE);
    }
}

int main(void) {
    RubikCube cube;
    initializeCube(&cube);

    int input;
    while ((input = getchar()) != EOF) {
        if (input == '.') {
            break;
        }
        if (input == '\n') {
            printCube(&cube);
            continue;
        }

        Command command = {0};
        if (isalpha(input)) {
            command.LayerCount = 1;
            ungetc(input, stdin);
        } else {
            while (isdigit(input)) {
                command.LayerCount = command.LayerCount * 10 + (input - '0');
                input = getchar();
            }
            ungetc(input, stdin);
        }

        // Handle Side (using if-else with defined constants)
        input = getchar();
        if (input == 'u') {
            command.Side = UP;
        } else if (input == 'l') {
            command.Side = LEFT;
        } else if (input == 'f') {
            command.Side = FRONT;
        } else if (input == 'r') {
            command.Side = RIGHT;
        } else if (input == 'b') {
            command.Side = BACK;
        } else if (input == 'd') {
            command.Side = DOWN;
        } else {
            return 1;  // Handle invalid side input
        }

        // Read the next input for Angle
        input = getchar();
        if (input == '\'') {
            command.Angle = MINUS_SIMPLE;
        } else if (input == '"') {
            command.Angle = SEMI_FULL;
        } else {
            command.Angle = SIMPLE;
            ungetc(input, stdin);
        }
        execute_command(&cube, &command);
    }
    return 0;
}