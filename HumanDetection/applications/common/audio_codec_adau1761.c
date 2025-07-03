/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2018 NeuronBasic Co., Ltd. All rights reserved.                        */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#include "nbsdk.h"
#include "audio_codec_adau1761.h"

#if !defined(NB_FPGA)
#define ADAU_SLAVE_ADDR   0x38
#else
#define ADAU_SLAVE_ADDR   0x3b
#endif
#define ADAU_REG_BASE	(0x4000)
#define ADAU_REG(x)	(ADAU_REG_BASE+(x))

enum adau1761_regs {								//see ADAU1761 datasheet
	R0_CLOCK_CONTROL								= 0x00,
	R1_PLL_CONTROL 									= 0x02,
	R2_DIGITAL_MIC_JACK_DETECTION_CONTROL 			= 0x08,
	R3_RECORD_POWER_MANAGEMENT						= 0x09,
	R4_RECORD_MIXER_LEFT_CONTROL_0 					= 0x0A,
	R5_RECORD_MIXER_LEFT_CONTROL_1 					= 0x0B,
	R6_RECORD_MIXER_RIGHT_CONTROL_0 				= 0x0C,
	R7_RECORD_MIXER_RIGHT_CONTROL_1 				= 0x0D,
	R8_LEFT_DIFFERENTIAL_INPUT_VOLUME_CONTROL 		= 0x0E,
	R9_RIGHT_DIFFERENTIAL_INPUT_VOLUME_CONTROL 		= 0x0F,
	R10_RECORD_MICROPHONE_BIAS_CONTROL 				= 0x10,
	R11_ALC_CONTROL_0								= 0x11,
	R12_ALC_CONTROL_1								= 0x12,
	R13_ALC_CONTROL_2								= 0x13,
	R14_ALC_CONTROL_3								= 0x14,
	R15_SERIAL_PORT_CONTROL_0 						= 0x15,
	R16_SERIAL_PORT_CONTROL_1 						= 0x16,
	R17_CONVERTER_CONTROL_0 						= 0x17,
	R18_CONVERTER_CONTROL_1 						= 0x18,
	R19_ADC_CONTROL									= 0x19,
	R20_LEFT_INPUT_DIGITAL_VOLUME 					= 0x1A,
	R21_RIGHT_INPUT_DIGITAL_VOLUME 					= 0x1B,
	R22_PLAYBACK_MIXER_LEFT_CONTROL_0 				= 0x1C,
	R23_PLAYBACK_MIXER_LEFT_CONTROL_1 				= 0x1D,
	R24_PLAYBACK_MIXER_RIGHT_CONTROL_0 				= 0x1E,
	R25_PLAYBACK_MIXER_RIGHT_CONTROL_1 				= 0x1F,
	R26_PLAYBACK_LR_MIXER_LEFT_LINE_OUTPUT_CONTROL 	= 0x20,
	R27_PLAYBACK_LR_MIXER_RIGHT_LINE_OUTPUT_CONTROL = 0x21,
	R28_PLAYBACK_LR_MIXER_MONO_OUTPUT_CONTROL 		= 0x22,
	R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL 		= 0x23,
	R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL 	= 0x24,
	R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL 	= 0x25,
	R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL 	= 0x26,
	R33_PLAYBACK_MONO_OUTPUT_CONTROL 				= 0x27,
	R34_PLAYBACK_POP_CLICK_SUPPRESSION 				= 0x28,
	R35_PLAYBACK_POWER_MANAGEMENT 					= 0x29,
	R36_DAC_CONTROL_0 								= 0x2A,
	R37_DAC_CONTROL_1 								= 0x2B,
	R38_DAC_CONTROL_2 								= 0x2C,
	R39_SERIAL_PORT_PAD_CONTROL 					= 0x2D,
	R40_CONTROL_PORT_PAD_CONTROL_0 					= 0x2F,
	R41_CONTROL_PORT_PAD_CONTROL_1 					= 0x30,
	R42_JACK_DETECT_PIN_CONTROL 					= 0x31,
	R67_DEJITTER_CONTROL 							= 0x36,
	R58_SERIAL_INPUT_ROUTE_CONTROL					= 0xF2,
	R59_SERIAL_OUTPUT_ROUTE_CONTROL					= 0xF3,
	R61_DSP_ENABLE									= 0xF5,
	R62_DSP_RUN										= 0xF6,
	R63_DSP_SLEW_MODES								= 0xF7,
	R64_SERIAL_PORT_SAMPLING_RATE 					= 0xF8,
	R65_CLOCK_ENABLE_0 								= 0xF9,
	R66_CLOCK_ENABLE_1 								= 0xFA
};

static void codec_write_reg(int reg,int val)
{
	int ret=0;
 	ret = i2c_write_reg(ADAU_SLAVE_ADDR, ADAU_REG(reg), 2,  val, 1 );
    if ( ret )
    {
        debug( "config adau reg:%x %x fail\n",reg,val);
    }
}

/*hp_out: 1 headphone output 0 line output*/
static int adau1761_init(int master)
{
	//debug("%s codec is master:%d\n",__func__,master);
	codec_write_reg(R0_CLOCK_CONTROL, 0x1); //clk:bypass pLL
	mdelay( 50 );

	if (master)
		codec_write_reg(R15_SERIAL_PORT_CONTROL_0, 0x1);
	else
		codec_write_reg(R15_SERIAL_PORT_CONTROL_0, 0x0);

	codec_write_reg(R58_SERIAL_INPUT_ROUTE_CONTROL, 0x01); //Connect I2S serial port output (SDATA_O) to DACs
	codec_write_reg(R59_SERIAL_OUTPUT_ROUTE_CONTROL, 0x01); //connect I2S serial port input (SDATA_I) to ADCs

	codec_write_reg(R65_CLOCK_ENABLE_0, 0x7F); //Enable clocks
	codec_write_reg(R66_CLOCK_ENABLE_1, 0x03); //Enable rest of clocks
    return 0;
}

