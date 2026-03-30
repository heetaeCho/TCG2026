// File: TestProjects/tinyxml2/tests/XMLElementInsertNewDeclarationTest_262.cpp

#include <gtest/gtest.h>
#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLElementInsertNewDeclarationTest_262 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        // Put root into the document so tree navigation (Parent/FirstChild/LastChild) is meaningful.
        ASSERT_NE(doc.InsertFirstChild(root), nullptr);
    }
};

TEST_F(XMLElementInsertNewDeclarationTest_262, InsertReturnsNonNullAndIsDeclarationNode_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    ASSERT_NE(decl, nullptr);

    // Observable type: it should be a declaration node.
    EXPECT_NE(decl->ToDeclaration(), nullptr);

    // Observable linkage: parent should be the element we inserted into.
    EXPECT_EQ(decl->Parent(), root);

    // Observable linkage: should be part of the tree.
    EXPECT_EQ(root->LastChild(), static_cast<const XMLNode*>(decl));
    EXPECT_EQ(decl->GetDocument(), &doc);
}

TEST_F(XMLElementInsertNewDeclarationTest_262, InsertAppendsAtEndWhenOtherChildrenExist_262) {
    // Add an existing child first.
    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);
    ASSERT_NE(root->InsertEndChild(child), nullptr);

    const XMLNode* firstBefore = root->FirstChild();
    ASSERT_NE(firstBefore, nullptr);

    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    // Existing first child remains the same, declaration should be appended at end.
    EXPECT_EQ(root->FirstChild(), firstBefore);
    EXPECT_EQ(root->LastChild(), static_cast<const XMLNode*>(decl));

    // And the declaration should have a previous sibling (the existing child).
    EXPECT_EQ(decl->PreviousSibling(), child);
}

TEST_F(XMLElementInsertNewDeclarationTest_262, MultipleInsertionsPreserveOrder_262) {
    XMLDeclaration* decl1 = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl1, nullptr);

    XMLDeclaration* decl2 = root->InsertNewDeclaration("xml version=\"1.1\"");
    ASSERT_NE(decl2, nullptr);

    // Second one should be the last child.
    EXPECT_EQ(root->LastChild(), static_cast<const XMLNode*>(decl2));

    // Order checks via sibling navigation.
    EXPECT_EQ(decl2->PreviousSibling(), decl1);
    EXPECT_EQ(decl1->NextSibling(), decl2);

    // Both should be children of root.
    EXPECT_EQ(decl1->Parent(), root);
    EXPECT_EQ(decl2->Parent(), root);
}

TEST_F(XMLElementInsertNewDeclarationTest_262, ChildElementCountNotAffectedByDeclarationNodes_262) {
    // Baseline: no element children.
    EXPECT_EQ(root->ChildElementCount(), 0);

    // Insert a declaration (not an element).
    XMLDeclaration* decl = root->InsertNewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    // Element-child count should remain unchanged because we didn't add an element.
    EXPECT_EQ(root->ChildElementCount(), 0);

    // Add a real element child and verify it counts.
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(root->ChildElementCount(), 1);
}

TEST_F(XMLElementInsertNewDeclarationTest_262, NullTextDoesNotCrashAndIfInsertedIsLinkedCorrectly_262) {
    // Behavior may vary (could return nullptr or create a default declaration).
    XMLDeclaration* decl = root->InsertNewDeclaration(nullptr);

    if (decl) {
        // If it succeeds, it must be a properly linked declaration node.
        EXPECT_NE(decl->ToDeclaration(), nullptr);
        EXPECT_EQ(decl->Parent(), root);
        EXPECT_EQ(root->LastChild(), static_cast<const XMLNode*>(decl));
        EXPECT_EQ(decl->GetDocument(), &doc);
    } else {
        // If it fails, it should simply report failure via nullptr (observable).
        SUCCEED();
    }
}

TEST_F(XMLElementInsertNewDeclarationTest_262, EmptyTextDoesNotCrashAndIfInsertedIsLinkedCorrectly_262) {
    XMLDeclaration* decl = root->InsertNewDeclaration("");

    if (decl) {
        EXPECT_NE(decl->ToDeclaration(), nullptr);
        EXPECT_EQ(decl->Parent(), root);
        EXPECT_EQ(root->LastChild(), static_cast<const XMLNode*>(decl));
        EXPECT_EQ(decl->GetDocument(), &doc);
    } else {
        SUCCEED();
    }
}
