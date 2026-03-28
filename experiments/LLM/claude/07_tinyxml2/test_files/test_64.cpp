#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextTest_64 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLTextTest_64, DefaultCDataIsFalse_64) {
    // Create a text node and verify CData is false by default
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextTest_64, SetCDataTrue_64) {
    // Set CData to true and verify
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextTest_64, SetCDataFalse_64) {
    // Set CData to false explicitly and verify
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextTest_64, SetCDataToggle_64) {
    // Toggle CData between true and false
    XMLDocument doc;
    doc.Parse("<root>Some text</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    EXPECT_FALSE(text->CData());
    
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
    
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
    
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextTest_64, SetCDataTrueTwice_64) {
    // Setting CData to true twice should still be true
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    text->SetCData(true);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextTest_64, SetCDataFalseTwice_64) {
    // Setting CData to false twice should still be false
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    text->SetCData(false);
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextTest_64, ToTextReturnsNonNull_64) {
    // Verify ToText returns the XMLText node itself
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    XMLNode* node = doc.FirstChildElement("root")->FirstChild();
    ASSERT_NE(node, nullptr);
    XMLText* text = node->ToText();
    ASSERT_NE(text, nullptr);
}

TEST_F(XMLTextTest_64, ParseCDataSection_64) {
    // Parse a CDATA section and verify CData() returns true
    XMLDocument doc;
    doc.Parse("<root><![CDATA[Some CDATA content]]></root>");
    ASSERT_EQ(doc.ErrorID(), XML_SUCCESS);
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextTest_64, ShallowClonePreservesCData_64) {
    // Verify that ShallowClone preserves the CData flag
    XMLDocument doc;
    doc.Parse("<root>Hello</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    text->SetCData(true);
    
    XMLNode* clone = text->ShallowClone(&doc);
    ASSERT_NE(clone, nullptr);
    XMLText* clonedText = clone->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_TRUE(clonedText->CData());
    
    // Clean up - the clone is not attached to the document tree
    // tinyxml2 manages memory through the document
}

TEST_F(XMLTextTest_64, ShallowEqualSameCData_64) {
    // Two text nodes with same content and same CData flag should be ShallowEqual
    XMLDocument doc1;
    doc1.Parse("<root>Hello</root>");
    XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text1, nullptr);
    
    XMLDocument doc2;
    doc2.Parse("<root>Hello</root>");
    XMLText* text2 = doc2.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text2, nullptr);
    
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

TEST_F(XMLTextTest_64, ShallowEqualDifferentCData_64) {
    // Two text nodes with same content but different CData flags
    XMLDocument doc1;
    doc1.Parse("<root>Hello</root>");
    XMLText* text1 = doc1.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text1, nullptr);
    text1->SetCData(true);
    
    XMLDocument doc2;
    doc2.Parse("<root>Hello</root>");
    XMLText* text2 = doc2.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text2, nullptr);
    text2->SetCData(false);
    
    // They have different CData flags, so they may not be ShallowEqual
    // This tests observable behavior
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

TEST_F(XMLTextTest_64, AcceptVisitor_64) {
    // Test that Accept works with a printer visitor
    XMLDocument doc;
    doc.Parse("<root>Hello World</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_STRNE(output, "");
}

TEST_F(XMLTextTest_64, CDataAcceptVisitor_64) {
    // Test that a CData text node prints correctly through Accept
    XMLDocument doc;
    doc.Parse("<root><![CDATA[Hello <World>]]></root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
    
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    // The output should contain CDATA markers
    EXPECT_NE(std::string(output).find("CDATA"), std::string::npos);
}

TEST_F(XMLTextTest_64, ValueOfTextNode_64) {
    // Verify text node value
    XMLDocument doc;
    doc.Parse("<root>TestValue</root>");
    XMLText* text = doc.FirstChildElement("root")->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "TestValue");
}

TEST_F(XMLTextTest_64, EmptyTextNode_64) {
    // Test with empty text
    XMLDocument doc;
    doc.Parse("<root></root>");
    // Empty element might not have a text child
    XMLNode* child = doc.FirstChildElement("root")->FirstChild();
    // If there's no child, that's valid behavior
    if (child != nullptr) {
        XMLText* text = child->ToText();
        if (text != nullptr) {
            EXPECT_FALSE(text->CData());
        }
    }
}

TEST_F(XMLTextTest_64, NewTextNodeViaDocument_64) {
    // Create a new text node via the document
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    
    XMLText* text = doc.NewText("New text content");
    ASSERT_NE(text, nullptr);
    root->InsertFirstChild(text);
    
    EXPECT_FALSE(text->CData());
    EXPECT_STREQ(text->Value(), "New text content");
    
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}
