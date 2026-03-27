#include <gtest/gtest.h>

#include "exiv2/types.hpp"



namespace Exiv2 {

    size_t ull2Data(byte* buf, uint64_t l, ByteOrder byteOrder);

}



class Ull2DataTest_1147 : public ::testing::Test {

protected:

    static constexpr size_t BufferSize = 8;

    byte buffer_[BufferSize];

};



TEST_F(Ull2DataTest_1147, PutLittleEndianValue_1147) {

    uint64_t value = 0x123456789ABCDEF0;

    Exiv2::ull2Data(buffer_, value, Exiv2::littleEndian);

    EXPECT_EQ(buffer_[0], 0xF0);

    EXPECT_EQ(buffer_[1], 0xDE);

    EXPECT_EQ(buffer_[2], 0xBC);

    EXPECT_EQ(buffer_[3], 0x9A);

    EXPECT_EQ(buffer_[4], 0x78);

    EXPECT_EQ(buffer_[5], 0x56);

    EXPECT_EQ(buffer_[6], 0x34);

    EXPECT_EQ(buffer_[7], 0x12);

}



TEST_F(Ull2DataTest_1147, PutBigEndianValue_1147) {

    uint64_t value = 0x123456789ABCDEF0;

    Exiv2::ull2Data(buffer_, value, Exiv2::bigEndian);

    EXPECT_EQ(buffer_[0], 0x12);

    EXPECT_EQ(buffer_[1], 0x34);

    EXPECT_EQ(buffer_[2], 0x56);

    EXPECT_EQ(buffer_[3], 0x78);

    EXPECT_EQ(buffer_[4], 0x9A);

    EXPECT_EQ(buffer_[5], 0xBC);

    EXPECT_EQ(buffer_[6], 0xDE);

    EXPECT_EQ(buffer_[7], 0xF0);

}



TEST_F(Ull2DataTest_1147, ZeroValueLittleEndian_1147) {

    uint64_t value = 0;

    Exiv2::ull2Data(buffer_, value, Exiv2::littleEndian);

    for (size_t i = 0; i < BufferSize; ++i) {

        EXPECT_EQ(buffer_[i], 0x00);

    }

}



TEST_F(Ull2DataTest_1147, ZeroValueBigEndian_1147) {

    uint64_t value = 0;

    Exiv2::ull2Data(buffer_, value, Exiv2::bigEndian);

    for (size_t i = 0; i < BufferSize; ++i) {

        EXPECT_EQ(buffer_[i], 0x00);

    }

}



TEST_F(Ull2DataTest_1147, MaxValueLittleEndian_1147) {

    uint64_t value = UINT64_MAX;

    Exiv2::ull2Data(buffer_, value, Exiv2::littleEndian);

    for (size_t i = 0; i < BufferSize; ++i) {

        EXPECT_EQ(buffer_[i], 0xFF);

    }

}



TEST_F(Ull2DataTest_1147, MaxValueBigEndian_1147) {

    uint64_t value = UINT64_MAX;

    Exiv2::ull2Data(buffer_, value, Exiv2::bigEndian);

    for (size_t i = 0; i < BufferSize; ++i) {

        EXPECT_EQ(buffer_[i], 0xFF);

    }

}



TEST_F(Ull2DataTest_1147, InvalidByteOrder_1147) {

    uint64_t value = 0x123456789ABCDEF0;

    size_t result = Exiv2::ull2Data(buffer_, value, static_cast<Exiv2::ByteOrder>(0));

    EXPECT_EQ(result, 8); // Assuming it does not change behavior for invalid input

}
