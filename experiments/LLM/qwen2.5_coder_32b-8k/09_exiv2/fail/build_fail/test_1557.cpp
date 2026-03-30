#include <gtest/gtest.h>

#include <exiv2/asfvideo.hpp>

#include <array>



namespace {



using namespace Exiv2;



TEST(GUIDTagTest_1557, EqualityOperatorSameValues_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 123, 456, data4);



    EXPECT_TRUE(tag1 == tag2);

}



TEST(GUIDTagTest_1557, EqualityOperatorDifferentData1_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(654321, 123, 456, data4);



    EXPECT_FALSE(tag1 == tag2);

}



TEST(GUIDTagTest_1557, EqualityOperatorDifferentData2_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 321, 456, data4);



    EXPECT_FALSE(tag1 == tag2);

}



TEST(GUIDTagTest_1557, EqualityOperatorDifferentData3_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 123, 654, data4);



    EXPECT_FALSE(tag1 == tag2);

}



TEST(GUIDTagTest_1557, EqualityOperatorDifferentData4_1557) {

    std::array<byte, 8> data4a = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    std::array<byte, 8> data4b = {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};

    GUIDTag tag1(123456, 123, 456, data4a);

    GUIDTag tag2(123456, 123, 456, data4b);



    EXPECT_FALSE(tag1 == tag2);

}



TEST(GUIDTagTest_1557, ToStringNonEmptyString_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag(123456, 123, 456, data4);



    EXPECT_FALSE(tag.to_string().empty());

}



TEST(GUIDTagTest_1557, LessThanOperatorSameValues_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 123, 456, data4);



    EXPECT_FALSE(tag1 < tag2);

}



TEST(GUIDTagTest_1557, LessThanOperatorDifferentData1_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(654321, 123, 456, data4);



    EXPECT_TRUE(tag1 < tag2);

}



TEST(GUIDTagTest_1557, LessThanOperatorDifferentData2_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 321, 456, data4);



    EXPECT_TRUE(tag1 < tag2);

}



TEST(GUIDTagTest_1557, LessThanOperatorDifferentData3_1557) {

    std::array<byte, 8> data4 = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    GUIDTag tag1(123456, 123, 456, data4);

    GUIDTag tag2(123456, 123, 654, data4);



    EXPECT_TRUE(tag1 < tag2);

}



TEST(GUIDTagTest_1557, LessThanOperatorDifferentData4_1557) {

    std::array<byte, 8> data4a = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

    std::array<byte, 8> data4b = {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};

    GUIDTag tag1(123456, 123, 456, data4a);

    GUIDTag tag2(123456, 123, 456, data4b);



    EXPECT_TRUE(tag1 < tag2);

}



} // namespace
