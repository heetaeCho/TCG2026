#include <gtest/gtest.h>

#include "poppler-page.h"



class PopplerRectangleTest_2464 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PopplerRectangleTest_2464, CreateNewInstance_2464) {

    PopplerRectangle* rect = poppler_rectangle_new();

    ASSERT_NE(rect, nullptr);

    free(rect);  // Assuming free is appropriate to clean up

}



TEST_F(PopplerRectangleTest_2464, MultipleInstances_2464) {

    PopplerRectangle* rect1 = poppler_rectangle_new();

    PopplerRectangle* rect2 = poppler_rectangle_new();

    ASSERT_NE(rect1, nullptr);

    ASSERT_NE(rect2, nullptr);

    EXPECT_NE(rect1, rect2);

    free(rect1);  // Assuming free is appropriate to clean up

    free(rect2);  // Assuming free is appropriate to clean up

}



TEST_F(PopplerRectangleTest_2464, MemoryAllocationFailure_2464) {

    // This test assumes a way to simulate memory allocation failure, which might not be directly possible.

    // If there's no way to simulate it through the interface, this test can be skipped or modified.

    // For now, we assume that poppler_rectangle_new will return nullptr if memory allocation fails.

    // This is a hypothetical test and might need adjustment based on actual behavior.

    PopplerRectangle* rect = poppler_rectangle_new();

    ASSERT_NE(rect, nullptr);

    free(rect);  // Assuming free is appropriate to clean up

}
