#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"  // Assuming this file contains the function definition



using namespace Exiv2::Internal;

using ::testing::Return;

using ::testing::_;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_METHOD(std::string, getExifModel, (), (const));

};



TEST_F(MockTiffComponentTest_1538, ModelEmpty_ReturnsNegativeOne_1538) {

    MockTiffComponent mockComponent;

    EXPECT_CALL(mockComponent, getExifModel()).WillOnce(Return(""));



    int result = sonyCsSelector(0, nullptr, 0, &mockComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(MockTiffComponentTest_1538, ModelDSLR_A330_ReturnsOne_1538) {

    MockTiffComponent mockComponent;

    EXPECT_CALL(mockComponent, getExifModel()).WillOnce(Return("DSLR-A330"));



    int result = sonyCsSelector(0, nullptr, 0, &mockComponent);

    EXPECT_EQ(result, 1);

}



TEST_F(MockTiffComponentTest_1538, ModelDSLR_A380_ReturnsOne_1538) {

    MockTiffComponent mockComponent;

    EXPECT_CALL(mockComponent, getExifModel()).WillOnce(Return("DSLR-A380"));



    int result = sonyCsSelector(0, nullptr, 0, &mockComponent);

    EXPECT_EQ(result, 1);

}



TEST_F(MockTiffComponentTest_1538, ModelOther_ReturnsZero_1538) {

    MockTiffComponent mockComponent;

    EXPECT_CALL(mockComponent, getExifModel()).WillOnce(Return("SomeOtherModel"));



    int result = sonyCsSelector(0, nullptr, 0, &mockComponent);

    EXPECT_EQ(result, 0);

}
