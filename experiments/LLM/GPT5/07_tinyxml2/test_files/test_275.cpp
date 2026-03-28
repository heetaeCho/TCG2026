// File: ./TestProjects/tinyxml2/tests/XMLDocumentNewDeclarationTest_275.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLDocumentNewDeclarationTest_275 : public ::testing::Test {
protected:
    // Use a common document instance for most tests.
    // Constructor signature per provided header: XMLDocument(bool processEntities, Whitespace whitespaceMode)
    XMLDocument doc{true, PRESERVE_WHITESPACE};
};

TEST_F(XMLDocumentNewDeclarationTest_275, NewDeclarationWithNullptrUsesDefaultValue_275) {
    XMLDeclaration* decl = doc.NewDeclaration(nullptr);
    ASSERT_NE(decl, nullptr);

    // Observable behavior via public interface:
    // - Returned node is a declaration node
    EXPECT_EQ(decl->ToDeclaration(), decl);

    // - Value should be set to the library default when nullptr is provided
    EXPECT_STREQ(decl->Value(), "xml version=\"1.0\" encoding=\"UTF-8\"");

    // - Node should belong to the document that created it
    EXPECT_EQ(decl->GetDocument(), &doc);
}

TEST_F(XMLDocumentNewDeclarationTest_275, NewDeclarationWithCustomTextSetsValue_275) {
    const char* kText = "xml version=\"1.0\" encoding=\"UTF-16\"";
    XMLDeclaration* decl = doc.NewDeclaration(kText);
    ASSERT_NE(decl, nullptr);

    EXPECT_EQ(decl->ToDeclaration(), decl);
    EXPECT_STREQ(decl->Value(), kText);
    EXPECT_EQ(decl->GetDocument(), &doc);
}

TEST_F(XMLDocumentNewDeclarationTest_275, NewDeclarationWithEmptyStringKeepsEmptyValue_275) {
    // Boundary: empty but non-null input should not fall back to default.
    XMLDeclaration* decl = doc.NewDeclaration("");
    ASSERT_NE(decl, nullptr);

    EXPECT_EQ(decl->ToDeclaration(), decl);
    EXPECT_STREQ(decl->Value(), "");
}

TEST_F(XMLDocumentNewDeclarationTest_275, MultipleDeclarationsAreDistinctNodes_275) {
    XMLDeclaration* d1 = doc.NewDeclaration("xml version=\"1.0\"");
    XMLDeclaration* d2 = doc.NewDeclaration("xml version=\"1.1\"");
    ASSERT_NE(d1, nullptr);
    ASSERT_NE(d2, nullptr);

    EXPECT_NE(d1, d2);
    EXPECT_STRNE(d1->Value(), d2->Value());
}

TEST_F(XMLDocumentNewDeclarationTest_275, InsertDeclarationIntoDocumentAndPrint_275) {
    // Insert into the document tree and ensure printing reflects the declaration value.
    XMLDeclaration* decl = doc.NewDeclaration(nullptr);
    ASSERT_NE(decl, nullptr);

    XMLNode* inserted = doc.InsertFirstChild(decl);
    ASSERT_EQ(inserted, decl);

    XMLPrinter printer;
    doc.Print(&printer);

    const std::string out = printer.CStr();
    // We keep checks resilient: only verify key observable substrings.
    EXPECT_NE(out.find("<?xml"), std::string::npos);
    EXPECT_NE(out.find("xml version=\"1.0\" encoding=\"UTF-8\""), std::string::npos);
    EXPECT_NE(out.find("?>"), std::string::npos);
}

TEST_F(XMLDocumentNewDeclarationTest_275, DeleteNodeAfterInsertionRemovesFromTree_275) {
    XMLDeclaration* decl = doc.NewDeclaration("xml version=\"1.0\"");
    ASSERT_NE(decl, nullptr);

    ASSERT_EQ(doc.InsertEndChild(decl), decl);
    ASSERT_FALSE(doc.NoChildren());

    // Observable behavior: after deleting the only child, document has no children.
    doc.DeleteNode(decl);
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(doc.FirstChild(), nullptr);
}
