#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FoFiIdentifier.h"

// Forward declare the function under test
class Reader;
static FoFiIdentifierType identifyCFF(Reader *reader, int start);

// We need to include the actual source to get the function
// Since identifyCFF is static, we need to include the .cc file
#include "FoFiIdentifier.cc"

using ::testing::_;
using ::testing::Return;
using ::testing::DoAll;
using ::testing::SetArgPointee;

class MockReader : public Reader {
public:
    MOCK_METHOD(int, getByte, (int pos), (override));
    MOCK_METHOD(bool, getU16BE, (int pos, int *val), (override));
    MOCK_METHOD(bool, getU32BE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getU32LE, (int pos, unsigned int *val), (override));
    MOCK_METHOD(bool, getUVarBE, (int pos, int size, unsigned int *val), (override));
    MOCK_METHOD(bool, cmp, (int pos, const char *s), (override));
};

class IdentifyCFFTest_52 : public ::testing::Test {
protected:
    MockReader reader;
};

// Test: First byte is not 0x01 -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, InvalidFirstByte_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x02));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Second byte is not 0x00 -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, InvalidSecondByte_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x01));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: hdrSize (byte at start+2) is negative -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, NegativeHdrSize_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(-1));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: offSize0 at start+3 is 0 (less than 1) -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, OffSize0TooSmall_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(0));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: offSize0 at start+3 is 5 (greater than 4) -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, OffSize0TooLarge_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(5));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: getU16BE fails at first name INDEX -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, FirstGetU16BEFails_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(1));
    EXPECT_CALL(reader, getU16BE(4, _)).WillOnce(Return(false));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Name INDEX count is 0, then second getU16BE fails -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, NameIndexCountZero_SecondU16BEFails_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(1));
    // First getU16BE at pos=4: n=0
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    // pos becomes 4+2=6, second getU16BE at pos=6
    EXPECT_CALL(reader, getU16BE(6, _)).WillOnce(Return(false));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Name INDEX count is 0, second getU16BE returns n<1 -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, NameIndexCountZero_TopDictCountZero_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(1));
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Name INDEX n>0 but offSize1 invalid -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, NameIndexNonZero_InvalidOffSize_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(1));
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize1 at pos+2 = 6
    EXPECT_CALL(reader, getByte(6)).WillOnce(Return(0));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Name INDEX n>0 but getUVarBE fails -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, NameIndexNonZero_GetUVarBEFails_52) {
    EXPECT_CALL(reader, getByte(0)).WillOnce(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillOnce(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillOnce(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillOnce(Return(1));
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize1 at pos+2=6, value=1
    EXPECT_CALL(reader, getByte(6)).WillOnce(Return(1));
    // getUVarBE(pos+3+n*offSize1, offSize1, ...) = getUVarBE(4+3+1*1, 1, ...) = getUVarBE(8, 1, ...)
    EXPECT_CALL(reader, getUVarBE(8, 1, _)).WillOnce(Return(false));
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Full valid CFF that results in fofiIdCFF8Bit (simple case)
// Construct a minimal valid CFF structure where the Top DICT doesn't contain ROS operator
TEST_F(IdentifyCFFTest_52, ValidCFF8Bit_SimpleCase_52) {
    int start = 0;
    // Header: version 1.0, hdrSize=4, offSize=1
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    // Name INDEX at pos=4: count=0
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    // pos becomes 6
    
    // Top DICT INDEX at pos=6: count=1
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize1 at pos+2=8, value=1
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    // offset0 at pos+3=9, offSize=1: value=1
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    // offset1 at pos+3+offSize=10, offSize=1: value=4
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(4u), Return(true)));
    
    // pos = 6 + 3 + (1+1)*1 + 1 - 1 = 6 + 3 + 2 + 0 = 11
    // endPos = 6 + 3 + 2 + 4 - 1 = 14
    // Top DICT data from pos=11 to endPos=14, length=3
    
    // Reading 3 bytes of Top DICT DICT data
    // Use simple integer operands (0x20-0xf6 range)
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x20)); // valid single-byte integer
    EXPECT_CALL(reader, getByte(12)).WillOnce(Return(0x20));
    EXPECT_CALL(reader, getByte(13)).WillOnce(Return(0x20));
    
    // After loop, pos=14, endPos=14, pos+1=15 < endPos=14 is false
    // So we skip the ROS check and return fofiIdCFF8Bit
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}

