#include "Sound.h"


HWAVEOUT Sound::getHWO() {
    return hwo;
}



void Sound::SetLocalVolume(DWORD dwVolume) {
    wf.wFormatTag = WAVE_FORMAT_PCM;
    wf.nChannels = 1;
    wf.nSamplesPerSec = 8000 * 1000;
    wf.wBitsPerSample = 8;
    wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;
    wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;
    wf.cbSize = 0;

    for (UINT id = 0; id < waveOutGetNumDevs(); id++) {
        if (waveOutOpen(&hwo, id, &wf, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
            waveOutSetVolume(hwo, dwVolume);
            break;
        }
    }
}