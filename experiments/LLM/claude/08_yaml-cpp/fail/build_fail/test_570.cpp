#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"

// Test push_back with a scalar value to a sequence node
TEST_F_570(NodePushBackTest_570, PushBackScalarToSequence_570) {
    // Use TEST instead of TEST_F since we don't need a fixture
}

TEST(NodePushBackTest_570, PushBackScalarNodeToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node value("hello");
    seq.push_back(value);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST(NodePushBackTest_570, PushBackMultipleNodesToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node v1("first");
    YAML::Node v2("second");
    YAML::Node v3("third");
    seq.push_back(v1);
    seq.push_back(v2);
    seq.push_back(v3);
    ASSERT_EQ(seq.size(), 3u);
    EXPECT_EQ(seq[0].as<std::string>(), "first");
    EXPECT_EQ(seq[1].as<std::string>(), "second");
    EXPECT_EQ(seq[2].as<std::string>(), "third");
}

TEST(NodePushBackTest_570, PushBackIntegerNodeToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node val(42);
    seq.push_back(val);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<int>(), 42);
}

TEST(NodePushBackTest_570, PushBackToDefaultNode_570) {
    YAML::Node node;
    YAML::Node val("test");
    node.push_back(val);
    EXPECT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "test");
}

TEST(NodePushBackTest_570, PushBackNodeToNullNode_570) {
    YAML::Node node(YAML::NodeType::Null);
    YAML::Node val("value");
    node.push_back(val);
    EXPECT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 1u);
    EXPECT_EQ(node[0].as<std::string>(), "value");
}

TEST(NodePushBackTest_570, PushBackSequenceNodeToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node innerSeq(YAML::NodeType::Sequence);
    innerSeq.push_back(YAML::Node("a"));
    innerSeq.push_back(YAML::Node("b"));
    seq.push_back(innerSeq);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_TRUE(seq[0].IsSequence());
    EXPECT_EQ(seq[0].size(), 2u);
}

TEST(NodePushBackTest_570, PushBackMapNodeToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node map(YAML::NodeType::Map);
    map["key"] = "value";
    seq.push_back(map);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_TRUE(seq[0].IsMap());
    EXPECT_EQ(seq[0]["key"].as<std::string>(), "value");
}

TEST(NodePushBackTest_570, PushBackTemplateVersionWithString_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(std::string("hello"));
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST(NodePushBackTest_570, PushBackTemplateVersionWithInt_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(100);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<int>(), 100);
}

TEST(NodePushBackTest_570, PushBackTemplateVersionWithDouble_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(3.14);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_DOUBLE_EQ(seq[0].as<double>(), 3.14);
}

TEST(NodePushBackTest_570, PushBackTemplateVersionWithBool_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(true);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<bool>(), true);
}

TEST(NodePushBackTest_570, PushBackPreservesExistingElements_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(YAML::Node("first"));
    EXPECT_EQ(seq[0].as<std::string>(), "first");
    seq.push_back(YAML::Node("second"));
    EXPECT_EQ(seq[0].as<std::string>(), "first");
    EXPECT_EQ(seq[1].as<std::string>(), "second");
    ASSERT_EQ(seq.size(), 2u);
}

TEST(NodePushBackTest_570, PushBackNullNodeToSequence_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node nullNode(YAML::NodeType::Null);
    seq.push_back(nullNode);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_TRUE(seq[0].IsNull());
}

TEST(NodePushBackTest_570, PushBackSelfReferenceDoesNotCrash_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(YAML::Node("initial"));
    // Pushing a copy of self - should not crash
    YAML::Node copy = seq;
    seq.push_back(copy);
    EXPECT_GE(seq.size(), 2u);
}

TEST(NodePushBackTest_570, PushBackManyElements_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    const int count = 100;
    for (int i = 0; i < count; ++i) {
        seq.push_back(YAML::Node(i));
    }
    ASSERT_EQ(seq.size(), static_cast<std::size_t>(count));
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(seq[i].as<int>(), i);
    }
}

TEST(NodePushBackTest_570, PushBackCStringTemplate_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back("hello");
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "hello");
}

TEST(NodePushBackTest_570, PushBackConvertsUndefinedNodeToSequence_570) {
    YAML::Node node;
    EXPECT_TRUE(node.IsNull());
    node.push_back(YAML::Node(1));
    EXPECT_TRUE(node.IsSequence());
    ASSERT_EQ(node.size(), 1u);
}

TEST(NodePushBackTest_570, SequenceTypeAfterPushBack_570) {
    YAML::Node node;
    node.push_back(YAML::Node("test"));
    EXPECT_EQ(node.Type(), YAML::NodeType::Sequence);
}

TEST(NodePushBackTest_570, PushBackEmptyStringNode_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(YAML::Node(""));
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "");
}

TEST(NodePushBackTest_570, IterateAfterPushBack_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    seq.push_back(YAML::Node("a"));
    seq.push_back(YAML::Node("b"));
    seq.push_back(YAML::Node("c"));

    std::vector<std::string> values;
    for (auto it = seq.begin(); it != seq.end(); ++it) {
        values.push_back(it->as<std::string>());
    }
    ASSERT_EQ(values.size(), 3u);
    EXPECT_EQ(values[0], "a");
    EXPECT_EQ(values[1], "b");
    EXPECT_EQ(values[2], "c");
}

TEST(NodePushBackTest_570, PushBackUndefinedRhsNode_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node undefined;
    // push_back on an undefined/null rhs should work (EnsureNodeExists creates it)
    seq.push_back(undefined);
    ASSERT_EQ(seq.size(), 1u);
}

TEST(NodePushBackTest_570, PushBackWithTaggedNode_570) {
    YAML::Node seq(YAML::NodeType::Sequence);
    YAML::Node tagged("value");
    tagged.SetTag("!custom");
    seq.push_back(tagged);
    ASSERT_EQ(seq.size(), 1u);
    EXPECT_EQ(seq[0].as<std::string>(), "value");
    EXPECT_EQ(seq[0].Tag(), "!custom");
}
