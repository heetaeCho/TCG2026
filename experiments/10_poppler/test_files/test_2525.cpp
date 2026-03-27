#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "gmock/gmock.h"



using namespace testing;



class MockStructElement : public StructElement {

public:

    MOCK_METHOD(bool, isInline, (), (const));

};



TEST_F(PopplerStructureElementTest_2525, NormalOperation_IsInline_ReturnsTrue_2525) {

    MockStructElement mockStructElement;

    EXPECT_CALL(mockStructElement, isInline()).WillOnce(Return(true));



    _PopplerStructureElement popplerStructureElement = {_PopplerStructureElement{&mockStructElement}};

    gboolean result = poppler_structure_element_is_inline(&popplerStructureElement);

    ASSERT_TRUE(result);

}



TEST_F(PopplerStructureElementTest_2525, NormalOperation_IsInline_ReturnsFalse_2525) {

    MockStructElement mockStructElement;

    EXPECT_CALL(mockStructElement, isInline()).WillOnce(Return(false));



    _PopplerStructureElement popplerStructureElement = {_PopplerStructureElement{&mockStructElement}};

    gboolean result = poppler_structure_element_is_inline(&popplerStructureElement);

    ASSERT_FALSE(result);

}



TEST_F(PopplerStructureElementTest_2525, BoundaryCondition_NullPtr_ReturnsFalse_2525) {

    _PopplerStructureElement popplerStructureElement = {_PopplerStructureElement{nullptr}};

    gboolean result = poppler_structure_element_is_inline(&popplerStructureElement);

    ASSERT_FALSE(result);

}



TEST_F(PopplerStructureElementTest_2525, BoundaryCondition_NullStruct_ReturnsFalse_2525) {

    _PopplerStructureElement popplerStructureElement = {_PopplerStructureElement{nullptr}};

    gboolean result = poppler_structure_element_is_inline(&popplerStructureElement);

    ASSERT_FALSE(result);

}



TEST_F(PopplerStructureElementTest_2525, BoundaryCondition_StructPtrIsNull_ReturnsFalse_2525) {

    _PopplerStructureElement popplerStructureElement = {_PopplerStructureElement{nullptr}};

    gboolean result = poppler_structure_element_is_inline(&popplerStructureElement);

    ASSERT_FALSE(result);

}
