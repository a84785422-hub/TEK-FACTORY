#pragma once
#include <JuceHeader.h>
#include "BinaryData.h"

struct EmbeddedKick { const char* name; const char* dataName; const char* data; int size; };
static const EmbeddedKick embeddedKicks[] = {
    {"K24 01 SUB CRUSH", "K24_01_SUB_CRUSH_wav", BinaryData::K24_01_SUB_CRUSH_wav, BinaryData::K24_01_SUB_CRUSH_wavSize},
    {"K24 02 ACID BITE", "K24_02_ACID_BITE_wav", BinaryData::K24_02_ACID_BITE_wav, BinaryData::K24_02_ACID_BITE_wavSize},
    {"K24 03 METAL EDGE", "K24_03_METAL_EDGE_wav", BinaryData::K24_03_METAL_EDGE_wav, BinaryData::K24_03_METAL_EDGE_wavSize},
    {"K24 04 DARK RUMBLE", "K24_04_DARK_RUMBLE_wav", BinaryData::K24_04_DARK_RUMBLE_wav, BinaryData::K24_04_DARK_RUMBLE_wavSize},
    {"K24 05 HARD CLIP", "K24_05_HARD_CLIP_wav", BinaryData::K24_05_HARD_CLIP_wav, BinaryData::K24_05_HARD_CLIP_wavSize},
    {"K24 06 NASAL FURY", "K24_06_NASAL_FURY_wav", BinaryData::K24_06_NASAL_FURY_wav, BinaryData::K24_06_NASAL_FURY_wavSize},
    {"K24 07 TIGHT PUNCH", "K24_07_TIGHT_PUNCH_wav", BinaryData::K24_07_TIGHT_PUNCH_wav, BinaryData::K24_07_TIGHT_PUNCH_wavSize},
    {"K24 08 BITROT", "K24_08_BITROT_wav", BinaryData::K24_08_BITROT_wav, BinaryData::K24_08_BITROT_wavSize},
    {"K24 09 WIDE GRIT", "K24_09_WIDE_GRIT_wav", BinaryData::K24_09_WIDE_GRIT_wav, BinaryData::K24_09_WIDE_GRIT_wavSize},
    {"K24 10 TERROR TAIL", "K24_10_TERROR_TAIL_wav", BinaryData::K24_10_TERROR_TAIL_wav, BinaryData::K24_10_TERROR_TAIL_wavSize},
    {"POTO 01 SUB CRUSH", "POTO_01_SUB_CRUSH_wav", BinaryData::POTO_01_SUB_CRUSH_wav, BinaryData::POTO_01_SUB_CRUSH_wavSize},
    {"POTO 02 ACID BITE", "POTO_02_ACID_BITE_wav", BinaryData::POTO_02_ACID_BITE_wav, BinaryData::POTO_02_ACID_BITE_wavSize},
    {"POTO 03 METAL EDGE", "POTO_03_METAL_EDGE_wav", BinaryData::POTO_03_METAL_EDGE_wav, BinaryData::POTO_03_METAL_EDGE_wavSize},
    {"POTO 04 DARK RUMBLE", "POTO_04_DARK_RUMBLE_wav", BinaryData::POTO_04_DARK_RUMBLE_wav, BinaryData::POTO_04_DARK_RUMBLE_wavSize},
    {"POTO 05 HARD CLIP", "POTO_05_HARD_CLIP_wav", BinaryData::POTO_05_HARD_CLIP_wav, BinaryData::POTO_05_HARD_CLIP_wavSize},
    {"POTO 06 NASAL FURY", "POTO_06_NASAL_FURY_wav", BinaryData::POTO_06_NASAL_FURY_wav, BinaryData::POTO_06_NASAL_FURY_wavSize},
    {"POTO 07 TIGHT PUNCH", "POTO_07_TIGHT_PUNCH_wav", BinaryData::POTO_07_TIGHT_PUNCH_wav, BinaryData::POTO_07_TIGHT_PUNCH_wavSize},
    {"POTO 08 BITROT", "POTO_08_BITROT_wav", BinaryData::POTO_08_BITROT_wav, BinaryData::POTO_08_BITROT_wavSize},
    {"POTO 09 WIDE GRIT", "POTO_09_WIDE_GRIT_wav", BinaryData::POTO_09_WIDE_GRIT_wav, BinaryData::POTO_09_WIDE_GRIT_wavSize},
    {"POTO 10 TERROR TAIL", "POTO_10_TERROR_TAIL_wav", BinaryData::POTO_10_TERROR_TAIL_wav, BinaryData::POTO_10_TERROR_TAIL_wavSize},
    {"TAP 01 SUB CRUSH", "TAP_01_SUB_CRUSH_wav", BinaryData::TAP_01_SUB_CRUSH_wav, BinaryData::TAP_01_SUB_CRUSH_wavSize},
    {"TAP 02 ACID BITE", "TAP_02_ACID_BITE_wav", BinaryData::TAP_02_ACID_BITE_wav, BinaryData::TAP_02_ACID_BITE_wavSize},
    {"TAP 03 METAL EDGE", "TAP_03_METAL_EDGE_wav", BinaryData::TAP_03_METAL_EDGE_wav, BinaryData::TAP_03_METAL_EDGE_wavSize},
    {"TAP 04 DARK RUMBLE", "TAP_04_DARK_RUMBLE_wav", BinaryData::TAP_04_DARK_RUMBLE_wav, BinaryData::TAP_04_DARK_RUMBLE_wavSize},
    {"TAP 05 HARD CLIP", "TAP_05_HARD_CLIP_wav", BinaryData::TAP_05_HARD_CLIP_wav, BinaryData::TAP_05_HARD_CLIP_wavSize},
    {"TAP 06 NASAL FURY", "TAP_06_NASAL_FURY_wav", BinaryData::TAP_06_NASAL_FURY_wav, BinaryData::TAP_06_NASAL_FURY_wavSize},
    {"TAP 07 TIGHT PUNCH", "TAP_07_TIGHT_PUNCH_wav", BinaryData::TAP_07_TIGHT_PUNCH_wav, BinaryData::TAP_07_TIGHT_PUNCH_wavSize},
    {"TAP 08 BITROT", "TAP_08_BITROT_wav", BinaryData::TAP_08_BITROT_wav, BinaryData::TAP_08_BITROT_wavSize},
    {"TAP 09 WIDE GRIT", "TAP_09_WIDE_GRIT_wav", BinaryData::TAP_09_WIDE_GRIT_wav, BinaryData::TAP_09_WIDE_GRIT_wavSize},
    {"TAP 10 TERROR TAIL", "TAP_10_TERROR_TAIL_wav", BinaryData::TAP_10_TERROR_TAIL_wav, BinaryData::TAP_10_TERROR_TAIL_wavSize},
};
static constexpr int embeddedKickCount = sizeof(embeddedKicks) / sizeof(embeddedKicks[0]);
