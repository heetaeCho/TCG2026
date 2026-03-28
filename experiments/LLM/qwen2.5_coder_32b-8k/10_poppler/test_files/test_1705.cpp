#include <gtest/gtest.h>

#include "StructElement.h"



class StructElementTest : public ::testing::Test {

protected:

    // Setup and teardown can be added if needed.

};



TEST_F(StructElementTest_1705, GetNumChildren_ReturnsZeroForContent_1705) {

    StructElement element;

    EXPECT_CALL(*element.s, isContent()).WillOnce(::testing::Return(true));

    EXPECT_EQ(element.getNumChildren(), 0U);

}



TEST_F(StructElementTest_1705, GetNumChildren_ReturnsSizeOfElementsArrayForNonContent_1705) {

    StructElement element;

    EXPECT_CALL(*element.s, isContent()).WillOnce(::testing::Return(false));

    EXPECT_CALL(element.s->elements, size()).WillOnce(::testing::Return(3U));

    EXPECT_EQ(element.getNumChildren(), 3U);

}



TEST_F(StructElementTest_1705, GetNumChildren_BoundaryConditionEmptyElementsArray_1705) {

    StructElement element;

    EXPECT_CALL(*element.s, isContent()).WillOnce(::testing::Return(false));

    EXPECT_CALL(element.s->elements, size()).WillOnce(::testing::Return(0U));

    EXPECT_EQ(element.getNumChildren(), 0U);

}



TEST_F(StructElementTest_1705, GetNumChildren_BoundaryConditionLargeElementsArray_1705) {

    StructElement element;

    EXPECT_CALL(*element.s, isContent()).WillOnce(::testing::Return(false));

    EXPECT_CALL(element.s->elements, size()).WillOnce(::testing::Return(100U));

    EXPECT_EQ(element.getNumChildren(), 100U);

}

```


