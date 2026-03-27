#include <gtest/gtest.h>

#include <cstring>



extern "C" {

    int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);

}



namespace {



class Base64EncodeTest_1803 : public ::testing::Test {

protected:

    static constexpr size_t kMaxResultSize = 1024;

    char result_[kMaxResultSize];

};



TEST_F(Base64EncodeTest_1803, EmptyInput_ReturnsEmptyString_1803) {

    const uint8_t* data = nullptr;

    size_t dataLength = 0;



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 1);

    EXPECT_STREQ(result_, "");

}



TEST_F(Base64EncodeTest_1803, SingleByteInput_ReturnsValidBase64_1803) {

    const uint8_t data[] = {0x41}; // 'A'

    size_t dataLength = sizeof(data);



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 1);

    EXPECT_STREQ(result_, "QQ==");

}



TEST_F(Base64EncodeTest_1803, TwoBytesInput_ReturnsValidBase64_1803) {

    const uint8_t data[] = {0x41, 0x42}; // 'AB'

    size_t dataLength = sizeof(data);



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 1);

    EXPECT_STREQ(result_, "QUI=");

}



TEST_F(Base64EncodeTest_1803, ThreeBytesInput_ReturnsValidBase64_1803) {

    const uint8_t data[] = {0x41, 0x42, 0x43}; // 'ABC'

    size_t dataLength = sizeof(data);



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 1);

    EXPECT_STREQ(result_, "QUJD");

}



TEST_F(Base64EncodeTest_1803, ArbitraryBytesInput_ReturnsValidBase64_1803) {

    const uint8_t data[] = {0x1f, 0x8b, 0x08};

    size_t dataLength = sizeof(data);



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 1);

    EXPECT_STREQ(result_, "GzsIAw==");

}



TEST_F(Base64EncodeTest_1803, NullDataBuffer_ReturnsZero_1803) {

    const uint8_t* data = nullptr;

    size_t dataLength = 5;



    int rc = base64encode(data, dataLength, result_, kMaxResultSize);



    EXPECT_EQ(rc, 0);

}



TEST_F(Base64EncodeTest_1803, NullResultBuffer_ReturnsZero_1803) {

    const uint8_t data[] = {0x01, 0x02};

    size_t dataLength = sizeof(data);



    int rc = base64encode(data, dataLength, nullptr, kMaxResultSize);



    EXPECT_EQ(rc, 0);

}



TEST_F(Base64EncodeTest_1803, InsufficientBufferSize_ReturnsZero_1803) {

    const uint8_t data[] = {0x01, 0x02, 0x03};

    size_t dataLength = sizeof(data);

    char small_result[5]; // insufficient buffer size



    int rc = base64encode(data, dataLength, small_result, sizeof(small_result));



    EXPECT_EQ(rc, 0);

}



} // namespace
