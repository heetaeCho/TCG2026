#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include <utility>
#include <vector>

// Test encoding a pair of simple types (int, int)
TEST(ConvertPairTest_619, EncodeIntIntPair_619) {
    std::pair<int, int> p(42, 99);
    YAML::Node node = YAML::convert<std::pair<int, int>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<int>(), 42);
    EXPECT_EQ(node[1].as<int>(), 99);
}

// Test encoding a pair of string and int
TEST(ConvertPairTest_619, EncodeStringIntPair_619) {
    std::pair<std::string, int> p("hello", 123);
    YAML::Node node = YAML::convert<std::pair<std::string, int>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "hello");
    EXPECT_EQ(node[1].as<int>(), 123);
}

// Test encoding a pair of int and string
TEST(ConvertPairTest_619, EncodeIntStringPair_619) {
    std::pair<int, std::string> p(7, "world");
    YAML::Node node = YAML::convert<std::pair<int, std::string>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<int>(), 7);
    EXPECT_EQ(node[1].as<std::string>(), "world");
}

// Test encoding a pair of string and string
TEST(ConvertPairTest_619, EncodeStringStringPair_619) {
    std::pair<std::string, std::string> p("key", "value");
    YAML::Node node = YAML::convert<std::pair<std::string, std::string>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "key");
    EXPECT_EQ(node[1].as<std::string>(), "value");
}

// Test encoding a pair of double and double
TEST(ConvertPairTest_619, EncodeDoubleDoublePair_619) {
    std::pair<double, double> p(3.14, 2.71);
    YAML::Node node = YAML::convert<std::pair<double, double>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_DOUBLE_EQ(node[0].as<double>(), 3.14);
    EXPECT_DOUBLE_EQ(node[1].as<double>(), 2.71);
}

// Test encoding a pair with empty strings
TEST(ConvertPairTest_619, EncodeEmptyStringPair_619) {
    std::pair<std::string, std::string> p("", "");
    YAML::Node node = YAML::convert<std::pair<std::string, std::string>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), "");
    EXPECT_EQ(node[1].as<std::string>(), "");
}

// Test encoding a pair with bool values
TEST(ConvertPairTest_619, EncodeBoolBoolPair_619) {
    std::pair<bool, bool> p(true, false);
    YAML::Node node = YAML::convert<std::pair<bool, bool>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<bool>(), true);
    EXPECT_EQ(node[1].as<bool>(), false);
}

// Test encoding a pair with negative integers
TEST(ConvertPairTest_619, EncodeNegativeIntPair_619) {
    std::pair<int, int> p(-100, -200);
    YAML::Node node = YAML::convert<std::pair<int, int>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<int>(), -100);
    EXPECT_EQ(node[1].as<int>(), -200);
}

// Test encoding a pair with zero values
TEST(ConvertPairTest_619, EncodeZeroZeroPair_619) {
    std::pair<int, int> p(0, 0);
    YAML::Node node = YAML::convert<std::pair<int, int>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<int>(), 0);
    EXPECT_EQ(node[1].as<int>(), 0);
}

// Test that the encoded node type is Sequence
TEST(ConvertPairTest_619, EncodedNodeIsSequenceType_619) {
    std::pair<int, std::string> p(1, "test");
    YAML::Node node = YAML::convert<std::pair<int, std::string>>::encode(p);
    
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
    EXPECT_FALSE(node.IsMap());
    EXPECT_FALSE(node.IsScalar());
    EXPECT_FALSE(node.IsNull());
}

// Test encoding a pair with large values
TEST(ConvertPairTest_619, EncodeLargeValuePair_619) {
    std::pair<long long, long long> p(9999999999LL, -9999999999LL);
    YAML::Node node = YAML::convert<std::pair<long long, long long>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<long long>(), 9999999999LL);
    EXPECT_EQ(node[1].as<long long>(), -9999999999LL);
}

