#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class InsertNewTextTest_261 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that InsertNewText returns a non-null XMLText pointer for normal text
TEST_F(InsertNewTextTest_261, ReturnsNonNullForNormalText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("Hello, World!");
    ASSERT_NE(text, nullptr);
}

// Test that the inserted text node has the correct value
TEST_F(InsertNewTextTest_261, InsertedTextHasCorrectValue_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("Hello, World!");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Hello, World!");
}

// Test that InsertNewText with empty string works
TEST_F(InsertNewTextTest_261, EmptyStringText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "");
}

// Test that the text node is added as a child of the element
TEST_F(InsertNewTextTest_261, TextIsChildOfElement_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("child text");
    ASSERT_NE(text, nullptr);
    
    const XMLNode* firstChild = root->FirstChild();
    ASSERT_NE(firstChild, nullptr);
    EXPECT_EQ(firstChild->ToText(), text);
}

// Test that InsertNewText appends to end (after existing children)
TEST_F(InsertNewTextTest_261, TextIsAppendedAtEnd_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = doc.NewElement("child");
    root->InsertEndChild(child);
    
    XMLText* text = root->InsertNewText("appended text");
    ASSERT_NE(text, nullptr);
    
    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToText(), text);
}

// Test multiple InsertNewText calls
TEST_F(InsertNewTextTest_261, MultipleTextInsertions_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text1 = root->InsertNewText("first");
    XMLText* text2 = root->InsertNewText("second");
    XMLText* text3 = root->InsertNewText("third");
    
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    ASSERT_NE(text3, nullptr);
    
    EXPECT_STREQ(text1->Value(), "first");
    EXPECT_STREQ(text2->Value(), "second");
    EXPECT_STREQ(text3->Value(), "third");
    
    // Verify order
    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first->ToText(), text1);
    
    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->ToText(), text2);
    
    const XMLNode* third = second->NextSibling();
    ASSERT_NE(third, nullptr);
    EXPECT_EQ(third->ToText(), text3);
}

// Test InsertNewText with special characters
TEST_F(InsertNewTextTest_261, SpecialCharactersInText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("Hello <>&\"' World");
    ASSERT_NE(text, nullptr);
    // The value should contain the original text
    EXPECT_NE(text->Value(), nullptr);
}

// Test InsertNewText with whitespace text
TEST_F(InsertNewTextTest_261, WhitespaceText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("   \t\n  ");
    ASSERT_NE(text, nullptr);
}

// Test that the text node's parent is the element
TEST_F(InsertNewTextTest_261, TextParentIsElement_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("test");
    ASSERT_NE(text, nullptr);
    EXPECT_EQ(text->Parent(), root);
}

// Test InsertNewText with long text
TEST_F(InsertNewTextTest_261, LongText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    std::string longStr(10000, 'a');
    XMLText* text = root->InsertNewText(longStr.c_str());
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), longStr.c_str());
}

// Test that InsertNewText works with parsed document
TEST_F(InsertNewTextTest_261, WorksWithParsedDocument_261) {
    const char* xml = "<root><child/></root>";
    doc.Parse(xml);
    ASSERT_FALSE(doc.Error());
    
    XMLElement* root = doc.RootElement();
    ASSERT_NE(root, nullptr);
    
    XMLText* text = root->InsertNewText("new text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "new text");
    
    // The text should be the last child
    const XMLNode* lastChild = root->LastChild();
    ASSERT_NE(lastChild, nullptr);
    EXPECT_EQ(lastChild->ToText(), text);
}

// Test that element is not empty after inserting text
TEST_F(InsertNewTextTest_261, ElementNotEmptyAfterInsert_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    EXPECT_TRUE(root->NoChildren());
    
    XMLText* text = root->InsertNewText("content");
    ASSERT_NE(text, nullptr);
    
    EXPECT_FALSE(root->NoChildren());
}

// Test GetText after InsertNewText
TEST_F(InsertNewTextTest_261, GetTextAfterInsertNewText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    root->InsertNewText("Hello");
    
    const char* getText = root->GetText();
    ASSERT_NE(getText, nullptr);
    EXPECT_STREQ(getText, "Hello");
}

// Test InsertNewText with Unicode-like content
TEST_F(InsertNewTextTest_261, UnicodeContent_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLText* text = root->InsertNewText("Héllo Wörld");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "Héllo Wörld");
}

// Test InsertNewText on nested elements
TEST_F(InsertNewTextTest_261, NestedElementText_261) {
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    
    XMLElement* child = root->InsertNewChildElement("child");
    ASSERT_NE(child, nullptr);
    
    XMLText* text = child->InsertNewText("nested text");
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text->Value(), "nested text");
    EXPECT_EQ(text->Parent(), child);
}
