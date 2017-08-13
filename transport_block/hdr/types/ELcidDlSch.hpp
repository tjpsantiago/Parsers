#pragma once

namespace transport_block
{

enum class ELcidDlSch
{
    Xcch = 0x00,
    LogicalChannelMin = 0x01,
    LogicalChannelMax = 0x0A,
    BrsBeamChangeInd = 0x0B,
    BrrsBeamChangeInd = 0x0C,
    ReservedMin = 0x0D,
    ReservedMax = 0x1B,
    UeContentionResolution = 0x1C,
    TimingAdvancedCmd = 0x1D,
    Reserved = 0x1E,
    Padding = 0x1F,
    Max = 0xFF
};

} // namespace transport_block
