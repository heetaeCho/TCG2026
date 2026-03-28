#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "StructElement.h"



class PopplerStructureElementTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock StructElement for testing

        mock_struct_element = new testing::NiceMock<MockStructElement>();

        poppler_structure_element = static_cast<PopplerStructureElement*>(g_malloc0(sizeof(PopplerStructureElement)));

        poppler_structure_element->elem = mock_struct_element;

    }



    void TearDown() override {

        g_free(poppler_structure_element);

        delete mock_struct_element;

    }



    PopplerStructureElement *poppler_structure_element;

    MockStructElement *mock_struct_element;

};



class MockStructElement : public StructElement {

public:

    MOCK_CONST_METHOD0(isGrouping, bool());

};



TEST_F(PopplerStructureElementTest_2527, IsGrouping_ReturnsTrue_2527) {

    EXPECT_CALL(*mock_struct_element, isGrouping()).WillOnce(::testing::Return(true));

    EXPECT_EQ(poppler_structure_element_is_grouping(poppler_structure_element), TRUE);

}



TEST_F(PopplerStructureElementTest_2527, IsGrouping_ReturnsFalse_2527) {

    EXPECT_CALL(*mock_struct_element, isGrouping()).WillOnce(::testing::Return(false));

    EXPECT_EQ(poppler_structure_element_is_grouping(poppler_structure_element), FALSE);

}



TEST_F(PopplerStructureElementTest_2527, NullPointer_ReturnsFalse_2527) {

    poppler_structure_element->elem = nullptr;

    EXPECT_EQ(poppler_structure_element_is_grouping(poppler_structure_element), FALSE);

}



TEST_F(PopplerStructureElementTest_2527, InvalidStructureElement_ReturnsFalse_2527) {

    g_free(poppler_structure_element);

    poppler_structure_element = nullptr;

    EXPECT_EQ(poppler_structure_element_is_grouping(poppler_structure_element), FALSE);

}
