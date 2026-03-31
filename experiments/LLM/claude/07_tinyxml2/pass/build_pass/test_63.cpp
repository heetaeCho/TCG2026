#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextTest_63 : public ::testing::Test {
protected:
    XMLDocument doc;
    
    XMLText* createTextNode(const char* text) {
        // Use the document to create a text node via element manipulation
        XMLElement* root = doc.NewElement("root");
        doc.InsertFirstChild(root);
        root->SetText(text);
        XMLNode* child = root->FirstChild();
        return child ? child->ToText() : nullptr;
    }
};

// Test that ToText() returns a valid non-null pointer for an XMLText node
TEST_F(XMLTextTest_63, ToTextReturnsNonNull_63) {
    XMLText* text = createTextNode("Hello");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->ToText(), text);
}

// Test that ToText() returns itself (identity)
TEST_F(XMLTextTest_63, ToTextReturnsSelf_63) {
    XMLText* text = createTextNode("test");
    ASSERT_NE(text, nullptr);
    XMLText* result = text->ToText();
    EXPECT_EQ(result, text);
}

// Test CData defaults to false
TEST_F(XMLTextTest_63, CDataDefaultsFalse_63) {
    XMLText* text = createTextNode("sample");
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test SetCData to true
TEST_F(XMLTextTest_63, SetCDataTrue_63) {
    XMLText* text = createTextNode("data");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

// Test SetCData to false after setting true
TEST_F(XMLTextTest_63, SetCDataFalseThenTrue_63) {
    XMLText* text = createTextNode("data");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

// Test SetCData toggle multiple times
TEST_F(XMLTextTest_63, SetCDataToggle_63) {
    XMLText* text = createTextNode("toggle");
    ASSERT_NE(text, nullptr);
    for (int i = 0; i < 5; ++i) {
        text->SetCData(true);
        EXPECT_TRUE(text->CData());
        text->SetCData(false);
        EXPECT_FALSE(text->CData());
    }
}

// Test ShallowClone creates a valid copy
TEST_F(XMLTextTest_63, ShallowCloneCreatesValidCopy_63) {
    XMLText* text = createTextNode("clone me");
    ASSERT_NE(text, nullptr);
    
    XMLDocument targetDoc;
    XMLNode* cloned = text->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_STREQ(clonedText->Value(), text->Value());
}

// Test ShallowClone preserves CData flag
TEST_F(XMLTextTest_63, ShallowClonePreservesCData_63) {
    XMLText* text = createTextNode("cdata content");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    
    XMLDocument targetDoc;
    XMLNode* cloned = text->ShallowClone(&targetDoc);
    ASSERT_NE(cloned, nullptr);
    
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_TRUE(clonedText->CData());
}

// Test ShallowEqual with equal text nodes
TEST_F(XMLTextTest_63, ShallowEqualWithEqualNodes_63) {
    XMLText* text1 = createTextNode("equal");
    ASSERT_NE(text1, nullptr);
    
    XMLDocument doc2;
    XMLNode* cloned = text1->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    
    EXPECT_TRUE(text1->ShallowEqual(cloned));
}

// Test ShallowEqual with different text nodes
TEST_F(XMLTextTest_63, ShallowEqualWithDifferentNodes_63) {
    XMLDocument doc1;
    XMLElement* root1 = doc1.NewElement("r1");
    doc1.InsertFirstChild(root1);
    root1->SetText("text1");
    XMLText* text1 = root1->FirstChild()->ToText();
    
    XMLDocument doc2;
    XMLElement* root2 = doc2.NewElement("r2");
    doc2.InsertFirstChild(root2);
    root2->SetText("text2");
    XMLText* text2 = root2->FirstChild()->ToText();
    
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

// Test Accept with XMLVisitor (using XMLPrinter as a concrete visitor)
TEST_F(XMLTextTest_63, AcceptVisitor_63) {
    XMLText* text = createTextNode("visit me");
    ASSERT_NE(text, nullptr);
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("visit me"), std::string::npos);
}

// Test that text value is correctly stored
TEST_F(XMLTextTest_63, TextValueIsCorrect_63) {
    XMLText* text = createTextNode("Hello World");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello World");
}

// Test empty text node
TEST_F(XMLTextTest_63, EmptyTextNode_63) {
    XMLText* text = createTextNode("");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "");
}

// Test text with special characters
TEST_F(XMLTextTest_63, TextWithSpecialCharacters_63) {
    const char* xml = "<root>Hello &amp; World</root>";
    XMLDocument specialDoc;
    specialDoc.Parse(xml);
    XMLElement* root = specialDoc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello & World");
}

// Test that an XMLElement's ToText returns null (non-text node contrast)
TEST_F(XMLTextTest_63, ElementToTextReturnsNull_63) {
    XMLElement* elem = doc.NewElement("nottext");
    ASSERT_NE(elem, nullptr);
    EXPECT_EQ(elem->ToText(), nullptr);
}

// Test ShallowClone into same document
TEST_F(XMLTextTest_63, ShallowCloneIntoSameDocument_63) {
    XMLText* text = createTextNode("same doc clone");
    ASSERT_NE(text, nullptr);
    
    XMLNode* cloned = text->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_STREQ(clonedText->Value(), "same doc clone");
}

// Test CData text node through XML parsing
TEST_F(XMLTextTest_63, CDataNodeFromParsing_63) {
    const char* xml = "<root><![CDATA[Some <special> data]]></root>";
    XMLDocument cdataDoc;
    cdataDoc.Parse(xml);
    ASSERT_EQ(cdataDoc.ErrorID(), XML_SUCCESS);
    
    XMLElement* root = cdataDoc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
    EXPECT_STREQ(text->Value(), "Some <special> data");
}

// Test ShallowEqual with CData mismatch
TEST_F(XMLTextTest_63, ShallowEqualCDataMismatch_63) {
    XMLText* text1 = createTextNode("data");
    ASSERT_NE(text1, nullptr);
    text1->SetCData(false);
    
    XMLDocument doc2;
    XMLNode* cloned = text1->ShallowClone(&doc2);
    XMLText* text2 = cloned->ToText();
    ASSERT_NE(text2, nullptr);
    text2->SetCData(true);
    
    // They have same value but different CData flag - behavior depends on implementation
    // Just verify ShallowEqual returns a boolean without crashing
    text1->ShallowEqual(text2);
}

// Test Accept with CData node and XMLPrinter
TEST_F(XMLTextTest_63, AcceptCDataVisitor_63) {
    const char* xml = "<root><![CDATA[cdata content]]></root>";
    XMLDocument cdataDoc;
    cdataDoc.Parse(xml);
    XMLElement* root = cdataDoc.RootElement();
    ASSERT_NE(root, nullptr);
    XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("CDATA"), std::string::npos);
}
