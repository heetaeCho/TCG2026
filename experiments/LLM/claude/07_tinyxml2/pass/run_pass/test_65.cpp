#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextTest_65 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that a newly created XMLText node via NewText is not CData by default
TEST_F(XMLTextTest_65, DefaultCDataIsFalse_65) {
    XMLText* text = doc.NewText("Hello");
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test that SetCData(true) makes CData() return true
TEST_F(XMLTextTest_65, SetCDataTrue_65) {
    XMLText* text = doc.NewText("Hello");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

// Test that SetCData(false) makes CData() return false
TEST_F(XMLTextTest_65, SetCDataFalse_65) {
    XMLText* text = doc.NewText("Hello");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

// Test toggling CData multiple times
TEST_F(XMLTextTest_65, ToggleCDataMultipleTimes_65) {
    XMLText* text = doc.NewText("test");
    ASSERT_NE(text, nullptr);
    
    for (int i = 0; i < 5; ++i) {
        text->SetCData(true);
        EXPECT_TRUE(text->CData());
        text->SetCData(false);
        EXPECT_FALSE(text->CData());
    }
}

// Test that ToText() returns non-null for an XMLText node
TEST_F(XMLTextTest_65, ToTextReturnsNonNull_65) {
    XMLText* text = doc.NewText("Hello");
    ASSERT_NE(text, nullptr);
    EXPECT_NE(text->ToText(), nullptr);
    EXPECT_EQ(text->ToText(), text);
}

// Test ShallowClone preserves CData=false
TEST_F(XMLTextTest_65, ShallowClonePreservesCDataFalse_65) {
    XMLText* text = doc.NewText("clone test");
    ASSERT_NE(text, nullptr);
    text->SetCData(false);
    
    XMLNode* cloned = text->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_FALSE(clonedText->CData());
}

// Test ShallowClone preserves CData=true
TEST_F(XMLTextTest_65, ShallowClonePreservesCDataTrue_65) {
    XMLText* text = doc.NewText("clone test");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    
    XMLNode* cloned = text->ShallowClone(&doc);
    ASSERT_NE(cloned, nullptr);
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_TRUE(clonedText->CData());
}

// Test ShallowEqual with matching text nodes
TEST_F(XMLTextTest_65, ShallowEqualMatchingNodes_65) {
    XMLText* text1 = doc.NewText("equal");
    XMLText* text2 = doc.NewText("equal");
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_TRUE(text1->ShallowEqual(text2));
}

// Test ShallowEqual with non-matching text nodes
TEST_F(XMLTextTest_65, ShallowEqualNonMatchingNodes_65) {
    XMLText* text1 = doc.NewText("hello");
    XMLText* text2 = doc.NewText("world");
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_FALSE(text1->ShallowEqual(text2));
}

// Test that parsing a document with CDATA sets CData() to true
TEST_F(XMLTextTest_65, ParseCDataSection_65) {
    const char* xml = "<root><![CDATA[some cdata content]]></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_TRUE(text->CData());
}

// Test that parsing a document with normal text sets CData() to false
TEST_F(XMLTextTest_65, ParseNormalText_65) {
    const char* xml = "<root>normal text</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    XMLText* text = root->FirstChild()->ToText();
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test NewText with empty string
TEST_F(XMLTextTest_65, NewTextWithEmptyString_65) {
    XMLText* text = doc.NewText("");
    ASSERT_NE(text, nullptr);
    EXPECT_FALSE(text->CData());
}

// Test that Accept works with XMLPrinter (basic visitor)
TEST_F(XMLTextTest_65, AcceptWithPrinter_65) {
    XMLText* text = doc.NewText("visitor test");
    ASSERT_NE(text, nullptr);
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
}

// Test Accept with CData text and printer
TEST_F(XMLTextTest_65, AcceptCDataWithPrinter_65) {
    XMLText* text = doc.NewText("cdata visitor test");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    
    XMLPrinter printer;
    bool result = text->Accept(&printer);
    EXPECT_TRUE(result);
    // The printed output should contain CDATA markers
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    EXPECT_NE(std::string(output).find("<![CDATA["), std::string::npos);
}

// Test that SetCData(true) then SetCData(true) is idempotent
TEST_F(XMLTextTest_65, SetCDataTrueTwice_65) {
    XMLText* text = doc.NewText("idempotent");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

// Test that SetCData(false) then SetCData(false) is idempotent
TEST_F(XMLTextTest_65, SetCDataFalseTwice_65) {
    XMLText* text = doc.NewText("idempotent");
    ASSERT_NE(text, nullptr);
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

// Test ShallowClone into a different document
TEST_F(XMLTextTest_65, ShallowCloneToDifferentDocument_65) {
    XMLDocument doc2;
    XMLText* text = doc.NewText("cross doc");
    ASSERT_NE(text, nullptr);
    text->SetCData(true);
    
    XMLNode* cloned = text->ShallowClone(&doc2);
    ASSERT_NE(cloned, nullptr);
    XMLText* clonedText = cloned->ToText();
    ASSERT_NE(clonedText, nullptr);
    EXPECT_TRUE(clonedText->CData());
}

// Test Value() of XMLText node
TEST_F(XMLTextTest_65, TextNodeValue_65) {
    XMLText* text = doc.NewText("my value");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "my value");
}
