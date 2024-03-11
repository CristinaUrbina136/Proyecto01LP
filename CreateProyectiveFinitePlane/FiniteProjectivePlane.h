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

Connections setCards() {
    Connections cards = createConnections();   // This saves all the cards created
    Connections notInclude = createConnections(); // The values I must not use per card
    int currentCard = 0;
    while (currentCard < N) {  // Tries to create a card
        int k = 0; // Number of objects in currentCard
        ByteArray mod = createByteArray(); // Modifications made in currentCard

            // PRINTS (DELETE LATER)
        printf("Card #%d\n", currentCard);
        printf("NOT INCLUDE: \t");
        showByteArray(notInclude, currentCard);
        printf("\tNode -> [ ");

        // Checks in connections for the first r cards available
        for (int connectionID = 0; connectionID < connections.size; connectionID++) {
            // If k == r no more cards will be added to node, and if notInclude has the id ON, we should not test it
            if (k < r && !isOnBit(notInclude, currentCard, connectionID)) {
                // mod has the ids already connected, so lets check if the actual id doesn't collide
                if (has0(connections, connectionID) && !andCards(connections, connectionID, mod)) {
                    k++;
                    turnOnBitAux(mod, connectionID);
                    printf("%d ", connectionID); //////////
                }
            }
        }

        printf("] | k = %d\n", k); ///////////

        // I need this if to work for r > 5::In r > 5 it loops (need fix)
        if (k == 0) {      // There is no more possible combinations for currentCard
            if (currentCard == 0) {  // This should only happen on r = 7
                printf("Error, no logro respuesta\n");
                return cards;
            }
            // Restart notInclude bits on this card
            setAllTo0(notInclude, currentCard);
            // There is no possible combination so try above by burning the first node
            ByteArray lastCard = cards.cards[--currentCard];
            // XOR connections in node to revert changes
            xorCards(connections, lastCard);
            // Add the last 1 from that currentCard to exclusions (And erase further ones)
            int last1Found = last1Aux(lastCard);
            turnOnBit(notInclude, currentCard, last1Found);
            setTo0FromIndex(notInclude, currentCard, last1Found);
            // Delete last card data from result
            setAllTo0Aux(cards.cards[currentCard]);
        } else if (k < r) {     // Wrong combination (Try again)
            // Check if there is another solution by removing the last number from the node
            int last1Found = last1Aux(mod);
            turnOnBit(notInclude, currentCard, last1Found);
            setTo0FromIndex(notInclude, currentCard, last1Found);
        } else {        // Good combination
            orCardsAux(cards.cards[currentCard++], mod);
            // Set the changes into connections
            orCards(connections, mod);
        }
        // Free memory of mod
        freeSpaceByteArray(&mod);
    }
    // Free memory of notInclude
    freeSpaceConnections(&notInclude);
    // result
    return cards;
}

#endif //TRYCONNECTIONDB_FINITEPROJECTIVEPLANE_H
