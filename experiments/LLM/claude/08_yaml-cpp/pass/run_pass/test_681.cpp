#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include "nodeevents.h"
#include "yaml-cpp/eventhandler.h"

using namespace YAML;
using ::testing::_;
using ::testing::AtLeast;

// Mock EventHandler for testing Emit
class MockEventHandler : public EventHandler {
public:
    MOCK_METHOD(void, OnDocumentStart, (const Mark& mark), (override));
    MOCK_METHOD(void, OnDocumentEnd, (), (override));
    MOCK_METHOD(void, OnNull, (const Mark& mark, anchor_t anchor), (override));
    MOCK_METHOD(void, OnAlias, (const Mark& mark, anchor_t anchor), (override));
    MOCK_METHOD(void, OnScalar, (const Mark& mark, const std::string& tag, anchor_t anchor, const std::string& value), (override));
    MOCK_METHOD(void, OnSequenceStart, (const Mark& mark, const std::string& tag, anchor_t anchor, EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnSequenceEnd, (), (override));
    MOCK_METHOD(void, OnMapStart, (const Mark& mark, const std::string& tag, anchor_t anchor, EmitterStyle::value style), (override));
    MOCK_METHOD(void, OnMapEnd, (), (override));
};

class NodeEventsTest_681 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with default (null) node
TEST_F(NodeEventsTest_681, ConstructWithNullNode_681) {
    Node node;
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test construction with scalar node
TEST_F(NodeEventsTest_681, ConstructWithScalarNode_681) {
    Node node("hello");
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test construction with integer scalar node
TEST_F(NodeEventsTest_681, ConstructWithIntegerScalarNode_681) {
    Node node(42);
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test construction with sequence node
TEST_F(NodeEventsTest_681, ConstructWithSequenceNode_681) {
    Node node;
    node.push_back("item1");
    node.push_back("item2");
    node.push_back("item3");
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test construction with map node
TEST_F(NodeEventsTest_681, ConstructWithMapNode_681) {
    Node node;
    node["key1"] = "value1";
    node["key2"] = "value2";
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test Emit with null node calls appropriate handler methods
TEST_F(NodeEventsTest_681, EmitNullNodeCallsOnNull_681) {
    Node node;
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnNull(_, _)).Times(1);

    events.Emit(handler);
}

// Test Emit with scalar node calls OnScalar
TEST_F(NodeEventsTest_681, EmitScalarNodeCallsOnScalar_681) {
    Node node("hello");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);

    events.Emit(handler);
}

// Test Emit with sequence node calls OnSequenceStart and OnSequenceEnd
TEST_F(NodeEventsTest_681, EmitSequenceNodeCallsSequenceEvents_681) {
    Node node;
    node.push_back("item1");
    node.push_back("item2");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2);

    events.Emit(handler);
}

// Test Emit with map node calls OnMapStart and OnMapEnd
TEST_F(NodeEventsTest_681, EmitMapNodeCallsMapEvents_681) {
    Node node;
    node["key"] = "value";
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(2); // key and value

    events.Emit(handler);
}

// Test Emit with empty sequence
TEST_F(NodeEventsTest_681, EmitEmptySequence_681) {
    Node node(NodeType::Sequence);
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);

    events.Emit(handler);
}

// Test Emit with empty map
TEST_F(NodeEventsTest_681, EmitEmptyMap_681) {
    Node node(NodeType::Map);
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);

    events.Emit(handler);
}

// Test Emit with nested structure (map containing sequence)
TEST_F(NodeEventsTest_681, EmitNestedMapWithSequence_681) {
    Node node;
    node["list"].push_back("a");
    node["list"].push_back("b");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(3); // "list", "a", "b"

    events.Emit(handler);
}

// Test Emit with aliased (shared) nodes triggers OnAlias
TEST_F(NodeEventsTest_681, EmitAliasedNodesCallsOnAlias_681) {
    Node shared_node("shared");
    Node seq;
    seq.push_back(shared_node);
    seq.push_back(shared_node); // same node added twice -> alias

    NodeEvents events(seq);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "shared")).Times(1);
    EXPECT_CALL(handler, OnAlias(_, _)).Times(1);

    events.Emit(handler);
}

// Test that NodeEvents is not copyable
TEST_F(NodeEventsTest_681, NodeEventsIsNotCopyable_681) {
    EXPECT_FALSE(std::is_copy_constructible<NodeEvents>::value);
    EXPECT_FALSE(std::is_copy_assignable<NodeEvents>::value);
}

// Test that NodeEvents is not movable
TEST_F(NodeEventsTest_681, NodeEventsIsNotMovable_681) {
    EXPECT_FALSE(std::is_move_constructible<NodeEvents>::value);
    EXPECT_FALSE(std::is_move_assignable<NodeEvents>::value);
}

// Test Emit with empty string scalar
TEST_F(NodeEventsTest_681, EmitEmptyStringScalar_681) {
    Node node("");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "")).Times(1);

    events.Emit(handler);
}

// Test Emit with tagged node
TEST_F(NodeEventsTest_681, EmitTaggedScalarNode_681) {
    Node node("value");
    node.SetTag("!custom");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, "!custom", _, "value")).Times(1);

    events.Emit(handler);
}

// Test Emit can be called multiple times
TEST_F(NodeEventsTest_681, EmitCalledMultipleTimes_681) {
    Node node("test");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(2);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(2);
    EXPECT_CALL(handler, OnScalar(_, _, _, "test")).Times(2);

    events.Emit(handler);
    events.Emit(handler);
}

// Test construction and emit with deeply nested structure
TEST_F(NodeEventsTest_681, EmitDeeplyNestedStructure_681) {
    Node node;
    node["level1"]["level2"]["level3"] = "deep";
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(3);
    EXPECT_CALL(handler, OnMapEnd()).Times(3);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4); // "level1", "level2", "level3", "deep"

    events.Emit(handler);
}

// Test Emit with a large sequence
TEST_F(NodeEventsTest_681, EmitLargeSequence_681) {
    Node node;
    const int count = 100;
    for (int i = 0; i < count; i++) {
        node.push_back(std::to_string(i));
    }
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(count);

    events.Emit(handler);
}

// Test construction with a node loaded from YAML string
TEST_F(NodeEventsTest_681, ConstructFromParsedYAML_681) {
    Node node = Load("foo: bar\nbaz: [1, 2, 3]");
    EXPECT_NO_THROW(NodeEvents events(node));
}

// Test Emit with a node loaded from YAML string
TEST_F(NodeEventsTest_681, EmitFromParsedYAML_681) {
    Node node = Load("foo: bar");
    NodeEvents events(node);
    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "foo")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "bar")).Times(1);

    events.Emit(handler);
}

// Test with undefined node
TEST_F(NodeEventsTest_681, ConstructWithUndefinedNode_681) {
    Node node;
    Node undefined = node["nonexistent"];
    // Accessing a non-existent key on a null node
    // This may or may not throw; we test it doesn't crash
    EXPECT_NO_THROW(NodeEvents events(undefined));
}
