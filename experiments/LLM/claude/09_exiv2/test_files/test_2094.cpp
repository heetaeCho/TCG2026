#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include the necessary headers for ExpatAdapter
#include "ExpatAdapter.hpp"

class ExpatAdapterTest_2094 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that parsing a simple well-formed XML element works correctly
TEST_F(ExpatAdapterTest_2094, ParseSimpleElement_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    // After parsing, the tree should have content
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test that parsing nested elements works - EndElementHandler pops parseStack
TEST_F(ExpatAdapterTest_2094, ParseNestedElements_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root><child><grandchild/></child></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    // parseStack should be back to initial state after all end elements processed
    EXPECT_TRUE(adapter.parseStack.empty() || adapter.parseStack.size() == 1);
}

// Test parsing multiple sibling elements
TEST_F(ExpatAdapterTest_2094, ParseSiblingElements_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root><a/><b/><c/></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test parsing an empty self-closing element
TEST_F(ExpatAdapterTest_2094, ParseSelfClosingElement_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root/>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test parsing deeply nested elements to verify EndElementHandler pops correctly
TEST_F(ExpatAdapterTest_2094, ParseDeeplyNestedElements_2094) {
    ExpatAdapter adapter;
    const char* xml = "<a><b><c><d><e><f></f></e></d></c></b></a>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test incremental parsing - buffer split across calls
TEST_F(ExpatAdapterTest_2094, ParseIncrementalBuffer_2094) {
    ExpatAdapter adapter;
    const char* xml1 = "<root><child>";
    const char* xml2 = "</child></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml1, strlen(xml1), false));
    ASSERT_NO_THROW(adapter.ParseBuffer(xml2, strlen(xml2), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test parsing with attributes
TEST_F(ExpatAdapterTest_2094, ParseElementWithAttributes_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root attr=\"value\"><child key=\"val\"/></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test parsing with text content
TEST_F(ExpatAdapterTest_2094, ParseElementWithTextContent_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root>Hello World</root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test parsing with namespaces
TEST_F(ExpatAdapterTest_2094, ParseElementWithNamespaces_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root xmlns:ns=\"http://example.com\"><ns:child/></root>";
    ASSERT_NO_THROW(adapter.ParseBuffer(xml, strlen(xml), true));
    EXPECT_GT(adapter.rootCount, 0u);
}

// Test that empty buffer with last=true doesn't crash
TEST_F(ExpatAdapterTest_2094, ParseEmptyBufferLast_2094) {
    ExpatAdapter adapter;
    ASSERT_NO_THROW(adapter.ParseBuffer("", 0, true));
}

// Test that parseStack is properly managed after complete parse
TEST_F(ExpatAdapterTest_2094, ParseStackEmptyAfterCompleteParse_2094) {
    ExpatAdapter adapter;
    const char* xml = "<root><a><b/></a><c/></root>";
    adapter.ParseBuffer(xml, strlen(xml), true);
    // After complete parsing, parseStack should not have leftover entries from elements
    // The stack should only contain the tree root or be empty
    EXPECT_LE(adapter.parseStack.size(), 1u);
}
