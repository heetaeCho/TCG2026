#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "./TestProjects/poppler/glib/poppler-structure-element.h"

}



class PopplerStructureElementTest_2587 : public ::testing::Test {

protected:

    struct _PopplerStructureElement *poppler_structure_element;



    void SetUp() override {

        poppler_structure_element = static_cast<struct _PopplerStructureElement*>(malloc(sizeof(struct _PopplerStructureElement)));

        // Assuming a valid setup for testing, we need to mock or set elem if necessary.

    }



    void TearDown() override {

        free(poppler_structure_element);

    }

};



TEST_F(PopplerStructureElementTest_2587, GetListNumbering_ValidListItem_2587) {

    // Arrange

    poppler_structure_element->elem = /* Mock or set a valid listItem element */;

    

    // Act

    PopplerStructureListNumbering result = poppler_structure_element_get_list_numbering(poppler_structure_element);

    

    // Assert

    EXPECT_NE(result, EnumNameValue<PopplerStructureListNumbering>::values[0].value); // Assuming valid values are not the first one.

}



TEST_F(PopplerStructureElementTest_2587, GetListNumbering_InvalidKind_2587) {

    // Arrange

    poppler_structure_element->elem = /* Mock or set an invalid element kind */;

    

    // Act & Assert

    EXPECT_EQ(poppler_structure_element_get_list_numbering(poppler_structure_element), EnumNameValue<PopplerStructureListNumbering>::values[0].value);

}



TEST_F(PopplerStructureElementTest_2587, GetListNumbering_NullPointer_2587) {

    // Arrange & Act & Assert

    EXPECT_EQ(poppler_structure_element_get_list_numbering(nullptr), EnumNameValue<PopplerStructureListNumbering>::values[0].value);

}

```


