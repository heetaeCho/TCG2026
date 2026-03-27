#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

#include "./TestProjects/poppler/glib/poppler-structure-element.h"

}



class PopplerStructureElementTest : public ::testing::Test {

protected:

    struct _PopplerStructureElement *poppler_structure_element;

    StructElement *struct_element_mock;



    void SetUp() override {

        struct_element_mock = new StructElement();

        poppler_structure_element = new _PopplerStructureElement{.elem = struct_element_mock};

    }



    void TearDown() override {

        delete poppler_structure_element->elem;

        delete poppler_structure_element;

    }

};



TEST_F(PopplerStructureElementTest_2524, IsContent_ReturnsTrueWhenIsContent_ReturnsTrue_2524) {

    EXPECT_CALL(*struct_element_mock, isContent()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_structure_element_is_content(poppler_structure_element));

}



TEST_F(PopplerStructureElementTest_2524, IsContent_ReturnsFalseWhenIsContent_ReturnsFalse_2524) {

    EXPECT_CALL(*struct_element_mock, isContent()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_structure_element_is_content(poppler_structure_element));

}



TEST_F(PopplerStructureElementTest_2524, IsContent_ReturnsFalseWhenPopplerStructureElementIsNull_2524) {

    EXPECT_FALSE(poppler_structure_element_is_content(nullptr));

}



TEST_F(PopplerStructureElementTest_2524, IsContent_ReturnsFalseWhenStructElementElemIsNull_2524) {

    poppler_structure_element->elem = nullptr;

    EXPECT_FALSE(poppler_structure_element_is_content(poppler_structure_element));

}
