//
//  CBridging.h
//  MP3Encoder
//
//  Created by kris.wang on 2020/4/29.
//  Copyright © 2020 kris.wang. All rights reserved.
//

#ifndef CBridging_h
#define CBridging_h

typedef void* WQMp3Encoder;

#ifdef __cplusplus
extern "C" {
#endif
    void printHellow(void);
    int getRandomInt(void);

//    void Destory();

    int WQMp3Encoderinit(WQMp3Encoder model, const char* pcmFilePath, const char *mp3FilePath, int sampleRate, int channels, int bitRate);

    WQMp3Encoder Mp3Encoder_init();
    void Mp3Encoder_Destory(WQMp3Encoder model);
    void Mp3Encoder_Encode(WQMp3Encoder model);
    
#ifdef __cplusplus
}
#endif

#endif /* CBridging_h */
