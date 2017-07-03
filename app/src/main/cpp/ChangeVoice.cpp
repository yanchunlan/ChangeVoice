#include <jni.h>
#include <string>
#include "com_example_yanchunlan_changevoice_VoiceUtil.h"
#include <fmod.hpp>
#include <android/log.h>
#include <unistd.h>
#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"zph",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"zph",FORMAT,##__VA_ARGS__);
#define TYPE_NORMAL  0
#define TYPE_LOLITA  1
#define TYPE_UNCLE   2
#define TYPE_THRILLER  3
#define TYPE_FUNNY  4
#define TYPE_ETHEREAL  5

using namespace FMOD;

JNIEXPORT void JNICALL Java_com_example_yanchunlan_changevoice_VoiceUtil_fix
        (JNIEnv *env, jclass jcls, jstring path_jstr, jint type) {
    LOGI("%s", "--> start");

    System *system;
    Sound *sound;
    DSP *dsp;
    Channel *channel;
    float frequency;
    bool isPlaying = true;

    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);
    const char *path_cstr = env->GetStringUTFChars(path_jstr, NULL);

    try {
        system->createSound(path_cstr, FMOD_DEFAULT, NULL, &sound);
        switch (type) {
            case TYPE_NORMAL:  // 普通
                LOGI("%s", path_cstr)
                system->playSound(sound, 0, false, &channel);
                LOGI("%s", "fix normal");
                break;
            case TYPE_LOLITA:  // 萝莉
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);    // 可改变音调
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 8.0);     // 8.0 为一个八度
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case TYPE_UNCLE:  // 大叔
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;

            case TYPE_THRILLER:   // 惊悚
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);       //可改变颤音
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 5);           // 时间偏移低频振荡周期
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case TYPE_FUNNY:  // 搞怪
                system->createDSPByType(FMOD_DSP_TYPE_NORMALIZE, &dsp);    //放大声音
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);

                channel->getFrequency(&frequency);
                frequency = frequency * 2;                                  //频率*2
                channel->setFrequency(frequency);
                break;
            case TYPE_ETHEREAL: // 空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);          // 控制回声
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);           // 延时
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);         // 回波衰减的延迟

                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }
    } catch (...) {
        LOGE("%s", "catch exception...")
        goto end;
    }

//    system->update();

    // 每隔一秒检测是否播放结束
    while (isPlaying) {
        channel->isPlaying(&isPlaying);
        usleep(1000 * 1000);
    }

    goto end;

    //释放资源
    end:
    env->ReleaseStringUTFChars(path_jstr, path_cstr);
    sound->release();
    system->close();
    system->release();
}
