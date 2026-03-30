#include <gtest/gtest.h>

#include <yaml-cpp/src/binary.cpp>



TEST(EncodeBase64Test_544, EmptyData_ReturnsEmptyString_544) {

    const unsigned char* data = nullptr;

    std::size_t size = 0;

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "");

}



TEST(EncodeBase64Test_544, SingleByteData_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "Eg==");

}



TEST(EncodeBase64Test_544, TwoBytesData_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12, 0x34};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "EjQ=");

}



TEST(EncodeBase64Test_544, ThreeBytesData_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12, 0x34, 0x56};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "EjRW");

}



TEST(EncodeBase64Test_544, MultipleOfThreeBytes_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "EjRWeJq8");

}



TEST(EncodeBase64Test_544, NonMultipleOfThreeBytes_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12, 0x34, 0x56, 0x78, 0x9A};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "EjRWeJq+");

}



TEST(EncodeBase64Test_544, FullRangeOfData_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x00, 0xFF, 0x7F, 0x80};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "AP//fw==");

}



TEST(EncodeBase64Test_544, LargeData_ReturnsCorrectString_544) {

    const unsigned char data[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};

    std::size_t size = sizeof(data);

    std::string result = YAML::EncodeBase64(data, size);

    EXPECT_EQ(result, "EjRWeJq83vA=");

}
