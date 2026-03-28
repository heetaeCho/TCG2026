// TEST_ID: 186
// File: tinyxml2_deepclone_test_186.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <string>

using namespace tinyxml2;

namespace {

std::string SerializeNode(const XMLNode* node) {
    EXPECT_NE(node, nullptr);
    XMLPrinter printer;
    const bool ok = node->Accept(&printer);
    EXPECT_TRUE(ok);
    return std::string(printer.CStr());
}

}  // namespace

class DeepCloneTest_186 : public ::testing::Test {};

TEST_F(DeepCloneTest_186, CloneSubtreePreservesSerializationAndTargetsDocument_186) {
    XMLDocument src(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    const char* xml =
        "<root>"
        "  <a>1</a>"
        "  <!--c-->"
        "  <b attr='x'/>"
        "</root>";
    ASSERT_EQ(src.Parse(xml), XML_SUCCESS);

    const XMLElement* root = src.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument target(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);

    XMLNode* clone = root->DeepClone(&target);
    ASSERT_NE(clone, nullptr);

    // The clone should report it belongs to the target document.
    EXPECT_EQ(clone->GetDocument(), &target);

    // DeepClone returns a node; it may or may not be attached yet, but it should be safe to query Parent().
    EXPECT_EQ(clone->Parent(), nullptr);

    // Structural/observable equivalence: serialize both subtrees and compare.
    const std::string srcPrinted = SerializeNode(root);
    const std::string clonePrinted = SerializeNode(clone);
    EXPECT_EQ(clonePrinted, srcPrinted);
}

TEST_F(DeepCloneTest_186, CloneIsIndependentAfterSourceMutation_186) {
    XMLDocument src(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    const char* xml =
        "<root>"
        "  <child/>"
        "  <sibling/>"
        "</root>";
    ASSERT_EQ(src.Parse(xml), XML_SUCCESS);

    const XMLElement* root = src.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument target(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);

    XMLNode* clone = root->DeepClone(&target);
    ASSERT_NE(clone, nullptr);

    const std::string cloneBefore = SerializeNode(clone);

    // Mutate the source tree via public interface.
    // (Changing element name via SetValue is observable in serialization.)
    XMLNode* firstChild = src.RootElement()->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    firstChild->SetValue("renamedChild", /*staticMem=*/false);

    // The clone serialization should remain the same (independence).
    const std::string cloneAfter = SerializeNode(clone);
    EXPECT_EQ(cloneAfter, cloneBefore);

    // And the source should now differ from the clone (mutation took effect on source).
    const std::string srcAfter = SerializeNode(root);
    EXPECT_NE(srcAfter, cloneBefore);
}

TEST_F(DeepCloneTest_186, CloneLeafNodeMatchesSerialization_186) {
    XMLDocument src(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    const char* xml = "<root><leaf/></root>";
    ASSERT_EQ(src.Parse(xml), XML_SUCCESS);

    const XMLElement* root = src.RootElement();
    ASSERT_NE(root, nullptr);

    const XMLElement* leaf = root->FirstChildElement("leaf");
    ASSERT_NE(leaf, nullptr);

    XMLDocument target(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    XMLNode* leafClone = leaf->DeepClone(&target);
    ASSERT_NE(leafClone, nullptr);

    EXPECT_EQ(leafClone->GetDocument(), &target);

    const std::string leafPrinted = SerializeNode(leaf);
    const std::string leafClonePrinted = SerializeNode(leafClone);
    EXPECT_EQ(leafClonePrinted, leafPrinted);

    // Leaf should have no children; the clone should match.
    EXPECT_TRUE(leaf->NoChildren());
    EXPECT_TRUE(leafClone->NoChildren());
}

TEST_F(DeepCloneTest_186, CloneMaintainsChildElementCountAndOrder_186) {
    XMLDocument src(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    const char* xml =
        "<root>"
        "  <a/>"
        "  <b/>"
        "  <c/>"
        "</root>";
    ASSERT_EQ(src.Parse(xml), XML_SUCCESS);

    const XMLElement* root = src.RootElement();
    ASSERT_NE(root, nullptr);

    XMLDocument target(/*processEntities=*/true, /*whitespaceMode=*/XMLDocument::PRESERVE_WHITESPACE);
    XMLNode* cloneNode = root->DeepClone(&target);
    ASSERT_NE(cloneNode, nullptr);

    const XMLNode* cloneRootAsNode = cloneNode;
    ASSERT_NE(cloneRootAsNode, nullptr);

    // Element count should match.
    EXPECT_EQ(root->ChildElementCount(), cloneRootAsNode->ChildElementCount());

    // Order of child elements should match via name traversal.
    const XMLElement* srcA = root->FirstChildElement();
    ASSERT_NE(srcA, nullptr);
    const XMLElement* srcB = srcA->NextSiblingElement();
    ASSERT_NE(srcB, nullptr);
    const XMLElement* srcC = srcB->NextSiblingElement();
    ASSERT_NE(srcC, nullptr);

    const XMLElement* cloneA = cloneRootAsNode->FirstChildElement();
    ASSERT_NE(cloneA, nullptr);
    const XMLElement* cloneB = cloneA->NextSiblingElement();
    ASSERT_NE(cloneB, nullptr);
    const XMLElement* cloneC = cloneB->NextSiblingElement();
    ASSERT_NE(cloneC, nullptr);

    EXPECT_STREQ(srcA->Value(), cloneA->Value());
    EXPECT_STREQ(srcB->Value(), cloneB->Value());
    EXPECT_STREQ(srcC->Value(), cloneC->Value());

    // Boundary: last element should have no next sibling element.
    EXPECT_EQ(srcC->NextSiblingElement(), nullptr);
    EXPECT_EQ(cloneC->NextSiblingElement(), nullptr);
}
