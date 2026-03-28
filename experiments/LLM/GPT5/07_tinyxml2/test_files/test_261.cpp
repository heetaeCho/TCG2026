// TEST_ID: 261
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class InsertNewTextTest_261 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* root_ = nullptr;

    void SetUp() override {
        root_ = doc_.NewElement("root");
        ASSERT_NE(root_, nullptr);
        ASSERT_NE(doc_.InsertEndChild(root_), nullptr);
    }
};

TEST_F(InsertNewTextTest_261, InsertNewTextReturnsNonNullAndAppendsAsChild_261) {
    ASSERT_NE(root_, nullptr);

    XMLText* t = root_->InsertNewText("hello");
    ASSERT_NE(t, nullptr);

    // Observable via public XMLNode navigation APIs.
    const XMLNode* first = root_->FirstChild();
    ASSERT_NE(first, nullptr);

    const XMLText* firstText = first->ToText();
    ASSERT_NE(firstText, nullptr);

    ASSERT_STREQ(firstText->Value(), "hello");
}

TEST_F(InsertNewTextTest_261, InsertNewTextUpdatesGetTextToInsertedText_261) {
    ASSERT_NE(root_, nullptr);

    XMLText* t = root_->InsertNewText("greetings");
    ASSERT_NE(t, nullptr);

    const char* text = root_->GetText();
    ASSERT_NE(text, nullptr);
    ASSERT_STREQ(text, "greetings");
}

TEST_F(InsertNewTextTest_261, InsertNewTextAllowsEmptyString_261) {
    ASSERT_NE(root_, nullptr);

    XMLText* t = root_->InsertNewText("");
    ASSERT_NE(t, nullptr);

    const XMLNode* child = root_->FirstChild();
    ASSERT_NE(child, nullptr);

    const XMLText* childText = child->ToText();
    ASSERT_NE(childText, nullptr);

    ASSERT_STREQ(childText->Value(), "");
    ASSERT_NE(root_->GetText(), nullptr);
    ASSERT_STREQ(root_->GetText(), "");
}

TEST_F(InsertNewTextTest_261, InsertNewTextAppendsInOrderAndLastChildMatches_261) {
    ASSERT_NE(root_, nullptr);

    XMLText* t1 = root_->InsertNewText("first");
    ASSERT_NE(t1, nullptr);

    XMLText* t2 = root_->InsertNewText("second");
    ASSERT_NE(t2, nullptr);

    const XMLNode* first = root_->FirstChild();
    ASSERT_NE(first, nullptr);
    const XMLText* firstText = first->ToText();
    ASSERT_NE(firstText, nullptr);
    ASSERT_STREQ(firstText->Value(), "first");

    const XMLNode* last = root_->LastChild();
    ASSERT_NE(last, nullptr);
    const XMLText* lastText = last->ToText();
    ASSERT_NE(lastText, nullptr);
    ASSERT_STREQ(lastText->Value(), "second");

    // Also verify the returned pointer corresponds to the last child text node.
    ASSERT_EQ(t2, last->ToText());
}

TEST_F(InsertNewTextTest_261, InsertNewTextWithNullptrIsHandledGracefully_261) {
    ASSERT_NE(root_, nullptr);

    // Behavior is implementation-defined; we only require it to be safe and observable.
    XMLText* t = nullptr;
    EXPECT_NO_FATAL_FAILURE(t = root_->InsertNewText(nullptr));

    // InsertNewText can return nullptr on failure; if it succeeds, it should yield a text node.
    if (t) {
        ASSERT_NE(t->ToText(), nullptr);

        // Some implementations treat nullptr as empty string; accept either empty or non-empty,
        // but ensure Value() is a valid C-string.
        const char* v = t->Value();
        ASSERT_NE(v, nullptr);

        // If the element reports a text, it should also be a valid C-string.
        const char* gt = root_->GetText();
        // GetText() may be null if implementation treats null input as "no text inserted";
        // both are acceptable as long as it doesn't crash.
        if (gt) {
            ASSERT_NE(gt, nullptr);
        }
    }
}

TEST_F(InsertNewTextTest_261, InsertNewTextPreservesLongStringContent_261) {
    ASSERT_NE(root_, nullptr);

    std::string longText(10000, 'x');
    XMLText* t = root_->InsertNewText(longText.c_str());
    ASSERT_NE(t, nullptr);

    const XMLNode* child = root_->FirstChild();
    ASSERT_NE(child, nullptr);
    const XMLText* childText = child->ToText();
    ASSERT_NE(childText, nullptr);

    ASSERT_STREQ(childText->Value(), longText.c_str());

    const char* gt = root_->GetText();
    ASSERT_NE(gt, nullptr);
    ASSERT_STREQ(gt, longText.c_str());
}
