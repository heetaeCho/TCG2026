#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class ShallowCloneTest_265 : public ::testing::Test {
protected:
    // Use compact documents; behavior under test shouldn't depend on whitespace/entities.
    XMLDocument doc_{true, WHITESPACE_PRESERVE};
    XMLDocument otherDoc_{true, WHITESPACE_PRESERVE};
};

TEST_F(ShallowCloneTest_265, CloneWithNullDocUsesSourceDocumentAndCopiesName_265) {
    XMLElement* src = doc_.NewElement("root");
    ASSERT_NE(src, nullptr);

    XMLNode* clonedNode = src->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);

    XMLElement* clonedElem = clonedNode->ToElement();
    ASSERT_NE(clonedElem, nullptr);

    // Name/value should match.
    ASSERT_STREQ(src->Value(), clonedElem->Value());

    // When document argument is null, it should use the source element's document.
    ASSERT_EQ(clonedElem->GetDocument(), src->GetDocument());
}

TEST_F(ShallowCloneTest_265, CloneWithProvidedDocBelongsToThatDocAndCopiesName_265) {
    XMLElement* src = doc_.NewElement("root");
    ASSERT_NE(src, nullptr);

    XMLNode* clonedNode = src->ShallowClone(&otherDoc_);
    ASSERT_NE(clonedNode, nullptr);

    XMLElement* clonedElem = clonedNode->ToElement();
    ASSERT_NE(clonedElem, nullptr);

    ASSERT_STREQ("root", clonedElem->Value());
    ASSERT_EQ(clonedElem->GetDocument(), &otherDoc_);
}

TEST_F(ShallowCloneTest_265, CopiesAllAttributesAndValues_265) {
    XMLElement* src = doc_.NewElement("e");
    ASSERT_NE(src, nullptr);

    src->SetAttribute("a", "1");
    src->SetAttribute("b", "two");
    src->SetAttribute("empty", "");

    XMLNode* clonedNode = src->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);

    XMLElement* cloned = clonedNode->ToElement();
    ASSERT_NE(cloned, nullptr);

    // Verify each attribute exists and has the same value.
    const XMLAttribute* a = cloned->FindAttribute("a");
    ASSERT_NE(a, nullptr);
    ASSERT_STREQ(a->Value(), "1");

    const XMLAttribute* b = cloned->FindAttribute("b");
    ASSERT_NE(b, nullptr);
    ASSERT_STREQ(b->Value(), "two");

    const XMLAttribute* empty = cloned->FindAttribute("empty");
    ASSERT_NE(empty, nullptr);
    ASSERT_STREQ(empty->Value(), "");
}

TEST_F(ShallowCloneTest_265, CloneFromElementWithNoAttributesHasNoAttributes_265) {
    XMLElement* src = doc_.NewElement("e");
    ASSERT_NE(src, nullptr);
    ASSERT_EQ(src->FirstAttribute(), nullptr);

    XMLNode* clonedNode = src->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);

    XMLElement* cloned = clonedNode->ToElement();
    ASSERT_NE(cloned, nullptr);

    ASSERT_EQ(cloned->FirstAttribute(), nullptr);
}

TEST_F(ShallowCloneTest_265, DoesNotCopyChildrenOrText_265) {
    XMLElement* src = doc_.NewElement("parent");
    ASSERT_NE(src, nullptr);

    // Add a child element and a text node.
    XMLElement* child = doc_.NewElement("child");
    ASSERT_NE(child, nullptr);
    src->InsertEndChild(child);

    // Also add text under the parent.
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);
    src->InsertEndChild(text);

    ASSERT_FALSE(src->NoChildren());  // Sanity check: source has children.

    XMLNode* clonedNode = src->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);

    XMLElement* cloned = clonedNode->ToElement();
    ASSERT_NE(cloned, nullptr);

    // Shallow clone should not include children or text content.
    EXPECT_TRUE(cloned->NoChildren());
    EXPECT_EQ(cloned->FirstChild(), nullptr);
    EXPECT_EQ(cloned->GetText(), nullptr);
    EXPECT_EQ(cloned->ChildElementCount(), 0);
}

TEST_F(ShallowCloneTest_265, ReturnedNodeIsAnElement_265) {
    XMLElement* src = doc_.NewElement("x");
    ASSERT_NE(src, nullptr);

    XMLNode* clonedNode = src->ShallowClone(nullptr);
    ASSERT_NE(clonedNode, nullptr);

    // Observable type behavior through the public polymorphic API.
    EXPECT_NE(clonedNode->ToElement(), nullptr);
    EXPECT_EQ(clonedNode->ToText(), nullptr);
    EXPECT_EQ(clonedNode->ToComment(), nullptr);
    EXPECT_EQ(clonedNode->ToDocument(), nullptr);
    EXPECT_EQ(clonedNode->ToDeclaration(), nullptr);
    EXPECT_EQ(clonedNode->ToUnknown(), nullptr);
}

}  // namespace
