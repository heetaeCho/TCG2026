#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstring>
#include <string>

using namespace tinyxml2;

class XMLCommentTest_197 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Test that a well-formed comment is parsed correctly
TEST_F(XMLCommentTest_197, ParseValidComment_197) {
    const char* xml = "<root><!-- This is a comment --></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLNode* child = root->FirstChild();
    ASSERT_NE(nullptr, child);
    
    XMLComment* comment = child->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ(" This is a comment ", comment->Value());
}

// Test that an empty comment is parsed correctly
TEST_F(XMLCommentTest_197, ParseEmptyComment_197) {
    const char* xml = "<root><!----></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLNode* child = root->FirstChild();
    ASSERT_NE(nullptr, child);
    
    XMLComment* comment = child->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("", comment->Value());
}

// Test that an unterminated comment causes an error
TEST_F(XMLCommentTest_197, ParseUnterminatedComment_197) {
    const char* xml = "<root><!-- This comment never ends</root>";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_EQ(XML_ERROR_PARSING_COMMENT, err);
}

// Test comment with special characters
TEST_F(XMLCommentTest_197, ParseCommentWithSpecialChars_197) {
    const char* xml = "<root><!-- <tag> & \"quotes\" 'apos' --></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ(" <tag> & \"quotes\" 'apos' ", comment->Value());
}

// Test comment with newlines
TEST_F(XMLCommentTest_197, ParseCommentWithNewlines_197) {
    const char* xml = "<root><!--\nline1\nline2\n--></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
}

// Test multiple comments in a document
TEST_F(XMLCommentTest_197, ParseMultipleComments_197) {
    const char* xml = "<root><!-- first --><!-- second --></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* first = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, first);
    EXPECT_STREQ(" first ", first->Value());
    
    XMLComment* second = first->NextSibling()->ToComment();
    ASSERT_NE(nullptr, second);
    EXPECT_STREQ(" second ", second->Value());
}

// Test comment at document level
TEST_F(XMLCommentTest_197, ParseDocumentLevelComment_197) {
    const char* xml = "<!-- top level --><root/>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLComment* comment = doc.FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ(" top level ", comment->Value());
}

// Test comment with only whitespace
TEST_F(XMLCommentTest_197, ParseWhitespaceOnlyComment_197) {
    const char* xml = "<root><!--   --></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_STREQ("   ", comment->Value());
}

// Test comment with dashes inside (but not -->)
TEST_F(XMLCommentTest_197, ParseCommentWithDashes_197) {
    const char* xml = "<root><!-- some-thing - here --></root>";
    XMLError err = doc.Parse(xml);
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
}

// Test that only opening comment tag with no content and no close triggers error
TEST_F(XMLCommentTest_197, ParseCommentOnlyOpening_197) {
    const char* xml = "<!--";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
}

// Test error is reported for comment that has partial close
TEST_F(XMLCommentTest_197, ParseCommentPartialClose_197) {
    const char* xml = "<root><!-- almost done --";
    XMLError err = doc.Parse(xml);
    EXPECT_NE(XML_SUCCESS, err);
}

// Test long comment
TEST_F(XMLCommentTest_197, ParseLongComment_197) {
    std::string longContent(10000, 'x');
    std::string xml = "<root><!--" + longContent + "--></root>";
    XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(nullptr, root);
    
    XMLComment* comment = root->FirstChild()->ToComment();
    ASSERT_NE(nullptr, comment);
    EXPECT_EQ(longContent, std::string(comment->Value()));
}
