#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/convert.h"
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cmath>

// Test fixture
class ConvertTest_599 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Tests for const char* encoding
// =============================================================================

TEST_F(ConvertTest_599, EncodeConstCharPtr_NormalString_599) {
    YAML::Node node = YAML::Node("hello world");
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello world");
}

TEST_F(ConvertTest_599, EncodeConstCharPtr_EmptyString_599) {
    YAML::Node node = YAML::Node("");
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "");
}

TEST_F(ConvertTest_599, EncodeConstCharPtr_SpecialCharacters_599) {
    YAML::Node node = YAML::Node("hello\nworld\ttab");
    EXPECT_TRUE(node.IsDefined());
    EXPECT_EQ(node.as<std::string>(), "hello\nworld\ttab");
}

// =============================================================================
// Tests for std::string conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertString_Encode_599) {
    std::string value = "test string";
    YAML::Node node;
    node = value;
    EXPECT_EQ(node.as<std::string>(), "test string");
}

TEST_F(ConvertTest_599, ConvertString_Decode_599) {
    YAML::Node node = YAML::Node("decoded string");
    std::string result;
    EXPECT_TRUE(YAML::convert<std::string>::decode(node, result));
    EXPECT_EQ(result, "decoded string");
}

TEST_F(ConvertTest_599, ConvertString_EmptyString_599) {
    YAML::Node node = YAML::Node("");
    std::string result;
    EXPECT_TRUE(YAML::convert<std::string>::decode(node, result));
    EXPECT_EQ(result, "");
}

// =============================================================================
// Tests for bool conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertBool_True_599) {
    YAML::Node node = YAML::Node("true");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertTest_599, ConvertBool_False_599) {
    YAML::Node node = YAML::Node("false");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(ConvertTest_599, ConvertBool_Yes_599) {
    YAML::Node node = YAML::Node("yes");
    EXPECT_TRUE(node.as<bool>());
}

TEST_F(ConvertTest_599, ConvertBool_No_599) {
    YAML::Node node = YAML::Node("no");
    EXPECT_FALSE(node.as<bool>());
}

TEST_F(ConvertTest_599, ConvertBool_EncodeTrue_599) {
    YAML::Node node;
    node = true;
    EXPECT_EQ(node.as<std::string>(), "true");
}

TEST_F(ConvertTest_599, ConvertBool_EncodeFalse_599) {
    YAML::Node node;
    node = false;
    EXPECT_EQ(node.as<std::string>(), "false");
}

// =============================================================================
// Tests for integer conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertInt_PositiveValue_599) {
    YAML::Node node = YAML::Node("42");
    EXPECT_EQ(node.as<int>(), 42);
}

TEST_F(ConvertTest_599, ConvertInt_NegativeValue_599) {
    YAML::Node node = YAML::Node("-42");
    EXPECT_EQ(node.as<int>(), -42);
}

TEST_F(ConvertTest_599, ConvertInt_Zero_599) {
    YAML::Node node = YAML::Node("0");
    EXPECT_EQ(node.as<int>(), 0);
}

TEST_F(ConvertTest_599, ConvertInt_Encode_599) {
    YAML::Node node;
    node = 123;
    EXPECT_EQ(node.as<int>(), 123);
}

TEST_F(ConvertTest_599, ConvertInt_HexValue_599) {
    YAML::Node node = YAML::Node("0x1A");
    EXPECT_EQ(node.as<int>(), 26);
}

TEST_F(ConvertTest_599, ConvertInt_OctalValue_599) {
    YAML::Node node = YAML::Node("010");
    EXPECT_EQ(node.as<int>(), 8);
}

TEST_F(ConvertTest_599, ConvertInt_InvalidString_599) {
    YAML::Node node = YAML::Node("not_a_number");
    int result;
    EXPECT_FALSE(YAML::convert<int>::decode(node, result));
}

// =============================================================================
// Tests for unsigned int conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertUnsignedInt_PositiveValue_599) {
    YAML::Node node = YAML::Node("100");
    EXPECT_EQ(node.as<unsigned int>(), 100u);
}

