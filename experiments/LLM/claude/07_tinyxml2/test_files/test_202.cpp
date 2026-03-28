#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDeclarationShallowCloneTest_202 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test ShallowClone with a different target document
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneToAnotherDocument_202) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, decl); // Should be a different node
    EXPECT_EQ(cloned->GetDocument(), &targetDoc); // Should belong to target document

    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);

    // The value should match the original
    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    targetDoc.DeleteNode(cloned);
}

// Test ShallowClone with null document (should use the declaration's own document)
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneWithNullDocument_202) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLNode* cloned = decl->ShallowClone(nullptr);

    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, decl);
    EXPECT_EQ(cloned->GetDocument(), doc); // Should belong to the same document

    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);

    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    doc->DeleteNode(cloned);
}

// Test ShallowClone preserves the declaration value
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowClonePreservesValue_202) {
    XMLDeclaration* decl = doc->NewDeclaration("version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"");
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);

    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    targetDoc.DeleteNode(cloned);
    doc->DeleteNode(decl);
}

// Test ShallowClone with default declaration (no custom text)
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneDefaultDeclaration_202) {
    XMLDeclaration* decl = doc->NewDeclaration(nullptr);
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);

    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    targetDoc.DeleteNode(cloned);
    doc->DeleteNode(decl);
}

// Test ShallowClone to the same document
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneToSameDocument_202) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLNode* cloned = decl->ShallowClone(doc);

    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned, decl); // Should still be a different node
    EXPECT_EQ(cloned->GetDocument(), doc);

    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);
    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    doc->DeleteNode(cloned);
}

// Test that the cloned declaration is indeed a declaration node
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneResultIsDeclaration_202) {
    XMLDeclaration* decl = doc->NewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);

    // Should be a declaration
    EXPECT_NE(cloned->ToDeclaration(), nullptr);
    // Should NOT be other types
    EXPECT_EQ(cloned->ToElement(), nullptr);
    EXPECT_EQ(cloned->ToComment(), nullptr);
    EXPECT_EQ(cloned->ToText(), nullptr);
    EXPECT_EQ(cloned->ToDocument(), nullptr);
    EXPECT_EQ(cloned->ToUnknown(), nullptr);

    targetDoc.DeleteNode(cloned);
    doc->DeleteNode(decl);
}

// Test ShallowClone does not clone children (shallow copy)
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneDoesNotCopyChildren_202) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(cloned->NoChildren());

    targetDoc.DeleteNode(cloned);
}

// Test ShallowClone with empty string declaration
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneEmptyDeclaration_202) {
    XMLDeclaration* decl = doc->NewDeclaration("");
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    XMLDeclaration* clonedDecl = cloned->ToDeclaration();
    ASSERT_NE(clonedDecl, nullptr);
    EXPECT_STREQ(clonedDecl->Value(), decl->Value());

    targetDoc.DeleteNode(cloned);
    doc->DeleteNode(decl);
}

// Test ShallowClone: cloned node has no parent (it's unlinked)
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneNodeHasNoParent_202) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    // The cloned node should not have a parent since it's not inserted into the tree
    EXPECT_EQ(cloned->Parent(), nullptr);

    targetDoc.DeleteNode(cloned);
}

// Test ShallowEqual between original and cloned declaration
TEST_F(XMLDeclarationShallowCloneTest_202, ShallowCloneIsShallowEqual_202) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc->Parse(xml);

    XMLDeclaration* decl = doc->FirstChild()->ToDeclaration();
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc;
    XMLNode* cloned = decl->ShallowClone(&targetDoc);

    ASSERT_NE(cloned, nullptr);
    EXPECT_TRUE(decl->ShallowEqual(cloned));
    EXPECT_TRUE(cloned->ShallowEqual(decl));

    targetDoc.DeleteNode(cloned);
}

// Test multiple ShallowClone calls produce independent nodes
TEST_F(XMLDeclarationShallowCloneTest_202, MultipleShallowClonesAreIndependent_202) {
    XMLDeclaration* decl = doc->NewDeclaration("version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    XMLDocument targetDoc1;
    XMLDocument targetDoc2;

    XMLNode* clone1 = decl->ShallowClone(&targetDoc1);
    XMLNode* clone2 = decl->ShallowClone(&targetDoc2);

    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_NE(clone1, clone2);

    EXPECT_EQ(clone1->GetDocument(), &targetDoc1);
    EXPECT_EQ(clone2->GetDocument(), &targetDoc2);

    EXPECT_STREQ(clone1->Value(), decl->Value());
    EXPECT_STREQ(clone2->Value(), decl->Value());

    targetDoc1.DeleteNode(clone1);
    targetDoc2.DeleteNode(clone2);
    doc->DeleteNode(decl);
}
