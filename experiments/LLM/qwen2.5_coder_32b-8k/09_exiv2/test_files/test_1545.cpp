#include <gtest/gtest.h>

#include "cr2header_int.hpp"



namespace Exiv2 {

namespace Internal {



class Cr2HeaderTest_1545 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Cleanup if needed

    }

};



TEST_F(Cr2HeaderTest_1545, Write_ReturnsCorrectSize_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.size(), 16U);

}



TEST_F(Cr2HeaderTest_1545, Write_LittleEndian_CorrectFirstByte_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint8(0), 'I');

}



TEST_F(Cr2HeaderTest_1545, Write_BigEndian_CorrectFirstByte_1545) {

    Cr2Header header(bigEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint8(0), 'M');

}



TEST_F(Cr2HeaderTest_1545, Write_SecondByte_MatchesFirstByte_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint8(1), result.read_uint8(0));

}



TEST_F(Cr2HeaderTest_1545, Write_TagWrittenCorrectly_LittleEndian_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint16(2, littleEndian), 42U);

}



TEST_F(Cr2HeaderTest_1545, Write_TagWrittenCorrectly_BigEndian_1545) {

    Cr2Header header(bigEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint16(2, bigEndian), 42U);

}



TEST_F(Cr2HeaderTest_1545, Write_OffsetWrittenCorrectly_LittleEndian_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint32(4, littleEndian), 0x00000010U);

}



TEST_F(Cr2HeaderTest_1545, Write_OffsetWrittenCorrectly_BigEndian_1545) {

    Cr2Header header(bigEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint32(4, bigEndian), 0x00000010U);

}



TEST_F(Cr2HeaderTest_1545, Write_TrailingZerosWrittenCorrectly_1545) {

    Cr2Header header(littleEndian);

    DataBuf result = header.write();

    EXPECT_EQ(result.read_uint32(12, littleEndian), 0x00000000U);

}



} // namespace Internal

} // namespace Exiv2
