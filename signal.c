#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int main(){
    struct Wave wave;
    loadwave("file.wav", &wave);
    random_interference(&wave);
    savewave("myw2.wav", &wave);




};