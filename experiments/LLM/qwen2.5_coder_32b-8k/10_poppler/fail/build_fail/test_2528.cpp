#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



class PopplerStructureElementTest : public ::testing::Test {

protected:

    struct _PopplerStructureElement poppler_structure_element;

    StructElement mock_struct_element;



    void SetUp() override {

        poppler_structure_element.elem = &mock_struct_element;

    }

};



TEST_F(PopplerStructureElementTest_2528, GetId_ReturnsValidString_2528) {

    const char* expected_id = "test_id";

    EXPECT_CALL(mock_struct_element, getID()).WillOnce(::testing::Return(new GooString(expected_id)));

    

    gchar *result = poppler_structure_element_get_id(&poppler_structure_element);

    ASSERT_STREQ(result, expected_id);

    g_free(result);

}



TEST_F(PopplerStructureElementTest_2528, GetId_ReturnsNullWhenGooStringIsNull_2528) {

    EXPECT_CALL(mock_struct_element, getID()).WillOnce(::testing::Return(static_cast<const GooString*>(nullptr)));

    

    gchar *result = poppler_structure_element_get_id(&poppler_structure_element);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2528, GetId_ReturnsNullWhenPopplerStructureElementIsNull_2528) {

    gchar *result = poppler_structure_element_get_id(nullptr);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2528, GetId_ReturnsNullWhenElemIsNull_2528) {

    poppler_structure_element.elem = nullptr;

    gchar *result = poppler_structure_element_get_id(&poppler_structure_element);

    ASSERT_EQ(result, nullptr);

}
