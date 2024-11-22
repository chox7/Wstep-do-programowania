#include <stdio.h>

#define MAX_CARDS 81 // 3 * 3 * 3 * 3 = 81 possible cards
#define SET_SIZE 3
#define TABLE_SIZE 12

typedef struct {
    int number;      // Number of shapes
    int color;       // Color
    int fill;        // Fill type
    int shape;       // Shape
} Card;

// Reads a deck of cards from standard input (stdin) and returns the number of cards read.
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

// Reverses the order of the deck.
void reverse_deck(Card deck[], const int deck_size) {
    for (int i = 0; i < deck_size / 2; i++) {
        const Card temp = deck[i];
        deck[i] = deck[deck_size - 1 - i];
        deck[deck_size - 1 - i] = temp;
    }
}

// Prints the cards currently on the table.
void print_table(const Card table[], const int table_card_count) {
    printf("=");
    for (int i = 0; i < table_card_count; i++) {
        printf(" %d%d%d%d", table[i].number, table[i].color, table[i].fill, table[i].shape);
    }
    printf("\n");
}

// Prints the cards that form a set.
void print_set(const Card table[], const int set_indices[]) {
    printf("-");
    for (int i = 0; i < SET_SIZE; i++) {
        printf(" %d%d%d%d", table[set_indices[i]].number, table[set_indices[i]].color, table[set_indices[i]].fill, table[set_indices[i]].shape);
    }
    printf("\n");
}

// Checks if three attribute values form a valid set (all same or all different).
int is_attribute_valid(const int a, const int b, const int c) {
    return (a == b && b == c) || (a != b && b != c && a != c);
}

// Checks if three cards form a valid set.
int is_set(const Card card1, const Card card2, const Card card3) {
    return !(is_attribute_valid(card1.number, card2.number, card3.number) &&
           is_attribute_valid(card1.color, card2.color, card3.color) &&
           is_attribute_valid(card1.fill, card2.fill, card3.fill) &&
           is_attribute_valid(card1.shape, card2.shape, card3.shape));
}

// Finds a set among the cards on the table. Returns 0 if a set is found, 1 otherwise.
int find_set(const Card table[], const int table_card_count, int set_indices[]) {
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
    return 1; // No set found
}

// Removes the cards forming a set from the table.
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

// Draws cards from the deck to the table.
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

    // Filling table with cards from deck. Initial table setup.
    Card table[MAX_CARDS];
    int table_card_count = 0;
    draw_cards(table, &table_card_count, deck, &deck_card_count, TABLE_SIZE);

    while (1) {
        print_table(table, table_card_count);

        int set_indices[SET_SIZE];
        // If set is found
        if (find_set(table, table_card_count, set_indices) == 0) {
            print_set(table, set_indices);
            remove_set(table, &table_card_count, set_indices);

            // Draw more cards if the table has fewer than 12 cards
            if (table_card_count < TABLE_SIZE && deck_card_count > 0) {
                draw_cards(table, &table_card_count, deck, &deck_card_count, SET_SIZE);
            }
        }
        // If no set is found and there are cards left in the deck.
        else if (deck_card_count >= SET_SIZE) {
            printf("+\n");
            draw_cards(table, &table_card_count, deck, &deck_card_count, SET_SIZE);
        }
        // Break if no set is found and the deck is empty.
        else {
            break;
        }
    }
    return 0;
}