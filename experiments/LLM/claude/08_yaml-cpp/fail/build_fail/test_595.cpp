#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/convert.h"
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cmath>

// Test fixture
class ConvertTest_595 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== String Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeEmptyString_595) {
    std::string input = "";
    Node node = Node(input);
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(ConvertTest_595, EncodeSimpleString_595) {
    std::string input = "hello";
    Node node = Node(input);
    EXPECT_EQ(node.as<std::string>(), "hello");
}

TEST_F(ConvertTest_595, EncodeStringWithSpaces_595) {
    std::string input = "hello world";
    Node node = Node(input);
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(ConvertTest_595, EncodeStringWithSpecialCharacters_595) {
    std::string input = "hello\nworld\ttab";
    Node node = Node(input);
    EXPECT_EQ(node.as<std::string>(), "hello\nworld\ttab");
}

TEST_F(ConvertTest_595, DecodeStringFromNode_595) {
    Node node = Node("test_value");
    std::string result;
    EXPECT_TRUE(YAML::convert<std::string>::decode(node, result));
    EXPECT_EQ(result, "test_value");
}

// ==================== Integer Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeInt_595) {
    int value = 42;
    Node node = Node(value);
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(ConvertTest_595, EncodeDecodeNegativeInt_595) {
    int value = -100;
    Node node = Node(value);
    EXPECT_EQ(node.as<int>(), -100);
}

TEST_F(ConvertTest_595, EncodeDecodeZeroInt_595) {
    int value = 0;
    Node node = Node(value);
    EXPECT_EQ(node.as<int>(), 0);
}

TEST_F(ConvertTest_595, EncodeDecodeIntMax_595) {
    int value = std::numeric_limits<int>::max();
    Node node = Node(value);
    EXPECT_EQ(node.as<int>(), std::numeric_limits<int>::max());
}

TEST_F(ConvertTest_595, EncodeDecodeIntMin_595) {
    int value = std::numeric_limits<int>::min();
    Node node = Node(value);
    EXPECT_EQ(node.as<int>(), std::numeric_limits<int>::min());
}

// ==================== Unsigned Integer Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeUnsignedInt_595) {
    unsigned int value = 42u;
    Node node = Node(value);
    EXPECT_EQ(node.as<unsigned int>(), 42u);
}

TEST_F(ConvertTest_595, EncodeDecodeUnsignedIntMax_595) {
    unsigned int value = std::numeric_limits<unsigned int>::max();
    Node node = Node(value);
    EXPECT_EQ(node.as<unsigned int>(), std::numeric_limits<unsigned int>::max());
}

// ==================== Long Long Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeLongLong_595) {
    long long value = 1234567890123LL;
    Node node = Node(value);
    EXPECT_EQ(node.as<long long>(), 1234567890123LL);
}

TEST_F(ConvertTest_595, EncodeDecodeNegativeLongLong_595) {
    long long value = -1234567890123LL;
    Node node = Node(value);
    EXPECT_EQ(node.as<long long>(), -1234567890123LL);
}

// ==================== Double Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeDouble_595) {
    double value = 3.14159;
    Node node = Node(value);
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.14159);
}

TEST_F(ConvertTest_595, EncodeDecodeNegativeDouble_595) {
    double value = -2.71828;
    Node node = Node(value);
    EXPECT_DOUBLE_EQ(node.as<double>(), -2.71828);
}

TEST_F(ConvertTest_595, EncodeDecodeZeroDouble_595) {
    double value = 0.0;
    Node node = Node(value);
    EXPECT_DOUBLE_EQ(node.as<double>(), 0.0);
}

// ==================== Float Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeFloat_595) {
    float value = 1.5f;
    Node node = Node(value);
    EXPECT_FLOAT_EQ(node.as<float>(), 1.5f);
}

// ==================== Boolean Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeBoolTrue_595) {
    bool value = true;
    Node node = Node(value);
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertTest_595, EncodeDecodeBoolFalse_595) {
    bool value = false;
    Node node = Node(value);
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(ConvertTest_595, DecodeTrueString_595) {
    Node node = Node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertTest_595, DecodeFalseString_595) {
    Node node = Node("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(ConvertTest_595, DecodeYesAsBool_595) {
    Node node = Node("yes");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertTest_595, DecodeNoAsBool_595) {
    Node node = Node("no");
    EXPECT_FALSE(node.as<bool>());
}

// ==================== Null Node Tests ====================

TEST_F(ConvertTest_595, NullNodeConversion_595) {
    Node node;
    EXPECT_FALSE(node.IsDefined());
}

// ==================== Char Pointer Encode Tests ====================

TEST_F(ConvertTest_595, EncodeCharPointer_595) {
    const char* value = "c_string_test";
    Node node = Node(value);
    EXPECT_EQ(node.as<std::string>(), "c_string_test");
}

// ==================== Vector Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeVectorOfInts_595) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Node node = Node(vec);
    std::vector<int> result = node.as<std::vector<int>>();
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[4], 5);
}

TEST_F(ConvertTest_595, EncodeDecodeEmptyVector_595) {
    std::vector<int> vec;
    Node node = Node(vec);
    std::vector<int> result = node.as<std::vector<int>>();
    EXPECT_TRUE(result.empty());
}

TEST_F(ConvertTest_595, EncodeDecodeVectorOfStrings_595) {
    std::vector<std::string> vec = {"hello", "world"};
    Node node = Node(vec);
    std::vector<std::string> result = node.as<std::vector<std::string>>();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");
}