// Test encoding a pair with float values
TEST(ConvertPairTest_619, EncodeFloatPair_619) {
    std::pair<float, float> p(1.5f, 2.5f);
    YAML::Node node = YAML::convert<std::pair<float, float>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_FLOAT_EQ(node[0].as<float>(), 1.5f);
    EXPECT_FLOAT_EQ(node[1].as<float>(), 2.5f);
}

// Test encoding a pair where first and second are the same
TEST(ConvertPairTest_619, EncodeSameValuePair_619) {
    std::pair<int, int> p(5, 5);
    YAML::Node node = YAML::convert<std::pair<int, int>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<int>(), 5);
    EXPECT_EQ(node[1].as<int>(), 5);
}

// Test that decode roundtrips properly for a pair
TEST(ConvertPairTest_619, DecodeRoundTrip_619) {
    std::pair<int, std::string> original(42, "test");
    YAML::Node node = YAML::convert<std::pair<int, std::string>>::encode(original);
    
    std::pair<int, std::string> decoded;
    bool result = YAML::convert<std::pair<int, std::string>>::decode(node, decoded);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(decoded.first, 42);
    EXPECT_EQ(decoded.second, "test");
}

// Test that decode fails for wrong-sized sequence
TEST(ConvertPairTest_619, DecodeFailsForWrongSize_619) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    node.push_back(2);
    node.push_back(3);
    
    std::pair<int, int> decoded;
    bool result = YAML::convert<std::pair<int, int>>::decode(node, decoded);
    
    EXPECT_FALSE(result);
}

// Test that decode fails for non-sequence node
TEST(ConvertPairTest_619, DecodeFailsForScalarNode_619) {
    YAML::Node node("just a string");
    
    std::pair<int, int> decoded;
    bool result = YAML::convert<std::pair<int, int>>::decode(node, decoded);
    
    EXPECT_FALSE(result);
}

// Test that decode fails for single-element sequence
TEST(ConvertPairTest_619, DecodeFailsForSingleElementSequence_619) {
    YAML::Node node(YAML::NodeType::Sequence);
    node.push_back(1);
    
    std::pair<int, int> decoded;
    bool result = YAML::convert<std::pair<int, int>>::decode(node, decoded);
    
    EXPECT_FALSE(result);
}

// Test that decode fails for empty sequence
TEST(ConvertPairTest_619, DecodeFailsForEmptySequence_619) {
    YAML::Node node(YAML::NodeType::Sequence);
    
    std::pair<int, int> decoded;
    bool result = YAML::convert<std::pair<int, int>>::decode(node, decoded);
    
    EXPECT_FALSE(result);
}

// Test encoding a pair with a long string
TEST(ConvertPairTest_619, EncodeLongStringPair_619) {
    std::string longStr(1000, 'x');
    std::pair<std::string, std::string> p(longStr, "short");
    YAML::Node node = YAML::convert<std::pair<std::string, std::string>>::encode(p);
    
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 2u);
    EXPECT_EQ(node[0].as<std::string>(), longStr);
    EXPECT_EQ(node[1].as<std::string>(), "short");
}

// Test encoding and then iterating over the sequence
TEST(ConvertPairTest_619, EncodeAndIterate_619) {
    std::pair<int, int> p(10, 20);
    YAML::Node node = YAML::convert<std::pair<int, int>>::encode(p);
    
    std::vector<int> values;
    for (auto it = node.begin(); it != node.end(); ++it) {
        values.push_back(it->as<int>());
    }
    
    ASSERT_EQ(values.size(), 2u);
    EXPECT_EQ(values[0], 10);
    EXPECT_EQ(values[1], 20);
}

// Test decode roundtrip for string-string pair
TEST(ConvertPairTest_619, DecodeRoundTripStringString_619) {
    std::pair<std::string, std::string> original("foo", "bar");
    YAML::Node node = YAML::convert<std::pair<std::string, std::string>>::encode(original);
    
    std::pair<std::string, std::string> decoded;
    bool result = YAML::convert<std::pair<std::string, std::string>>::decode(node, decoded);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(decoded.first, "foo");
    EXPECT_EQ(decoded.second, "bar");
}
