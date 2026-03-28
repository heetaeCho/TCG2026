#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::Return;



class TiffSubIfdTest_406 : public ::testing::Test {

protected:

    TiffSubIfdTest_406() : tiffSubIfd(1, 2, 3) {}



    TiffSubIfd tiffSubIfd;

};



TEST_F(TiffSubIfdTest_406, DoSizeImage_ReturnsZeroWhenEmpty_406) {

    EXPECT_EQ(tiffSubIfd.doSizeImage(), 0);

}



TEST_F(TiffSubIfdTest_406, DoSizeImage_ReturnsSumOfSizes_406) {

    // Assuming we can add TiffSubIfds to ifds_ for testing

    auto mockIfd1 = std::make_unique<TiffSubIfd>(1, 2, 3);

    auto mockIfd2 = std::make_unique<TiffSubIfd>(4, 5, 6);



    // Mock the sizeImage method of TiffSubIfd if necessary

    EXPECT_CALL(*mockIfd1, doSizeImage()).WillRepeatedly(Return(10));

    EXPECT_CALL(*mockIfd2, doSizeImage()).WillRepeatedly(Return(20));



    tiffSubIfd.ifds_.push_back(std::move(mockIfd1));

    tiffSubIfd.ifds_.push_back(std::move(mockIfd2));



    EXPECT_EQ(tiffSubIfd.doSizeImage(), 30);

}



TEST_F(TiffSubIfdTest_406, DoSizeImage_BoundaryConditionSingleElement_406) {

    auto mockIfd = std::make_unique<TiffSubIfd>(1, 2, 3);



    EXPECT_CALL(*mockIfd, doSizeImage()).WillRepeatedly(Return(42));



    tiffSubIfd.ifds_.push_back(std::move(mockIfd));



    EXPECT_EQ(tiffSubIfd.doSizeImage(), 42);

}
