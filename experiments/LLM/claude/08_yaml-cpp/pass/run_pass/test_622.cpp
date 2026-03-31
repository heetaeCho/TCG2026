#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/binary.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/convert.h"

// Helper to encode binary data to base64 for creating test nodes
// We'll use YAML's own encoding via Node assignment

class BinaryDecodeTest_622 : public ::testing::Test {
protected:
    // Helper: create a scalar node with a given string value
    YAML::Node makeScalar(const std::string& value) {
        YAML::Node node;
        node = value;
        return node;
    }

    YAML::Node makeSequence() {
        YAML::Node node;
        node.push_back(1);
        node.push_back(2);
        return node;
    }

    YAML::Node makeMap() {
        YAML::Node node;
        node["key"] = "value";
        return node;
    }

    YAML::Node makeNull() {
        YAML::Node node;
        return node;
    }
};

// Test: Decoding a non-scalar node (sequence) should return false
TEST_F(BinaryDecodeTest_622, DecodeSequenceNodeReturnsFalse_622) {
    YAML::Node node = makeSequence();
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_FALSE(result);
}

// Test: Decoding a non-scalar node (map) should return false
TEST_F(BinaryDecodeTest_622, DecodeMapNodeReturnsFalse_622) {
    YAML::Node node = makeMap();
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_FALSE(result);
}

// Test: Decoding an empty scalar should succeed with empty binary data
TEST_F(BinaryDecodeTest_622, DecodeEmptyScalarReturnsEmptyBinary_622) {
    YAML::Node node = makeScalar("");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 0u);
}

// Test: Decoding valid base64 encoded data should succeed
TEST_F(BinaryDecodeTest_622, DecodeValidBase64Succeeds_622) {
    // "SGVsbG8=" is base64 for "Hello"
    YAML::Node node = makeScalar("SGVsbG8=");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 5u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "Hello");
}

// Test: Decoding invalid base64 string should return false
TEST_F(BinaryDecodeTest_622, DecodeInvalidBase64ReturnsFalse_622) {
    // "!!!!" is not valid base64
    YAML::Node node = makeScalar("!!!!");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_FALSE(result);
}

// Test: Decoding base64 "dGVzdA==" which encodes "test"
TEST_F(BinaryDecodeTest_622, DecodeBase64Test_622) {
    YAML::Node node = makeScalar("dGVzdA==");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 4u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "test");
}

// Test: Decoding base64 with padding "YQ==" which encodes "a"
TEST_F(BinaryDecodeTest_622, DecodeBase64SingleChar_622) {
    YAML::Node node = makeScalar("YQ==");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 1u);
    EXPECT_EQ(binary.data()[0], 'a');
}

// Test: Decoding base64 "YWI=" which encodes "ab"
TEST_F(BinaryDecodeTest_622, DecodeBase64TwoChars_622) {
    YAML::Node node = makeScalar("YWI=");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 2u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "ab");
}

// Test: Decoding base64 "YWJj" which encodes "abc" (no padding)
TEST_F(BinaryDecodeTest_622, DecodeBase64ThreeCharsNoPadding_622) {
    YAML::Node node = makeScalar("YWJj");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 3u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "abc");
}

// Test: Using Node::as<Binary> with valid base64
TEST_F(BinaryDecodeTest_622, NodeAsWithValidBase64_622) {
    YAML::Node node = makeScalar("SGVsbG8=");
    YAML::Binary binary = node.as<YAML::Binary>();
    EXPECT_EQ(binary.size(), 5u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "Hello");
}

// Test: Decoding a longer base64 string
TEST_F(BinaryDecodeTest_622, DecodeLongerBase64String_622) {
    // "SGVsbG8gV29ybGQh" is base64 for "Hello World!"
    YAML::Node node = makeScalar("SGVsbG8gV29ybGQh");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 12u);
    std::string decoded(reinterpret_cast<const char*>(binary.data()), binary.size());
    EXPECT_EQ(decoded, "Hello World!");
}

// Test: Binary data replaces previous content after decode
TEST_F(BinaryDecodeTest_622, DecodeReplacesPreviousContent_622) {
    unsigned char initial[] = {0xFF, 0xFE, 0xFD};
    YAML::Binary binary(initial, 3);
    EXPECT_EQ(binary.size(), 3u);

    // Decode "YQ==" -> "a"
    YAML::Node node = makeScalar("YQ==");
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 1u);
    EXPECT_EQ(binary.data()[0], 'a');
}

// Test: Null node (undefined) is not scalar, should fail
TEST_F(BinaryDecodeTest_622, DecodeNullNodeReturnsFalse_622) {
    YAML::Node node;
    YAML::Binary binary;
    // A default-constructed node is Null type, not scalar
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_FALSE(result);
}

// Test: Base64 encoding with binary zeros
TEST_F(BinaryDecodeTest_622, DecodeBase64WithBinaryZeros_622) {
    // "AAAA" is base64 for three zero bytes
    YAML::Node node = makeScalar("AAAA");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 3u);
    EXPECT_EQ(binary.data()[0], 0);
    EXPECT_EQ(binary.data()[1], 0);
    EXPECT_EQ(binary.data()[2], 0);
}

// Test: Base64 "/w==" decodes to a single byte 0xFF
TEST_F(BinaryDecodeTest_622, DecodeBase64SingleByte0xFF_622) {
    YAML::Node node = makeScalar("/w==");
    YAML::Binary binary;
    bool result = YAML::convert<YAML::Binary>::decode(node, binary);
    EXPECT_TRUE(result);
    EXPECT_EQ(binary.size(), 1u);
    EXPECT_EQ(binary.data()[0], 0xFF);
}
