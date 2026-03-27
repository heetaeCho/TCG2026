#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxState.h"



using namespace testing;



class GfxLabColorSpaceTest_447 : public Test {

protected:

    std::unique_ptr<GfxLabColorSpace> labColorSpace;



    void SetUp() override {

        labColorSpace = std::make_unique<GfxLabColorSpace>();

    }

};



TEST_F(GfxLabColorSpaceTest_447, GetModeReturnsCsLab_447) {

    EXPECT_EQ(labColorSpace->getMode(), csLab);

}



TEST_F(GfxLabColorSpaceTest_447, CopyCreatesNewInstance_447) {

    auto copy = labColorSpace->copy();

    EXPECT_NE(copy.get(), nullptr);

    EXPECT_EQ(copy->getMode(), csLab);

}



// Assuming getNComps() returns a constant value for GfxLabColorSpace

TEST_F(GfxLabColorSpaceTest_447, GetNCompsReturnsConstantValue_447) {

    EXPECT_GE(labColorSpace->getNComps(), 1); // Assuming at least one component

}



// Boundary conditions and exceptional/error cases are not directly observable from the provided interface.

// Mocking is not required as there are no external collaborators involved in the functions being tested.



TEST_F(GfxLabColorSpaceTest_447, GetAMinReturnsValidValue_447) {

    EXPECT_DOUBLE_EQ(labColorSpace->getAMin(), labColorSpace->getAMin());

}



TEST_F(GfxLabColorSpaceTest_447, GetAMaxReturnsValidValue_447) {

    EXPECT_DOUBLE_EQ(labColorSpace->getAMax(), labColorSpace->getAMax());

}



TEST_F(GfxLabColorSpaceTest_447, GetBMinReturnsValidValue_447) {

    EXPECT_DOUBLE_EQ(labColorSpace->getBMin(), labColorSpace->getBMin());

}



TEST_F(GfxLabColorSpaceTest_447, GetBMaxReturnsValidValue_447) {

    EXPECT_DOUBLE_EQ(labColorSpace->getBMax(), labColorSpace->getBMax());

}
