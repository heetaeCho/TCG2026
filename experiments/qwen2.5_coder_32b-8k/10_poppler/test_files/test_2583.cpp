#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace testing;



// Mock for the StructElement to simulate external behavior

class MockStructElement : public StructElement {

public:

    MOCK_METHOD(PopplerStructureGlyphOrientation, getGlyphOrientation, (), const);

};



// Test fixture class for PopplerStructureElement tests

class PopplerStructureElementTest_2583 : public ::testing::Test {

protected:

    MockStructElement mock_elem;

    _PopplerStructureElement poppler_structure_element;



    void SetUp() override {

        poppler_structure_element.elem = &mock_elem;

    }

};



TEST_F(PopplerStructureElementTest_2583, GetGlyphOrientation_NormalOperation_2583) {

    EXPECT_CALL(mock_elem, getGlyphOrientation()).WillOnce(Return(POPPLER_STRUCTURE_GLYPH_ORIENTATION_NORMAL));

    PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(&poppler_structure_element);

    EXPECT_EQ(result, POPPLER_STRUCTURE_GLYPH_ORIENTATION_NORMAL);

}



TEST_F(PopplerStructureElementTest_2583, GetGlyphOrientation_BoundaryCondition_EmptyEnum_2583) {

    EXPECT_CALL(mock_elem, getGlyphOrientation()).WillOnce(Return(static_cast<PopplerStructureGlyphOrientation>(-1)));

    PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(&poppler_structure_element);

    EXPECT_EQ(result, EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value);

}



TEST_F(PopplerStructureElementTest_2583, GetGlyphOrientation_ExceptionalCase_NotInline_2583) {

    poppler_structure_element.elem = nullptr;

    PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(&poppler_structure_element);

    EXPECT_EQ(result, EnumNameValue<PopplerStructureGlyphOrientation>::values[0].value);

}
