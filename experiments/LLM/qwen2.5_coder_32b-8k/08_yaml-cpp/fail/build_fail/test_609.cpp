#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "yaml-cpp/node/convert.h"



using namespace YAML;



class EncodeUnorderedMapTest_609 : public ::testing::Test {

protected:

    Node encodeMap(const std::unordered_map<std::string, int>& map) {

        return encode(map);

    }

};



TEST_F(EncodeUnorderedMapTest_609, EmptyMap_609) {

    auto encodedNode = encodeMap({});

    EXPECT_EQ(encodedNode.Type(), NodeType::Map);

    EXPECT_EQ(encodedNode.size(), 0);

}



TEST_F(EncodeUnorderedMapTest_609, SingleElementMap_609) {

    std::unordered_map<std::string, int> map = {{"key1", 42}};

    auto encodedNode = encodeMap(map);

    EXPECT_EQ(encodedNode.Type(), NodeType::Map);

    EXPECT_EQ(encodedNode.size(), 1);

    EXPECT_EQ(encodedNode["key1"].as<int>(), 42);

}



TEST_F(EncodeUnorderedMapTest_609, MultipleElementsMap_609) {

    std::unordered_map<std::string, int> map = {{"key1", 42}, {"key2", 84}};

    auto encodedNode = encodeMap(map);

    EXPECT_EQ(encodedNode.Type(), NodeType::Map);

    EXPECT_EQ(encodedNode.size(), 2);

    EXPECT_EQ(encodedNode["key1"].as<int>(), 42);

    EXPECT_EQ(encodedNode["key2"].as<int>(), 84);

}



TEST_F(EncodeUnorderedMapTest_609, LargeMap_609) {

    std::unordered_map<std::string, int> map;

    for (int i = 0; i < 100; ++i) {

        map["key" + std::to_string(i)] = i * 2;

    }

    auto encodedNode = encodeMap(map);

    EXPECT_EQ(encodedNode.Type(), NodeType::Map);

    EXPECT_EQ(encodedNode.size(), 100);

    for (int i = 0; i < 100; ++i) {

        EXPECT_EQ(encodedNode["key" + std::to_string(i)].as<int>(), i * 2);

    }

}



TEST_F(EncodeUnorderedMapTest_609, MixedTypesValuesMap_609) {

    std::unordered_map<std::string, Node> map = {{"key1", Node(42)}, {"key2", Node("value")}};

    auto encodedNode = encode(map);

    EXPECT_EQ(encodedNode.Type(), NodeType::Map);

    EXPECT_EQ(encodedNode.size(), 2);

    EXPECT_EQ(encodedNode["key1"].as<int>(), 42);

    EXPECT_EQ(encodedNode["key2"].as<std::string>(), "value");

}
