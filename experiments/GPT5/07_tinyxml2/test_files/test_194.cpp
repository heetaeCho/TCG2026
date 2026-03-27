// TEST_ID: 194
// File: ./TestProjects/tinyxml2/test_xmltext_shallowclone_194.cpp

#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLTextShallowCloneTest_194 : public ::testing::Test {
protected:
    // Prefer default constructors (tinyxml2 commonly provides defaults).
    // If your local tinyxml2 build requires args, change to:
    //   XMLDocument doc1{true, PRESERVE_WHITESPACE};
    //   XMLDocument doc2{true, PRESERVE_WHITESPACE};
    XMLDocument doc1;
    XMLDocument doc2;
};

TEST_F(XMLTextShallowCloneTest_194, CloneWithNullDocUsesOwningDocument_194) {
    XMLText* original = doc1.NewText("hello");
    ASSERT_NE(original, nullptr);
    original->SetCData(true);

    const XMLText* originalConst = original;
    XMLNode* cloneNode = originalConst->ShallowClone(nullptr);

    ASSERT_NE(cloneNode, nullptr);
    EXPECT_NE(cloneNode, original);
    EXPECT_EQ(cloneNode->GetDocument(), &doc1);

    XMLText* cloneText = cloneNode->ToText();
    ASSERT_NE(cloneText, nullptr);
    EXPECT_STREQ(cloneText->Value(), "hello");
    EXPECT_TRUE(cloneText->CData());
}

TEST_F(XMLTextShallowCloneTest_194, CloneWithProvidedDocBelongsToThatDoc_194) {
    XMLText* original = doc1.NewText("world");
    ASSERT_NE(original, nullptr);
    original->SetCData(false);

    const XMLText* originalConst = original;
    XMLNode* cloneNode = originalConst->ShallowClone(&doc2);

    ASSERT_NE(cloneNode, nullptr);
    EXPECT_NE(cloneNode, original);
    EXPECT_EQ(cloneNode->GetDocument(), &doc2);

    XMLText* cloneText = cloneNode->ToText();
    ASSERT_NE(cloneText, nullptr);
    EXPECT_STREQ(cloneText->Value(), "world");
    EXPECT_FALSE(cloneText->CData());
}

TEST_F(XMLTextShallowCloneTest_194, ClonePreservesCDataFlagWhenFalse_194) {
    XMLText* original = doc1.NewText("plain");
    ASSERT_NE(original, nullptr);
    original->SetCData(false);

    XMLNode* cloneNode = static_cast<const XMLText*>(original)->ShallowClone(nullptr);
    ASSERT_NE(cloneNode, nullptr);

    XMLText* cloneText = cloneNode->ToText();
    ASSERT_NE(cloneText, nullptr);
    EXPECT_FALSE(cloneText->CData());
    EXPECT_STREQ(cloneText->Value(), "plain");
}

TEST_F(XMLTextShallowCloneTest_194, CloneHandlesEmptyTextValue_194) {
    XMLText* original = doc1.NewText("");
    ASSERT_NE(original, nullptr);
    original->SetCData(true);

    XMLNode* cloneNode = static_cast<const XMLText*>(original)->ShallowClone(&doc1);
    ASSERT_NE(cloneNode, nullptr);

    XMLText* cloneText = cloneNode->ToText();
    ASSERT_NE(cloneText, nullptr);
    EXPECT_STREQ(cloneText->Value(), "");
    EXPECT_TRUE(cloneText->CData());
}

TEST_F(XMLTextShallowCloneTest_194, ModifyingCloneDoesNotModifyOriginal_194) {
    XMLText* original = doc1.NewText("orig");
    ASSERT_NE(original, nullptr);
    original->SetCData(false);

    XMLNode* cloneNode = static_cast<const XMLText*>(original)->ShallowClone(nullptr);
    ASSERT_NE(cloneNode, nullptr);

    XMLText* cloneText = cloneNode->ToText();
    ASSERT_NE(cloneText, nullptr);

    // Mutate clone via public interface.
    cloneText->SetCData(true);
    cloneText->SetValue("changed", /*staticMem=*/false);

    // Original remains unchanged (observable through public getters).
    EXPECT_STREQ(original->Value(), "orig");
    EXPECT_FALSE(original->CData());

    // Clone reflects its own changes.
    EXPECT_STREQ(cloneText->Value(), "changed");
    EXPECT_TRUE(cloneText->CData());
}
