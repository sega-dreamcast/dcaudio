// ---- aica_lowlevel.h - Low-Level AICA Header ----
//
// Version 0.8.0
//
// This file provides low-level access to the Sega Dreamcast's AICA and is mainly
// meant for use on the AICA, NOT the SH4. It is hereby released into the public
// domain in the hope that it may prove useful.
//
// --Moopthehedgehog

#ifndef __AICA_LOWLEVEL_H_
#define __AICA_LOWLEVEL_H_

// Thanks to yamato who made aica_v08.txt in 2002. That file was an instrumental
// reference in putting this together. The intent for this file is to use
// that document as a reference when working with anything in here.
//
// NOTE: most defines that have a "MASK" have a corresponding "SHIFT" for << purposes.
// So when you see #define LFO_FREQ_SHIFT 10, that means x << 10 is the part of the
// register that controls that setting, NOT that there's some LFO Frequency Shift
// hardware or whatever with a value of 10.

// ============================================================================
// Addresses
// ============================================================================
//
// ARM7_AICA_BASE is the base address when running on the AICA itself. G2_AICA_BASE
// is for the SH4 to access the AICA's registers. So if compiled with an ARM
// compiler to run on the AICA, use ARM7_AICA_BASE instead of G2_AICA_BASE.
//

#define G2_AICA_BASE 0xa0700000
#define ARM7_AICA_BASE 0x00800000

// x is sample channel 0-63
#define SAMPLE_CHANNEL(x) (0x0000 + x*0x80)

// ============================================================================
// Volume Values
// ============================================================================
//
// 4-bit unsigned values (Note: LPF1 uses 8bit volume, but it seems all the other
// registers use 4bit volume)
//

#define VOLUME_MIN 0x00
#define VOLUME_MAX 0x0f

// ============================================================================
// Panning Values
// ============================================================================
//
// 5-bit signed values (sign-magnitude)
//

// -15
#define PAN_RIGHT_MAX 0x1f
// 0, and apparently also -0 (0x10) works
#define PAN_CENTER 0x00
// 15
#define PAN_LEFT_MAX 0x0f

// ============================================================================
// Per-Channel Registers
// ============================================================================
//
// Each of these registers exists per-channel. The #defines are grouped together
// based on what register they belong to.
//

#define PLAYCONTROL_REG 0x0000
#define SAMPLE_ADDRESS_HIGH_MASK 0x3f
#define SAMPLE_ADDRESS_HIGH_SHIFT 0
#define PLAYCONTROL_FORMAT_16BIT (0 << 7)
#define PLAYCONTROL_FORMAT_8BIT (1 << 7)
#define PLAYCONTROL_FORMAT_4BIT_ADPCM (2 << 7)
#define PLAYCONTROL_FORMAT_4BIT_LOOPING_ADPCM (3 << 7)
#define PLAYCONTROL_FORWARD_LOOP_ENABLE (1 << 9)
#define PLAYCONTROL_FORWARD_LOOP_DISABLE (1 << 9)
// TODO What is 'u' at bit 10????
#define PLAYCONTROL_KEY_ENABLE (1 << 14)
#define PLAYCONTROL_KEY_DISABLE (0 << 14)
#define PLAYCONTROL_AFTERTOUCH_ENABLE (1 << 15)
#define PLAYCONTROL_AFTERTOUCH_DISABLE (0 << 15)

#define SAMPLE_ADDR_LOW_REG 0x0004
#define SAMPLE_ADDRESS_LOW_MASK 0xffff
#define SAMPLE_ADDRESS_LOW_SHIFT 0

#define LOOP_START_REG 0x0008
#define LOOP_START_MASK 0xffff
#define LOOP_START_SHIFT 0

#define LOOP_END_REG 0x000c
#define LOOP_END_MASK 0xffff
#define LOOP_END_SHIFT 0

#define AMP_ENV1_REG 0x0010
#define AMP_ENV1_ATT_MAX 0x1f
#define AMP_ENV1_ATT_MIN 0x00
#define AMP_ENV1_ATT_SHIFT 0
#define AMP_ENV1_DEC1_MAX (0x1f << 6)
#define AMP_ENV1_DEC1_MIN (0x00 << 6)
#define AMP_ENV1_DEC1_SHIFT 6
#define AMP_ENV1_DEC2_MAX (0x1f << 11)
#define AMP_ENV1_DEC2_MIN (0x00 << 11)
#define AMP_ENV1_DEC2_SHIFT 11

#define AMP_ENV2_REG 0x0014
#define AMP_ENV2_RES_MAX 0x1f
#define AMP_ENV2_RES_MIN 0x00
#define AMP_ENV2_RES_SHIFT 0
#define AMP_ENV2_DLEV_MAX (0x1f << 5)
#define AMP_ENV2_DLEV_MIN (0x00 << 5)
#define AMP_ENV2_DLEV_SHIFT 5
#define AMP_ENV2_KEY_MAX (0xe << 10)
#define AMP_ENV2_KEY_MIN (0x0 << 10)
#define AMP_ENV2_KEY_OFF (0xf << 10)
#define AMP_ENV2_KEY_SHIFT 10
#define AMP_ENV2_LINK_ENABLE (1 << 14)
#define AMP_ENV2_LINK_DISABLE (0 << 14)

