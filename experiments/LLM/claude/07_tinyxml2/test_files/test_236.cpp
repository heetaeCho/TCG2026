#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextTest_236 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test SetText with const char* on an element with no children
TEST_F(XMLElementSetTextTest_236, SetTextOnEmptyElement_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("Hello World");
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

// Test SetText replaces existing text content
TEST_F(XMLElementSetTextTest_236, SetTextReplacesExistingText_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("Original");
    EXPECT_STREQ(elem->GetText(), "Original");
    
    elem->SetText("Replaced");
    EXPECT_STREQ(elem->GetText(), "Replaced");
}

// Test SetText with empty string
TEST_F(XMLElementSetTextTest_236, SetTextWithEmptyString_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("");
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "");
}

// Test SetText with int value
TEST_F(XMLElementSetTextTest_236, SetTextWithInt_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(42);
    
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 42);
}

// Test SetText with negative int
TEST_F(XMLElementSetTextTest_236, SetTextWithNegativeInt_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(-100);
    
    int val = 0;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, -100);
}

// Test SetText with unsigned int
TEST_F(XMLElementSetTextTest_236, SetTextWithUnsignedInt_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText((unsigned)123u);
    
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 123u);
}

// Test SetText with int64_t
TEST_F(XMLElementSetTextTest_236, SetTextWithInt64_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    int64_t big = 9223372036854775807LL;
    elem->SetText(big);
    
    int64_t val = 0;
    XMLError err = elem->QueryInt64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, big);
}

// Test SetText with uint64_t
TEST_F(XMLElementSetTextTest_236, SetTextWithUint64_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    uint64_t big = 18446744073709551615ULL;
    elem->SetText(big);
    
    uint64_t val = 0;
    XMLError err = elem->QueryUnsigned64Text(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, big);
}

// Test SetText with bool true
TEST_F(XMLElementSetTextTest_236, SetTextWithBoolTrue_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(true);
    
    bool val = false;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(val);
}

// Test SetText with bool false
TEST_F(XMLElementSetTextTest_236, SetTextWithBoolFalse_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(false);
    
    bool val = true;
    XMLError err = elem->QueryBoolText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(val);
}

// Test SetText with double
TEST_F(XMLElementSetTextTest_236, SetTextWithDouble_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(3.14159);
    
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14159, 1e-5);
}

// Test SetText with float
TEST_F(XMLElementSetTextTest_236, SetTextWithFloat_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(2.5f);
    
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 2.5f, 1e-5f);
}

// Test SetText when element already has a child element (not text)
TEST_F(XMLElementSetTextTest_236, SetTextOnElementWithChildElement_236) {
    XMLElement* parent = doc.NewElement("parent");
    doc.InsertEndChild(parent);
    
    XMLElement* child = doc.NewElement("child");
    parent->InsertEndChild(child);
    
    // First child is an element, not text, so SetText should insert a text node as first child
    parent->SetText("New Text");
    
    const char* text = parent->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "New Text");
}

// Test SetText with a long string
TEST_F(XMLElementSetTextTest_236, SetTextWithLongString_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    std::string longStr(1000, 'A');
    elem->SetText(longStr.c_str());
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, longStr.c_str());
}

// Test SetText multiple times with different types
TEST_F(XMLElementSetTextTest_236, SetTextMultipleTimes_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("First");
    EXPECT_STREQ(elem->GetText(), "First");
    
    elem->SetText(42);
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
    
    elem->SetText("Back to string");
    EXPECT_STREQ(elem->GetText(), "Back to string");
}

// Test SetText preserves element name
TEST_F(XMLElementSetTextTest_236, SetTextPreservesElementName_236) {
    XMLElement* elem = doc.NewElement("myElement");
    doc.InsertEndChild(elem);
    
    elem->SetText("some text");
    
    EXPECT_STREQ(elem->Name(), "myElement");
    EXPECT_STREQ(elem->GetText(), "some text");
}

// Test SetText preserves attributes
TEST_F(XMLElementSetTextTest_236, SetTextPreservesAttributes_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetAttribute("key", "value");
    elem->SetText("content");
    
    EXPECT_STREQ(elem->Attribute("key"), "value");
    EXPECT_STREQ(elem->GetText(), "content");
}

// Test GetText returns nullptr for element with no text
TEST_F(XMLElementSetTextTest_236, GetTextReturnsNullForNoText_236) {
    XMLElement* elem = doc.NewElement("empty");
    doc.InsertEndChild(elem);
    
    EXPECT_EQ(elem->GetText(), nullptr);
}

// Test SetText with special characters
TEST_F(XMLElementSetTextTest_236, SetTextWithSpecialCharacters_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("Hello <World> & \"Friends\"");
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello <World> & \"Friends\"");
}

// Test SetText via Parse and then modify
TEST_F(XMLElementSetTextTest_236, SetTextOnParsedDocument_236) {
    const char* xml = "<root><item>Original</item></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* item = doc.FirstChildElement("root")->FirstChildElement("item");
    ASSERT_NE(item, nullptr);
    EXPECT_STREQ(item->GetText(), "Original");
    
    item->SetText("Modified");
    EXPECT_STREQ(item->GetText(), "Modified");
}

// Test SetText with zero int
TEST_F(XMLElementSetTextTest_236, SetTextWithZeroInt_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(0);
    
    int val = -1;
    XMLError err = elem->QueryIntText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 0);
}

// Test SetText with double zero
TEST_F(XMLElementSetTextTest_236, SetTextWithDoubleZero_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText(0.0);
    
    double val = -1.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 0.0, 1e-10);
}

// Test that SetText on element with text child modifies the text node value
TEST_F(XMLElementSetTextTest_236, SetTextModifiesExistingTextNode_236) {
    const char* xml = "<root>Old Text</root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(err, XML_SUCCESS);
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Old Text");
    
    root->SetText("New Text");
    EXPECT_STREQ(root->GetText(), "New Text");
    
    // Verify no extra children were added
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->NextSibling(), nullptr);
}

// Test SetText then verify through printing
TEST_F(XMLElementSetTextTest_236, SetTextVerifyThroughPrint_236) {
    XMLElement* elem = doc.NewElement("item");
    doc.InsertEndChild(elem);
    
    elem->SetText("Printed Text");
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    const char* result = printer.CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_NE(std::string(result).find("Printed Text"), std::string::npos);
}

// Test SetText with whitespace-only string
TEST_F(XMLElementSetTextTest_236, SetTextWithWhitespaceOnly_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("   ");
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "   ");
}

// Test SetText with newlines
TEST_F(XMLElementSetTextTest_236, SetTextWithNewlines_236) {
    XMLElement* elem = doc.NewElement("test");
    doc.InsertEndChild(elem);
    
    elem->SetText("line1\nline2\nline3");
    
    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "line1\nline2\nline3");
}
