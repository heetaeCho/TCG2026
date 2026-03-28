#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <exiv2/exiv2.hpp>
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Define test arrays for TagDetailsBitlistSorted
// TagDetailsBitlistSorted is expected to have { uint32_t first (bit position), const char* second (label) }

static constexpr TagDetailsBitlistSorted testArray3[] = {
    {0, "Bit0Label"},
    {1, "Bit1Label"},
    {2, "Bit2Label"},
};

static constexpr TagDetailsBitlistSorted testArray8[] = {
    {0, "Alpha"},
    {1, "Beta"},
    {2, "Gamma"},
    {3, "Delta"},
    {4, "Epsilon"},
    {5, "Zeta"},
    {6, "Eta"},
    {7, "Theta"},
};

static constexpr TagDetailsBitlistSorted testArraySparse[] = {
    {0, "First"},
    {3, "Fourth"},
    {7, "Eighth"},
};

static constexpr TagDetailsBitlistSorted testArraySingle[] = {
    {0, "OnlyBit"},
};

static constexpr TagDetailsBitlistSorted testArrayHighBits[] = {
    {0, "Low"},
    {8, "High8"},
    {15, "High15"},
};

class PrintTagBitlistAllLETest_185 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that all-zero value outputs "None"
TEST_F(PrintTagBitlistAllLETest_185, AllZeroBytesOutputsNone_185) {
    DataBuf buf(1);
    buf.data()[0] = 0x00;
    DataValue value(unsignedByte);
    value.read(buf.data(), buf.size(), byteOrder);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    // "None" may be translated but in default locale should be "None"
    EXPECT_NE(os.str().find("None"), std::string::npos);
}

// Test single bit 0 set
TEST_F(PrintTagBitlistAllLETest_185, SingleBit0Set_185) {
    DataValue value(unsignedByte);
    byte data = 0x01; // bit 0 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(os.str(), "Bit0Label");
}

// Test single bit 1 set
TEST_F(PrintTagBitlistAllLETest_185, SingleBit1Set_185) {
    DataValue value(unsignedByte);
    byte data = 0x02; // bit 1 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(os.str(), "Bit1Label");
}

// Test multiple bits set - bits 0 and 2
TEST_F(PrintTagBitlistAllLETest_185, MultipleBitsSet_185) {
    DataValue value(unsignedByte);
    byte data = 0x05; // bits 0 and 2 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(os.str(), "Bit0Label, Bit2Label");
}

// Test all three bits set
TEST_F(PrintTagBitlistAllLETest_185, AllThreeBitsSet_185) {
    DataValue value(unsignedByte);
    byte data = 0x07; // bits 0, 1, 2 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(os.str(), "Bit0Label, Bit1Label, Bit2Label");
}

// Test bit beyond array range outputs unknown index
TEST_F(PrintTagBitlistAllLETest_185, BitBeyondArrayRangeOutputsUnknownIndex_185) {
    DataValue value(unsignedByte);
    byte data = 0x08; // bit 3 set, but array only has bits 0-2
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_NE(os.str().find("[3]"), std::string::npos);
}

// Test mixed known and unknown bits
TEST_F(PrintTagBitlistAllLETest_185, MixedKnownAndUnknownBits_185) {
    DataValue value(unsignedByte);
    byte data = 0x09; // bits 0 and 3 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Bit0Label"), std::string::npos);
    EXPECT_NE(result.find("[3]"), std::string::npos);
}

// Test all 8 bits set with full 8-entry array
TEST_F(PrintTagBitlistAllLETest_185, AllEightBitsSet_185) {
    DataValue value(unsignedByte);
    byte data = 0xFF;
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<8, testArray8>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Alpha"), std::string::npos);
    EXPECT_NE(result.find("Theta"), std::string::npos);
}

// Test sparse array - only defined bits appear by label
TEST_F(PrintTagBitlistAllLETest_185, SparseArrayDefinedBits_185) {
    DataValue value(unsignedByte);
    byte data = 0x89; // bits 0, 3, 7 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArraySparse>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("First"), std::string::npos);
    EXPECT_NE(result.find("Fourth"), std::string::npos);
    EXPECT_NE(result.find("Eighth"), std::string::npos);
}

// Test single element array
TEST_F(PrintTagBitlistAllLETest_185, SingleElementArray_185) {
    DataValue value(unsignedByte);
    byte data = 0x01; // bit 0 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<1, testArraySingle>(os, value, nullptr);
    EXPECT_EQ(os.str(), "OnlyBit");
}

// Test multi-byte value - second byte contains bits
TEST_F(PrintTagBitlistAllLETest_185, MultiByteValueSecondByte_185) {
    DataValue value(unsignedByte);
    byte data[2] = {0x00, 0x01}; // bit 8 set (first bit of second byte)
    value.read(data, 2, bigEndian);

    printTagBitlistAllLE<3, testArrayHighBits>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("High8"), std::string::npos);
}

// Test multi-byte value - both bytes have bits set
TEST_F(PrintTagBitlistAllLETest_185, MultiByteValueBothBytesHaveBits_185) {
    DataValue value(unsignedByte);
    byte data[2] = {0x01, 0x81}; // bit 0 and bit 8 and bit 15
    value.read(data, 2, bigEndian);

    printTagBitlistAllLE<3, testArrayHighBits>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("Low"), std::string::npos);
    EXPECT_NE(result.find("High8"), std::string::npos);
    EXPECT_NE(result.find("High15"), std::string::npos);
}

// Test multiple zero bytes still outputs "None"
TEST_F(PrintTagBitlistAllLETest_185, MultipleZeroBytesOutputNone_185) {
    DataValue value(unsignedByte);
    byte data[3] = {0x00, 0x00, 0x00};
    value.read(data, 3, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_NE(os.str().find("None"), std::string::npos);
}

// Test that the function returns the same ostream reference
TEST_F(PrintTagBitlistAllLETest_185, ReturnsSameOstream_185) {
    DataValue value(unsignedByte);
    byte data = 0x01;
    value.read(&data, 1, bigEndian);

    auto& result = printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

// Test unknown bit in second byte beyond array max
TEST_F(PrintTagBitlistAllLETest_185, UnknownBitInSecondByteBeyondMax_185) {
    DataValue value(unsignedByte);
    byte data[2] = {0x00, 0x02}; // bit 9 set, array max is 2
    value.read(data, 2, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("[9]"), std::string::npos);
}

// Test bit 7 (highest in first byte) beyond small array
TEST_F(PrintTagBitlistAllLETest_185, HighestBitInFirstByteBeyondArray_185) {
    DataValue value(unsignedByte);
    byte data = 0x80; // bit 7 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    std::string result = os.str();
    EXPECT_NE(result.find("[7]"), std::string::npos);
}

// Test only bit 2 set
TEST_F(PrintTagBitlistAllLETest_185, OnlyBit2Set_185) {
    DataValue value(unsignedByte);
    byte data = 0x04; // bit 2 set
    value.read(&data, 1, bigEndian);

    printTagBitlistAllLE<3, testArray3>(os, value, nullptr);
    EXPECT_EQ(os.str(), "Bit2Label");
}

// Test nullptr ExifData parameter is accepted
TEST_F(PrintTagBitlistAllLETest_185, NullptrExifDataAccepted_185) {
    DataValue value(unsignedByte);
    byte data = 0x01;
    value.read(&data, 1, bigEndian);

    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(printTagBitlistAllLE<3, testArray3>(os, value, nullptr));
}
