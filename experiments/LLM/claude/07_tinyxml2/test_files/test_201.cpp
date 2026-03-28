#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDeclarationTest_201 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test: Parse a valid XML declaration
TEST_F(XMLDeclarationTest_201, ParseValidDeclaration_201) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    EXPECT_STREQ("xml version=\"1.0\" encoding=\"UTF-8\"", decl->Value());
}

// Test: Parse XML declaration with only version
TEST_F(XMLDeclarationTest_201, ParseDeclarationVersionOnly_201) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    EXPECT_STREQ("xml version=\"1.0\"", decl->Value());
}

// Test: Parse XML declaration with all attributes
TEST_F(XMLDeclarationTest_201, ParseDeclarationAllAttributes_201) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    EXPECT_STREQ("xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"", decl->Value());
}

// Test: Parse XML with no closing ?> should fail
TEST_F(XMLDeclarationTest_201, ParseDeclarationMissingClose_201) {
    const char* xml = "<?xml version=\"1.0\"";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_EQ(XML_ERROR_PARSING_DECLARATION, err);
}

// Test: Parse empty XML declaration
TEST_F(XMLDeclarationTest_201, ParseEmptyDeclaration_201) {
    const char* xml = "<?xml?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
}

// Test: Document with no declaration
TEST_F(XMLDeclarationTest_201, NoDeclaration_201) {
    const char* xml = "<root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLNode* firstChild = doc.FirstChild();
    ASSERT_NE(nullptr, firstChild);
    const XMLDeclaration* decl = firstChild->ToDeclaration();
    EXPECT_EQ(nullptr, decl);
}

// Test: Declaration with newlines should be normalized
TEST_F(XMLDeclarationTest_201, ParseDeclarationWithNewlines_201) {
    const char* xml = "<?xml version=\"1.0\"\nencoding=\"UTF-8\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
}

// Test: Declaration followed by content
TEST_F(XMLDeclarationTest_201, DeclarationFollowedByElement_201) {
    const char* xml = "<?xml version=\"1.0\"?><root><child/></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
}

// Test: Truncated declaration with only opening
TEST_F(XMLDeclarationTest_201, ParseDeclarationTruncated_201) {
    const char* xml = "<?xml";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
}

// Test: Declaration with special characters in encoding
TEST_F(XMLDeclarationTest_201, ParseDeclarationSpecialEncoding_201) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    const XMLDeclaration* decl = doc.FirstChild()->ToDeclaration();
    ASSERT_NE(nullptr, decl);
    EXPECT_STREQ("xml version=\"1.0\" encoding=\"ISO-8859-1\"", decl->Value());
}

// Test: Error line number is set on parse failure
TEST_F(XMLDeclarationTest_201, ParseDeclarationErrorSetsLineNumber_201) {
    const char* xml = "<?xml version=\"1.0\"";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_ERROR_PARSING_DECLARATION, err);
    EXPECT_NE(0, doc.ErrorLineNum());
}

// Test: Processing instruction that is not xml declaration
TEST_F(XMLDeclarationTest_201, ProcessingInstructionNotDeclaration_201) {
    const char* xml = "<root><?pi target?></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
}
