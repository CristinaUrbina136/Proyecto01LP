
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

// Print byteArray data
void showByteArray(Connections c, int card) {
    showByteArrayAux(c.cards[card]);
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
