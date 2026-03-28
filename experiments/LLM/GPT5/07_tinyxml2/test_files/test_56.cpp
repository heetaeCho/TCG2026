// File: ./TestProjects/tinyxml2/tests/xmlnode_previoussibling_test_56.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {
namespace {

// Test seam: derive to access protected ctor and protected linkage fields for setup.
// We are not testing/probing internal logic—only using protected access to build states
// that are observable through the public interface under test.
class TestXMLNode_56 : public XMLNode {
public:
	explicit TestXMLNode_56(XMLDocument* doc) : XMLNode(doc) {}

	void SetPrev_56(XMLNode* prev) { _prev = prev; }
};

class XMLNodePreviousSiblingTest_56 : public ::testing::Test {
protected:
	XMLDocument doc_;
};

TEST_F(XMLNodePreviousSiblingTest_56, DefaultPreviousSiblingIsNull_56) {
	TestXMLNode_56 node(&doc_);

	// Observable behavior: PreviousSibling returns the previous node pointer (or null).
	EXPECT_EQ(node.PreviousSibling(), nullptr);
}

TEST_F(XMLNodePreviousSiblingTest_56, ReturnsAssignedPreviousSibling_56) {
	TestXMLNode_56 prev(&doc_);
	TestXMLNode_56 node(&doc_);

	node.SetPrev_56(&prev);

	EXPECT_EQ(node.PreviousSibling(), &prev);
}

TEST_F(XMLNodePreviousSiblingTest_56, ConstCallReturnsSamePointer_56) {
	TestXMLNode_56 prev(&doc_);
	TestXMLNode_56 node(&doc_);
	node.SetPrev_56(&prev);

	const XMLNode* constNode = &node;
	EXPECT_EQ(constNode->PreviousSibling(), &prev);
}

}  // namespace
}  // namespace tinyxml2
