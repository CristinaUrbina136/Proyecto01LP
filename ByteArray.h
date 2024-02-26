
#ifndef TRYCONNECTIONDB_BYTEARRAY_H
#define TRYCONNECTIONDB_BYTEARRAY_H

//#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

const int r = 9;                            // Number of images per card and Number of times an image appears in the whole game
const int N = (r * r) - r + 1;              // Total of cards and Total of images
const int bytes = (N / 4) + (N % 4 > 0);    // Number of bytes needed to save all the data

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
    return byteArray;
}

// Turns a bit into 1
void turnOnBitAux(ByteArray b, int bit) {
    const int slot = bit / 4;
    const int shift = bit % 4;
    b.data[slot] |= (1U << shift);
}

// Turns a bit into 0
void turnOffBitAux(ByteArray b, int bit) {
    const int slot = bit / 4;
    const int shift = bit % 4;
    b.data[slot] &= ~(1U << shift);
}

// Check the value of a bit
bool isOnBitAux(ByteArray b, int bit) {
    const int slot = bit / 4;
    const int shift = bit % 4;
    return (b.data[slot] & (1U << shift));
}

// Print byteArray data
void showByteArrayAux(ByteArray b){
    for (int i = 0; i < b.size; i++) {
        printf("%b | ", b.data[i]);
    }
    printf("\n");
}

// Free the space of ByteArray location
/*
void freeSpaceByteArray(ByteArray *binArray) {
    free(binArray->data);
    free(binArray);
}
 */

#endif //TRYCONNECTIONDB_BYTEARRAY_H
