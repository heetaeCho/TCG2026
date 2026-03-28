#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"  // Assuming this file contains the implementation



using namespace Exiv2::Internal;

using ::testing::_;



class MockTiffComponent : public TiffComponent {

public:

    MOCK_CONST_METHOD0(getExifModel, std::string());

};



TEST_F(WriteBatchTest_1540, ModelStartsWithSLT_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("SLT-A9"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(WriteBatchTest_1540, ModelStartsWithHV_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("HV1"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(WriteBatchTest_1540, ModelStartsWithILCA_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("ILCA-7M3"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(WriteBatchTest_1540, ModelDoesNotMatch_ReturnsZero_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("Alpha A7"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, 0);

}



TEST_F(WriteBatchTest_1540, EmptyModel_ReturnsZero_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return(""));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, 0);

}



TEST_F(WriteBatchTest_1540, ModelStartsWithSLTAndExtra_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("SLT-A9E II"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(WriteBatchTest_1540, ModelStartsWithHVAndExtra_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("HV2M"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}



TEST_F(WriteBatchTest_1540, ModelStartsWithILCAAndExtra_ReturnsNegativeOne_1540) {

    MockTiffComponent mockTiffComponent;

    EXPECT_CALL(mockTiffComponent, getExifModel()).WillOnce(::testing::Return("ILCA-6800M"));



    int result = sony2FpSelector(0x1234, nullptr, 0, &mockTiffComponent);

    EXPECT_EQ(result, -1);

}
