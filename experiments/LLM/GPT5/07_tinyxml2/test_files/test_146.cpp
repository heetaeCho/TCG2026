// File: ./TestProjects/tinyxml2/xmlconsthandle_todeclaration_test_146.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLConstHandleToDeclarationTest_146 : public ::testing::Test {};

TEST_F(XMLConstHandleToDeclarationTest_146, NullNodeReturnsNull_146) {
    XMLConstHandle handle(nullptr);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

TEST_F(XMLConstHandleToDeclarationTest_146, DeclarationNodeReturnsNonNull_146) {
    XMLDocument doc;
    // Include an XML declaration.
    const XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(err, XML_SUCCESS);

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);

    XMLConstHandle handle(first);

    // Observable behavior: when the underlying node is a declaration, ToDeclaration() is non-null
    // and matches what the node itself reports via its public virtual API.
    const XMLDeclaration* declFromNode = first->ToDeclaration();
    ASSERT_NE(declFromNode, nullptr);

    EXPECT_EQ(handle.ToDeclaration(), declFromNode);
}

TEST_F(XMLConstHandleToDeclarationTest_146, NonDeclarationNodeReturnsNull_146) {
    XMLDocument doc;
    const XMLError err = doc.Parse("<root/>");
    ASSERT_EQ(err, XML_SUCCESS);

    const XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);

    XMLConstHandle handle(root);
    EXPECT_EQ(handle.ToDeclaration(), nullptr);
}

TEST_F(XMLConstHandleToDeclarationTest_146, CopyConstructedHandlePreservesResult_146) {
    XMLDocument doc;
    const XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(err, XML_SUCCESS);

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->ToDeclaration(), nullptr);

    XMLConstHandle original(first);
    XMLConstHandle copy(original);

    EXPECT_EQ(copy.ToDeclaration(), original.ToDeclaration());
}

TEST_F(XMLConstHandleToDeclarationTest_146, AssignedHandlePreservesResult_146) {
    XMLDocument doc;
    const XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(err, XML_SUCCESS);

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);
    ASSERT_NE(first->ToDeclaration(), nullptr);

    XMLConstHandle source(first);
    XMLConstHandle target(nullptr);

    target = source;

    EXPECT_EQ(target.ToDeclaration(), source.ToDeclaration());
}

TEST_F(XMLConstHandleToDeclarationTest_146, ConstructedFromNodeReferenceWorks_146) {
    XMLDocument doc;
    const XMLError err = doc.Parse("<?xml version=\"1.0\"?><root/>");
    ASSERT_EQ(err, XML_SUCCESS);

    const XMLNode* first = doc.FirstChild();
    ASSERT_NE(first, nullptr);

    const XMLDeclaration* decl = first->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    // Construct from XMLNode& (via the node reference overload).
    const XMLNode& nodeRef = *first;
    XMLConstHandle handle(nodeRef);

    EXPECT_EQ(handle.ToDeclaration(), decl);
}

}  // namespace tinyxml2
