#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/slice.hpp"



namespace Exiv2 { namespace Internal {



class SliceBaseTest_2146 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(SliceBaseTest_2146, ConstructorValidRange_2146) {

    EXPECT_NO_THROW((SliceBase(0, 1)));

}



TEST_F(SliceBaseTest_2146, ConstructorEqualBounds_2146) {

    EXPECT_THROW((SliceBase(5, 5)), std::out_of_range);

}



TEST_F(SliceBaseTest_2146, ConstructorReverseBounds_2146) {

    EXPECT_THROW((SliceBase(10, 5)), std::out_of_range);

}



TEST_F(SliceBaseTest_2146, SizeCalculation_2146) {

    SliceBase slice(3, 8);

    EXPECT_EQ(slice.size(), 5);

}



// Assuming size() is the only public method, no further tests for rangeCheck as it's protected

}} // namespace Exiv2::Internal