TEST_F(ConvertTest_599, ConvertUnsignedInt_Zero_599) {
    YAML::Node node = YAML::Node("0");
    EXPECT_EQ(node.as<unsigned int>(), 0u);
}

// =============================================================================
// Tests for long long conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertLongLong_LargeValue_599) {
    YAML::Node node = YAML::Node("9223372036854775807");
    EXPECT_EQ(node.as<long long>(), 9223372036854775807LL);
}

TEST_F(ConvertTest_599, ConvertLongLong_NegativeLargeValue_599) {
    YAML::Node node;
    node = -9223372036854775807LL;
    EXPECT_EQ(node.as<long long>(), -9223372036854775807LL);
}

// =============================================================================
// Tests for float conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertFloat_PositiveValue_599) {
    YAML::Node node = YAML::Node("3.14");
    EXPECT_FLOAT_EQ(node.as<float>(), 3.14f);
}

TEST_F(ConvertTest_599, ConvertFloat_NegativeValue_599) {
    YAML::Node node = YAML::Node("-2.5");
    EXPECT_FLOAT_EQ(node.as<float>(), -2.5f);
}

TEST_F(ConvertTest_599, ConvertFloat_Zero_599) {
    YAML::Node node = YAML::Node("0.0");
    EXPECT_FLOAT_EQ(node.as<float>(), 0.0f);
}

TEST_F(ConvertTest_599, ConvertFloat_Infinity_599) {
    YAML::Node node = YAML::Node(".inf");
    float val = node.as<float>();
    EXPECT_TRUE(std::isinf(val));
    EXPECT_GT(val, 0);
}

TEST_F(ConvertTest_599, ConvertFloat_NegativeInfinity_599) {
    YAML::Node node = YAML::Node("-.inf");
    float val = node.as<float>();
    EXPECT_TRUE(std::isinf(val));
    EXPECT_LT(val, 0);
}

TEST_F(ConvertTest_599, ConvertFloat_NaN_599) {
    YAML::Node node = YAML::Node(".nan");
    float val = node.as<float>();
    EXPECT_TRUE(std::isnan(val));
}

TEST_F(ConvertTest_599, ConvertFloat_InvalidString_599) {
    YAML::Node node = YAML::Node("not_a_float");
    float result;
    EXPECT_FALSE(YAML::convert<float>::decode(node, result));
}

// =============================================================================
// Tests for double conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertDouble_PositiveValue_599) {
    YAML::Node node = YAML::Node("3.141592653589793");
    EXPECT_DOUBLE_EQ(node.as<double>(), 3.141592653589793);
}

TEST_F(ConvertTest_599, ConvertDouble_NegativeValue_599) {
    YAML::Node node = YAML::Node("-1.23456789");
    EXPECT_DOUBLE_EQ(node.as<double>(), -1.23456789);
}

TEST_F(ConvertTest_599, ConvertDouble_Encode_599) {
    YAML::Node node;
    node = 2.718281828;
    EXPECT_NEAR(node.as<double>(), 2.718281828, 1e-9);
}

TEST_F(ConvertTest_599, ConvertDouble_Infinity_599) {
    YAML::Node node = YAML::Node(".inf");
    double val = node.as<double>();
    EXPECT_TRUE(std::isinf(val));
}

TEST_F(ConvertTest_599, ConvertDouble_NaN_599) {
    YAML::Node node = YAML::Node(".nan");
    double val = node.as<double>();
    EXPECT_TRUE(std::isnan(val));
}

// =============================================================================
// Tests for Node-to-Node conversion (identity)
// =============================================================================

TEST_F(ConvertTest_599, ConvertNodeToNode_599) {
    YAML::Node original = YAML::Node("test");
    YAML::Node converted = original.as<YAML::Node>();
    EXPECT_EQ(converted.as<std::string>(), "test");
}

// =============================================================================
// Tests for vector conversion (sequence)
// =============================================================================

