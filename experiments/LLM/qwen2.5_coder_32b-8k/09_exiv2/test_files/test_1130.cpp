#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/types.hpp"



using namespace Exiv2;



class DataBufTest_1130 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(DataBufTest_1130, NormalOperationWithinBounds_1130) {

    DataBuf buf(10);

    EXPECT_NO_THROW(checkDataBufBounds(buf, 5));

}



TEST_F(DataBufTest_1130, BoundaryConditionExactSize_1130) {

    DataBuf buf(10);

    EXPECT_NO_THROW(checkDataBufBounds(buf, 10));

}



TEST_F(DataBufTest_1130, BoundaryConditionOnePastEnd_1130) {

    DataBuf buf(10);

    EXPECT_THROW(checkDataBufBounds(buf, 11), std::out_of_range);

}



TEST_F(DataBufTest_1130, LargeValueWithinMaxLong_1130) {

    DataBuf buf(static_cast<size_t>(std::numeric_limits<long>::max()));

    EXPECT_NO_THROW(checkDataBufBounds(buf, static_cast<size_t>(std::numeric_limits<long>::max())));

}



TEST_F(DataBufTest_1130, LargeValueExceedingMaxLong_1130) {

    DataBuf buf(static_cast<size_t>(std::numeric_limits<long>::max()) + 1);

    EXPECT_THROW(checkDataBufBounds(buf, static_cast<size_t>(std::numeric_limits<long>::max()) + 1), std::invalid_argument);

}



TEST_F(DataBufTest_1130, EmptyBufferZeroEnd_1130) {

    DataBuf buf;

    EXPECT_NO_THROW(checkDataBufBounds(buf, 0));

}



TEST_F(DataBufTest_1130, EmptyBufferNonZeroEnd_1130) {

    DataBuf buf;

    EXPECT_THROW(checkDataBufBounds(buf, 1), std::out_of_range);

}
