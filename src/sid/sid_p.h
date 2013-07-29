#ifndef SID_P_H
#define SID_P_H

#include "lmms_lv2.h"
#include "resid.h"

//http://www.waitingforfriday.com/index.php/Commodore_SID_6581_Datasheet
enum sid_ports {
    SID_CONTROL = 0,
    SID_OUT,

    SID_VOLUME,
    SID_CHIP,
    SID_LPF,
    SID_BP,
    SID_HPF,
    SID_RES,
    SID_CUTOFF,

    //voices
    SID_V1_CHANNEL,
    SID_V1_PORTAMENTO,
    SID_V1_ATT,
    SID_V1_DEC,
    SID_V1_SUS,
    SID_V1_REL,
    SID_V1_PW,
    SID_V1_OCTAVE,
    SID_V1_DETUNE,
    SID_V1_WAVEFORM,
    SID_V1_SYNC,
    SID_V1_RINGMOD,
    SID_V1_FILTER,
    SID_V1_TEST,

    SID_V2_CHANNEL,
    SID_V2_PORTAMENTO,
    SID_V2_ATT,
    SID_V2_DEC,
    SID_V2_SUS,
    SID_V2_REL,
    SID_V2_PW,
    SID_V1_OCTAVE,
    SID_V2_DETUNE,
    SID_V2_WAVEFORM,
    SID_V2_SYNC,
    SID_V2_RINGMOD,
    SID_V2_FILTER,
    SID_V2_TEST,

    SID_V3_CHANNEL,
    SID_V3_PORTAMENTO,
    SID_V3_ATT,
    SID_V3_DEC,
    SID_V3_SUS,
    SID_V3_REL,
    SID_V3_PW,
    SID_V1_OCTAVE,
    SID_V3_DETUNE,
    SID_V3_WAVEFORM,
    SID_V3_SYNC,
    SID_V3_RINGMOD,
    SID_V3_FILTER,
    SID_V3_TEST,
    SID_V3_FREQ,
    SID_V3_OFF

};

typedef struct sidVoicePorts_
{
    float*      channel_p;
    float*      portamento_p;
    float*      attack_p;
    float*      decay_p;
    float*      sustain_p;
    float*      release_p;
    float*      pulsewidth_p;
    float*      octave_p;
    float*      detune_p;
    float*      waveform_p;
    float*      sync_p;
    float*      ringmod_p;
    float*      filter_p;
    float*      test_p;
}sidVoicePorts;

//the full instrument
typedef struct SidIntrument_{
    cSID sid;

    //register values
    reg16 v1freq;
    reg16 v1pw;
    reg8  v1ctl;
    reg8  v1ad;//attack/decay
    reg8  v1sr;//sustain/release

    reg16 v2freq;
    reg16 v2pw;
    reg8  v2ctl;
    reg8  v2ad;
    reg8  v2sr;

    reg16 v3freq;
    reg16 v3pw;
    reg8  v3ctl;
    reg8  v3ad;
    reg8  v3sr;

    reg16 filterfreq;
    reg8  resfilt;
    reg8  modevol;



    //ports
    LV2_Atom*   event_port;
    float*      output_port;

    float*      volume_p;
    float*      chip_p;
    float*      lpf_p;
    float*      bp_p;
    float*      hpf_p;
    float*      res_p;
    float*      filter_freq_p;

    sidVoicePorts voice[3];
    float*      v3freq_p;
    float*      v3off_p;

}SidInstrument;

#endif // SID_P_H