// TODO This one was unfinished, no idea what these are
#define SAMPLE_RATE_PITCH_REG 0x0018
#define OCT (0x1f << 11)
#define FNS 0x3ff

#define LFO_CONTROL_REG 0x001c
#define LFO_AMPLITUDE_MODULATION_RANGE_MASK (0x7 << 0)
#define LFO_AMPLITUDE_MODULATION_RANGE_SHIFT 0
#define LFO_AMPLITUDE_SHAPE_SAW (0 << 3)
#define LFO_AMPLITUDE_SHAPE_SQUARE (1 << 3)
#define LFO_AMPLITUDE_SHAPE_TRIANGLE (2 << 3)
#define LFO_AMPLITUDE_SHAPE_NOISE (3 << 3)
#define LFO_PITCH_MODULATION_RANGE_MASK (0x7 << 5)
#define LFO_PITCH_MODULATION_RANGE_SHIFT 5
#define LFO_PITCH_SHAPE_SAW (0 << 8)
#define LFO_PITCH_SHAPE_SQUARE (1 << 8)
#define LFO_PITCH_SHAPE_TRIANGLE (2 << 8)
#define LFO_PITCH_SHAPE_NOISE (3 << 8)
#define LFO_FREQ_MAX (0x1f << 10)
#define LFO_FREQ_MIN (0x00 << 10)
#define LFO_FREQ_SHIFT 10
#define LFO_RESET_ENABLE (1 << 15)
#define LFO_RESET_DISABLE (0 << 15)

#define DSP_CHANNEL_SEND_REG 0x0020
// x is DSP channel 0-15 to redirect this sample channel to
#define DSP_CHANNEL_SEND_CH(x) (x)
// TODO Volume level of this channel to send to dsp mixer...?
#define DSP_CHANNEL_SEND_LEVEL_MASK (0xf << 8)
#define DSP_CHANNEL_SEND_LEVEL_SHIFT 8

#define DIRECT_PAN_VOL_SEND_REG 0x0024
#define DIRECT_PAN_PAN_MASK 0xf
#define DIRECT_PAN_PAN_SHIFT 0
#define DIRECT_PAN_VOLUME_MASK (0xf << 8)
#define DIRECT_PAN_VOLUME_SHIFT 8

// The volume part of this register takes 8-bit volume (unsigned)
#define LPF1_VOL_REG 0x0028
#define FILTER_Q_MASK 0xf
#define FILTER_Q_SHIFT 0
#define LPF_ENABLE (0 << 5)
#define LPF_DISABLE (1 << 5)
#define LPF1_VOLUME_MAX (0xff << 8)
#define LPF1_VOLUME_MIN (0x00 << 8)
#define LPF1_VOLUME_SHIFT 8

#define LPF2_REG 0x002c
#define LPF2_FREQ_MAX 0x1fff
#define LPF2_FREQ_MIN 0x0000

#define LPF3_REG 0x0030
#define LPF3_FREQ_MAX 0x1fff
#define LPF3_FREQ_MIN 0x0000

#define LPF4_REG 0x0034
#define LPF4_FREQ_MAX 0x1fff
#define LPF4_FREQ_MIN 0x0000

#define LPF5_REG 0x0038
#define LPF5_FREQ_MAX 0x1fff
#define LPF5_FREQ_MIN 0x0000

#define LPF6_REG 0x003c
#define LPF6_FREQ_MAX 0x1fff
#define LPF6_FREQ_MIN 0x0000

// TODO Are MAX and MIN flipped?
#define LPF7_REG 0x0040
// Is dec1 max actually 0xff?
#define LPF7_DEC1_MAX 0x1f
#define LPF7_DEC1_MIN 0x00
#define LPF7_DEC1_SHIFT 0
#define LPF7_ATT_MAX (0x1f << 8)
#define LPF7_ATT_MIN (0x00 << 8)
#define LPF7_ATT_SHIFT 8

// TODO Are MAX and MIN flipped?
#define LPF8_REG 0x0044
// Is rel max actually 0xff?
#define LPF8_REL_MAX 0x1f
#define LPF8_REL_MIN 0x00
#define LPF8_REL_SHIFT 0
#define LPF8_DEC2_MAX (0x1f << 8)
#define LPF8_DEC2_MIN (0x00 << 8)
#define LPF8_DEC2_SHIFT 8

// ============================================================================
// DSP Output Mixer Channels Registers
// ============================================================================

// Each mixer channel has individual volume and pan
#define DSP_VOLUME_MASK (0xf << 8)
#define DSP_VOLUME_SHIFT 8
#define DSP_PAN_MASK 0xf
#define DSP_PAN_SHIFT 0

// x is DSP channel 0-15 (16-17 are CD-DA, but they also have their own defines below)
#define DSP_REG(x) (0x2000 + x*4)

// CD-DA
#define DSP_CDDA_LEFT_REG 0x2040
#define DSP_CDDA_RIGHT_REG 0x2044

