#include <math.h>
#include <time.h>
#include <complex.h>

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


//The wave format struct, the format's specifications are avaible on: http://soundfile.sapp.org/doc/WaveFormat/
//Char fields should have lenght 5 we add a byte in order to insert the nul terminator (\0)
struct  Wave{
    char ChunkID[5];
    int  ChunkSize;
    char Format[5];
    char Subchunk1ID[5];
    int Subchunk1Size;
    short int AudioFormat;
    short int NumChannels;
    int SampleRate;
    int ByteRate;
    short int BlockAlign;
    short int BitsPerSample;
    char Subchunk2ID[5];
    int Subchunk2Size;
    int * data;
};

//The spectrum struct. It contains an array of complex number and the size of the array
struct Spectrum{
    double complex * values;
    int size; 
};

//Support function to generate a random double between 0 and 1
double generate_rand(){
    srand(time(NULL));
    double random = ((double) rand())/((double) RAND_MAX);
    return random;
}

//This function is used to load a wav file into a wave struct
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

    //close the file
    fclose(fpointer);
};

//This function saves a signal in a .wav file 
void savewave(char * filename, struct Wave * signal){
    //Create the new wav file
    FILE * fpointer = fopen(filename , "wb");
    if (fpointer == NULL){
        perror("Unable to create the file");
    }
if (fwrite(&(signal->ChunkID), ChunkId_size - 1, 1, fpointer) != 1) {
        perror("Error writing ChunkID");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->ChunkSize), ChunkSize_size, 1, fpointer) != 1) {
        perror("Error writing ChunkSize");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->Format), Format_size - 1, 1, fpointer) != 1) {
        perror("Error writing Format");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->Subchunk1ID), Subchunk1ID_size - 1, 1, fpointer) != 1) {
        perror("Error writing Subchunk1ID");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->Subchunk1Size), Subchunk1Size_size, 1, fpointer) != 1) {
        perror("Error writing Subchunk1Size");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->AudioFormat), AudioFormat_size, 1, fpointer) != 1) {
        perror("Error writing AudioFormat");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->NumChannels), NumChannels_size, 1, fpointer) != 1) {
        perror("Error writing NumChannels");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->SampleRate), SampleRate_size, 1, fpointer) != 1) {
        perror("Error writing SampleRate");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->ByteRate), ByteRate_size, 1, fpointer) != 1) {
        perror("Error writing ByteRate");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->BlockAlign), BlockAlign_size, 1, fpointer) != 1) {
        perror("Error writing BlockAlign");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->BitsPerSample), BitsPerSample_size, 1, fpointer) != 1) {
        perror("Error writing BitsPerSample");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->Subchunk2ID), Subchunk2ID_size - 1, 1, fpointer) != 1) {
        perror("Error writing Subchunk2ID");
        fclose(fpointer);
        return;
    }

    if (fwrite(&(signal->Subchunk2Size), Subchunk2Size_size, 1, fpointer) != 1) {
        perror("Error writing Subchunk2Size");
        fclose(fpointer);
        return;
    }

    if (fwrite(signal->data, signal->Subchunk2Size, 1, fpointer) != 1) {
        perror("Error writing signal data");
        fclose(fpointer);
        return;
    }

    // Close the file
    fclose(fpointer);
}

//This function creates random interference int the loaded wave 
void random_interference(struct Wave * signal){
    for(int i = 0; i < (signal->Subchunk2Size/sizeof(int)); i++){
        int perturbed = round((*(signal->data + i) * generate_rand()) + *(signal->data + i) );
        (*(signal->data + i)) = perturbed;
    }
}

//This function perform a dft using the standard formula
struct Spectrum dft(struct Wave * signal){
    int N = (signal->Subchunk2Size/sizeof(int));
    double complex * spectrum = malloc(N*sizeof(double complex));
    for(int k = 0; k < N; k++ ){
        double complex Xk =  {0.0f};
        for(int n = 0; n < N ; n++ ){
            double complex X0 = ((double)*(signal->data +n )) * cexp( (double)-2 * I * M_PI * (double)n * (double)k * ((double)1/((double)N)) ); 
            Xk += X0;
            }
        spectrum[k] = Xk;
    }
    struct Spectrum output_fourier;
    output_fourier.values = spectrum;
    output_fourier.size = signal->Subchunk2Size/sizeof(int);
    return output_fourier;
}



//This function perfom a dfat using the standard formula
int * dfat(struct Spectrum * spectrum){
    int K = spectrum->size;
    int * signal_values = malloc(K*sizeof(int));
    for(int n = 0; n < K ; n++ ){
        double complex Xn = {0.0f};
        for(int k = 0; k < spectrum->size ; k++ ){
            double complex X0 = ((double complex)*(spectrum->values +k )) * cexp( (double)2 * I  * M_PI * (double)k * (double)n * ((double)1/((double)K))); 
            Xn += X0;
        }
        Xn /= (double)(spectrum->size); 
        signal_values[n] = (int)creal(Xn);
    }
    return signal_values;
}

