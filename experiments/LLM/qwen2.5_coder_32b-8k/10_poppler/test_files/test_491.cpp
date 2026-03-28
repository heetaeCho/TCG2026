#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using namespace testing;



class GfxPatternTest_491 : public ::testing::Test {

protected:

    std::unique_ptr<GfxPattern> pattern;



    void SetUp() override {

        pattern = std::make_unique<GfxPattern>(1, 123);

    }

};



TEST_F(GfxPatternTest_491, GetPatternRefNum_ReturnsCorrectValue_491) {

    EXPECT_EQ(pattern->getPatternRefNum(), 123);

}



TEST_F(GfxPatternTest_491, Copy_ReturnsNewInstanceWithSamePatternRefNum_491) {

    auto copiedPattern = pattern->copy();

    EXPECT_NE(copiedPattern.get(), pattern.get());

    EXPECT_EQ(copiedPattern->getPatternRefNum(), pattern->getPatternRefNum());

}



TEST_F(GfxPatternTest_491, Copy_ReturnsNewInstanceWithSameType_491) {

    auto copiedPattern = pattern->copy();

    EXPECT_NE(copiedPattern.get(), pattern.get());

    EXPECT_EQ(copiedPattern->getType(), pattern->getType());

}



TEST_F(GfxPatternTest_491, DeletedCopyConstructor_ShouldNotCompile_491) {

    // This test case is more of a compilation check and cannot be automatically tested with Google Test.

    // Ensure that the copy constructor is deleted by attempting to use it in code that would fail to compile.

}



TEST_F(GfxPatternTest_491, DeletedCopyAssignmentOperator_ShouldNotCompile_491) {

    // This test case is more of a compilation check and cannot be automatically tested with Google Test.

    // Ensure that the copy assignment operator is deleted by attempting to use it in code that would fail to compile.

}
