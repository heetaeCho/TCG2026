#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include <memory>



using namespace std;



class OutputDevTest : public ::testing::Test {

protected:

    unique_ptr<OutputDev> output_dev;



    void SetUp() override {

        output_dev = make_unique<OutputDev>();

    }

};



TEST_F(OutputDevTest_1079, GetDisplayProfile_DefaultValue_1079) {

    EXPECT_EQ(output_dev->getDisplayProfile(), nullptr);

}



TEST_F(OutputDevTest_1079, SetAndGetDisplayProfile_NormalOperation_1079) {

    GfxLCMSProfilePtr test_profile = make_shared<GfxLCMSProfile>();

    output_dev->setDisplayProfile(test_profile);

    EXPECT_EQ(output_dev->getDisplayProfile(), test_profile);

}



// Boundary conditions and exceptional/error cases are less relevant here as the class does not specify any constraints

// on the profile pointers being set. It simply stores and retrieves them.

```



These tests cover:

- The default value of `displayprofile` after object creation.

- Setting a `GfxLCMSProfilePtr` and verifying that it is correctly retrieved.


