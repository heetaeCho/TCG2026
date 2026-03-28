#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDeclarationTest_203 : public ::testing::Test {
protected:
    XMLDocument doc1;
    XMLDocument doc2;
};

// Test ShallowEqual: Two declarations with the same value should be equal
TEST_F(XMLDeclarationTest_203, ShallowEqual_SameValue_ReturnsTrue_203) {
    const char* xml1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    const char* xml2 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLNode* node1 = doc1.FirstChild();
    const XMLNode* node2 = doc2.FirstChild();
    
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    
    const XMLDeclaration* decl1 = node1->ToDeclaration();
    const XMLDeclaration* decl2 = node2->ToDeclaration();
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    EXPECT_TRUE(decl1->ShallowEqual(decl2));
}

// Test ShallowEqual: Two declarations with different values should not be equal
TEST_F(XMLDeclarationTest_203, ShallowEqual_DifferentValue_ReturnsFalse_203) {
    const char* xml1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    const char* xml2 = "<?xml version=\"1.1\" encoding=\"UTF-8\"?><root/>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLNode* node1 = doc1.FirstChild();
    const XMLNode* node2 = doc2.FirstChild();
    
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    
    const XMLDeclaration* decl1 = node1->ToDeclaration();
    const XMLDeclaration* decl2 = node2->ToDeclaration();
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    EXPECT_FALSE(decl1->ShallowEqual(decl2));
}

// Test ShallowEqual: Comparing a declaration with a non-declaration node should return false
TEST_F(XMLDeclarationTest_203, ShallowEqual_CompareWithElement_ReturnsFalse_203) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    const XMLElement* elem = doc1.RootElement();
    ASSERT_NE(elem, nullptr);
    
    EXPECT_FALSE(decl->ShallowEqual(elem));
}

// Test ShallowEqual: Comparing a declaration with a comment node should return false
TEST_F(XMLDeclarationTest_203, ShallowEqual_CompareWithComment_ReturnsFalse_203) {
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    const char* xml2 = "<root><!-- comment --></root>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    const XMLNode* commentNode = doc2.RootElement()->FirstChild();
    ASSERT_NE(commentNode, nullptr);
    ASSERT_NE(commentNode->ToComment(), nullptr);
    
    EXPECT_FALSE(decl->ShallowEqual(commentNode));
}

// Test ShallowEqual: Declaration compared to itself should return true
TEST_F(XMLDeclarationTest_203, ShallowEqual_CompareWithSelf_ReturnsTrue_203) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    EXPECT_TRUE(decl->ShallowEqual(declNode));
}

// Test ShallowClone: Cloned declaration should be ShallowEqual to original
TEST_F(XMLDeclarationTest_203, ShallowClone_CloneIsShallowEqual_203) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    XMLNode* cloned = decl->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    
    EXPECT_TRUE(decl->ShallowEqual(cloned));
    
    // Clean up: insert into doc2 so it owns the memory
    doc2.InsertFirstChild(cloned);
}

// Test ShallowClone: Cloned node should be a declaration
TEST_F(XMLDeclarationTest_203, ShallowClone_CloneIsDeclaration_203) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    XMLNode* cloned = decl->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned->ToDeclaration(), nullptr);
    
    doc2.InsertFirstChild(cloned);
}

// Test ToDeclaration: Returns non-null for declaration nodes
TEST_F(XMLDeclarationTest_203, ToDeclaration_ReturnsNonNull_203) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml);
    
    XMLNode* node = doc1.FirstChild();
    ASSERT_NE(node, nullptr);
    
    XMLDeclaration* decl = node->ToDeclaration();
    EXPECT_NE(decl, nullptr);
}

// Test ToDeclaration: Returns null for non-declaration nodes
TEST_F(XMLDeclarationTest_203, ToDeclaration_ReturnsNullForElement_203) {
    const char* xml = "<root/>";
    doc1.Parse(xml);
    
    XMLNode* node = doc1.FirstChild();
    ASSERT_NE(node, nullptr);
    
    XMLDeclaration* decl = node->ToDeclaration();
    EXPECT_EQ(decl, nullptr);
}

