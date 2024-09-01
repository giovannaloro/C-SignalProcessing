#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wave.h"

int main(){
    
    struct Wave wave;
    loadwave("mosk.wav", &wave);
    savewave("faled_saved.wav", &wave);
    //random_interference(&wave);
    struct Spectrum spectrum = dft(&wave);
    wave.data=dfat(&spectrum);
    savewave("saved333.wav", &wave);
};