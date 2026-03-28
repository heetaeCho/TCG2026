#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace testing;



// Mocking external collaborators if needed

class MockPopplerStructureElement {

public:

    MOCK_METHOD1(attr_value_or_default, const double&(Attribute));

};



TEST_F(PopplerStructureElementTest_2562, GetPadding_ValidInput_ReturnsCorrectPaddings_2562) {

    PopplerStructureElement element;

    double paddings[4] = {0};

    MockPopplerStructureElement mock;



    // Assuming attr_value_or_default returns a valid set of paddings

    EXPECT_CALL(mock, attr_value_or_default(Attribute::Padding))

        .WillOnce(Return(std::array<double, 4>{1.0, 2.0, 3.0, 4.0}));



    poppler_structure_element_get_padding(&element, paddings);



    EXPECT_DOUBLE_EQ(paddings[0], 1.0);

    EXPECT_DOUBLE_EQ(paddings[1], 2.0);

    EXPECT_DOUBLE_EQ(paddings[2], 3.0);

    EXPECT_DOUBLE_EQ(paddings[3], 4.0);

}



TEST_F(PopplerStructureElementTest_2562, GetPadding_NullPaddings_ReturnsNoCrash_2562) {

    PopplerStructureElement element;



    // Passing nullptr for paddings should not cause a crash

    EXPECT_NO_FATAL_FAILURE(poppler_structure_element_get_padding(&element, nullptr));

}



TEST_F(PopplerStructureElementTest_2562, GetPadding_NullPopplerStructureElement_ReturnsNoCrash_2562) {

    double paddings[4] = {0};



    // Passing nullptr for poppler_structure_element should not cause a crash

    EXPECT_NO_FATAL_FAILURE(poppler_structure_element_get_padding(nullptr, paddings));

}



TEST_F(PopplerStructureElementTest_2562, GetPadding_ValidInput_SetsDefaultPaddings_2562) {

    PopplerStructureElement element;

    double paddings[4] = {0};

    MockPopplerStructureElement mock;



    // Assuming attr_value_or_default returns a default set of paddings

    EXPECT_CALL(mock, attr_value_or_default(Attribute::Padding))

        .WillOnce(Return(std::array<double, 4>{0.0, 0.0, 0.0, 0.0}));



    poppler_structure_element_get_padding(&element, paddings);



    EXPECT_DOUBLE_EQ(paddings[0], 0.0);

    EXPECT_DOUBLE_EQ(paddings[1], 0.0);

    EXPECT_DOUBLE_EQ(paddings[2], 0.0);

    EXPECT_DOUBLE_EQ(paddings[3], 0.0);

}
