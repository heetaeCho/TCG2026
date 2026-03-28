// TEST_ID: 45
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

using namespace tinyxml2;

// Expose protected XMLNode constructor/destructor for testing.
class TestNode_45 : public XMLNode {
public:
    explicit TestNode_45(XMLDocument* doc) : XMLNode(doc) {}
    ~TestNode_45() override = default;
    // Intentionally do not override ToComment(); we want the base behavior.
};

// Create a real XMLComment instance we can safely point at (without dereferencing invalid pointers).
class TestComment_45 : public XMLComment {
public:
    explicit TestComment_45(XMLDocument* doc) : XMLComment(doc) {}
    ~TestComment_45() override = default;
};

// A node that overrides ToComment() to verify virtual dispatch.
class OverrideToCommentNode_45 : public XMLNode {
public:
    OverrideToCommentNode_45(XMLDocument* doc, XMLComment* toReturn)
        : XMLNode(doc), toReturn_(toReturn) {}
    ~OverrideToCommentNode_45() override = default;

    XMLComment* ToComment() override { return toReturn_; }

private:
    XMLComment* toReturn_;
};

class XMLNodeToCommentTest_45 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

}  // namespace

TEST_F(XMLNodeToCommentTest_45, DefaultImplementationReturnsNullptr_45) {
    TestNode_45 node(&doc_);
    EXPECT_EQ(node.ToComment(), nullptr);
}

TEST_F(XMLNodeToCommentTest_45, DefaultImplementationReturnsNullptrThroughBasePointer_45) {
    TestNode_45 node(&doc_);
    XMLNode* base = &node;
    EXPECT_EQ(base->ToComment(), nullptr);
}

TEST_F(XMLNodeToCommentTest_45, VirtualDispatchUsesOverride_45) {
    TestComment_45 comment(&doc_);
    OverrideToCommentNode_45 node(&doc_, &comment);

    XMLNode* base = &node;
    EXPECT_EQ(base->ToComment(), &comment);
}
