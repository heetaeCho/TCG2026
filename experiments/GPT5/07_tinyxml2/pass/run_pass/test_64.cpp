#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

class XMLTextSetCDataTest_64 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLTextSetCDataTest_64, DefaultIsNotCData_64) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);

    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextSetCDataTest_64, SetCDataTrueSetsFlag_64) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    EXPECT_TRUE(text->CData());
}

TEST_F(XMLTextSetCDataTest_64, SetCDataFalseClearsFlag_64) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    ASSERT_TRUE(text->CData());

    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}

TEST_F(XMLTextSetCDataTest_64, SetCDataIsIdempotentForSameValue_64) {
    XMLText* text = doc.NewText("hello");
    ASSERT_NE(text, nullptr);

    text->SetCData(true);
    text->SetCData(true);
    EXPECT_TRUE(text->CData());

    text->SetCData(false);
    text->SetCData(false);
    EXPECT_FALSE(text->CData());
}
