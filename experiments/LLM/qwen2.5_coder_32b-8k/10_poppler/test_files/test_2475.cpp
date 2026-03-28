#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming PopplerTextAttributes is a struct or class defined somewhere

struct PopplerTextAttributes {

    // Dummy member to make it a valid struct

    int dummy;

};



extern "C" {

    PopplerTextAttributes *poppler_text_attributes_new(void);

}



class PopplerPageTest_2475 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(PopplerPageTest_2475, NewTextAttributesNotNull_2475) {

    PopplerTextAttributes* attributes = poppler_text_attributes_new();

    ASSERT_NE(attributes, nullptr);

}



TEST_F(PopplerPageTest_2475, NewTextAttributesInitializedToZero_2475) {

    PopplerTextAttributes* attributes = poppler_text_attributes_new();

    EXPECT_EQ(attributes->dummy, 0);

    g_slice_free(PopplerTextAttributes, attributes);

}

```



In this code:

- The test `NewTextAttributesNotNull_2475` checks that the function returns a non-null pointer.

- The test `NewTextAttributesInitializedToZero_2475` assumes that `g_slice_new0` initializes memory to zero and checks if a member of `PopplerTextAttributes` is indeed initialized to zero. This is a simple check based on typical behavior, as we treat the implementation as a black box.


