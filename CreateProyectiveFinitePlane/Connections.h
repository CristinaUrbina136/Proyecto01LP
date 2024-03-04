
#ifndef TRYCONNECTIONDB_CONNECTIONS_H
#define TRYCONNECTIONDB_CONNECTIONS_H

#include "ByteArray.h"

// This struct is made to store the connections of each card
typedef struct {
    ByteArray *cards;
    int size;
} Connections;

// Constructor
Connections createConnections() {
    Connections connections;
    connections.size = N;
    connections.cards = malloc(connections.size * sizeof(ByteArray));
    if (connections.cards == NULL) {
        printf("No se pudo alojar memoria para Connections");
        connections.size = -1;
    }
    for (int card = 0; card < connections.size; card++) {
        connections.cards[card] = createByteArray();
    }
    return connections;
}

// Turns a bit into 1
void turnOnBit(Connections c, int card, int bit) {
    turnOnBitAux(c.cards[card], bit);
}

// Turns a bit into 0
void turnOffBit(Connections c, int card, int bit) {
    turnOffBitAux(c.cards[card], bit);
}

// Check the value of a bit
bool isOnBit(Connections c, int card, int bit) {
    return isOnBitAux(c.cards[card], bit);
}

// Returns the id of the last 1 in the array
int last1(Connections c, int card) {
    return last1Aux(c.cards[card]);
}

// Returns the id of the first 0 in the array
int first0(Connections c, int card) {
    return first0Aux(c.cards[card]);
}

// Counts all the 1s in the array
int countBits(Connections c, int card) {
    return countBitsAux(c.cards[card]);
}

bool has0(Connections c, int card) {
    return has0Aux(c.cards[card]);
}

bool andCards(Connections c, int card, ByteArray compare) {
    andCardsAux(c.cards[card], compare);
}

// Apply XOR of an array to arrays with the same id
void xorCards(Connections connections, ByteArray compare) {
    for (int id = 0; id < compare.size; id++) {
        if (isOnBitAux(compare, id)) {
            xorCardsAux(connections.cards[id], compare);
        }
    }
}

// This turns on a set of bits
void orCards(Connections connections, ByteArray compare) {
    for (int id = 0; id < connections.size; id++) {
        if (isOnBitAux(compare, id)) {
            orCardsAux(connections.cards[id], compare);
        }
    }
}

// Print byteArray data
void showByteArray(Connections c, int card) {
    showByteArrayAux(c.cards[card]);
}

// Print all the connections
void showConnections(Connections c) {
    for (int i = 0; i < c.size; i++) {
        printf("Card #%d: \n", i + 1);
        showByteArray(c, i);
    }
}

// Free the space of Connections location
/*
void freeSpaceConnections(Connections *connections){
    for (int i = 0; i < connections->size; i++) {
        freeSpaceByteArray(&connections->cards[i]);
    }
    free(connections->cards);
    free(connections);
}
 */

#endif //TRYCONNECTIONDB_CONNECTIONS_H
