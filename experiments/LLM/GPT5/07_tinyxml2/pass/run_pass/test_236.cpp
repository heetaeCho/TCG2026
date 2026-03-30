// File: ./TestProjects/tinyxml2/tests/test_xmlelement_settext_char_236.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextCharTest_236 : public ::testing::Test {
protected:
    XMLDocument doc;
};

// Normal operation: element has no children -> creates a text child that is returned by GetText().
TEST_F(XMLElementSetTextCharTest_236, CreatesTextWhenNoChildren_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    elem->SetText("hello");

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "hello");

    const XMLNode* first = elem->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_NE(first->ToText(), nullptr);
}

// Normal operation: element already has a first-child text node -> updates that node (observable via stable FirstChild()).
TEST_F(XMLElementSetTextCharTest_236, UpdatesExistingFirstChildTextNode_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    elem->SetText("first");
    const XMLNode* firstBefore = elem->FirstChild();
    ASSERT_NE(firstBefore, nullptr);
    ASSERT_NE(firstBefore->ToText(), nullptr);
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "first");

    elem->SetText("second");

    const XMLNode* firstAfter = elem->FirstChild();
    ASSERT_NE(firstAfter, nullptr);
    EXPECT_EQ(firstAfter, firstBefore) << "First child should remain the existing text node when possible.";
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "second");
}

// Boundary/structural: first child is NOT a text node -> inserts a new text node as the first child.
TEST_F(XMLElementSetTextCharTest_236, InsertsTextBeforeNonTextFirstChild_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    // Add a non-text child as the first child.
    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);
    XMLNode* insertedChild = elem->InsertEndChild(child);
    ASSERT_EQ(insertedChild, child);

    const XMLNode* firstBefore = elem->FirstChild();
    ASSERT_EQ(firstBefore, child);
    ASSERT_EQ(firstBefore->ToText(), nullptr);

    elem->SetText("prefix");

    const XMLNode* firstAfter = elem->FirstChild();
    ASSERT_NE(firstAfter, nullptr);
    EXPECT_NE(firstAfter->ToText(), nullptr) << "A text node should become the first child.";
    EXPECT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "prefix");

    // The previously-first child should still exist and follow the inserted text node.
    const XMLNode* secondAfter = firstAfter->NextSibling();
    ASSERT_NE(secondAfter, nullptr);
    EXPECT_EQ(secondAfter, child);
}

// Boundary: multiple children; first is text, later is element -> SetText should not reorder/remove later children.
TEST_F(XMLElementSetTextCharTest_236, UpdatesFirstTextWithoutAffectingLaterChildren_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    elem->SetText("old");
    const XMLNode* textNode = elem->FirstChild();
    ASSERT_NE(textNode, nullptr);
    ASSERT_NE(textNode->ToText(), nullptr);

    XMLElement* child = doc.NewElement("child");
    ASSERT_NE(child, nullptr);
    ASSERT_EQ(elem->InsertEndChild(child), child);

    // Sanity: text then child.
    ASSERT_EQ(elem->FirstChild(), textNode);
    ASSERT_EQ(elem->FirstChild()->NextSibling(), child);

    elem->SetText("new");

    // Text updated, structure preserved.
    EXPECT_EQ(elem->FirstChild(), textNode);
    ASSERT_NE(elem->GetText(), nullptr);
    EXPECT_STREQ(elem->GetText(), "new");
    EXPECT_EQ(elem->FirstChild()->NextSibling(), child);
}

// Boundary: empty string input should be handled without breaking observable accessors.
TEST_F(XMLElementSetTextCharTest_236, AcceptsEmptyString_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    elem->SetText("");
    const char* text = elem->GetText();

    // Depending on library behavior, empty text may be reported as "" (most common) or possibly nullptr.
    // This test only enforces that the call is safe and the result is consistent with an empty value.
    if (text) {
        EXPECT_STREQ(text, "");
    } else {
        SUCCEED() << "GetText() returned nullptr after SetText(\"\").";
    }
}

// Boundary: larger input should round-trip through GetText().
TEST_F(XMLElementSetTextCharTest_236, LargeStringRoundTrip_236) {
    XMLElement* elem = doc.NewElement("root");
    ASSERT_NE(elem, nullptr);

    std::string big(4096, 'x');
    big[0] = 'A';
    big[4095] = 'Z';

    elem->SetText(big.c_str());

    const char* text = elem->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, big.c_str());
}
