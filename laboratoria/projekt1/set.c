#include <stdio.h>

#define MAX_CARDS 81 // 3 * 3 * 3 * 3 = 81 possible cards
#define SET_SIZE 3
#define DRAW_SIZE 3 // Number of cards to draw from the deck
#define TABLE_SIZE 12

typedef struct {
    int number;      // Number of shapes (1, 2, or 3)
    int color;       // Color (red, green, or purple)
    int fill;        // Fill type (empty, striped, or solid)
    int shape;       // Shape (diamond, wave, or oval)
} Card;


// Reads a deck of cards from standard input (stdin).
int read_deck(Card deck[]) {
    int card_count = 0;
    int x;
    while ((x = getchar()) != EOF && card_count < MAX_CARDS) {
        if (x != ' ' && x != '\n' && x != '\t') {
            deck[card_count].number = x - '0';
            deck[card_count].color = getchar() - '0';
            deck[card_count].fill = getchar() - '0';
            deck[card_count].shape = getchar() - '0';

            card_count++;
        }
    }
    return card_count;
}


void reverse_deck(Card deck[], const int deck_size) {
    int start = 0;
    int end = deck_size - 1;

    // Swap the cards from the start and end
    while (start < end) {
        const Card temp = deck[start];
        deck[start] = deck[end];
        deck[end] = temp;

        start++;
        end--;
    }
}


void print_table(Card table[], const int table_card_count) {
    printf("=");
    for (int i = 0; i < table_card_count; i++) {
        printf(" %d%d%d%d", table[i].number, table[i].color, table[i].fill, table[i].shape);
    }
    printf("\n");
}


void print_set(Card table[], const int set_indices[]) {
    printf("-");
    for (int i = 0; i < SET_SIZE; i++) {
        printf(" %d%d%d%d", table[set_indices[i]].number, table[set_indices[i]].color, table[set_indices[i]].fill, table[set_indices[i]].shape);
    }
    printf("\n");
}


int is_set(const Card card1, const Card card2, const Card card3) {
    // Check the 'number' attribute
    if ((card1.number == card2.number && card2.number == card3.number) ||
        (card1.number != card2.number && card2.number != card3.number && card1.number != card3.number)) {
        // Check the 'color' attribute
        if ((card1.color == card2.color && card2.color == card3.color) ||
            (card1.color != card2.color && card2.color != card3.color && card1.color != card3.color)) {
            // Check the 'fill' attribute
            if ((card1.fill == card2.fill && card2.fill == card3.fill) ||
                (card1.fill != card2.fill && card2.fill != card3.fill && card1.fill != card3.fill)) {
                // Check the 'shape' attribute
                if ((card1.shape == card2.shape && card2.shape == card3.shape) ||
                    (card1.shape != card2.shape && card2.shape != card3.shape && card1.shape != card3.shape)) {
                    return 0;  // All attributes match the set condition
                }
            }
        }
    }
    return 1;  // Not a set
}


int find_set(Card table[], const int table_card_count, int set_indices[]) {
    for (int i = 0; i < table_card_count - 2; i++) {
        for (int j = i + 1; j < table_card_count - 1; j++) {
            for (int k = j + 1; k < table_card_count; k++) {
                if (is_set(table[i], table[j], table[k]) == 0) {
                    set_indices[0] = i;
                    set_indices[1] = j;
                    set_indices[2] = k;
                    return 0; // Set found
                }
            }
        }
    }
    return 1; // Set not found
}


// Function to remove set cards from the table.
void remove_set(Card table[], int *table_card_count, const int set_indices[]) {
    int removed = 0;
    for (int i = 0; i < *table_card_count; i++) {
        if (i == set_indices[0] || i == set_indices[1] || i == set_indices[2]) {
            removed++;
        } else {
            table[i - removed] = table[i];
        }
    }
    *table_card_count -= SET_SIZE;
}


void handle_set_found(Card table[], int *table_card_count, int set_indices[]) {
    print_set(table, set_indices);
    remove_set(table, table_card_count, set_indices);
}


void draw_cards(Card table[], int *table_card_count, Card deck[], int *deck_card_count, const int cards_to_add) {
    for (int i = 0; i < cards_to_add && *deck_card_count > 0; i++) {
        table[*table_card_count] = deck[*deck_card_count - 1];
        (*table_card_count)++;
        (*deck_card_count)--;
    }
}


int main(void) {
    // Reading deck from stdin
    Card deck[MAX_CARDS];
    int deck_card_count = read_deck(deck);
    reverse_deck(deck, deck_card_count);

    // Filling table with cards from deck.
    Card table[MAX_CARDS];
    int table_card_count = 0;
    draw_cards(table, &table_card_count, deck, &deck_card_count, TABLE_SIZE);

    while (1) {
        print_table(table, table_card_count);

        int set_indices[SET_SIZE];
        // If set is found
        if (find_set(table, table_card_count, set_indices) == 0) {
            handle_set_found(table, &table_card_count, set_indices);

            // If there are fewer than 12 cards on the table, draw more.
            if (table_card_count < TABLE_SIZE && deck_card_count > 0) {
                draw_cards(table, &table_card_count, deck, &deck_card_count, DRAW_SIZE);
            }
        }
        // If no set is found and there are cards left in the deck.
        else if (deck_card_count >= SET_SIZE) {
            printf("+\n");
            draw_cards(table, &table_card_count, deck, &deck_card_count, DRAW_SIZE);
        }
        // Break if no set is found and the deck is empty.
        else {
            break;
        }
    }
    return 0;
}