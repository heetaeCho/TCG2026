// File: ./TestProjects/tinyxml2/tests/test_xmlelement_booltext_255.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class BoolTextTest_255 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // Create a simple document with a single element we can manipulate.
        elem = doc.NewElement("e");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }
};

TEST_F(BoolTextTest_255, ReturnsDefaultWhenNoText_DefaultFalse_255) {
    // No text set on the element.
    const bool result = elem->BoolText(false);
    EXPECT_FALSE(result);
}

TEST_F(BoolTextTest_255, ReturnsDefaultWhenNoText_DefaultTrue_255) {
    // No text set on the element.
    const bool result = elem->BoolText(true);
    EXPECT_TRUE(result);
}

TEST_F(BoolTextTest_255, ReturnsTrueWhenTextSetViaSetTextBool_WithOppositeDefault_255) {
    elem->SetText(true);

    // Even if the default is false, BoolText should reflect the element's text.
    const bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(BoolTextTest_255, ReturnsFalseWhenTextSetViaSetTextBool_WithOppositeDefault_255) {
    elem->SetText(false);

    // Even if the default is true, BoolText should reflect the element's text.
    const bool result = elem->BoolText(true);
    EXPECT_FALSE(result);
}

TEST_F(BoolTextTest_255, ReflectsLatestValueAfterTextChanges_255) {
    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));

    elem->SetText(false);
    EXPECT_FALSE(elem->BoolText(true));

    elem->SetText(true);
    EXPECT_TRUE(elem->BoolText(false));
}

TEST_F(BoolTextTest_255, ReturnsParsedValueWhenTextSetAsCStringTrue_WithOppositeDefault_255) {
    // Use the public interface that sets raw text; BoolText should parse it.
    elem->SetText("true");

    const bool result = elem->BoolText(false);
    EXPECT_TRUE(result);
}

TEST_F(BoolTextTest_255, ReturnsParsedValueWhenTextSetAsCStringFalse_WithOppositeDefault_255) {
    elem->SetText("false");

    const bool result = elem->BoolText(true);
    EXPECT_FALSE(result);
}
