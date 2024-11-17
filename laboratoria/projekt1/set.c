#include <stdio.h>
#include <stdlib.h>

#define MAX_CARDS 81 // 3 * 3 * 3 * 3 = 81 possible cards

typedef struct {
    int number;      // Number of shapes (1, 2, or 3)
    int color;       // Color (red, green, or purple)
    int fill;        // Fill type (empty, striped, or solid)
    int shape;       // Shape (diamond, wave, or oval)
} Card;

// Reads a deck of cards from standard input (stdin).
// Parameters:
// - deck[]: Array to store the cards read from stdin.
// Returns:
// - The total number of cards read from stdin and stored in the deck[].
int read_deck(Card deck[]) {
    card_count = 0
    char x;
    while ((x = getchar()) != EOF && card_count < MAX_CARDS) {
        if (!isspace(x)) {
            deck[card_count].number = x - '0';
            deck[card_count].color = getchar() - '0';
            deck[card_count].fill = getchar() - '0';
            deck[card_count].shape = getchar() - '0';

            card_count++;
        }
    }
    return card_count;
}

// Function to reverse a deck.
void reverse_deck(Card deck[], int deck_size) {
    int start = 0;
    int end = deck_size - 1;

    // Swap the cards from the start and end
    while (start < end) {
        Card temp = deck[start];
        deck[start] = deck[end];
        deck[end] = temp;

        start++;
        end--;
    }
}

// Transfers cards from the deck to the table.
// Parameters:
// - table[]: Array to store cards on the table.
// - table_size: Current number of cards on the table.
// - deck[]: Array representing the deck of cards.
// - deck_size: Current number of cards on the deck.
// - cards_to_add: Number of cards to transfer from the deck to the table.
void transfer_cards_to_table(Card table[], int table_size, Card deck[], int deck_size, int cards_to_add) {
    for (int i = 0; i < cards_to_add; i++) {
        table[table_size + i] = deck[deck_size - 1 - i]
    }
}

// Function to print out the table.
void print_table(Card table[], int table_size) {
    printf("= ");
    for (int i = 0; i < table_size; i++) {
        printf("%d%d%d%d ", table[i].number, table[i].color, table[i].fill, table[i].shape);
    }
    printf("\n");
}

// Function to print out the set.
void print_set(Card table[], int set_indices) {
    printf("- ");
    for (int i = 0; i < 3; i++) {
        int index = set_indices[i];
        printf("%d%d%d%d ", table[index].number, table[index].color, table[index].fill, table[index].shape);
    }
    printf("\n");
}

// Function to check if three cards are set.
int is_set(Card card1, Card card2, Card card3) {
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
                    return 1;  // All attributes match the set condition
                }
            }
        }
    }
    return 0;  // Not a set
}

// Function to find a set.
int* find_set(Card table[], int table_size, int *set_indices) {
    for (int i = 0; i < table_size - 2; i++) {
        for (int j = i + 1; j < table_size - 1; j++) {
            for (int k = j + 1; j < table_size; k++) {
                if (is_set(table[i], table[j], table[k])) {
                    set_indices[0] = i;
                    set_indices[1] = j;
                    set_indices[2] = k;
                    return set_indices
                }
            }
        }
    }
}

// Function to remove set cards from the table.
void remove_set(Card table[], int table_size, int set_indices) {
    for (int i = 0; i < 3; i++) {
        int index = set_indices[i];
        for (j = index; j < table_size - 1; j++) {
            table[j] = table[j + 1];
        }
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
    int cards_to_add;

    if (deck_card_count > 12) cards_to_add = 12;
    else cards_to_add = deck_card_count;
    transfer_cards_to_table(table, table_card_count, deck, deck_card_count, cards_to_add);
    table_card_count += cards_to_add;
    deck_card_count -= cards_to_add;

    int set_indices[3];  // Array to store the indices of the set
    bool set_found = true;
    // While deck not empty. If empty and set not found end.
    while (deck_card_count > 0 || set_found) {
        print_table(table, table_card_count);
        int* set = find_set(table, table_card_count, set_indices);
        if (set != NULL) {
            print_set(table, set_indices);
            remove_set(table, table_card_count, set_indices);
            table_card_count -= 3;

            if (table_card_count < 12) {
                cards_to_add = 3;
            } else {
                cards_to_add = 0;
            }
        } else {
            set_found = false;
            cards_to_add = 3;
        }

        if (cards_to_add > 0 && deck_card_count >= cards_to_add) {
            printf("+\n")
            transfer_cards_to_table(table, table_card_count, deck, deck_card_count, cards_to_add);
            table_card_count += cards_to_add;
            deck_card_count -= cards_to_add;
        }
    }
}