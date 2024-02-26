//
// Created by fish on 25/02/24.
//
#include "Connections.h"

int main() {
    Connections c = createConnections();
    showByteArray(c,0);
    turnOnBit(c,0,11);
    printf("bool: %b \n", isOnBit(c,0, 11));
    showByteArray(c,0);
    turnOffBit(c,0, 11);
    printf("bool(2): %b \n", isOnBit(c,0, 11));
    showByteArray(c,0);
}
