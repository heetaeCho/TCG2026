#include <gtest/gtest.h>

#include "poppler-page.h"



// Assuming poppler_point_copy is declared in a header file that we include

extern "C" PopplerPoint *poppler_point_copy(PopplerPoint *point);



class PopplerPointCopyTest_2470 : public ::testing::Test {

protected:

    PopplerPoint original_point;

};



TEST_F(PopplerPointCopyTest_2470, CopyNonNullPoint_2470) {

    // Arrange

    // Initialize the original_point if necessary



    // Act

    PopplerPoint *copied_point = poppler_point_copy(&original_point);



    // Assert

    EXPECT_NE(copied_point, nullptr);

    EXPECT_NE(copied_point, &original_point);  // Ensure it's a different instance



    // Clean up

    g_slice_free(PopplerPoint, copied_point);

}



TEST_F(PopplerPointCopyTest_2470, CopyNullPoint_2470) {

    // Arrange

    PopplerPoint *null_point = nullptr;



    // Act

    PopplerPoint *copied_point = poppler_point_copy(null_point);



    // Assert

    EXPECT_EQ(copied_point, nullptr);

}



// Assuming there are no boundary conditions or exceptional cases specific to this function

// as it only checks for nullity and performs a memory copy.

```