// Test: Valid CFF with ROS operator -> fofiIdCFFCID
TEST_F(IdentifyCFFTest_52, ValidCFFCID_52) {
    int start = 0;
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    // Name INDEX at pos=4: count=0
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    
    // Top DICT INDEX at pos=6: count=1
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    // offset0=1, offset1=6 (so data is 5 bytes long)
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(6u), Return(true)));
    
    // pos = 6+3+2+1-1=11, endPos = 6+3+2+6-1=16
    // Data: pos=11..15 (5 bytes)
    // 3 operands then check for ROS (12, 30)
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x20)); // single byte int, pos=12
    EXPECT_CALL(reader, getByte(12)).WillOnce(Return(0x20)); // single byte int, pos=13
    EXPECT_CALL(reader, getByte(13)).WillOnce(Return(0x20)); // single byte int, pos=14
    
    // Now check pos=14, endPos=16, pos+1=15 < 16 is true
    EXPECT_CALL(reader, getByte(14)).WillOnce(Return(12));
    EXPECT_CALL(reader, getByte(15)).WillOnce(Return(30));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFFCID);
}

// Test: Top DICT has operand 0x1c (2-byte integer) followed by ROS
TEST_F(IdentifyCFFTest_52, TopDict_0x1c_Operand_CID_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    // offset0=1, offset1=14 (data is 13 bytes)
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(14u), Return(true)));
    
    // pos=11, endPos=24
    // Operand 1: 0x1c (skip 2 more bytes), pos goes 11->14
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x1c));
    // Operand 2: 0x1d (skip 4 more bytes), pos goes 14->19
    EXPECT_CALL(reader, getByte(14)).WillOnce(Return(0x1d));
    // Operand 3: 0xf7 (skip 1 more byte), pos goes 19->21
    EXPECT_CALL(reader, getByte(19)).WillOnce(Return(0xf7));
    
    // pos=21, endPos=24, pos+1=22 < 24 true
    EXPECT_CALL(reader, getByte(21)).WillOnce(Return(12));
    EXPECT_CALL(reader, getByte(22)).WillOnce(Return(30));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFFCID);
}

// Test: Top DICT has invalid operator byte (<0x20 and not 0x1c/0x1d) -> fofiIdCFF8Bit
TEST_F(IdentifyCFFTest_52, TopDict_InvalidByte_ReturnsCFF8Bit_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(10u), Return(true)));
    
    // pos=11, endPos=20
    // First byte: 0x0a (operator, not 0x1c or 0x1d, < 0x20) -> fofiIdCFF8Bit
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x0a));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}

// Test: Non-zero start offset
TEST_F(IdentifyCFFTest_52, NonZeroStartOffset_52) {
    int start = 10;
    EXPECT_CALL(reader, getByte(10)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(11)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(12)).WillRepeatedly(Return(14)); // hdrSize=14
    EXPECT_CALL(reader, getByte(13)).WillRepeatedly(Return(1));  // offSize=1

    // pos = start + hdrSize = 10 + 14 = 24
    EXPECT_CALL(reader, getU16BE(24, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    // pos = 26
    EXPECT_CALL(reader, getU16BE(26, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(28)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(29, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(30, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(4u), Return(true)));
    
    // pos=31, endPos=34
    EXPECT_CALL(reader, getByte(31)).WillOnce(Return(0x20));
    EXPECT_CALL(reader, getByte(32)).WillOnce(Return(0x20));
    EXPECT_CALL(reader, getByte(33)).WillOnce(Return(0x20));
    
    EXPECT_EQ(identifyCFF(&reader, start), fofiIdCFF8Bit);
}

// Test: Name INDEX with non-zero count
TEST_F(IdentifyCFFTest_52, NameIndexNonZeroCount_ValidCFF8Bit_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    // Name INDEX at pos=4: count=1
    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize at pos+2=6, value=1
    EXPECT_CALL(reader, getByte(6)).WillOnce(Return(1));
    
    // getUVarBE(pos+3+n*offSize, offSize, ...) = getUVarBE(4+3+1*1, 1, ...) = getUVarBE(8, 1, ...)
    // offset1=5 (name data is 4 bytes)
    EXPECT_CALL(reader, getUVarBE(8, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(5u), Return(true)));
    
    // new pos = 4 + 3 + (1+1)*1 + 5 - 1 = 4 + 3 + 2 + 4 = 13
    // Top DICT INDEX at pos=13: count=1
    EXPECT_CALL(reader, getU16BE(13, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize at 15
    EXPECT_CALL(reader, getByte(15)).WillOnce(Return(1));
    
    // offset0 at 16: value=1
    EXPECT_CALL(reader, getUVarBE(16, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    // offset1 at 17: value=4
    EXPECT_CALL(reader, getUVarBE(17, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(4u), Return(true)));
    
    // pos = 13+3+(1+1)*1+1-1 = 18, endPos = 13+3+2+4-1 = 21
    EXPECT_CALL(reader, getByte(18)).WillOnce(Return(0x20));
    EXPECT_CALL(reader, getByte(19)).WillOnce(Return(0x20));
    EXPECT_CALL(reader, getByte(20)).WillOnce(Return(0x20));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}

// Test: Top DICT INDEX offSize1 invalid for second check -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, TopDictOffSizeInvalid_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    // offSize at 8 = 5 (invalid)
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(5));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: Top DICT INDEX offset0 > offset1 -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, TopDictOffset0GreaterThanOffset1_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    // offset0=5, offset1=3 (offset0 > offset1)
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(5u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(3u), Return(true)));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: ROS check - byte at pos is 12 but next byte is not 30 -> fofiIdCFF8Bit
TEST_F(IdentifyCFFTest_52, NotROS_FirstByteIs12_SecondNot30_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(6u), Return(true)));
    
    // pos=11, endPos=16
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x20)); // pos=12
    EXPECT_CALL(reader, getByte(12)).WillOnce(Return(0x20)); // pos=13
    EXPECT_CALL(reader, getByte(13)).WillOnce(Return(0x20)); // pos=14
    
    // ROS check: pos=14, endPos=16
    EXPECT_CALL(reader, getByte(14)).WillOnce(Return(12));
    EXPECT_CALL(reader, getByte(15)).WillOnce(Return(29)); // Not 30
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}

// Test: Top DICT byte > 0xf6 -> fofiIdCFF8Bit
TEST_F(IdentifyCFFTest_52, TopDict_ByteGreaterThanF6_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(10u), Return(true)));
    
    // pos=11, endPos=20
    // 0xff is > 0xf6 but is in range 0xf7-0xfe, so it skips 1 byte
    // Wait, 0xff > 0xfe so it falls through to the else branch: b0 > 0xf6 -> fofiIdCFF8Bit
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0xff));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}

