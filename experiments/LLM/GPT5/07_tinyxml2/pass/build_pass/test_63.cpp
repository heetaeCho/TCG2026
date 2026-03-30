// TEST_ID: 63
// File: ./TestProjects/tinyxml2/tests/xmltext_totext_test_63.cpp

#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace tinyxml2 {

class XMLTextToTextTest_63 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLTextToTextTest_63, ToTextReturnsThisPointer_63) {
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    // Observable behavior: ToText() should return the same object for XMLText.
    EXPECT_EQ(text->ToText(), text);
}

TEST_F(XMLTextToTextTest_63, ToTextViaBasePointerReturnsSameText_63) {
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    XMLNode* asNode = text;
    ASSERT_NE(asNode, nullptr);

    // Verify virtual dispatch through the base interface.
    EXPECT_EQ(asNode->ToText(), text);
}

TEST_F(XMLTextToTextTest_63, ToTextIsIdempotent_63) {
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    XMLText* first = text->ToText();
    XMLText* second = text->ToText();

    EXPECT_EQ(first, text);
    EXPECT_EQ(second, text);
    EXPECT_EQ(first, second);
}

}  // namespace tinyxml2