TEST_F(ConvertTest_599, ConvertVectorInt_Decode_599) {
    YAML::Node node;
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    std::vector<int> result = node.as<std::vector<int>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST_F(ConvertTest_599, ConvertVectorString_Decode_599) {
    YAML::Node node;
    node.push_back("a");
    node.push_back("b");
    node.push_back("c");
    std::vector<std::string> result = node.as<std::vector<std::string>>();
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
}

TEST_F(ConvertTest_599, ConvertVectorInt_Encode_599) {
    std::vector<int> vec = {10, 20, 30};
    YAML::Node node;
    node = vec;
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
    EXPECT_EQ(node[0].as<int>(), 10);
    EXPECT_EQ(node[1].as<int>(), 20);
    EXPECT_EQ(node[2].as<int>(), 30);
}

TEST_F(ConvertTest_599, ConvertVectorInt_EmptyVector_599) {
    std::vector<int> vec;
    YAML::Node node;
    node = vec;
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(ConvertTest_599, ConvertVectorInt_DecodeFromScalarFails_599) {
    YAML::Node node = YAML::Node("not a sequence");
    std::vector<int> result;
    EXPECT_FALSE(YAML::convert<std::vector<int>>::decode(node, result));
}

// =============================================================================
// Tests for map conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertMapStringInt_Decode_599) {
    YAML::Node node;
    node["one"] = 1;
    node["two"] = 2;
    node["three"] = 3;
    std::map<std::string, int> result = node.as<std::map<std::string, int>>();
    EXPECT_EQ(result.size(), 3u);
    EXPECT_EQ(result["one"], 1);
    EXPECT_EQ(result["two"], 2);
    EXPECT_EQ(result["three"], 3);
}

TEST_F(ConvertTest_599, ConvertMapStringInt_Encode_599) {
    std::map<std::string, int> m;
    m["x"] = 10;
    m["y"] = 20;
    YAML::Node node;
    node = m;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["x"].as<int>(), 10);
    EXPECT_EQ(node["y"].as<int>(), 20);
}

TEST_F(ConvertTest_599, ConvertMapStringInt_EmptyMap_599) {
    std::map<std::string, int> m;
    YAML::Node node;
    node = m;
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node.size(), 0u);
}

TEST_F(ConvertTest_599, ConvertMapStringString_DecodeFromScalarFails_599) {
    YAML::Node node = YAML::Node("not a map");
    std::map<std::string, std::string> result;
    EXPECT_FALSE(YAML::convert<std::map<std::string, std::string>>::decode(node, result));
}

// =============================================================================
// Tests for pair conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertPairStringInt_Decode_599) {
    YAML::Node node;
    node.push_back("hello");
    node.push_back(42);
    auto result = node.as<std::pair<std::string, int>>();
    EXPECT_EQ(result.first, "hello");
    EXPECT_EQ(result.second, 42);
}

TEST_F(ConvertTest_599, ConvertPairStringInt_Encode_599) {
    std::pair<std::string, int> p = {"world", 99};
    YAML::Node node;
    node = p;
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
}

// =============================================================================
// Tests for char type conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertChar_Encode_599) {
    YAML::Node node;
    node = 'A';
    // char is typically encoded as an integer
    EXPECT_TRUE(node.IsDefined());
}

// =============================================================================
// Tests for short type conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertShort_Decode_599) {
    YAML::Node node = YAML::Node("32767");
    EXPECT_EQ(node.as<short>(), 32767);
}

TEST_F(ConvertTest_599, ConvertShort_NegativeValue_599) {
    YAML::Node node = YAML::Node("-32768");
    EXPECT_EQ(node.as<short>(), -32768);
}

// =============================================================================
// Tests for unsigned long long
// =============================================================================

TEST_F(ConvertTest_599, ConvertUnsignedLongLong_MaxValue_599) {
    YAML::Node node = YAML::Node("18446744073709551615");
    EXPECT_EQ(node.as<unsigned long long>(), 18446744073709551615ULL);
}

// =============================================================================
// Tests for null/undefined node decode failures
// =============================================================================

TEST_F(ConvertTest_599, DecodeUndefinedNodeThrows_599) {
    YAML::Node node;
    EXPECT_THROW(node.as<int>(), YAML::Exception);
}

// =============================================================================
// Tests for YAML parsing and conversion round-trip
// =============================================================================

