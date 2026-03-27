#include <gtest/gtest.h>

#include <yaml-cpp/node/convert.h>

#include <yaml-cpp/binary.h>



class EncodeBinaryTest_621 : public ::testing::Test {

protected:

    YAML::Binary binaryData;

};



TEST_F(EncodeBinaryTest_621, EmptyBinaryEncodesToEmptyNode_621) {

    auto node = YAML::encode(binaryData);

    EXPECT_TRUE(node.IsNull());

}



TEST_F(EncodeBinaryTest_621, NonEmptyBinaryEncodesToBase64StringNode_621) {

    const unsigned char testData[] = {0x00, 0x01, 0x02};

    YAML::Binary binary(testData, sizeof(testData));

    auto node = YAML::encode(binary);

    EXPECT_EQ(node.as<std::string>(), "AAEC");

}



TEST_F(EncodeBinaryTest_621, LargeBinaryEncodesCorrectly_621) {

    const unsigned char testData[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    YAML::Binary binary(testData, sizeof(testData));

    auto node = YAML::encode(binary);

    EXPECT_EQ(node.as<std::string>(), "AAECAwQFBgcICg==");

}



TEST_F(EncodeBinaryTest_621, BinaryWithPaddingEncodesCorrectly_621) {

    const unsigned char testData[2] = {0x00, 0x01};

    YAML::Binary binary(testData, sizeof(testData));

    auto node = YAML::encode(binary);

    EXPECT_EQ(node.as<std::string>(), "AAEC");

}



TEST_F(EncodeBinaryTest_621, BinaryWithAllFFBytesEncodesCorrectly_621) {

    const unsigned char testData[3] = {0xFF, 0xFF, 0xFF};

    YAML::Binary binary(testData, sizeof(testData));

    auto node = YAML::encode(binary);

    EXPECT_EQ(node.as<std::string>(), "/////w==");

}
