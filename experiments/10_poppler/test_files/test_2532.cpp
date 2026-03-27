#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



using namespace testing;



class PopplerStructureElementTest : public ::testing::Test {

protected:

    struct _PopplerStructureElement poppler_structure_element;

    StructElement mock_struct_element;



    void SetUp() override {

        poppler_structure_element.elem = &mock_struct_element;

    }

};



TEST_F(PopplerStructureElementTest_2532, GetAltText_ReturnsNullptrWhenStructElementIsNull_2532) {

    poppler_structure_element.elem = nullptr;

    gchar *result = poppler_structure_element_get_alt_text(&poppler_structure_element);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2532, GetAltText_ReturnsNullptrWhenStructElementElemIsNull_2532) {

    mock_struct_element = StructElement(nullptr, nullptr, nullptr); // Assuming a constructor that can set elem to null

    gchar *result = poppler_structure_element_get_alt_text(&poppler_structure_element);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2532, GetAltText_ReturnsNullptrWhenGooStringIsNull_2532) {

    EXPECT_CALL(mock_struct_element, getAltText()).WillOnce(Return(nullptr));

    gchar *result = poppler_structure_element_get_alt_text(&poppler_structure_element);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2532, GetAltText_ReturnsUtf8StringWhenGooStringIsNotNull_2532) {

    const GooString goo_string("test");

    EXPECT_CALL(mock_struct_element, getAltText()).WillOnce(Return(&goo_string));

    gchar *result = poppler_structure_element_get_alt_text(&poppler_structure_element);

    ASSERT_NE(result, nullptr);

    EXPECT_STREQ(result, "test");

    g_free(result); // Free the allocated memory

}



TEST_F(PopplerStructureElementTest_2532, GetAltText_CallsGetAltTextOnStructElement_2532) {

    EXPECT_CALL(mock_struct_element, getAltText()).Times(1);

    poppler_structure_element_get_alt_text(&poppler_structure_element);

}
