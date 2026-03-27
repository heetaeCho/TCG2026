#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/node/convert.h"

#include "yaml-cpp/binary.h"



using namespace YAML;



class DecodeBinaryTest_622 : public ::testing::Test {

protected:

    Node node;

    Binary binary;

};



TEST_F(DecodeBinaryTest_622, DecodeScalarNode_622) {

    std::string base64Data = "SGVsbG8gV29ybGQh"; // "Hello World!" in Base64

    node = Node(base64Data);

    

    ASSERT_TRUE(decode(node, binary));

    EXPECT_EQ(binary.size(), 13); // "Hello World!" is 13 characters long



    const unsigned char* dataPtr = binary.data();

    std::string decodedString(reinterpret_cast<const char*>(dataPtr), binary.size());

    EXPECT_EQ(decodedString, "Hello World!");

}



TEST_F(DecodeBinaryTest_622, DecodeEmptyScalarNode_622) {

    node = Node("");

    

    ASSERT_TRUE(decode(node, binary));

    EXPECT_EQ(binary.size(), 0);

}



TEST_F(DecodeBinaryTest_622, DecodeInvalidBase64Node_622) {

    std::string invalidBase64Data = "SGVsbG8gV29ybGQh="; // Invalid Base64

    node = Node(invalidBase64Data);

    

    ASSERT_FALSE(decode(node, binary));

}



TEST_F(DecodeBinaryTest_622, DecodeNonScalarNode_622) {

    node = Node(NodeType::Map);



    ASSERT_FALSE(decode(node, binary));

}
