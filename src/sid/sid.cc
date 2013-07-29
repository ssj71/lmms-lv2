#include <iostream>
#include "lmms_lv2.h"
#include "uris.h"
#include "sid_p.h"
#include "sid.h"

//these values from lmms
#define C64_PAL_CYCLES_PER_SEC  985248

#define NUMSIDREGS 0x19
#define SIDWRITEDELAY 9 // lda $xxxx,x 4 cycles, sta $d400,x 5 cycles
#define SIDWAVEDELAY 4 // and $xxxx,x 4 cycles extra

#define LO(reg) ((reg8)((reg&0xFF00)>>8))
#define HI(reg) ((reg8)(reg&0xFF))

#define PWHIMASK    0x0F
#define PWLOMASK    0xFF

#define NOISEMASK   0x80
#define SQRMASK     0x40
#define SAWMASK     0x20
#define TRIMASK     0x10
#define TESTMASK    0x08
#define RINGMASK    0x04
#define SYNCMASK    0x02
#define GATEMASK    0x01

#define AMASK       0xF0
#define DMASK       0x0F
#define SMASK       0xF0
#define RMASK       0x0F

#define FCHIMASK    0xFF
#define FCLOMASK    0x07

#define RESMASK     0xF0
#define F1MASK      0x01
#define F2MASK      0x02
#define F3MASK      0x04

#define THREOFFMASK 0x80
#define HPMASK      0x40
#define BPMASK      0x20
#define LPMASK      0x10
#define VOLMASK     0x0F


void SidInstrument::fun()
{
	std::cout << "Hello World!" << std::endl;
	*control_port1 = 1.0f;

    SidInstrument cow;
    cow.engine.cSID();//call constructor
    cow.engine.~cSID();


}
static LV2_Handle
sid_instantiate (const LV2_Descriptor     *descriptor,
                 double                    rate,
                 const char               *path,
                 const LV2_Feature * const *features)
{

    SidInstrument *plugin = (SidInstrument*)malloc(sizeof(SidInstrument));
    if (!plugin) {
        fprintf(stderr, "lmms-lv2: Could not allocate Sid.\n");
        return NULL;
    }

    plugin->sid.cSID();//call constructor
    plugin->sid->set_sampling_parameters( clockrate, SAMPLE_FAST, samplerate );
    plugin->sid->set_chip_model( MOS6581 );
    plugin->sid->enable_filter( true );
    plugin->sid->reset();
}

static void
sid_connect_port (LV2_Handle  instance,
                  uint32_t    port,
                  void       *data)
{
    SidIntrument *plugin = (SidInstrument *)instance;
    int vidx, vport;
    // Handle Plugin-global ports
    if (port < SID_V1_CHANNEL || port >= SID_V3_FREQ) {
        BEGIN_CONNECT_PORTS(port);
        CONNECT_PORT(SID_CONTROL, event_port, LV2_Atom_Sequence);
        CONNECT_PORT(SID_OUT, out_port, float);
        CONNECT_PORT(SID_VOLUME, volume_p, float);
        CONNECT_PORT(SID_CHIP, chip_p, float);
        CONNECT_PORT(SID_LPF, lpf_p, float);
        CONNECT_PORT(SID_BP, bp_p, float);
        CONNECT_PORT(SID_HPF, hpf_p, float);
        CONNECT_PORT(SID_RES, res_p, float);
        CONNECT_PORT(SID_CUTOFF, filter_freq_p, float);
        CONNECT_PORT(SID_V3_FREQ, v3freq_p, float);
        CONNECT_PORT(SID_V3_OFF, v3off_p, float);
        END_CONNECT_PORTS();
        return;
    // Calculate osc index of osc-specific ports
    } else if (port < SID_V2_CHANNEL) {
        vidx = 0;
        vport = port;
    } else if (port < SID_V3_CHANNEL) {
        vidx = 1;
        vport = port - (SID_V2_CHANNEL - SID_V1_CHANNEL);
    } else {
        vidx = 2;
        vport = port - (SID_V3_CHANNEL - SID_V1_CHANNEL);
    }

    // Now connect an osc-specific port
    BEGIN_CONNECT_PORTS(vport);
    CONNECT_PORT(SID_V1_CHANNEL, voice[vidx].channel_p, float);
    CONNECT_PORT(SID_V1_PORTAMENTO, voice[vidx].portamento_p, float);
    CONNECT_PORT(SID_V1_ATT, voice[vidx].attack_p, float);
    CONNECT_PORT(SID_V1_DEC, voice[vidx].decay_p, float);
    CONNECT_PORT(SID_V1_SUS, voice[vidx].sustain_p, float);
    CONNECT_PORT(SID_V1_REL, voice[vidx].release_p, float);
    CONNECT_PORT(SID_V1_PW, voice[vidx].pulsewidth_p, float);
    CONNECT_PORT(SID_V1_OCTAVE, voice[vidx].octave_p, float);
    CONNECT_PORT(SID_V1_DETUNE, voice[vidx].detune_p, float);
    CONNECT_PORT(SID_V1_WAVEFORM, voice[vidx].waveform_p, float);
    CONNECT_PORT(SID_V1_SYNC, voice[vidx].sync_p, float);
    CONNECT_PORT(SID_V1_RINGMOD, voice[vidx].ringmod_p, float);
    CONNECT_PORT(SID_V1_FILTER, voice[vidx].filter_p, float);
    CONNECT_PORT(SID_V1_TEST, voice[vidx].test_p, float);
    END_CONNECT_PORTS();
}

static void
sid_run(LV2_Handle instance,
        uint32_t   sample_count)
{

}

void sid_cleanup()
{

}

// Fill in your call-back functions here
// Probably want static member functions that take an instance as
// the LV2_Handle
const LV2_Descriptor sid_descriptor = {
    SID_URI,
    sid_instantiate,
    sid_connect_port,
    NULL, // activate,
    sid_run,
    NULL, // deactivate,
    sid_cleanup,
    sid_extension_data
};

