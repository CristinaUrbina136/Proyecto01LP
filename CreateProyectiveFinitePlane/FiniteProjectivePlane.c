//
// Created by fish on 25/02/24.
//
#include "FiniteProjectivePlane.h"


int main() {
    setConnections();
    Connections cards = setCards();
    //showConnections(cards);
    freeSpaceConnections(&cards);
    freeSpaceConnections(&connections);
}
