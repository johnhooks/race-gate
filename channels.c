#include "channels.h"


const uint16_t channelTable[] PROGMEM = {
    #define _CHANNEL_REG_FLO(f) ((f - 479) / 2)
    #define _CHANNEL_REG_N(f) (_CHANNEL_REG_FLO(f) / 32)
    #define _CHANNEL_REG_A(f) (_CHANNEL_REG_FLO(f) % 32)
    #define CHANNEL_REG(f) (_CHANNEL_REG_N(f) << 7) | _CHANNEL_REG_A(f)

    // A
    CHANNEL_REG(5865),
    CHANNEL_REG(5845),
    CHANNEL_REG(5825),
    CHANNEL_REG(5805),
    CHANNEL_REG(5785),
    CHANNEL_REG(5765),
    CHANNEL_REG(5745),
    CHANNEL_REG(5725),

    // B
    CHANNEL_REG(5733),
    CHANNEL_REG(5752),
    CHANNEL_REG(5771),
    CHANNEL_REG(5790),
    CHANNEL_REG(5809),
    CHANNEL_REG(5828),
    CHANNEL_REG(5847),
    CHANNEL_REG(5866),

    // E
    CHANNEL_REG(5705),
    CHANNEL_REG(5685),
    CHANNEL_REG(5665),
    CHANNEL_REG(5645),
    CHANNEL_REG(5885),
    CHANNEL_REG(5905),
    CHANNEL_REG(5925),
    CHANNEL_REG(5945),

    // F
    CHANNEL_REG(5740),
    CHANNEL_REG(5760),
    CHANNEL_REG(5780),
    CHANNEL_REG(5800),
    CHANNEL_REG(5820),
    CHANNEL_REG(5840),
    CHANNEL_REG(5860),
    CHANNEL_REG(5880),

    // C / R
    CHANNEL_REG(5658),
    CHANNEL_REG(5695),
    CHANNEL_REG(5732),
    CHANNEL_REG(5769),
    CHANNEL_REG(5806),
    CHANNEL_REG(5843),
    CHANNEL_REG(5880),
    CHANNEL_REG(5917)

    #undef _CHANNEL_REG_FLO
    #undef _CHANNEL_REG_A
    #undef _CHANNEL_REG_N
    #undef CHANNEL_REG
};

// Channels with their Mhz Values
const uint16_t channelFreqTable[] PROGMEM = {
    5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // A
    5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866, // B
    5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // E
    5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880, // F / Airwave
    5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917  // C / Immersion Raceband
};

uint16_t getSynthRegisterB(uint8_t index)
{
  return pgm_read_word_near(channelTable + index);
}

uint16_t getFrequency(uint8_t index)
{
  return pgm_read_word_near(channelFreqTable + index);
}
