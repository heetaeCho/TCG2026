#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <map>



using namespace YAML;



TEST(YamlEmitterTest_658, WriteEmptyMap_658) {

    Emitter emitter;

    std::map<std::string, int> m;

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{}");

}



TEST(YamlEmitterTest_658, WriteSimpleMap_658) {

    Emitter emitter;

    std::map<std::string, int> m = {{"key1", 1}, {"key2", 2}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{key1: 1, key2: 2}");

}



TEST(YamlEmitterTest_658, WriteNestedMap_658) {

    Emitter emitter;

    std::map<std::string, std::map<std::string, int>> m = {{"outer", {{"inner", 42}}}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{outer: {inner: 42}}");

}



TEST(YamlEmitterTest_658, WriteMapWithDifferentTypes_658) {

    Emitter emitter;

    std::map<std::string, std::string> m = {{"key1", "value1"}, {"key2", "value2"}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{key1: value1, key2: value2}");

}



TEST(YamlEmitterTest_658, WriteMapWithSpecialCharacters_658) {

    Emitter emitter;

    std::map<std::string, std::string> m = {{"key with spaces", "value with spaces"}, {"special#char", "value"}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{\"key with spaces\": \"value with spaces\", special#char: value}");

}



TEST(YamlEmitterTest_658, WriteMapWithLongKeys_658) {

    Emitter emitter;

    std::map<std::string, int> m = {{"a_really_long_key_that_needs_to_be_wrapped", 1}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{a_really_long_key_that_needs_to_be_wrapped: 1}");

}



TEST(YamlEmitterTest_658, WriteMapWithEmptyValues_658) {

    Emitter emitter;

    std::map<std::string, std::string> m = {{"key1", ""}, {"key2", "value"}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{key1: , key2: value}");

}



TEST(YamlEmitterTest_658, WriteMapWithNullValues_658) {

    Emitter emitter;

    std::map<std::string, _Null> m = {{"key1", _Null()}, {"key2", _Null()}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{key1: null, key2: null}");

}



TEST(YamlEmitterTest_658, WriteMapWithBoolValues_658) {

    Emitter emitter;

    std::map<std::string, bool> m = {{"key1", true}, {"key2", false}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{key1: true, key2: false}");

}



TEST(YamlEmitterTest_658, WriteMapWithNumericKeys_658) {

    Emitter emitter;

    std::map<int, std::string> m = {{1, "value1"}, {2, "value2"}};

    emitter << m;

    EXPECT_EQ(emitter.c_str(), "{1: value1, 2: value2}");

}



TEST(YamlEmitterTest_658, WriteMapWithFormattedValues_658) {

    Emitter emitter;

    std::map<std::string, int> m = {{"key1", 1}, {"key2", 2}};

    emitter << BeginMap;

    emitter << Key << "key1" << Value << DoubleQuoted << m["key1"];

    emitter << Key << "key2" << Value << SingleQuoted << m["key2"];

    emitter << EndMap;

    EXPECT_EQ(emitter.c_str(), "{key1: \"1\", key2: '2'}");

}



TEST(YamlEmitterTest_658, WriteMapWithFormattedKeys_658) {

    Emitter emitter;

    std::map<std::string, int> m = {{"key1", 1}, {"key2", 2}};

    emitter << BeginMap;

    emitter << Key << DoubleQuoted << "key1" << Value << m["key1"];

    emitter << Key << SingleQuoted << "key2" << Value << m["key2"];

    emitter << EndMap;

    EXPECT_EQ(emitter.c_str(), "{\"key1\": 1, 'key2': 2}");

}
