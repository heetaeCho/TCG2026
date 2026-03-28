#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test that decode copies the source node to the destination node for a scalar
TEST(YAMLNodeConvertDecode_594, DecodeScalarNode_594) {
    YAML::Node source("hello");
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsDefined());
    EXPECT_EQ(dest.as<std::string>(), "hello");
}

// Test that decode returns true
TEST(YAMLNodeConvertDecode_594, DecodeReturnsTrue_594) {
    YAML::Node source(42);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
}

// Test that decode with a null/undefined node
TEST(YAMLNodeConvertDecode_594, DecodeNullNode_594) {
    YAML::Node source(YAML::NodeType::Null);
    YAML::Node dest("previously set value");
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsNull());
}

// Test that decode with a sequence node
TEST(YAMLNodeConvertDecode_594, DecodeSequenceNode_594) {
    YAML::Node source;
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    
    YAML::Node dest;
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsSequence());
    EXPECT_EQ(dest.size(), 3u);
    EXPECT_EQ(dest[0].as<int>(), 1);
    EXPECT_EQ(dest[1].as<int>(), 2);
    EXPECT_EQ(dest[2].as<int>(), 3);
}

// Test that decode with a map node
TEST(YAMLNodeConvertDecode_594, DecodeMapNode_594) {
    YAML::Node source;
    source["key1"] = "value1";
    source["key2"] = "value2";
    
    YAML::Node dest;
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsMap());
    EXPECT_EQ(dest["key1"].as<std::string>(), "value1");
    EXPECT_EQ(dest["key2"].as<std::string>(), "value2");
}

// Test that after decode, dest references same underlying node (reset semantics)
TEST(YAMLNodeConvertDecode_594, DecodeCreatesReference_594) {
    YAML::Node source("original");
    YAML::Node dest;
    
    YAML::convert<YAML::Node>::decode(source, dest);
    
    // After reset, dest should reference the same node as source
    EXPECT_TRUE(dest.is(source));
}

// Test decode with an empty default-constructed node
TEST(YAMLNodeConvertDecode_594, DecodeDefaultConstructedNode_594) {
    YAML::Node source;
    YAML::Node dest("some value");
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    // After decode, dest should reflect source's state
    EXPECT_TRUE(dest.is(source));
}

// Test decode with integer scalar
TEST(YAMLNodeConvertDecode_594, DecodeIntegerScalar_594) {
    YAML::Node source(12345);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsScalar());
    EXPECT_EQ(dest.as<int>(), 12345);
}

// Test decode with double scalar
TEST(YAMLNodeConvertDecode_594, DecodeDoubleScalar_594) {
    YAML::Node source(3.14);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsScalar());
    EXPECT_NEAR(dest.as<double>(), 3.14, 0.001);
}

// Test decode with boolean scalar
TEST(YAMLNodeConvertDecode_594, DecodeBoolScalar_594) {
    YAML::Node source(true);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsScalar());
    EXPECT_TRUE(dest.as<bool>());
}

// Test decode with nested map
TEST(YAMLNodeConvertDecode_594, DecodeNestedMapNode_594) {
    YAML::Node source;
    source["outer"]["inner"] = "value";
    
    YAML::Node dest;
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsMap());
    EXPECT_EQ(dest["outer"]["inner"].as<std::string>(), "value");
}

// Test decode overwrites previous dest content
TEST(YAMLNodeConvertDecode_594, DecodeOverwritesPreviousContent_594) {
    YAML::Node source("new value");
    YAML::Node dest("old value");
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(dest.as<std::string>(), "new value");
}

// Test that decode with a node that has a tag preserves the tag
TEST(YAMLNodeConvertDecode_594, DecodePreservesTag_594) {
    YAML::Node source("tagged value");
    source.SetTag("!custom");
    
    YAML::Node dest;
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(dest.Tag(), "!custom");
}

// Test that as<Node>() works (which uses the decode function)
TEST(YAMLNodeConvertDecode_594, AsNodeUsesConvert_594) {
    YAML::Node source("test value");
    
    YAML::Node dest = source.as<YAML::Node>();
    
    EXPECT_TRUE(dest.IsDefined());
    EXPECT_EQ(dest.as<std::string>(), "test value");
}

// Test decode with empty sequence
TEST(YAMLNodeConvertDecode_594, DecodeEmptySequence_594) {
    YAML::Node source(YAML::NodeType::Sequence);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsSequence());
    EXPECT_EQ(dest.size(), 0u);
}

// Test decode with empty map
TEST(YAMLNodeConvertDecode_594, DecodeEmptyMap_594) {
    YAML::Node source(YAML::NodeType::Map);
    YAML::Node dest;
    
    bool result = YAML::convert<YAML::Node>::decode(source, dest);
    
    EXPECT_TRUE(result);
    EXPECT_TRUE(dest.IsMap());
    EXPECT_EQ(dest.size(), 0u);
}

// Test that modifications to source after decode affect dest (shared reference)
TEST(YAMLNodeConvertDecode_594, DecodeSharedMutation_594) {
    YAML::Node source;
    source["key"] = "original";
    
    YAML::Node dest;
    YAML::convert<YAML::Node>::decode(source, dest);
    
    // Since reset makes them point to the same node, modifying source should affect dest
    source["key"] = "modified";
    EXPECT_EQ(dest["key"].as<std::string>(), "modified");
}

// Test self-decode (source and dest are the same node)
TEST(YAMLNodeConvertDecode_594, DecodeSelfReference_594) {
    YAML::Node node("self");
    
    bool result = YAML::convert<YAML::Node>::decode(node, node);
    
    EXPECT_TRUE(result);
    EXPECT_EQ(node.as<std::string>(), "self");
}
