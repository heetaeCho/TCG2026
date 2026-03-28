#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>

// Define the types and constants from the XMP SDK
typedef uint8_t XMP_Uns8;
typedef uint32_t XMP_OptionBits;

enum {
    _XMP_LittleEndian_Bit = 1,
    _XMP_UTF16_Bit = 2,
    _XMP_UTF32_Bit = 4,
    kXMP_EncodingMask = 7,
    kXMP_EncodeUTF8 = 0,
    kXMP_EncodeUTF16Big = 2,
    kXMP_EncodeUTF16Little = 3,
    kXMP_EncodeUTF32Big = 4,
    kXMP_EncodeUTF32Little = 5
};

// Declare the function under test (it's static in the original file, so we
// need to include the implementation or re-declare it for testing purposes)
// Since we cannot modify the source, we include the implementation directly.
static XMP_OptionBits DetermineInputEncoding(const XMP_Uns8* buffer, size_t length) {
    if (length < 2) return kXMP_EncodeUTF8;

    XMP_Uns8* uniChar = (XMP_Uns8*)buffer;

    if (uniChar[0] == 0) {
        if ((length < 4) || (uniChar[1] != 0)) return kXMP_EncodeUTF16Big;
        return kXMP_EncodeUTF32Big;
    } else if (uniChar[0] < 0x80) {
        if (uniChar[1] != 0) return kXMP_EncodeUTF8;
        if ((length < 4) || (uniChar[2] != 0)) return kXMP_EncodeUTF16Little;
        return kXMP_EncodeUTF32Little;
    } else {
        if (uniChar[0] == 0xEF) return kXMP_EncodeUTF8;
        if (uniChar[0] == 0xFE) return kXMP_EncodeUTF16Big;
        if ((length < 4) || (uniChar[2] != 0)) return kXMP_EncodeUTF16Little;
        return kXMP_EncodeUTF32Little;
    }
}

class DetermineInputEncodingTest_1970 : public ::testing::Test {
protected:
};

// ==================== Empty / Very Short Buffers ====================

TEST_F(DetermineInputEncodingTest_1970, EmptyBuffer_ReturnsUTF8_1970) {
    XMP_Uns8 buffer[] = {};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 0));
}

TEST_F(DetermineInputEncodingTest_1970, SingleByte_ReturnsUTF8_1970) {
    XMP_Uns8 buffer[] = {0x41};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 1));
}

TEST_F(DetermineInputEncodingTest_1970, SingleByteNull_ReturnsUTF8_1970) {
    XMP_Uns8 buffer[] = {0x00};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 1));
}

// ==================== First byte == 0x00 branch ====================

// uniChar[0]==0, length<4, should return UTF16Big
TEST_F(DetermineInputEncodingTest_1970, FirstByteZero_Length2_UTF16Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByteZero_Length3_UTF16Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x3C, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 3));
}

// uniChar[0]==0, length>=4, uniChar[1]!=0 => UTF16Big
TEST_F(DetermineInputEncodingTest_1970, FirstByteZero_Length4_SecondByteNonZero_UTF16Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x3C, 0x00, 0x3F};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 4));
}

// uniChar[0]==0, length>=4, uniChar[1]==0 => UTF32Big
TEST_F(DetermineInputEncodingTest_1970, FirstByteZero_Length4_SecondByteZero_UTF32Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x00, 0x00, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByteZero_Length5_SecondByteZero_UTF32Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x00, 0x00, 0x3C, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, 5));
}

// ==================== First byte < 0x80 (ASCII range, non-zero) ====================

// uniChar[0]<0x80, uniChar[1]!=0 => UTF8
TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteNonZero_UTF8_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x3F};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteNonZero_Length4_UTF8_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x3F, 0x78, 0x6D};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 4));
}

// uniChar[0]<0x80, uniChar[1]==0, length<4 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteZero_Length2_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteZero_Length3_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x3F, 0x00};
    // length 3, so (length < 4) is true => UTF16Little
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 3));
}

// uniChar[0]<0x80, uniChar[1]==0, length>=4, uniChar[2]!=0 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteZero_ThirdByteNonZero_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x3F, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// uniChar[0]<0x80, uniChar[1]==0, length>=4, uniChar[2]==0 => UTF32Little
TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteZero_ThirdByteZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, AsciiFirstByte_SecondByteZero_ThirdByteZero_LargeLength_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 8));
}

// ==================== First byte >= 0x80 branch ====================

// uniChar[0] == 0xEF (UTF-8 BOM start) => UTF8
TEST_F(DetermineInputEncodingTest_1970, UTF8BOM_ReturnsUTF8_1970) {
    XMP_Uns8 buffer[] = {0xEF, 0xBB, 0xBF, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, UTF8BOM_Length2_ReturnsUTF8_1970) {
    XMP_Uns8 buffer[] = {0xEF, 0xBB};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 2));
}

// uniChar[0] == 0xFE (UTF-16 BE BOM start) => UTF16Big
TEST_F(DetermineInputEncodingTest_1970, UTF16BEBOM_ReturnsUTF16Big_1970) {
    XMP_Uns8 buffer[] = {0xFE, 0xFF, 0x00, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, UTF16BEBOM_Length2_ReturnsUTF16Big_1970) {
    XMP_Uns8 buffer[] = {0xFE, 0xFF};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 2));
}

// uniChar[0] == 0xFF (UTF-16 LE BOM start), length < 4 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, UTF16LEBOM_Length2_ReturnsUTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, UTF16LEBOM_Length3_ReturnsUTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 3));
}

