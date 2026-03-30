#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/OutputDev.h"

#include <memory>



// Mock for GfxLCMSProfilePtr if needed (not required in this case as it's a simple setter/getter)

using namespace testing;



class OutputDevTest : public ::testing::Test {

protected:

    OutputDev output_dev;

};



TEST_F(OutputDevTest_SetDisplayProfile_NormalOperation_1078, SetAndGetValidProfile_1078) {

    GfxLCMSProfilePtr profile = std::make_shared<GfxLCMSProfile>();

    output_dev.setDisplayProfile(profile);

    EXPECT_EQ(output_dev.getDisplayProfile(), profile);

}



TEST_F(OutputDevTest_SetDisplayProfile_BoundaryConditionNull_1078, SetAndGetNullProfile_1078) {

    GfxLCMSProfilePtr null_profile = nullptr;

    output_dev.setDisplayProfile(null_profile);

    EXPECT_EQ(output_dev.getDisplayProfile(), null_profile);

}
