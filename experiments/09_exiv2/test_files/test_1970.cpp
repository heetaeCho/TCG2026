#include <gtest/gtest.h>

#include "XMPMeta-Parse.cpp"

#include "XMP_Const.h"



class DetermineInputEncodingTest_1970 : public ::testing::Test {

protected:

    using XMP_OptionBits = unsigned int;

};



TEST_F(DetermineInputEncodingTest_1970, LengthLessThan2_ReturnsUTF8_1970) {

    const XMP_Uns8 buffer[] = { 0x00 };

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length2_UTF8_ReturnsUTF8_1970) {

    const XMP_Uns8 buffer[] = { 0x65, 0x6E }; // "en" in ASCII

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length2_UTF16Big_ReturnsUTF16Big_1970) {

    const XMP_Uns8 buffer[] = { 0x00, 0x45 }; // "E" in UTF-16 Big Endian

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length3_UTF8_ReturnsUTF8_1970) {

    const XMP_Uns8 buffer[] = { 0x45, 0x6E, 0x67 }; // "Eng" in ASCII

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length3_UTF16Little_ReturnsUTF16Little_1970) {

    const XMP_Uns8 buffer[] = { 0x45, 0x00 }; // "E" in UTF-16 Little Endian

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length4_UTF32Big_ReturnsUTF32Big_1970) {

    const XMP_Uns8 buffer[] = { 0x00, 0x00, 0x00, 0x45 }; // "E" in UTF-32 Big Endian

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF32Big, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, Length4_UTF32Little_ReturnsUTF32Little_1970) {

    const XMP_Uns8 buffer[] = { 0x45, 0x00, 0x00, 0x00 }; // "E" in UTF-32 Little Endian

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF32Little, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, UTF8_BOM_ReturnsUTF8_1970) {

    const XMP_Uns8 buffer[] = { 0xEF, 0xBB, 0xBF }; // UTF-8 BOM

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF8, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, UTF16Big_BOM_ReturnsUTF16Big_1970) {

    const XMP_Uns8 buffer[] = { 0xFE, 0xFF }; // UTF-16 Big Endian BOM

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF16Big, DetermineInputEncoding(buffer, length));

}



TEST_F(DetermineInputEncodingTest_1970, UTF16Little_BOM_ReturnsUTF16Little_1970) {

    const XMP_Uns8 buffer[] = { 0xFF, 0xFE }; // UTF-16 Little Endian BOM

    size_t length = sizeof(buffer);

    EXPECT_EQ(kXMP_EncodeUTF16Little, DetermineInputEncoding(buffer, length));

}
