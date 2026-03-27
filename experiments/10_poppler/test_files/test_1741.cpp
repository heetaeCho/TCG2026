#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/CairoOutputDev.h"



class CairoImageOutputDevTest : public ::testing::Test {

protected:

    CairoImageOutputDev* output_dev;



    void SetUp() override {

        output_dev = new CairoImageOutputDev();

    }



    void TearDown() override {

        delete output_dev;

    }

};



TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_NormalOperation_1741) {

    EXPECT_TRUE(output_dev->useShadedFills(0));

    EXPECT_TRUE(output_dev->useShadedFills(3));

    EXPECT_TRUE(output_dev->useShadedFills(7));

}



TEST_F(CairoImageOutputDevTest_1741, UseShadedFills_BoundaryConditions_1741) {

    EXPECT_TRUE(output_dev->useShadedFills(-1)); // Assuming negative values are treated as <= 7

    EXPECT_FALSE(output_dev->useShadedFills(8));

}



TEST_F(CairoImageOutputDevTest_1741, GetNumImages_DefaultValue_1741) {

    EXPECT_EQ(output_dev->getNumImages(), 0);

}



// Assuming no external dependencies or callbacks are involved in the basic constructor and destructor

```