// Test: Top DICT getUVarBE for offset0 fails -> fofiIdUnknown
TEST_F(IdentifyCFFTest_52, TopDictGetUVarBE_Offset0Fails_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _)).WillOnce(Return(false));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdUnknown);
}

// Test: 0xfe byte in dict (in range 0xf7-0xfe, skips 1 byte)
TEST_F(IdentifyCFFTest_52, TopDict_0xFE_SkipsOneByte_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(10u), Return(true)));
    
    // pos=11, endPos=20
    // 0xfe: in range, skip 1 => pos=13
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0xfe));
    // 0xf7: in range, skip 1 => pos=15
    EXPECT_CALL(reader, getByte(13)).WillOnce(Return(0xf7));
    // 0x20: simple int => pos=16
    EXPECT_CALL(reader, getByte(15)).WillOnce(Return(0x20));
    
    // ROS check at pos=16, endPos=20
    EXPECT_CALL(reader, getByte(16)).WillOnce(Return(12));
    EXPECT_CALL(reader, getByte(17)).WillOnce(Return(30));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFFCID);
}

// Test: 0x1d operand (4-byte integer)
TEST_F(IdentifyCFFTest_52, TopDict_0x1d_Skips4Bytes_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(20u), Return(true)));
    
    // pos=11, endPos=30
    // 0x1d: skip 4 => pos=16
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x1d));
    // 0x1c: skip 2 => pos=19
    EXPECT_CALL(reader, getByte(16)).WillOnce(Return(0x1c));
    // 0x20: simple int => pos=20
    EXPECT_CALL(reader, getByte(19)).WillOnce(Return(0x20));
    
    // ROS check at pos=20, endPos=30
    EXPECT_CALL(reader, getByte(20)).WillOnce(Return(12));
    EXPECT_CALL(reader, getByte(21)).WillOnce(Return(30));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFFCID);
}

// Test: Loop exits early when pos >= endPos after processing an operand -> fofiIdCFF8Bit
TEST_F(IdentifyCFFTest_52, LoopExitsEarly_PosReachesEndPos_52) {
    EXPECT_CALL(reader, getByte(0)).WillRepeatedly(Return(0x01));
    EXPECT_CALL(reader, getByte(1)).WillRepeatedly(Return(0x00));
    EXPECT_CALL(reader, getByte(2)).WillRepeatedly(Return(4));
    EXPECT_CALL(reader, getByte(3)).WillRepeatedly(Return(1));

    EXPECT_CALL(reader, getU16BE(4, _))
        .WillOnce(DoAll(SetArgPointee<1>(0), Return(true)));
    EXPECT_CALL(reader, getU16BE(6, _))
        .WillOnce(DoAll(SetArgPointee<1>(1), Return(true)));
    EXPECT_CALL(reader, getByte(8)).WillOnce(Return(1));
    
    // Very short Top DICT data (2 bytes only: offset0=1, offset1=3 => 2 bytes)
    EXPECT_CALL(reader, getUVarBE(9, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(1u), Return(true)));
    EXPECT_CALL(reader, getUVarBE(10, 1, _))
        .WillOnce(DoAll(SetArgPointee<2>(3u), Return(true)));
    
    // pos=11, endPos=13 (2 bytes of data)
    // First iteration: 0x20, pos=12 (< 13, ok)
    EXPECT_CALL(reader, getByte(11)).WillOnce(Return(0x20));
    // Second iteration: 0x20, pos=13 (>= 13, exit loop)
    EXPECT_CALL(reader, getByte(12)).WillOnce(Return(0x20));
    
    EXPECT_EQ(identifyCFF(&reader, 0), fofiIdCFF8Bit);
}