// ============================================================================
// Whole AICA Control Registers
// ============================================================================

#define MASTER_VOLUME_REG 0x2800
#define MASTER_VOLUME_VOLUME_MAX 0xf
#define MASTER_VOLUME_VOLUME_MIN 0x0
#define MASTER_VOLUME_MODE_STEREO (0x00 << 8)
#define MASTER_VOLUME_MODE_MONO (0x80 << 8)

// Has both size and base address of DSP ring buffer
#define DSP_PROGRAM_ADDRESS_REG 0x2804

#define INT_BUS_REQUEST_REG 0x2808
#define INT_BUS_FIQ5 0x100

#define CHANNEL_INFO_REQUEST_REG 0x280c
// x is channel number 0-63
#define CHANNEL_INFO_REQUEST(x) (x << 8)
#define CHANNEL_INFO_REQUEST_MASK 0x0000c0ff;

#define CHANNEL_STATUS_REG 0x2810
#define CHANNEL_STATUS_IS_PLAYING 0x7fff
#define CHANNEL_STATUS_STOPPED 0x4000
#define CHANNEL_STATUS_LOOP_END_MARKER 0x4000

#define PLAYPOSITION_REG 0x2814
#define PLAYPOSITION_MASK 0xffff
#define PLAYPOSITION_SHIFT 0

#define ARM_RESET_REG 0x2c00
#define CABLE_TYPE_MASK 0x300
#define CABLE_TYPE_SHIFT 8
#define ARM_RESET (1 << 0)

// ----------------------------------------------------------------------------
// Interrupt and Timer Registers
// ----------------------------------------------------------------------------

// TODO what are these first 3 timer regs?
#define INT_TIMER_START_REG 0x2890

#define INT_TIMER_END_REG 0x289c

#define INT_TIMER_TRIGGER_REG 0x28a4

#define INT_ENABLE_REG 0x28b4
#define INT_ENABLE 0x20

#define INT_SEND_REG 0x28b8
#define INT_SEND 0x20

#define INT_RESET_REG 0x28bc
#define INT_RESET 0x20

// Status register
#define INT_REQUEST_REG 0x2d00
#define INT_REQUEST_TIMER 2
#define INT_RESET_BUS 5

#define INT_CLEAR_REG 0x2d04
#define INT_CLEAR (1 << 0)

// ============================================================================
// DSP FX Program Registers
// ============================================================================

// x is DSP step 0-127
#define DSP_INST_REG(x) (0x3000 + x*4)

// ============================================================================
// Register Wrapper Functions
// ============================================================================
//
// For a specific register, pass (G2_AICA_BASE | yyy_REG) or (ARM7_AICA_BASE | yyy_REG)
// as the 'reg' parameter. For specific channels, do (G2_AICA_BASE | SAMPLE_CHANNEL(x) | yyy_REG)
// or (ARM7_AICA_BASE | SAMPLE_CHANNEL(x) | yyy_REG). Likewise, DSP instruction channels use
// (ARM7_AICA_BASE | DSP_INST_REG(x)), etc.
//
// The 'data' parameter is just a 32-bit unsigned int comprised of the data to be written.
// You can just OR (|) a bunch of parameters together to build the register value.
//

// Set a register with data
static inline void set_aica_reg(unsigned int reg, unsigned int data)
{
  *(volatile unsigned int*)reg = data;
}

// Reads the register and returns its value
static inline unsigned int get_aica_reg(unsigned int reg)
{
  return *(volatile unsigned int*)reg;
}

//
// Misc
//
/*
// ChanInfoReq is special and needs this treatment
// Channel is 0-63
static inline unsigned int get_chan_info_request(unsigned int channel)
{
  unsigned int temp = *(volatile unsigned int*)(ARM7_AICA_BASE | CHANNEL_INFO_REQUEST_REG);
  temp &= CHANNEL_INFO_REQUEST_MASK;
  temp |= CHANNEL_INFO_REQUEST(channel);
  *(volatile unsigned int*)(ARM7_AICA_BASE | CHANNEL_INFO_REQUEST_REG) = temp;

  // TODO How long should there be a delay here?
  //
  // This is what KOS has a very bizarre loop for.
  //
  // Alternatively, make this two functions

  return *(volatile unsigned int*)(ARM7_AICA_BASE | PLAYPOSITION_REG);
}
*/
// Here is the above function split into two functions, so you can do something
// else that's useful on the ARM instead of spinlocking. Input channel is 0-63.
static inline void chan_info_request(unsigned int channel)
{
  unsigned int temp = *(volatile unsigned int*)(ARM7_AICA_BASE | CHANNEL_INFO_REQUEST_REG);
  temp &= CHANNEL_INFO_REQUEST_MASK;
  temp |= CHANNEL_INFO_REQUEST(channel);
  *(volatile unsigned int*)(ARM7_AICA_BASE | CHANNEL_INFO_REQUEST_REG) = temp;
}

static inline unsigned int get_playposition(void)
{
  return *(volatile unsigned int*)(ARM7_AICA_BASE | PLAYPOSITION_REG);
}

#endif /* __AICA_LOWLEVEL_H_ */
