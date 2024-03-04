//
// Created by fish on 26/02/24.
//

#ifndef TRYCONNECTIONDB_FINITEPROJECTIVEPLANE_H
#define TRYCONNECTIONDB_FINITEPROJECTIVEPLANE_H
#include "Connections.h"

Connections connections;

// Set everything to 0
void setConnections() {
    connections = createConnections();
}

int** makeMatrix(int rows, int columns) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(columns * sizeof(int));
    }
    for (int j = 0; j < rows; j++) {
        for (int k = 0; k < columns; k++) {
            matrix[j][k] = 0;
        }
    }
    return matrix;
}


int** setCards() {
    int** cards = makeMatrix(N, r);     // Matrix[N][r] to store the result of the algorithm
    ByteArray notInclude = createByteArray();   // The values I must not use
    int card = 0;
    while (card < N) {  // Tries to create a card
        int node[r];    // Taking the 1s from mod is "bit" long, so... lets save them here
        int lenNode = 0; // Number of objects per card
        printf("Card #%d\n", card);
        ByteArray mod = createByteArray(); // Modifications made in cards
        for (int connectionID = 0; connectionID < connections.size; connectionID++) {
            // If len == r no more cards will be added to node, and if notInclude has the id ON, we should not test it
            if (lenNode < r && !isOnBitAux(notInclude, connectionID)) {
                // mod has the ids already connected, so lets check if the actual id doesn't collide
                if (has0(connections, connectionID) && !andCards(connections, connectionID, mod)) {
                    node[lenNode++] = connectionID;
                    turnOnBitAux(mod, connectionID);
                }
            }
        }
        printf("Nodes -> ");
        for (int i = 0; i < lenNode; i++) {
            printf("%d - ", node[i]);
        }
        printf("\n");
        if (lenNode == 0) {      // There is no more possible combinations for card
            // No existe ninguna combinacion posible asi que intenta arriba quitando el primer nodo
            card--;
            setAllTo0Aux(notInclude);
            turnOnBitAux(notInclude, last1(connections, card));
        } else if (lenNode < r) {     // Wrong combination (Try again)
            // Busca si existe otra solucion quitando el ultimo numero del nodo
            int id = last1Aux(mod);
            turnOnBitAux(notInclude, last1Aux(mod));
        } else {        // Good combination
            cards[card++] = node;
            orCards(connections, mod);
            setAllTo0Aux(notInclude);
            /*
            for (int i = 0; i < lenNode; i++) {
                printf("%d", cards[card - 1][i]);
            }
            printf("\n");
             */
        }
        freeSpaceByteArray(&mod);
    }
    freeSpaceByteArray(&notInclude);
/*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d\n", cards[i][j]);
        }
    }
*/
    return cards;
}

#endif //TRYCONNECTIONDB_FINITEPROJECTIVEPLANE_H
