#include <gtest/gtest.h>

#include "exiv2/types.hpp"

#include <stdexcept>



using namespace Exiv2;



class DataBufTest_1125 : public ::testing::Test {

protected:

    void SetUp() override {

        // Common setup code if needed

    }

};



TEST_F(DataBufTest_1125, WriteUint64_NormalOperation_1125) {

    DataBuf buffer(8);

    uint64_t value = 0x1122334455667788;

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(buffer.write_uint64(0, value, byteOrder));



    // Verify the written value by reading it back

    EXPECT_EQ(value, buffer.read_uint64(0, byteOrder));

}



TEST_F(DataBufTest_1125, WriteUint64_OffsetAtBoundary_1125) {

    DataBuf buffer(8);

    uint64_t value = 0x1122334455667788;

    ByteOrder byteOrder = littleEndian;



    EXPECT_NO_THROW(buffer.write_uint64(0, value, byteOrder));

}



TEST_F(DataBufTest_1125, WriteUint64_OffsetTooLarge_1125) {

    DataBuf buffer(8);

    uint64_t value = 0x1122334455667788;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(buffer.write_uint64(1, value, byteOrder), std::out_of_range);

}



TEST_F(DataBufTest_1125, WriteUint64_BufferTooSmall_1125) {

    DataBuf buffer(7);

    uint64_t value = 0x1122334455667788;

    ByteOrder byteOrder = littleEndian;



    EXPECT_THROW(buffer.write_uint64(0, value, byteOrder), std::out_of_range);

}



TEST_F(DataBufTest_1125, WriteUint64_BigEndianCheck_1125) {

    DataBuf buffer(8);

    uint64_t value = 0x1122334455667788;

    ByteOrder byteOrder = bigEndian;



    EXPECT_NO_THROW(buffer.write_uint64(0, value, byteOrder));



    // Verify the written value by reading it back

    EXPECT_EQ(value, buffer.read_uint64(0, byteOrder));

}