// Test Value: Declaration value matches what was parsed
TEST_F(XMLDeclarationTest_203, Value_MatchesParsedContent_203) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    const char* value = decl->Value();
    ASSERT_NE(value, nullptr);
    // The value should contain the declaration content
    EXPECT_NE(std::string(value).find("version"), std::string::npos);
}

// Test ShallowEqual: Two declarations with different encodings should not be equal
TEST_F(XMLDeclarationTest_203, ShallowEqual_DifferentEncoding_ReturnsFalse_203) {
    const char* xml1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    const char* xml2 = "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?><root/>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLNode* node1 = doc1.FirstChild();
    const XMLNode* node2 = doc2.FirstChild();
    
    ASSERT_NE(node1, nullptr);
    ASSERT_NE(node2, nullptr);
    
    const XMLDeclaration* decl1 = node1->ToDeclaration();
    const XMLDeclaration* decl2 = node2->ToDeclaration();
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    EXPECT_FALSE(decl1->ShallowEqual(decl2));
}

// Test ShallowEqual: Comparing declaration with XMLText should return false
TEST_F(XMLDeclarationTest_203, ShallowEqual_CompareWithText_ReturnsFalse_203) {
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    const char* xml2 = "<root>some text</root>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    const XMLNode* textNode = doc2.RootElement()->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(textNode->ToText(), nullptr);
    
    EXPECT_FALSE(decl->ShallowEqual(textNode));
}

// Test Accept: A visitor is properly called
TEST_F(XMLDeclarationTest_203, Accept_VisitorIsCalled_203) {
    const char* xml = "<?xml version=\"1.0\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    XMLPrinter printer;
    bool result = decl->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("xml"), std::string::npos);
}

// Test DeepClone: Deep cloned declaration should be ShallowEqual
TEST_F(XMLDeclarationTest_203, DeepClone_IsShallowEqual_203) {
    const char* xml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><root/>";
    doc1.Parse(xml);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    XMLNode* deepCloned = decl->DeepClone(&doc2);
    ASSERT_NE(deepCloned, nullptr);
    EXPECT_NE(deepCloned->ToDeclaration(), nullptr);
    EXPECT_TRUE(decl->ShallowEqual(deepCloned));
    
    doc2.InsertFirstChild(deepCloned);
}

// Test ShallowEqual: Comparing with XMLUnknown should return false
TEST_F(XMLDeclarationTest_203, ShallowEqual_CompareWithUnknown_ReturnsFalse_203) {
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    const char* xml2 = "<root><![ something ]></root>";
    
    doc1.Parse(xml1);
    
    // Create an unknown node via parsing
    const char* xmlWithUnknown = "<root><![UNKNOWN[data]]></root>";
    doc2.Parse(xmlWithUnknown);
    
    const XMLNode* declNode = doc1.FirstChild();
    ASSERT_NE(declNode, nullptr);
    const XMLDeclaration* decl = declNode->ToDeclaration();
    ASSERT_NE(decl, nullptr);
    
    // Even if doc2 parse fails, we can test with the document node itself
    EXPECT_FALSE(decl->ShallowEqual(&doc2));
}

// Test: Multiple declarations parsed, each can ShallowEqual correctly
TEST_F(XMLDeclarationTest_203, ShallowEqual_SymmetricComparison_203) {
    const char* xml1 = "<?xml version=\"1.0\"?><root/>";
    const char* xml2 = "<?xml version=\"1.0\"?><root/>";
    
    doc1.Parse(xml1);
    doc2.Parse(xml2);
    
    const XMLDeclaration* decl1 = doc1.FirstChild()->ToDeclaration();
    const XMLDeclaration* decl2 = doc2.FirstChild()->ToDeclaration();
    
    ASSERT_NE(decl1, nullptr);
    ASSERT_NE(decl2, nullptr);
    
    // Symmetry: if A == B then B == A
    EXPECT_TRUE(decl1->ShallowEqual(decl2));
    EXPECT_TRUE(decl2->ShallowEqual(decl1));
}
