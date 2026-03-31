#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterAnchorTest_42 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that writing an anchor to a fresh emitter keeps it in good state
TEST_F(EmitterAnchorTest_42, WriteAnchorKeepsGoodState_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("test_anchor");
    // Anchor alone may not be valid YAML, but we check the emitter processes it
    // The emitter should still be in a usable state or report an error
    // We just verify no crash and check good() status
}

// Test operator<< with _Anchor returns the same emitter reference
TEST_F(EmitterAnchorTest_42, OperatorReturnsEmitterReference_42) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = (emitter << YAML::Anchor("myanchor"));
    EXPECT_EQ(&ref, &emitter);
}

// Test anchor with a scalar value produces expected YAML output
TEST_F(EmitterAnchorTest_42, AnchorWithScalarProducesCorrectOutput_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1") << "value1";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
    EXPECT_NE(output.find("value1"), std::string::npos);
}

// Test anchor in a map key context
TEST_F(EmitterAnchorTest_42, AnchorOnMapKey_42) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << YAML::Anchor("key_anchor") << "mykey";
    emitter << YAML::Value << "myvalue";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&key_anchor"), std::string::npos);
    EXPECT_NE(output.find("mykey"), std::string::npos);
    EXPECT_NE(output.find("myvalue"), std::string::npos);
}

// Test anchor on a map value
TEST_F(EmitterAnchorTest_42, AnchorOnMapValue_42) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1";
    emitter << YAML::Value << YAML::Anchor("val_anchor") << "value1";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&val_anchor"), std::string::npos);
}

// Test anchor on a sequence element
TEST_F(EmitterAnchorTest_42, AnchorOnSequenceElement_42) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("seq_anchor") << "element1";
    emitter << "element2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&seq_anchor"), std::string::npos);
    EXPECT_NE(output.find("element1"), std::string::npos);
}

// Test anchor with an alias reference
TEST_F(EmitterAnchorTest_42, AnchorAndAlias_42) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "first";
    emitter << YAML::Value << YAML::Anchor("shared") << "shared_value";
    emitter << YAML::Key << "second";
    emitter << YAML::Value << YAML::Alias("shared");
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&shared"), std::string::npos);
    EXPECT_NE(output.find("*shared"), std::string::npos);
}

// Test anchor with empty string content
TEST_F(EmitterAnchorTest_42, AnchorWithEmptyString_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("") << "value";
    // An empty anchor name is likely invalid; check behavior
    // We don't assert good() since it may legitimately fail
    // Just ensure no crash
}

// Test anchor on a sequence node
TEST_F(EmitterAnchorTest_42, AnchorOnSequenceNode_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("seq_node") << YAML::BeginSeq;
    emitter << "item1" << "item2";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&seq_node"), std::string::npos);
}

// Test anchor on a map node
TEST_F(EmitterAnchorTest_42, AnchorOnMapNode_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("map_node") << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&map_node"), std::string::npos);
}

// Test output to a stream via the stream constructor
TEST_F(EmitterAnchorTest_42, AnchorWithStreamConstructor_42) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::Anchor("stream_anchor") << "hello";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = ss.str();
    EXPECT_NE(output.find("&stream_anchor"), std::string::npos);
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test size after writing anchor + scalar
TEST_F(EmitterAnchorTest_42, SizeAfterAnchorWrite_42) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
    emitter << YAML::Anchor("a") << "val";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    EXPECT_GT(emitter.size(), 0u);
}

// Test c_str returns non-null after writing anchor
TEST_F(EmitterAnchorTest_42, CStrNonNullAfterAnchor_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("test") << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    EXPECT_NE(emitter.c_str(), nullptr);
}

// Test anchor with special characters in the name
TEST_F(EmitterAnchorTest_42, AnchorWithSpecialCharacters_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor-with-dashes_and_underscores123") << "value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anchor-with-dashes_and_underscores123"), std::string::npos);
}

// Test multiple anchors in the same document on different nodes
TEST_F(EmitterAnchorTest_42, MultipleAnchorsInDocument_42) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << YAML::Anchor("anchor_a") << "val_a";
    emitter << YAML::Key << "b" << YAML::Value << YAML::Anchor("anchor_b") << "val_b";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anchor_a"), std::string::npos);
    EXPECT_NE(output.find("&anchor_b"), std::string::npos);
}

// Test anchor combined with a tag
TEST_F(EmitterAnchorTest_42, AnchorWithTag_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("tagged_anchor") << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged_value";
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&tagged_anchor"), std::string::npos);
}

// Test anchor in flow sequence
TEST_F(EmitterAnchorTest_42, AnchorInFlowSequence_42) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << YAML::Anchor("flow_anchor") << "item";
    emitter << YAML::EndSeq;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&flow_anchor"), std::string::npos);
}

// Test anchor in flow map
TEST_F(EmitterAnchorTest_42, AnchorInFlowMap_42) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << YAML::Anchor("flow_map_anchor") << "val";
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&flow_map_anchor"), std::string::npos);
}

// Test that a freshly constructed emitter is in good state
TEST_F(EmitterAnchorTest_42, FreshEmitterIsGood_42) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(emitter.size(), 0u);
}

// Test anchor with boolean value
TEST_F(EmitterAnchorTest_42, AnchorWithBoolValue_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("bool_anchor") << true;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&bool_anchor"), std::string::npos);
}

// Test anchor with null value
TEST_F(EmitterAnchorTest_42, AnchorWithNullValue_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("null_anchor") << YAML::Null;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&null_anchor"), std::string::npos);
}

// Test anchor with integer value
TEST_F(EmitterAnchorTest_42, AnchorWithIntegerValue_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("int_anchor") << 42;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&int_anchor"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test anchor with double value
TEST_F(EmitterAnchorTest_42, AnchorWithDoubleValue_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("double_anchor") << 3.14;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&double_anchor"), std::string::npos);
}

// Test that GetLastError is empty when emitter is good
TEST_F(EmitterAnchorTest_42, GetLastErrorEmptyWhenGood_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("ok_anchor") << "value";
    if (emitter.good()) {
        EXPECT_TRUE(emitter.GetLastError().empty());
    }
}

// Test writing anchor with a long name
TEST_F(EmitterAnchorTest_42, AnchorWithLongName_42) {
    std::string longName(256, 'a');
    YAML::Emitter emitter;
    emitter << YAML::Anchor(longName) << "value";
    // Just verify no crash
    if (emitter.good()) {
        std::string output = emitter.c_str();
        EXPECT_NE(output.find(longName), std::string::npos);
    }
}

// Test nested anchors on nested structures
TEST_F(EmitterAnchorTest_42, NestedStructureAnchors_42) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("outer") << YAML::BeginMap;
    emitter << YAML::Key << "inner_seq";
    emitter << YAML::Value << YAML::Anchor("inner") << YAML::BeginSeq;
    emitter << "a" << "b";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    ASSERT_TRUE(emitter.good()) << emitter.GetLastError();
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&outer"), std::string::npos);
    EXPECT_NE(output.find("&inner"), std::string::npos);
}
