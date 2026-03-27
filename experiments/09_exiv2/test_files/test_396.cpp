#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"



namespace Exiv2 {

namespace Internal {



class TiffBinaryElementTest : public ::testing::Test {

protected:

    std::unique_ptr<TiffBinaryElement> tiffBinaryElement;



    void SetUp() override {

        tiffBinaryElement = std::make_unique<TiffBinaryElement>(0, ifdExif, ttUndefined);

    }

};



TEST_F(TiffBinaryElementTest_396, DoSizeReturnsZeroWhenValueIsNull_396) {

    EXPECT_EQ(tiffBinaryElement->doSize(), 0U);

}



TEST_F(TiffBinaryElementTest_396, DoSizeReturnsCorrectSizeWhenValueIsSet_396) {

    auto mockValue = std::make_unique<::testing::NiceMock<MockValue>>();

    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(42U));

    tiffBinaryElement->setValue(std::move(mockValue));



    EXPECT_EQ(tiffBinaryElement->doSize(), 42U);

}



TEST_F(TiffBinaryElementTest_396, DoSizeReturnsZeroWhenValueIsEmpty_396) {

    auto mockValue = std::make_unique<::testing::NiceMock<MockValue>>();

    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(0U));

    tiffBinaryElement->setValue(std::move(mockValue));



    EXPECT_EQ(tiffBinaryElement->doSize(), 0U);

}



// Mock class for Value to test interactions

class MockValue : public Value {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

};



}  // namespace Internal

}  // namespace Exiv2
