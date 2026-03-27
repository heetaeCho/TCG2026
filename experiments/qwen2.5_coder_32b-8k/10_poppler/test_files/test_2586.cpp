#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "poppler-private.h"



using namespace testing;



class PopplerStructureElementTest_2586 : public ::testing::Test {

protected:

    struct _PopplerStructureElement *element;

    guint n_values;



    void SetUp() override {

        element = new _PopplerStructureElement();

        n_values = 0;

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(PopplerStructureElementTest_2586, GetColumnWidths_ReturnsNullIfNotGrouping_2586) {

    EXPECT_CALL(*element, poppler_structure_element_is_grouping())

        .WillOnce(Return(false));



    gdouble *result = poppler_structure_element_get_column_widths(element, &n_values);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2586, GetColumnWidths_ReturnsNullIfNValuesIsNull_2586) {

    n_values = 0;



    gdouble *result = poppler_structure_element_get_column_widths(element, nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2586, GetColumnWidths_ReturnsNullIfColumnWidthsNotSet_2586) {

    EXPECT_CALL(*element, poppler_structure_element_is_grouping())

        .WillOnce(Return(true));



    gdouble *result = poppler_structure_element_get_column_widths(element, &n_values);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerStructureElementTest_2586, GetColumnWidths_ReturnsValidDataIfColumnWidthsSet_2586) {

    // Assuming setup for element to have ColumnWidths set with some values

    EXPECT_CALL(*element, poppler_structure_element_is_grouping())

        .WillOnce(Return(true));



    gdouble *result = poppler_structure_element_get_column_widths(element, &n_values);

    if (result != nullptr) {

        // Assuming we know the expected number of values for this test case

        EXPECT_GT(n_values, 0);

        delete[] result; // Clean up allocated memory

    }

}

```


