#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/binary.h"
#include "yaml-cpp/node/convert.h"
#include <vector>
#include <string>

// Test encoding an empty Binary produces a valid Node
TEST(BinaryConvertTest_621, EncodeEmptyBinary_621) {
    YAML::Binary bin;
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());
    // Empty binary should encode to empty base64 string
    std::string encoded = node.as<std::string>();
    EXPECT_TRUE(encoded.empty());
}

// Test encoding a single byte Binary
TEST(BinaryConvertTest_621, EncodeSingleByteBinary_621) {
    unsigned char data[] = {0x41}; // 'A'
    YAML::Binary bin(data, 1);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());
    std::string encoded = node.as<std::string>();
    EXPECT_FALSE(encoded.empty());
}

// Test encoding a multi-byte Binary
TEST(BinaryConvertTest_621, EncodeMultiByteBinary_621) {
    unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"
    YAML::Binary bin(data, 5);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());
    std::string encoded = node.as<std::string>();
    // Base64 of "Hello" is "SGVsbG8="
    EXPECT_EQ(encoded, "SGVsbG8=");
}

// Test encoding binary data with null bytes
TEST(BinaryConvertTest_621, EncodeBinaryWithNullBytes_621) {
    unsigned char data[] = {0x00, 0x01, 0x02, 0x00, 0x03};
    YAML::Binary bin(data, 5);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());
    std::string encoded = node.as<std::string>();
    EXPECT_FALSE(encoded.empty());
}

// Test encoding binary data with all possible byte values (boundary)
TEST(BinaryConvertTest_621, EncodeAllByteValues_621) {
    unsigned char data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<unsigned char>(i);
    }
    YAML::Binary bin(data, 256);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());
    std::string encoded = node.as<std::string>();
    EXPECT_FALSE(encoded.empty());
}

// Test round-trip: encode then decode should give back the same binary data
TEST(BinaryConvertTest_621, RoundTripEncodeDecode_621) {
    unsigned char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64};
    YAML::Binary original(data, 11);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(original);

    YAML::Binary decoded;
    bool success = YAML::convert<YAML::Binary>::decode(node, decoded);
    ASSERT_TRUE(success);
    EXPECT_EQ(original.size(), decoded.size());
    EXPECT_EQ(original, decoded);
}

// Test round-trip with empty binary
TEST(BinaryConvertTest_621, RoundTripEmptyBinary_621) {
    YAML::Binary original;
    YAML::Node node = YAML::convert<YAML::Binary>::encode(original);

    YAML::Binary decoded;
    bool success = YAML::convert<YAML::Binary>::decode(node, decoded);
    ASSERT_TRUE(success);
    EXPECT_EQ(original.size(), decoded.size());
    EXPECT_EQ(original, decoded);
}

// Test encoding binary data whose length is a multiple of 3 (no padding in base64)
TEST(BinaryConvertTest_621, EncodeMultipleOfThreeLength_621) {
    unsigned char data[] = {0x41, 0x42, 0x43}; // "ABC"
    YAML::Binary bin(data, 3);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    std::string encoded = node.as<std::string>();
    // Base64 of "ABC" is "QUJD" (no padding)
    EXPECT_EQ(encoded, "QUJD");
}

// Test encoding binary data whose length % 3 == 1 (two padding chars in base64)
TEST(BinaryConvertTest_621, EncodeLengthMod3Equals1_621) {
    unsigned char data[] = {0x41}; // "A"
    YAML::Binary bin(data, 1);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    std::string encoded = node.as<std::string>();
    // Base64 of "A" is "QQ=="
    EXPECT_EQ(encoded, "QQ==");
}

// Test encoding binary data whose length % 3 == 2 (one padding char in base64)
TEST(BinaryConvertTest_621, EncodeLengthMod3Equals2_621) {
    unsigned char data[] = {0x41, 0x42}; // "AB"
    YAML::Binary bin(data, 2);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    std::string encoded = node.as<std::string>();
    // Base64 of "AB" is "QUI="
    EXPECT_EQ(encoded, "QUI=");
}

// Test decoding from a non-scalar node fails gracefully
TEST(BinaryConvertTest_621, DecodeFromSequenceNodeFails_621) {
    YAML::Node node;
    node.push_back("item1");
    node.push_back("item2");

    YAML::Binary decoded;
    bool success = YAML::convert<YAML::Binary>::decode(node, decoded);
    EXPECT_FALSE(success);
}

// Test round-trip with binary data containing 0xFF bytes
TEST(BinaryConvertTest_621, RoundTripHighBytes_621) {
    unsigned char data[] = {0xFF, 0xFE, 0xFD, 0xFC, 0xFB};
    YAML::Binary original(data, 5);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(original);

    YAML::Binary decoded;
    bool success = YAML::convert<YAML::Binary>::decode(node, decoded);
    ASSERT_TRUE(success);
    EXPECT_EQ(original, decoded);
}

// Test encoding larger binary data
TEST(BinaryConvertTest_621, EncodeLargerBinaryData_621) {
    std::vector<unsigned char> data(1024);
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = static_cast<unsigned char>(i % 256);
    }
    YAML::Binary bin(data.data(), data.size());
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    ASSERT_TRUE(node.IsDefined());
    ASSERT_TRUE(node.IsScalar());

    YAML::Binary decoded;
    bool success = YAML::convert<YAML::Binary>::decode(node, decoded);
    ASSERT_TRUE(success);
    EXPECT_EQ(bin, decoded);
}

// Test that the encoded node is a scalar type
TEST(BinaryConvertTest_621, EncodedNodeIsScalar_621) {
    unsigned char data[] = {0x01, 0x02, 0x03};
    YAML::Binary bin(data, 3);
    YAML::Node node = YAML::convert<YAML::Binary>::encode(bin);
    EXPECT_TRUE(node.IsScalar());
    EXPECT_FALSE(node.IsSequence());
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsNull());
}
