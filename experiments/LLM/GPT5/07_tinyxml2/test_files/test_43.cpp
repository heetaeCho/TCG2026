// TEST_ID: 43
// File: ./TestProjects/tinyxml2/xmlnode_toelement_test_43.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class TestXMLNode_43 : public tinyxml2::XMLNode {
public:
    explicit TestXMLNode_43(tinyxml2::XMLDocument* doc) : tinyxml2::XMLNode(doc) {}
    ~TestXMLNode_43() override = default;

    // Intentionally do NOT override ToElement() so we test the base-class behavior.
};

}  // namespace

TEST(XMLNodeToElementTest_43, ReturnsNullptrForBaseImplementation_43) {
    tinyxml2::XMLDocument doc;
    TestXMLNode_43 node(&doc);

    // Observable behavior from the provided interface/partial implementation:
    // base XMLNode::ToElement() returns 0 (nullptr).
    EXPECT_EQ(nullptr, node.ToElement());
}

TEST(XMLNodeToElementTest_43, ReturnsNullptrViaBasePointerDispatch_43) {
    tinyxml2::XMLDocument doc;
    TestXMLNode_43 node(&doc);

    tinyxml2::XMLNode* asBase = &node;
    EXPECT_EQ(nullptr, asBase->ToElement());
}

TEST(XMLNodeToElementTest_43, ReturnsNullptrEvenWithNullDocumentPointer_43) {
    // Boundary condition: construct with nullptr document pointer (if allowed by implementation).
    TestXMLNode_43 node(nullptr);

    EXPECT_EQ(nullptr, node.ToElement());
}

TEST(XMLNodeToElementTest_43, HeapAllocatedNodeReturnsNullptrAndCanBeDeleted_43) {
    tinyxml2::XMLDocument doc;

    auto* node = new TestXMLNode_43(&doc);
    EXPECT_EQ(nullptr, node->ToElement());

    // Delete through derived type (base destructor is protected).
    delete node;
}
