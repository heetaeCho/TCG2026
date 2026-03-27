#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/glib/poppler-structure-element.h"

#include "TestProjects/poppler/glib/poppler-private.h"



// Mock class for PopplerStructureElement to simulate the behavior of poppler_structure_element_is_block

class MockPopplerStructureElement : public PopplerStructureElement {

public:

    MOCK_METHOD(bool, is_block, (), (const));

};



TEST_F(PopplerStructureInlineAlignTest_2573, NormalOperation_Block_2573) {

    MockPopplerStructureElement mockElement;

    EXPECT_CALL(mockElement, is_block()).WillOnce(::testing::Return(true));



    PopplerStructureInlineAlign align = poppler_structure_element_get_inline_align(&mockElement);

    // Assuming that the return value is a valid enum value when is_block returns true

    EXPECT_TRUE(align >= POPPLER_STRUCTURE_INLINE_ALIGN_LEFT && align <= POPPLER_STRUCTURE_INLINE_ALIGN_JUSTIFY);

}



TEST_F(PopplerStructureInlineAlignTest_2573, BoundaryCondition_NotBlock_2573) {

    MockPopplerStructureElement mockElement;

    EXPECT_CALL(mockElement, is_block()).WillOnce(::testing::Return(false));



    PopplerStructureInlineAlign align = poppler_structure_element_get_inline_align(&mockElement);

    // Assuming that the return value when not a block is the first enum value

    EXPECT_EQ(align, EnumNameValue<PopplerStructureInlineAlign>::values[0].value);

}