// uniChar[0] == 0xFF, length>=4, uniChar[2]!=0 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, UTF16LEBOM_Length4_ThirdByteNonZero_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE, 0x3C, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// uniChar[0] == 0xFF, length>=4, uniChar[2]==0 => UTF32Little
TEST_F(DetermineInputEncodingTest_1970, UTF16LEBOM_Length4_ThirdByteZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

// High byte >= 0x80 but not 0xEF or 0xFE - e.g., 0x80
// length < 4 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, HighByte0x80_Length2_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x80, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 2));
}

// High byte 0xC0, length>=4, uniChar[2]!=0 => UTF16Little
TEST_F(DetermineInputEncodingTest_1970, HighByte0xC0_Length4_ThirdNonZero_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xC0, 0x00, 0x01, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// High byte 0xC0, length>=4, uniChar[2]==0 => UTF32Little
TEST_F(DetermineInputEncodingTest_1970, HighByte0xC0_Length4_ThirdZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0xC0, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

// ==================== Edge cases for first byte values ====================

// First byte = 0x01 (smallest non-zero ASCII)
TEST_F(DetermineInputEncodingTest_1970, FirstByte0x01_SecondNonZero_UTF8_1970) {
    XMP_Uns8 buffer[] = {0x01, 0x02};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByte0x01_SecondZero_Length2_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x01, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 2));
}

// First byte = 0x7F (boundary of < 0x80)
TEST_F(DetermineInputEncodingTest_1970, FirstByte0x7F_SecondNonZero_UTF8_1970) {
    XMP_Uns8 buffer[] = {0x7F, 0x01};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 2));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByte0x7F_SecondZero_Length4_ThirdZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0x7F, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

// First byte = 0x80 (boundary of >= 0x80, but not 0xEF or 0xFE)
TEST_F(DetermineInputEncodingTest_1970, FirstByte0x80_Length4_ThirdZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0x80, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByte0x80_Length4_ThirdNonZero_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0x80, 0x00, 0x01, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// ==================== Realistic XMP patterns ====================

// Typical UTF-8 XML: "<?xp"
TEST_F(DetermineInputEncodingTest_1970, TypicalUTF8XML_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x3F, 0x78, 0x70};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 4));
}

// Typical UTF-16BE: 00 3C 00 3F
TEST_F(DetermineInputEncodingTest_1970, TypicalUTF16BE_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x3C, 0x00, 0x3F};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 4));
}

// Typical UTF-16LE: 3C 00 3F 00
TEST_F(DetermineInputEncodingTest_1970, TypicalUTF16LE_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x3F, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// Typical UTF-32BE: 00 00 00 3C
TEST_F(DetermineInputEncodingTest_1970, TypicalUTF32BE_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x00, 0x00, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, 4));
}

// Typical UTF-32LE: 3C 00 00 00
TEST_F(DetermineInputEncodingTest_1970, TypicalUTF32LE_1970) {
    XMP_Uns8 buffer[] = {0x3C, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

// ==================== BOM-based detection ====================

// Full UTF-8 BOM
TEST_F(DetermineInputEncodingTest_1970, FullUTF8BOM_1970) {
    XMP_Uns8 buffer[] = {0xEF, 0xBB, 0xBF, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 4));
}

// Full UTF-16BE BOM
TEST_F(DetermineInputEncodingTest_1970, FullUTF16BEBOM_1970) {
    XMP_Uns8 buffer[] = {0xFE, 0xFF, 0x00, 0x3C};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 4));
}

// Full UTF-16LE BOM followed by data
TEST_F(DetermineInputEncodingTest_1970, FullUTF16LEBOMWithData_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE, 0x3C, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

// UTF-32LE BOM: FF FE 00 00
TEST_F(DetermineInputEncodingTest_1970, UTF32LEBOM_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

// ==================== Exact boundary: length == 4 ====================

TEST_F(DetermineInputEncodingTest_1970, Length4Boundary_FirstZero_SecondZero_UTF32Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x00, 0xFE, 0xFF};
    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, Length4Boundary_FirstZero_SecondNonZero_UTF16Big_1970) {
    XMP_Uns8 buffer[] = {0x00, 0x01, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, 4));
}

// ==================== Large buffers ====================

TEST_F(DetermineInputEncodingTest_1970, LargeUTF8Buffer_1970) {
    XMP_Uns8 buffer[1024];
    memset(buffer, 0x41, 1024);  // All 'A's
    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, 1024));
}

TEST_F(DetermineInputEncodingTest_1970, LargeUTF16BigBuffer_1970) {
    XMP_Uns8 buffer[1024];
    memset(buffer, 0x00, 1024);
    buffer[1] = 0x3C;  // UTF-16BE pattern
    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, 1024));
    // uniChar[0]==0, length>=4, uniChar[1]==0 => UTF32Big
}

// ==================== uniChar[0] values in the >= 0x80 but not special ====================

TEST_F(DetermineInputEncodingTest_1970, FirstByte0xFD_Length4_ThirdZero_UTF32Little_1970) {
    XMP_Uns8 buffer[] = {0xFD, 0x00, 0x00, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByte0xFD_Length4_ThirdNonZero_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFD, 0x00, 0x01, 0x00};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 4));
}

TEST_F(DetermineInputEncodingTest_1970, FirstByte0xFF_Length2_UTF16Little_1970) {
    XMP_Uns8 buffer[] = {0xFF, 0xFE};
    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, 2));
}