/*hp_out: 1 hp out 0 line out*/
static int adau1761_init_dac(int hp_out)
{
	codec_write_reg(R22_PLAYBACK_MIXER_LEFT_CONTROL_0, 0x21); //unmute Left DAC into Mxr 3; enable mxr 3
	codec_write_reg(R23_PLAYBACK_MIXER_LEFT_CONTROL_1, 0);
	codec_write_reg(R24_PLAYBACK_MIXER_RIGHT_CONTROL_0, 0x41); //unmute Right DAC into Mxr4; enable mxr 4
	codec_write_reg(R25_PLAYBACK_MIXER_RIGHT_CONTROL_1, 0);

	if (hp_out)
	{
		codec_write_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0xff);//Mute Left channel of HP port (LHP)
		codec_write_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0xff); //Mute Right channel of HP port (LHP)
		codec_write_reg(R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL,0x1); //set LOUT volume (0db); unmute left channel of Line out port; set Line out port to line out mode
		codec_write_reg(R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL,0x1); // set ROUT volume (0db); unmute right channel of Line out port; set Line out port to line out mode
	}else
	{
		codec_write_reg(R29_PLAYBACK_HEADPHONE_LEFT_VOLUME_CONTROL, 0x0);//0xe4);//Mute Left channel of HP port (LHP)
		codec_write_reg(R30_PLAYBACK_HEADPHONE_RIGHT_VOLUME_CONTROL, 0x0);//0xe4); //Mute Right channel of HP port (LHP)
		codec_write_reg(R31_PLAYBACK_LINE_OUTPUT_LEFT_VOLUME_CONTROL, 0xfe);//0xE6); //set LOUT volume (0db); unmute left channel of Line out port; set Line out port to line out mode
		codec_write_reg(R32_PLAYBACK_LINE_OUTPUT_RIGHT_VOLUME_CONTROL, 0xfe);//0xE6); // set ROUT volume (0db); unmute right channel of Line out port; set Line out port to line out mode
	}
	
	codec_write_reg(R35_PLAYBACK_POWER_MANAGEMENT, 0x03); //enable left and right channel playback (not sure exactly what this does...)
	codec_write_reg(R36_DAC_CONTROL_0, 0x03); //enable both DACs
    return 0;
}

/*mic_in: 1 mic in 0 line in*/
static int adau1761_init_adc(int mic_in)
{
	if (mic_in)
	{
		codec_write_reg(R3_RECORD_POWER_MANAGEMENT, 0x60);
		codec_write_reg(R4_RECORD_MIXER_LEFT_CONTROL_0, 0xd);//0x01); //enable mixer 1
		codec_write_reg(R5_RECORD_MIXER_LEFT_CONTROL_1, 0x10);//0x17); //unmute Left channel of line in into mxr 1 and set gain to 6 db
		codec_write_reg(R6_RECORD_MIXER_RIGHT_CONTROL_0, 0xd);//0x01); //enable mixer 2
		codec_write_reg(R7_RECORD_MIXER_RIGHT_CONTROL_1,0x10);//0x17); //unmute Right channel of line in into mxr 2 and set gain to 6 db

		codec_write_reg(R10_RECORD_MICROPHONE_BIAS_CONTROL,1);

		codec_write_reg(R8_LEFT_DIFFERENTIAL_INPUT_VOLUME_CONTROL, 0x93);
		codec_write_reg(R9_RIGHT_DIFFERENTIAL_INPUT_VOLUME_CONTROL, 0x93);
	}else{
		codec_write_reg(R4_RECORD_MIXER_LEFT_CONTROL_0, 0x1); //enable mixer 1
		codec_write_reg(R5_RECORD_MIXER_LEFT_CONTROL_1, 0x5); //unmute Left channel of line in into mxr 1 and set gain to 6 db
		codec_write_reg(R6_RECORD_MIXER_RIGHT_CONTROL_0, 0x1); //enable mixer 2
		codec_write_reg(R7_RECORD_MIXER_RIGHT_CONTROL_1,0x5); //unmute Right channel of line in into mxr 2 and set gain to 6 db
	}
	
	codec_write_reg(R11_ALC_CONTROL_0, 0);
	codec_write_reg(R19_ADC_CONTROL, 0x3); //enable ADCs
    return 0;
}

static int adau1761_set_samplerate(int sample_rate)
{
	int val=0;
	if (sample_rate == 48000)
		val = 0;
	else if (sample_rate == 8000)
		val = 1;
	else if (sample_rate == 12000)
		val = 2;
	else if (sample_rate == 16000)
		val = 3;
	else if (sample_rate == 24000)
		val = 4;
	else if (sample_rate == 32000)
		val = 5;
	else if (sample_rate == 96000)
		val = 6;
	else
	{
		debug("sample rate:%d not support\n",sample_rate);
        return ERR_AUDIO_SAMPLE_RATE_NOT_SUPPORT;
	}
	
	codec_write_reg(R17_CONVERTER_CONTROL_0, val);//96 kHz
	codec_write_reg(R64_SERIAL_PORT_SAMPLING_RATE, val);//96 kHz
    return 0;
}

void adau1761_config(void)
{
	codec_conf->i2c_slave_addr = ADAU_SLAVE_ADDR;

	codec_conf->codec_init = adau1761_init;
	codec_conf->codec_init_adc = adau1761_init_adc;
	codec_conf->codec_init_dac = adau1761_init_dac;
	codec_conf->codec_set_samplerate = adau1761_set_samplerate;
	codec_conf->codec_uninit = 0;
	//debug("adau1761_config\n");
}