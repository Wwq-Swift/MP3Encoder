//
//  mp3_encoder.cpp
//  MP3Encoder
//
//  Created by kris.wang on 2020/4/29.
//  Copyright © 2020 kris.wang. All rights reserved.
//

#include "mp3_encoder.hpp"
#include "CBridging.h"

Mp3Encoder::Mp3Encoder() {
}

Mp3Encoder::~Mp3Encoder() {
}


///读取二进制的形式打开pcm文件，以写入二进制的文件打开MP3文件，然后初始化LAME
int Mp3Encoder::Init(const char* pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate) {
    int ret = -1;
    pcmFile = fopen(pcmFilePath, "rb");
    if(pcmFile) {
        mp3File = fopen(mp3FilePath, "wb");
        if(mp3File) {
            lameClient = lame_init();
            lame_set_in_samplerate(lameClient, sampleRate);
            lame_set_out_samplerate(lameClient, sampleRate);
            lame_set_num_channels(lameClient, channels);
            lame_set_brate(lameClient, bitRate / 1000);
            lame_init_params(lameClient);
            ret = 0;
        }
    }
    return ret;
}

int WQMp3Encoderinit(void* model, const char* pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate) {
    Mp3Encoder* m = (Mp3Encoder*)model;
    return m->Init(pcmFilePath, mp3FilePath, sampleRate, channels, bitRate);
}

void* Mp3Encoder_init() {
    return new Mp3Encoder();
}

void Mp3Encoder_Destory(void* model) {
    Mp3Encoder* m = (Mp3Encoder*)model;
    m->Destory();
    delete m;
}
void Mp3Encoder_Encode(void* model) {
    Mp3Encoder* m = (Mp3Encoder*)model;
    m->Encode();
}

/// 主体是一个循环，每次都会读取一段bufferSize大小的pcm数据buffer，然后再编写buffer，编写之前拆分左右声道再送入lLAME编写器，最后将编码之后的数据写入MP3中。
void Mp3Encoder::Encode() {
    int bufferSize = 1024 * 256;
    short* buffer = new short[bufferSize / 2];
    short* leftBuffer = new short[bufferSize / 4];
    short* rightBuffer = new short[bufferSize / 4];
    unsigned char* mp3_buffer = new unsigned char[bufferSize];
    size_t readBufferSize = 0;
    while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {
        for (int i = 0; i < readBufferSize; i++) {
            if (i % 2 == 0) {
                leftBuffer[i / 2] = buffer[i];
            } else {
                rightBuffer[i / 2] = buffer[i];
            }
        }
        size_t wroteSize = lame_encode_buffer(lameClient, (short int *) leftBuffer, (short int *) rightBuffer, (int)(readBufferSize / 2), mp3_buffer, bufferSize);
        fwrite(mp3_buffer, 1, wroteSize, mp3File);
    }
    delete[] buffer;
    delete[] leftBuffer;
    delete[] rightBuffer;
    delete[] mp3_buffer;
}

/// 销毁方法，关闭PCM文件，关闭MP3文件，销毁LAME
void Mp3Encoder::Destory() {
    if(pcmFile) {
        fclose(pcmFile);
    }
    if(mp3File) {
        fclose(mp3File);
        lame_close(lameClient);
    }
}
