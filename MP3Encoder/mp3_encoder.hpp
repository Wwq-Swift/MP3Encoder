//
//  mp3_encode.hpp
//  MP3Encoder
//
//  Created by kris.wang on 2020/4/29.
//  Copyright © 2020 kris.wang. All rights reserved.
//

#ifndef mp3_encoder_hpp
#define mp3_encoder_hpp

#include <stdio.h>
#include "lame.h"


/// MP3编码
class Mp3Encoder {
private:
    FILE* pcmFile;
    FILE* mp3File;
    lame_t lameClient;

public:
    Mp3Encoder();
    ~Mp3Encoder();

    int Init(const char* pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);
    void Encode();
    void Destory();
};

#endif /* mp3_encoder_h */
