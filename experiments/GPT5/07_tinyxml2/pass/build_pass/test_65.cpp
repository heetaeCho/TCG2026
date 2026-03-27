// TEST_ID: 65
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLTextCDataTest_65 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

} // namespace

TEST_F(XMLTextCDataTest_65, DefaultIsNotCData_65)
{
    // Create a text node through the public API.
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    // Default should be observable through CData().
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextCDataTest_65, SetCDataTrueMakesCDataTrue_65)
{
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextCDataTest_65, SetCDataFalseMakesCDataFalse_65)
{
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    ASSERT_TRUE(text->CData());

    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextCDataTest_65, ToggleCDataMultipleTimes_65)
{
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    EXPECT_FALSE(text->CData());

    text->SetCData(true);
    EXPECT_TRUE(text->CData());

    text->SetCData(false);
    EXPECT_FALSE(text->CData());

    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextCDataTest_65, CDataCallableOnConstPointer_65)
{
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);

    const XMLText* constText = text;
    EXPECT_TRUE(constText->CData());
}

TEST_F(XMLTextCDataTest_65, ShallowClonePreservesCDataFlag_65)
{
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    ASSERT_TRUE(text->CData());

    // Clone into the same document (public virtual API).
    XMLNode* clonedNode = text->ShallowClone(&doc_);
    ASSERT_NE(clonedNode, nullptr);

    XMLText* clonedText = clonedNode->ToText();
    ASSERT_NE(clonedText, nullptr);

    EXPECT_TRUE(clonedText->CData());
}
