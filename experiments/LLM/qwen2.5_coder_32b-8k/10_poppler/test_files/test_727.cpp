#include <gtest/gtest.h>

#include "poppler/Page.h"

#include <memory>



class PageTest_727 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a mock PDFDoc and other necessary objects are created here.

        // Since we cannot instantiate the actual PDFDoc, this is left as an assumption for the sake of testing.

        // In practice, you would have these objects ready to be passed into the Page constructor.



        // Mocking or setting up any required dependencies if needed.

    }



    void TearDown() override {

        // Clean up if necessary

    }



    // Assuming a way to create a valid Page object for testing purposes.

    std::unique_ptr<Page> page;

};



TEST_F(PageTest_727, GetDuration_ReturnsExpectedValue_727) {

    // Arrange

    double expectedDuration = 10.5; // Example value

    // Assuming there's a way to set the duration for testing purposes.

    // Since we treat it as a black box, this is just an assumption.



    // Act & Assert

    EXPECT_DOUBLE_EQ(expectedDuration, page->getDuration());

}



TEST_F(PageTest_727, GetDuration_ReturnsZero_WhenNotSet_727) {

    // Arrange

    double expectedDuration = 0.0; // Default value if not set



    // Act & Assert

    EXPECT_DOUBLE_EQ(expectedDuration, page->getDuration());

}



// Additional tests for other functions can be added following the same pattern.

```


