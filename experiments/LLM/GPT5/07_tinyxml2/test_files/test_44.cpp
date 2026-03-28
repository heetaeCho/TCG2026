// File: ./TestProjects/tinyxml2/tests/xmlnode_totext_test_44.cpp

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLNodeToTextTest_44 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLNodeToTextTest_44, DocumentToTextReturnsNull_44) {
    XMLNode* node = &doc_;
    EXPECT_EQ(node->ToText(), nullptr);
}

TEST_F(XMLNodeToTextTest_44, ElementToTextReturnsNull_44) {
    XMLElement* elem = doc_.NewElement("root");
    ASSERT_NE(elem, nullptr);

    XMLNode* node = elem;
    EXPECT_EQ(node->ToText(), nullptr);
}

TEST_F(XMLNodeToTextTest_44, CommentToTextReturnsNull_44) {
    XMLComment* comment = doc_.NewComment("hello");
    ASSERT_NE(comment, nullptr);

    XMLNode* node = comment;
    EXPECT_EQ(node->ToText(), nullptr);
}

TEST_F(XMLNodeToTextTest_44, TextToTextReturnsSelf_44) {
    XMLText* text = doc_.NewText("abc");
    ASSERT_NE(text, nullptr);

    XMLNode* node = text;
    XMLText* asText = node->ToText();

    ASSERT_NE(asText, nullptr);
    EXPECT_EQ(asText, text);
}

TEST_F(XMLNodeToTextTest_44, UnknownToTextReturnsNull_44) {
    XMLUnknown* unk = doc_.NewUnknown("<?x?>");
    ASSERT_NE(unk, nullptr);

    XMLNode* node = unk;
    EXPECT_EQ(node->ToText(), nullptr);
}
