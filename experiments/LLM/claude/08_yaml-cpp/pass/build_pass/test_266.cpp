#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/eventhandler.h"
#include "nodeevents.h"

using namespace YAML;
using ::testing::_;
using ::testing::InSequence;
using ::testing::AtLeast;

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
    MOCK_METHOD(void, OnAnchor, (const Mark& mark, const std::string& anchor_name), (override));
};

class NodeEventsTest_266 : public ::testing::Test {
protected:
    MockEventHandler handler;
};

// Test that emitting an empty/undefined node calls OnDocumentStart and OnDocumentEnd
TEST_F(NodeEventsTest_266, EmitUndefinedNode_266) {
    Node node;
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that emitting a null node calls OnDocumentStart, OnNull, and OnDocumentEnd
TEST_F(NodeEventsTest_266, EmitNullNode_266) {
    Node node = YAML::Load("~");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnNull(_, _)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that emitting a scalar node calls OnScalar with the correct value
TEST_F(NodeEventsTest_266, EmitScalarNode_266) {
    Node node = YAML::Load("hello");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that emitting a sequence node calls OnSequenceStart, elements, and OnSequenceEnd
TEST_F(NodeEventsTest_266, EmitSequenceNode_266) {
    Node node = YAML::Load("[1, 2, 3]");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "1")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "2")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "3")).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that emitting a map node calls OnMapStart, key-value pairs, and OnMapEnd
TEST_F(NodeEventsTest_266, EmitMapNode_266) {
    Node node = YAML::Load("{key: value}");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "key")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "value")).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting an empty sequence
TEST_F(NodeEventsTest_266, EmitEmptySequence_266) {
    Node node = YAML::Load("[]");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting an empty map
TEST_F(NodeEventsTest_266, EmitEmptyMap_266) {
    Node node = YAML::Load("{}");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting nested structures
TEST_F(NodeEventsTest_266, EmitNestedMapInSequence_266) {
    Node node = YAML::Load("[{a: b}]");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "a")).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "b")).Times(1);
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting a scalar with integer value
TEST_F(NodeEventsTest_266, EmitIntegerScalar_266) {
    Node node = YAML::Load("42");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "42")).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting a scalar with empty string
TEST_F(NodeEventsTest_266, EmitEmptyStringScalar_266) {
    Node node = YAML::Load("\"\"");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "")).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting a boolean value
TEST_F(NodeEventsTest_266, EmitBooleanScalar_266) {
    Node node = YAML::Load("true");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "true")).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that Emit can be called multiple times on the same NodeEvents
TEST_F(NodeEventsTest_266, EmitCalledMultipleTimes_266) {
    Node node = YAML::Load("hello");
    NodeEvents events(node);

    // First call
    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }
    events.Emit(handler);

    // Second call with a fresh mock
    MockEventHandler handler2;
    {
        InSequence seq;
        EXPECT_CALL(handler2, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler2, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler2, OnDocumentEnd()).Times(1);
    }
    events.Emit(handler2);
}

// Test emitting a map with multiple entries
TEST_F(NodeEventsTest_266, EmitMapMultipleEntries_266) {
    Node node = YAML::Load("{a: 1, b: 2}");
    NodeEvents events(node);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4); // a, 1, b, 2
    EXPECT_CALL(handler, OnMapEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting nested sequences
TEST_F(NodeEventsTest_266, EmitNestedSequences_266) {
    Node node = YAML::Load("[[1, 2], [3, 4]]");
    NodeEvents events(node);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(3); // outer + 2 inner
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(3);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test aliased nodes (anchors and aliases)
TEST_F(NodeEventsTest_266, EmitAliasedNodes_266) {
    Node node = YAML::Load("[&anchor hello, *anchor]");
    NodeEvents events(node);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    // The aliased scalar should appear, and an alias reference
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(AtLeast(1));
    EXPECT_CALL(handler, OnAlias(_, _)).Times(AtLeast(1));
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test that NodeEvents is not copyable or movable (compile-time check embedded in usage)
TEST_F(NodeEventsTest_266, NodeEventsNotCopyable_266) {
    EXPECT_FALSE(std::is_copy_constructible<NodeEvents>::value);
    EXPECT_FALSE(std::is_copy_assignable<NodeEvents>::value);
    EXPECT_FALSE(std::is_move_constructible<NodeEvents>::value);
    EXPECT_FALSE(std::is_move_assignable<NodeEvents>::value);
}

// Test emitting a tagged scalar
TEST_F(NodeEventsTest_266, EmitTaggedScalar_266) {
    Node node = YAML::Load("!!str hello");
    NodeEvents events(node);

    InSequence seq;
    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}

// Test emitting a deeply nested structure
TEST_F(NodeEventsTest_266, EmitDeeplyNested_266) {
    Node node = YAML::Load("{a: {b: {c: d}}}");
    NodeEvents events(node);

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(3);
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(4); // a, b, c, d
    EXPECT_CALL(handler, OnMapEnd()).Times(3);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    events.Emit(handler);
}
