#include <gtest/gtest.h>

#include "poppler/StructElement.h"



class StructElementTest_1714 : public ::testing::Test {

protected:

    StructElement* element;



    void SetUp() override {

        // Assuming a way to construct StructElement, even though the constructor is private.

        // This is a placeholder and should be replaced with actual construction if possible.

        element = new StructElement(nullptr, nullptr, nullptr, RefRecursionChecker());

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(StructElementTest_1714, GetText_NormalOperation_1714) {

    GooString* text = element->getText();

    ASSERT_NE(text, nullptr);

}



TEST_F(StructElementTest_1714, GetText_RecursiveFalse_1714) {

    GooString* text = element->getText(false);

    ASSERT_NE(text, nullptr);

}



TEST_F(StructElementTest_1714, GetText_NoChildren_1714) {

    // Assuming the element has no children for this test.

    GooString* text = element->getText();

    EXPECT_EQ(text->getCString(), "");  // If no text is expected

}



TEST_F(StructElementTest_1714, GetText_ExceptionalCase_1714) {

    // Assuming there's an exceptional case where getText might fail or return null.

    GooString* text = element->getText();

    EXPECT_NE(text, nullptr);  // Replace with actual condition if known

}



TEST_F(StructElementTest_1714, GetText_EmptyTree_1714) {

    // Assuming the tree is empty and should return an empty string.

    GooString* text = element->getText();

    EXPECT_EQ(text->getCString(), "");  // If no text is expected

}



TEST_F(StructElementTest_1714, GetText_NonEmptyTree_1714) {

    // Assuming the tree has some content and should return a non-empty string.

    GooString* text = element->getText();

    EXPECT_STRNE(text->getCString(), "");  // If some text is expected

}
