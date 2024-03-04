
#ifndef TRYCONNECTIONDB_BYTEARRAY_H
#define TRYCONNECTIONDB_BYTEARRAY_H

//#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

const int r = 5;                            // Number of images per card and Number of times an image appears in the whole game
const int N = (r * r) - r + 1;              // Total of cards and Total of images
const int bytes = (N / 8) + (N % 8 > 0);    // Number of bytes needed to save all the data

typedef struct {
    unsigned char *data;    // Array of chars (1 byte * size)
    int size;               // Number of bytes needed
} ByteArray;

// Constructor
ByteArray createByteArray() {
    ByteArray byteArray;
    byteArray.size = bytes;
    byteArray.data = malloc(byteArray.size * sizeof(unsigned char));
    if (byteArray.data == NULL) {
        printf("No se pudo alojar memoria para ByteArray");
        byteArray.size = -1;
    }
    for (int i = 0; i < byteArray.size; i++) {
        byteArray.data[i] = 0U;
    }
    return byteArray;
}

// Turns a bit into 1
void turnOnBitAux(ByteArray b, int bit) {
    const int slot = bit / 8;
    const int shift = bit % 8;
    b.data[slot] |= (1U << shift);
}

// Turns a bit into 0
void turnOffBitAux(ByteArray b, int bit) {
    const int slot = bit / 8;
    const int shift = bit % 8;
    b.data[slot] &= ~(1U << shift);
}

// Check the value of a bit
bool isOnBitAux(ByteArray b, int bit) {
    const int slot = bit / 8;
    const int shift = bit % 8;
    return (b.data[slot] & (1U << shift));
}

// Returns the id of the last 1 in the array
int last1Aux(ByteArray b) {     // There has to be a way to do it in O(1)!!!
    for (int id = N - 1; id >= 0; id--) {
        if (isOnBitAux(b, id)){
            return id;
        }
    }
    return -1;
}

// Returns the id of the first 0 in the array
int first0Aux(ByteArray b) {
    for (int id = 0; id < b.size; id++) {
        if (!isOnBitAux(b, id)) {
            return id;
        }
    }
    return -1;
}

// Counts all the 1s in the array
int countBitsAux(ByteArray b) {
    int count = 0;
    for (int i = 0; i < b.size; i++) {
        unsigned char copy = b.data[i];
        while (copy) {
            count += copy & 1;
            copy >>= 1;
        }
    }
    return count;
}

bool has0Aux(ByteArray b) {
    for (int slot = 0; slot < b.size; slot++) {
        if (b.data[slot] ^ 0b11111111) {
            return true;
        }
    }
    return false;
}

void setAllTo0Aux(ByteArray b) {
    for (int slot = 0; slot < b.size; slot++) {
        b.data[slot] &= 0;
    }
}

bool andCardsAux(ByteArray byteArray, ByteArray compare) {
    for (int slot = 0; slot < byteArray.size; slot++) {
        if (byteArray.data[slot] & compare.data[slot]) {
            return true;
        }
    }
    return false;
}

// This turns off a set of bits (1 ^ 1 = 0) ([1 | 0] ^ 0 = [1 | 0])
void xorCardsAux(ByteArray byteArray, ByteArray compare) {
    for (int slot = 0; slot < byteArray.size; slot++) {
        byteArray.data[slot] ^= compare.data[slot];
    }
}

// This turns on a set of bits
void orCardsAux(ByteArray byteArray, ByteArray compare) {
    for (int slot = 0; slot < byteArray.size; slot++) {
        byteArray.data[slot] |= compare.data[slot];
    }
}

// Print byteArray data
void showByteArrayAux(ByteArray b){
    for (int i = 0; i < b.size; i++) {
        printf("%b | ", b.data[i]);
    }
    printf("\n");
}

// Free the space of ByteArray location
void freeSpaceByteArray(ByteArray *binArray) {
    free(binArray->data);
}


#endif //TRYCONNECTIONDB_BYTEARRAY_H