// ==================== Map Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodeMapStringToString_595) {
    std::map<std::string, std::string> m;
    m["key1"] = "value1";
    m["key2"] = "value2";
    Node node = Node(m);
    auto result = node.as<std::map<std::string, std::string>>();
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result["key1"], "value1");
    EXPECT_EQ(result["key2"], "value2");
}

TEST_F(ConvertTest_595, EncodeDecodeEmptyMap_595) {
    std::map<std::string, int> m;
    Node node = Node(m);
    auto result = node.as<std::map<std::string, int>>();
    EXPECT_TRUE(result.empty());
}

TEST_F(ConvertTest_595, EncodeDecodeMapStringToInt_595) {
    std::map<std::string, int> m;
    m["a"] = 1;
    m["b"] = 2;
    Node node = Node(m);
    auto result = node.as<std::map<std::string, int>>();
    EXPECT_EQ(result["a"], 1);
    EXPECT_EQ(result["b"], 2);
}

// ==================== Type Mismatch / Error Cases ====================

TEST_F(ConvertTest_595, DecodeInvalidIntThrows_595) {
    Node node = Node("not_an_int");
    EXPECT_THROW(node.as<int>(), YAML::TypedBadConversion<int>);
}

TEST_F(ConvertTest_595, DecodeInvalidDoubleThrows_595) {
    Node node = Node("not_a_double");
    EXPECT_THROW(node.as<double>(), YAML::TypedBadConversion<double>);
}

TEST_F(ConvertTest_595, DecodeInvalidBoolThrows_595) {
    Node node = Node("not_a_bool");
    EXPECT_THROW(node.as<bool>(), YAML::TypedBadConversion<bool>);
}

TEST_F(ConvertTest_595, DecodeUndefinedNodeThrows_595) {
    Node node;
    EXPECT_THROW(node.as<std::string>(), YAML::TypedBadConversion<std::string>);
}

// ==================== Roundtrip Tests ====================

TEST_F(ConvertTest_595, RoundtripStringConversion_595) {
    std::string original = "roundtrip test value";
    Node node = Node(original);
    std::string decoded = node.as<std::string>();
    EXPECT_EQ(original, decoded);
}

TEST_F(ConvertTest_595, RoundtripIntConversion_595) {
    int original = 9999;
    Node node = Node(original);
    int decoded = node.as<int>();
    EXPECT_EQ(original, decoded);
}

TEST_F(ConvertTest_595, RoundtripBoolConversion_595) {
    bool original = true;
    Node node = Node(original);
    bool decoded = node.as<bool>();
    EXPECT_EQ(original, decoded);
}

// ==================== Hex and Octal Parsing Tests ====================

TEST_F(ConvertTest_595, DecodeHexInteger_595) {
    Node node = Node("0x1A");
    EXPECT_EQ(node.as<int>(), 26);
}

TEST_F(ConvertTest_595, DecodeOctalInteger_595) {
    Node node = Node("010");
    EXPECT_EQ(node.as<int>(), 8);
}

// ==================== Special Float Values ====================

TEST_F(ConvertTest_595, DecodeNanString_595) {
    Node node = Node(".nan");
    double val = node.as<double>();
    EXPECT_TRUE(std::isnan(val));
}

TEST_F(ConvertTest_595, DecodePosInfString_595) {
    Node node = Node(".inf");
    double val = node.as<double>();
    EXPECT_TRUE(std::isinf(val));
    EXPECT_GT(val, 0);
}

TEST_F(ConvertTest_595, DecodeNegInfString_595) {
    Node node = Node("-.inf");
    double val = node.as<double>();
    EXPECT_TRUE(std::isinf(val));
    EXPECT_LT(val, 0);
}

// ==================== Pair Conversion Tests ====================

TEST_F(ConvertTest_595, EncodeDecodePair_595) {
    std::pair<std::string, int> p = {"key", 42};
    Node node;
    node.push_back(Node(p.first));
    node.push_back(Node(p.second));
    EXPECT_EQ(node[0].as<std::string>(), "key");
    EXPECT_EQ(node[1].as<int>(), 42);
}

// ==================== Long String Tests ====================

TEST_F(ConvertTest_595, EncodeLongString_595) {
    std::string longStr(10000, 'a');
    Node node = Node(longStr);
    EXPECT_EQ(node.as<std::string>(), longStr);
}

TEST_F(ConvertTest_595, EncodeStringWithNullCharacter_595) {
    std::string input("hello\0world", 11);
    Node node = Node(input);
    std::string result = node.as<std::string>();
    EXPECT_EQ(result.length(), input.length());
}

// ==================== Default Value Tests ====================

TEST_F(ConvertTest_595, AsWithDefaultOnUndefinedNode_595) {
    Node node;
    std::string result = node.as<std::string>("default_value");
    EXPECT_EQ(result, "default_value");
}

TEST_F(ConvertTest_595, AsWithDefaultOnValidNode_595) {
    Node node = Node("actual_value");
    std::string result = node.as<std::string>("default_value");
    EXPECT_EQ(result, "actual_value");
}

TEST_F(ConvertTest_595, AsIntWithDefaultOnInvalidNode_595) {
    Node node = Node("not_a_number");
    int result = node.as<int>(99);
    EXPECT_EQ(result, 99);
}

TEST_F(ConvertTest_595, AsIntWithDefaultOnValidNode_595) {
    Node node = Node(42);
    int result = node.as<int>(99);
    EXPECT_EQ(result, 42);
}
