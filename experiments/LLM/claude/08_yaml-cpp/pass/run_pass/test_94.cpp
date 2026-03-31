#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "yaml-cpp/yaml.h"
#include "yaml-cpp/eventhandler.h"
#include "singledocparser.h"
#include "scanner.h"
#include "directives.h"
#include "collectionstack.h"

using namespace YAML;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::InSequence;

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

class SingleDocParserTest_94 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Simple scalar document triggers OnDocumentStart, OnScalar, OnDocumentEnd
TEST_F(SingleDocParserTest_94, SimpleScalarDocument_94) {
    std::istringstream input("hello");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Document with explicit doc start marker "---"
TEST_F(SingleDocParserTest_94, ExplicitDocStartMarker_94) {
    std::istringstream input("---\nhello");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Document with explicit doc end marker "..."
TEST_F(SingleDocParserTest_94, ExplicitDocEndMarker_94) {
    std::istringstream input("---\nhello\n...");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Empty/null document (just doc start, no content)
TEST_F(SingleDocParserTest_94, EmptyDocumentWithDocStart_94) {
    std::istringstream input("---\n...");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnNull(_, _)).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Sequence document
TEST_F(SingleDocParserTest_94, SequenceDocument_94) {
    std::istringstream input("- a\n- b\n- c");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "a")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "b")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "c")).Times(1);
        EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Map document
TEST_F(SingleDocParserTest_94, MapDocument_94) {
    std::istringstream input("key: value");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "key")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "value")).Times(1);
        EXPECT_CALL(handler, OnMapEnd()).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Flow sequence
TEST_F(SingleDocParserTest_94, FlowSequenceDocument_94) {
    std::istringstream input("[1, 2, 3]");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "1")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "2")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "3")).Times(1);
        EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Flow map
TEST_F(SingleDocParserTest_94, FlowMapDocument_94) {
    std::istringstream input("{a: b}");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "a")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "b")).Times(1);
        EXPECT_CALL(handler, OnMapEnd()).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Anchor and alias
TEST_F(SingleDocParserTest_94, AnchorAndAlias_94) {
    std::istringstream input("- &anchor hello\n- *anchor");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
    EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnAnchor(_, _)).Times(AtLeast(0));
    EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
    EXPECT_CALL(handler, OnAlias(_, _)).Times(1);
    EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    parser.HandleDocument(handler);
}

// Test: Quoted scalar
TEST_F(SingleDocParserTest_94, QuotedScalar_94) {
    std::istringstream input("\"hello world\"");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello world")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Nested map in sequence
TEST_F(SingleDocParserTest_94, NestedMapInSequence_94) {
    std::istringstream input("- key: value");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnSequenceStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnMapStart(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "key")).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "value")).Times(1);
        EXPECT_CALL(handler, OnMapEnd()).Times(1);
        EXPECT_CALL(handler, OnSequenceEnd()).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Multiple doc end markers are consumed
TEST_F(SingleDocParserTest_94, MultipleDocEndMarkers_94) {
    std::istringstream input("---\nhello\n...\n...");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Document with tag
TEST_F(SingleDocParserTest_94, DocumentWithTag_94) {
    std::istringstream input("!!str hello");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "hello")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Verify OnDocumentStart receives a Mark
TEST_F(SingleDocParserTest_94, DocumentStartReceivesMark_94) {
    std::istringstream input("test");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    Mark capturedMark;
    EXPECT_CALL(handler, OnDocumentStart(_))
        .WillOnce([&capturedMark](const Mark& mark) {
            capturedMark = mark;
        });
    EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);
    EXPECT_CALL(handler, OnDocumentEnd()).Times(1);

    parser.HandleDocument(handler);

    // Mark should have been set (line/column >= 0)
    EXPECT_GE(capturedMark.line, 0);
    EXPECT_GE(capturedMark.column, 0);
}

// Test: Single null/empty value document
TEST_F(SingleDocParserTest_94, NullValueDocument_94) {
    std::istringstream input("~");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, "~")).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Multiline scalar (literal block)
TEST_F(SingleDocParserTest_94, LiteralBlockScalar_94) {
    std::istringstream input("|\n  hello\n  world");
    Scanner scanner(input);
    Directives directives;
    SingleDocParser parser(scanner, directives);

    MockEventHandler handler;

    {
        InSequence seq;
        EXPECT_CALL(handler, OnDocumentStart(_)).Times(1);
        EXPECT_CALL(handler, OnScalar(_, _, _, _)).Times(1);
        EXPECT_CALL(handler, OnDocumentEnd()).Times(1);
    }

    parser.HandleDocument(handler);
}

// Test: Using Parser/Node high-level API to verify integration - simple parse
TEST_F(SingleDocParserTest_94, HighLevelParseSimpleScalar_94) {
    YAML::Node node = YAML::Load("hello");
    EXPECT_TRUE(node.IsScalar());
    EXPECT_EQ(node.as<std::string>(), "hello");
}

// Test: High-level parse of a sequence
TEST_F(SingleDocParserTest_94, HighLevelParseSequence_94) {
    YAML::Node node = YAML::Load("[1, 2, 3]");
    EXPECT_TRUE(node.IsSequence());
    EXPECT_EQ(node.size(), 3u);
}

// Test: High-level parse of a map
TEST_F(SingleDocParserTest_94, HighLevelParseMap_94) {
    YAML::Node node = YAML::Load("{a: b, c: d}");
    EXPECT_TRUE(node.IsMap());
    EXPECT_EQ(node["a"].as<std::string>(), "b");
    EXPECT_EQ(node["c"].as<std::string>(), "d");
}
