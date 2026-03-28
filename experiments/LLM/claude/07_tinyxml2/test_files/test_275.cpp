#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::NewDeclaration tests
class NewDeclarationTest_275 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that NewDeclaration with nullptr returns a declaration with default value
TEST_F(NewDeclarationTest_275, NullStrReturnsDefaultDeclaration_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_STREQ(dec->Value(), "xml version=\"1.0\" encoding=\"UTF-8\"");
}

// Test that NewDeclaration with a custom string returns a declaration with that string
TEST_F(NewDeclarationTest_275, CustomStrReturnsCustomDeclaration_275) {
    const char* customStr = "xml version=\"1.1\" encoding=\"UTF-16\"";
    XMLDeclaration* dec = doc.NewDeclaration(customStr);
    ASSERT_NE(dec, nullptr);
    EXPECT_STREQ(dec->Value(), customStr);
}

// Test that NewDeclaration with an empty string returns a declaration with empty value
TEST_F(NewDeclarationTest_275, EmptyStrReturnsEmptyDeclaration_275) {
    XMLDeclaration* dec = doc.NewDeclaration("");
    ASSERT_NE(dec, nullptr);
    EXPECT_STREQ(dec->Value(), "");
}

// Test that the returned node is indeed a declaration (ToDeclaration should return non-null)
TEST_F(NewDeclarationTest_275, ReturnedNodeIsDeclarationType_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_NE(dec->ToDeclaration(), nullptr);
    EXPECT_EQ(dec->ToElement(), nullptr);
    EXPECT_EQ(dec->ToComment(), nullptr);
    EXPECT_EQ(dec->ToText(), nullptr);
    EXPECT_EQ(dec->ToDocument(), nullptr);
    EXPECT_EQ(dec->ToUnknown(), nullptr);
}

// Test that the declaration is initially unattached (no parent)
TEST_F(NewDeclarationTest_275, DeclarationHasNoParent_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_EQ(dec->Parent(), nullptr);
}

// Test that the declaration can be inserted into the document
TEST_F(NewDeclarationTest_275, DeclarationCanBeInsertedIntoDocument_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    XMLNode* result = doc.InsertFirstChild(dec);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(dec->Parent(), &doc);
}

// Test that multiple declarations can be created
TEST_F(NewDeclarationTest_275, MultipleDeclarationsCanBeCreated_275) {
    XMLDeclaration* dec1 = doc.NewDeclaration("xml version=\"1.0\"");
    XMLDeclaration* dec2 = doc.NewDeclaration("xml version=\"1.1\"");
    ASSERT_NE(dec1, nullptr);
    ASSERT_NE(dec2, nullptr);
    EXPECT_NE(dec1, dec2);
    EXPECT_STREQ(dec1->Value(), "xml version=\"1.0\"");
    EXPECT_STREQ(dec2->Value(), "xml version=\"1.1\"");
}

// Test that the declaration belongs to the correct document
TEST_F(NewDeclarationTest_275, DeclarationBelongsToDocument_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_EQ(dec->GetDocument(), &doc);
}

// Test that NewDeclaration with a very long string works
TEST_F(NewDeclarationTest_275, LongStringDeclaration_275) {
    std::string longStr(1000, 'a');
    XMLDeclaration* dec = doc.NewDeclaration(longStr.c_str());
    ASSERT_NE(dec, nullptr);
    EXPECT_STREQ(dec->Value(), longStr.c_str());
}

// Test that the declaration can be deleted via the document
TEST_F(NewDeclarationTest_275, DeclarationCanBeDeleted_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    doc.InsertFirstChild(dec);
    EXPECT_FALSE(doc.NoChildren());
    doc.DeleteChild(dec);
    EXPECT_TRUE(doc.NoChildren());
}

// Test declaration with special characters in string
TEST_F(NewDeclarationTest_275, SpecialCharactersInDeclaration_275) {
    const char* specialStr = "xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"";
    XMLDeclaration* dec = doc.NewDeclaration(specialStr);
    ASSERT_NE(dec, nullptr);
    EXPECT_STREQ(dec->Value(), specialStr);
}

// Test that declaration's GetLineNum returns 0 for a newly created node
TEST_F(NewDeclarationTest_275, NewDeclarationLineNumIsZero_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_EQ(dec->GetLineNum(), 0);
}

// Test that declaration has no children
TEST_F(NewDeclarationTest_275, DeclarationHasNoChildren_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_TRUE(dec->NoChildren());
    EXPECT_EQ(dec->FirstChild(), nullptr);
    EXPECT_EQ(dec->LastChild(), nullptr);
}

// Test that declaration has no siblings when unattached
TEST_F(NewDeclarationTest_275, DeclarationHasNoSiblingsWhenUnattached_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    ASSERT_NE(dec, nullptr);
    EXPECT_EQ(dec->PreviousSibling(), nullptr);
    EXPECT_EQ(dec->NextSibling(), nullptr);
}

// Test round-trip: create declaration, insert, print, parse
TEST_F(NewDeclarationTest_275, DeclarationRoundTrip_275) {
    XMLDeclaration* dec = doc.NewDeclaration(nullptr);
    doc.InsertFirstChild(dec);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    XMLError err = doc2.Parse(printer.CStr());
    EXPECT_EQ(err, XML_SUCCESS);
}

// Test that we can create a declaration and then clear the document
TEST_F(NewDeclarationTest_275, ClearDocumentAfterDeclaration_275) {
    XMLDeclaration* dec = doc.NewDeclaration("xml version=\"1.0\"");
    doc.InsertFirstChild(dec);
    EXPECT_FALSE(doc.NoChildren());
    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
}

// Test DeepClone of a declaration
TEST_F(NewDeclarationTest_275, DeepCloneDeclaration_275) {
    XMLDeclaration* dec = doc.NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    doc.InsertFirstChild(dec);
    
    XMLDocument doc2;
    doc.DeepCopy(&doc2);
    
    const XMLNode* firstChild = doc2.FirstChild();
    ASSERT_NE(firstChild, nullptr);
    const XMLDeclaration* clonedDec = firstChild->ToDeclaration();
    ASSERT_NE(clonedDec, nullptr);
    EXPECT_STREQ(clonedDec->Value(), "xml version=\"1.0\" encoding=\"UTF-8\"");
}
