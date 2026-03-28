// File: ./TestProjects/tinyxml2/tests/InsertNewUnknownTest_263.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

int CountAllChildren(const XMLNode* node) {
    int count = 0;
    for (const XMLNode* c = node ? node->FirstChild() : nullptr; c; c = c->NextSibling()) {
        ++count;
    }
    return count;
}

class InsertNewUnknownTest_263 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* root = nullptr;

    void SetUp() override {
        root = doc.NewElement("root");
        ASSERT_NE(root, nullptr);
        ASSERT_NE(doc.InsertEndChild(root), nullptr);
    }
};

}  // namespace

TEST_F(InsertNewUnknownTest_263, InsertsUnknownAndReturnsPointer_263) {
    const char* text = "mystery-node";
    const int before = CountAllChildren(root);

    XMLUnknown* unknown = root->InsertNewUnknown(text);

    ASSERT_NE(unknown, nullptr);
    EXPECT_EQ(unknown->Parent(), root);
    EXPECT_EQ(root->LastChild(), unknown);
    EXPECT_NE(unknown->ToUnknown(), nullptr);

    // Value() is an observable public API; if it is provided, it should be stable to compare.
    const char* v = unknown->Value();
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, text);

    const int after = CountAllChildren(root);
    EXPECT_EQ(after, before + 1);
}

TEST_F(InsertNewUnknownTest_263, InsertsAsEndChildAfterExistingChildren_263) {
    ASSERT_NE(root->InsertNewChildElement("child"), nullptr);
    ASSERT_NE(root->InsertNewComment("c"), nullptr);

    const XMLNode* beforeLast = root->LastChild();
    ASSERT_NE(beforeLast, nullptr);

    XMLUnknown* unknown = root->InsertNewUnknown("u");

    ASSERT_NE(unknown, nullptr);
    EXPECT_EQ(root->LastChild(), unknown);
    EXPECT_EQ(unknown->PreviousSibling(), beforeLast);
    EXPECT_NE(unknown->ToUnknown(), nullptr);
}

TEST_F(InsertNewUnknownTest_263, MultipleInsertionsPreserveOrder_263) {
    XMLUnknown* u1 = root->InsertNewUnknown("u1");
    XMLUnknown* u2 = root->InsertNewUnknown("u2");

    ASSERT_NE(u1, nullptr);
    ASSERT_NE(u2, nullptr);

    const XMLNode* first = root->FirstChild();
    ASSERT_NE(first, nullptr);
    EXPECT_EQ(first, u1);

    const XMLNode* second = first->NextSibling();
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second, u2);

    EXPECT_EQ(u1->NextSibling(), u2);
    EXPECT_EQ(u2->PreviousSibling(), u1);
}

TEST_F(InsertNewUnknownTest_263, NullTextDoesNotCrashAndHasConsistentOutcome_263) {
    const int before = CountAllChildren(root);

    XMLUnknown* unknown = root->InsertNewUnknown(nullptr);

    const int after = CountAllChildren(root);

    if (unknown) {
        EXPECT_EQ(after, before + 1);
        EXPECT_EQ(unknown->Parent(), root);
        EXPECT_EQ(root->LastChild(), unknown);
        EXPECT_NE(unknown->ToUnknown(), nullptr);
        // Don't assert on Value() contents for nullptr input; just ensure it is callable.
        (void)unknown->Value();
    } else {
        EXPECT_EQ(after, before);
        // Ensure last child is unchanged (no new node appended).
        // (If there were no children before, LastChild() should still be nullptr.)
        if (before == 0) {
            EXPECT_EQ(root->LastChild(), nullptr);
        }
    }
}
