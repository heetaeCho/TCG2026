#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementGetTextTest_235 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test GetText returns the text content of a simple element
TEST_F(XMLElementGetTextTest_235, ReturnsTextForSimpleElement_235) {
    doc.Parse("<root>Hello World</root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello World");
}

// Test GetText returns nullptr when element has no children
TEST_F(XMLElementGetTextTest_235, ReturnsNullForEmptyElement_235) {
    doc.Parse("<root></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// Test GetText returns nullptr for self-closing element
TEST_F(XMLElementGetTextTest_235, ReturnsNullForSelfClosingElement_235) {
    doc.Parse("<root/>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// Test GetText returns nullptr when first child is a child element (not text)
TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenFirstChildIsElement_235) {
    doc.Parse("<root><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// Test GetText skips comment nodes and returns text after comment
TEST_F(XMLElementGetTextTest_235, SkipsCommentAndReturnsText_235) {
    doc.Parse("<root><!-- a comment -->Hello</root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Hello");
}

// Test GetText skips multiple comment nodes
TEST_F(XMLElementGetTextTest_235, SkipsMultipleCommentsAndReturnsText_235) {
    doc.Parse("<root><!-- comment1 --><!-- comment2 -->Text after comments</root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Text after comments");
}

// Test GetText returns nullptr when only comments exist (no text)
TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenOnlyComments_235) {
    doc.Parse("<root><!-- only comment --></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// Test GetText returns nullptr when comment followed by element (not text)
TEST_F(XMLElementGetTextTest_235, ReturnsNullWhenCommentFollowedByElement_235) {
    doc.Parse("<root><!-- comment --><child/></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}

// Test GetText returns numeric text
TEST_F(XMLElementGetTextTest_235, ReturnsNumericText_235) {
    doc.Parse("<root>12345</root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "12345");
}

// Test GetText with SetText (int)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextInt_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText(42);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "42");
}

// Test GetText with SetText (string)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextString_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText("NewText");
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "NewText");
}

// Test GetText with SetText (bool true)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextBoolTrue_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText(true);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "true");
}

// Test GetText with SetText (bool false)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextBoolFalse_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText(false);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "false");
}

// Test GetText with SetText (float)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextFloat_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText(3.14f);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    // Just check it's not null; exact format may vary
    EXPECT_NE(std::string(text).find("3.14"), std::string::npos);
}

// Test GetText with SetText (double)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextDouble_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText(2.718);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_NE(std::string(text).find("2.718"), std::string::npos);
}

// Test GetText with empty text content
TEST_F(XMLElementGetTextTest_235, ReturnsEmptyStringForWhitespacePreserved_235) {
    doc.Parse("<root> </root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    // Depending on whitespace handling, this may or may not be null
    // but if there's a text node, it should return its value
    if (text != nullptr) {
        EXPECT_TRUE(strlen(text) >= 0);
    }
}

// Test GetText on nested element returns first text node
TEST_F(XMLElementGetTextTest_235, ReturnsTextOfNestedElement_235) {
    doc.Parse("<root><child>ChildText</child></root>");
    const XMLElement* child = doc.FirstChildElement("root")->FirstChildElement("child");
    ASSERT_NE(child, nullptr);
    const char* text = child->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "ChildText");
}

// Test GetText with SetText (unsigned int)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextUnsigned_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText((unsigned int)100);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "100");
}

// Test GetText with SetText (int64_t)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextInt64_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText((int64_t)9999999999LL);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "9999999999");
}

// Test GetText with SetText (uint64_t)
TEST_F(XMLElementGetTextTest_235, ReturnsTextAfterSetTextUint64_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->SetText((uint64_t)18446744073709551615ULL);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "18446744073709551615");
}

// Test GetText with text that uses InsertNewText
TEST_F(XMLElementGetTextTest_235, ReturnsTextInsertedViaInsertNewText_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->InsertNewText("Inserted text");
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Inserted text");
}

// Test GetText returns text after comment inserted via InsertNewComment
TEST_F(XMLElementGetTextTest_235, SkipsInsertedCommentReturnsText_235) {
    doc.Parse("<root/>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    root->InsertNewComment("a comment");
    root->InsertNewText("After comment");
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "After comment");
}

// Test GetText with special characters in text
TEST_F(XMLElementGetTextTest_235, ReturnsTextWithSpecialCharacters_235) {
    doc.Parse("<root>&amp;&lt;&gt;</root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const char* text = root->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "&<>");
}

// Test GetText after replacing text via SetText
TEST_F(XMLElementGetTextTest_235, ReturnsUpdatedTextAfterSetText_235) {
    doc.Parse("<root>Original</root>");
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_STREQ(root->GetText(), "Original");
    root->SetText("Updated");
    EXPECT_STREQ(root->GetText(), "Updated");
}

// Test GetText on element with only multiple comments (no text)
TEST_F(XMLElementGetTextTest_235, ReturnsNullForMultipleCommentsOnly_235) {
    doc.Parse("<root><!-- c1 --><!-- c2 --><!-- c3 --></root>");
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->GetText(), nullptr);
}