TEST_F(ConvertTest_599, RoundTripInt_599) {
    YAML::Node node;
    node = 42;
    int val = node.as<int>();
    EXPECT_EQ(val, 42);
}

TEST_F(ConvertTest_599, RoundTripDouble_599) {
    YAML::Node node;
    node = 3.14;
    double val = node.as<double>();
    EXPECT_NEAR(val, 3.14, 1e-10);
}

TEST_F(ConvertTest_599, RoundTripString_599) {
    YAML::Node node;
    node = std::string("round trip test");
    std::string val = node.as<std::string>();
    EXPECT_EQ(val, "round trip test");
}

TEST_F(ConvertTest_599, RoundTripBool_599) {
    YAML::Node node;
    node = true;
    bool val = node.as<bool>();
    EXPECT_TRUE(val);
}

// =============================================================================
// Tests for as<> with default value
// =============================================================================

TEST_F(ConvertTest_599, AsWithDefaultValue_ValidNode_599) {
    YAML::Node node = YAML::Node("42");
    int val = node.as<int>(99);
    EXPECT_EQ(val, 42);
}

TEST_F(ConvertTest_599, AsWithDefaultValue_InvalidNode_599) {
    YAML::Node node;
    int val = node.as<int>(99);
    EXPECT_EQ(val, 99);
}

TEST_F(ConvertTest_599, AsWithDefaultValue_WrongType_599) {
    YAML::Node node = YAML::Node("not_an_int");
    int val = node.as<int>(77);
    EXPECT_EQ(val, 77);
}

// =============================================================================
// Tests for list conversion
// =============================================================================

TEST_F(ConvertTest_599, ConvertListInt_Decode_599) {
    YAML::Node node;
    node.push_back(5);
    node.push_back(10);
    node.push_back(15);
    std::list<int> result = node.as<std::list<int>>();
    ASSERT_EQ(result.size(), 3u);
    auto it = result.begin();
    EXPECT_EQ(*it++, 5);
    EXPECT_EQ(*it++, 10);
    EXPECT_EQ(*it++, 15);
}

TEST_F(ConvertTest_599, ConvertListInt_Encode_599) {
    std::list<int> lst = {1, 2, 3};
    YAML::Node node;
    node = lst;
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// =============================================================================
// Boundary: very long string
// =============================================================================

TEST_F(ConvertTest_599, ConvertString_VeryLongString_599) {
    std::string longStr(10000, 'x');
    YAML::Node node;
    node = longStr;
    EXPECT_EQ(node.as<std::string>(), longStr);
}

// =============================================================================
// Boundary: numeric edge cases
// =============================================================================

TEST_F(ConvertTest_599, ConvertInt_MaxIntValue_599) {
    YAML::Node node;
    node = std::numeric_limits<int>::max();
    EXPECT_EQ(node.as<int>(), std::numeric_limits<int>::max());
}

TEST_F(ConvertTest_599, ConvertInt_MinIntValue_599) {
    YAML::Node node;
    node = std::numeric_limits<int>::min();
    EXPECT_EQ(node.as<int>(), std::numeric_limits<int>::min());
}

TEST_F(ConvertTest_599, ConvertDouble_VerySmallValue_599) {
    YAML::Node node;
    node = std::numeric_limits<double>::min();
    double val = node.as<double>();
    EXPECT_NEAR(val, std::numeric_limits<double>::min(), 1e-320);
}

// =============================================================================
// Tests for binary data conversion (if supported)
// =============================================================================

TEST_F(ConvertTest_599, ConvertBinary_RoundTrip_599) {
    YAML::Binary bin(reinterpret_cast<const unsigned char*>("hello"), 5);
    YAML::Node node;
    node = bin;
    YAML::Binary result = node.as<YAML::Binary>();
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(std::string(reinterpret_cast<const char*>(result.data()), result.size()), "hello");
}

TEST_F(ConvertTest_599, ConvertBinary_EmptyData_599) {
    YAML::Binary bin(nullptr, 0);
    YAML::Node node;
    node = bin;
    YAML::Binary result = node.as<YAML::Binary>();
    EXPECT_EQ(result.size(), 0u);
}
