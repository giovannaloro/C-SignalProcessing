
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

