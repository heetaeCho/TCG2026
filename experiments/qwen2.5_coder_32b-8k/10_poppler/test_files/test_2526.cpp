#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-structure-element.h"

#include "./TestProjects/poppler/poppler/StructElement.h"



// Mock StructElement class to control behavior for testing

class MockStructElement : public StructElement {

public:

    MOCK_METHOD(bool, isBlock, (), (const, override));

};



TEST_F(PopplerStructureElementTest_2526, NormalOperation_IsBlock_ReturnsTrue_2526) {

    MockStructElement mock_elem;

    EXPECT_CALL(mock_elem, isBlock()).WillOnce(::testing::Return(true));



    _PopplerStructureElement poppler_elem = { &mock_elem };

    gboolean result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, TRUE);

}



TEST_F(PopplerStructureElementTest_2526, NormalOperation_IsBlock_ReturnsFalse_2526) {

    MockStructElement mock_elem;

    EXPECT_CALL(mock_elem, isBlock()).WillOnce(::testing::Return(false));



    _PopplerStructureElement poppler_elem = { &mock_elem };

    gboolean result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, FALSE);

}



TEST_F(PopplerStructureElementTest_2526, NullPointer_ReturnsFalse_2526) {

    _PopplerStructureElement poppler_elem = { nullptr };

    gboolean result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, FALSE);

}



TEST_F(PopplerStructureElementTest_2526, InvalidPointer_ReturnsFalse_2526) {

    _PopplerStructureElement poppler_elem = { reinterpret_cast<const StructElement*>(0xDEADBEEF) };

    gboolean result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, FALSE);

}



TEST_F(PopplerStructureElementTest_2526, ValidPointerButNullElem_ReturnsFalse_2526) {

    _PopplerStructureElement poppler_elem = { nullptr };

    gboolean result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, FALSE);



    // Manually setting elem to nullptr to simulate the condition

    poppler_elem.elem = nullptr;

    result = poppler_structure_element_is_block(&poppler_elem);

    EXPECT_EQ(result, FALSE);

}
