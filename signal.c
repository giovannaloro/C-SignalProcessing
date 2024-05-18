#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

//definition of field lenght in byte
#define ChunkId_size 5
#define ChunkSize_size 4
#define Format_size 5
#define Subchunk1ID_size 5
#define Subchunk1Size_size 4
#define AudioFormat_size 2
#define NumChannels_size 2
#define SampleRate_size 4
#define ByteRate_size 4
#define BlockAlign_size 2
#define BitsPerSample_size 2
#define Subchunk2ID_size 5
#define Subchunk2Size_size 4
//definition of byte size
#define byte_size 1



void * loadwave(char * filename, struct Wave * signal){

    //load the file
    FILE * fpointer = fopen(filename, "r");
    if (fpointer == NULL){
        perror("Unable to open the file");
        return NULL;
    }

    //for char fields we only load field_size - 1 bytes and then add the nul terminator manually
    if (fread(&signal->ChunkID, byte_size, ChunkId_size - 1, fpointer) != ChunkId_size - 1){
        perror("Unable to load ChunkID");
        fclose(fpointer);
        return NULL;
    }
    signal->ChunkID[ChunkId_size - 1] = '\0';  // Null-terminate the string

    if (fread(&signal->ChunkSize, byte_size, ChunkSize_size, fpointer) != ChunkSize_size) {
        perror("Unable to load ChunkSize");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->Format, byte_size, Format_size - 1, fpointer) != Format_size - 1) {
        perror("Unable to load Format");
        fclose(fpointer);
        return NULL;
    }
    signal->Format[Format_size - 1] = '\0';  // Null-terminate the string

    if (fread(&signal->Subchunk1ID, byte_size, Subchunk1ID_size - 1, fpointer) != Subchunk1ID_size - 1) {
        perror("Unable to load Subchunk1ID");
        fclose(fpointer);
        return NULL;
    }
    signal->Subchunk1ID[Subchunk1ID_size - 1] = '\0';  // Null-terminate the string

    if (fread(&signal->Subchunk1Size, byte_size, Subchunk1Size_size, fpointer) != Subchunk1Size_size) {
        perror("Unable to load Subchunk1Size");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->AudioFormat, byte_size, AudioFormat_size, fpointer) != AudioFormat_size) {
        perror("Unable to load AudioFormat");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->NumChannels, byte_size, NumChannels_size, fpointer) != NumChannels_size) {
        perror("Unable to load NumChannels");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->SampleRate, byte_size, SampleRate_size, fpointer) != SampleRate_size) {
        perror("Unable to load SampleRate");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->ByteRate, byte_size, ByteRate_size, fpointer) != ByteRate_size) {
        perror("Unable to load ByteRate");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->BlockAlign, byte_size, BlockAlign_size, fpointer) != BlockAlign_size) {
        perror("Unable to load BlockAlign");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->BitsPerSample, byte_size, BitsPerSample_size, fpointer) != BitsPerSample_size) {
        perror("Unable to load BitsPerSample");
        fclose(fpointer);
        return NULL;
    }

    if (fread(&signal->Subchunk2ID, byte_size ,Subchunk2ID_size - 1, fpointer) != Subchunk2ID_size - 1) {
        perror("Unable to load Subchunk2ID");
        fclose(fpointer);
        return NULL;
    }
    signal->Subchunk2ID[Subchunk2ID_size - 1] = '\0';  // Null-terminate the string

    if (fread(&signal->Subchunk2Size, byte_size, Subchunk2Size_size, fpointer) != Subchunk2Size_size) {
        perror("Unable to load Subchunk2Size");
        fclose(fpointer);
        return NULL;
    }

    //allocate memory for the signal data and load it
    signal->data = malloc(signal->Subchunk2Size*byte_size);
    if (signal->data == NULL){
        perror("unable to allocate memory");
        return NULL;
    }

    if (fread(signal->data, byte_size, signal->Subchunk2Size, fpointer) != signal->Subchunk2Size) {
        perror("Unable to load signal data");
        fclose(fpointer);
        return NULL;
    }

    //close the file an return the wave
    fclose(fpointer);
};

int main(){
    struct Wave wave;
    loadwave("file.wav", &wave);
    printf("%s \n", wave.ChunkID);
    for (int i = 0; i<wave.Subchunk2Size/8; i++){
        printf("%d ", *(&wave.Subchunk2Size + i));
    }

};