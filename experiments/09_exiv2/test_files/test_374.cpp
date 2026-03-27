#include <gmock/gmock.h>

#include <gtest/gtest.h>



// Mock IoWrapper for testing

class MockIoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t size), ());

};



using namespace Exiv2::Internal;



class TiffBinaryElementTest_374 : public ::testing::Test {

protected:

    MockIoWrapper mockIoWrapper;

    std::shared_ptr<TiffValue> tiffValue;

    TiffBinaryElement element;



    void SetUp() override {

        tiffValue = std::make_shared<TiffValue>(10); // Assuming TiffValue is a class that can be constructed with size

        element.pValue_ = tiffValue.get(); // Direct assignment for testing purposes, should not rely on private members in real scenario

    }

};



TEST_F(TiffBinaryElementTest_374, DoWrite_ReturnsZeroForNullPointer_374) {

    element.pValue_ = nullptr;

    size_t imageIdx = 0;

    EXPECT_EQ(element.doWrite(mockIoWrapper, littleEndian, 0, 0, 0, imageIdx), 0);

}



TEST_F(TiffBinaryElementTest_374, DoWrite_ReturnsZeroForEmptyCount_374) {

    tiffValue->count(0);

    size_t imageIdx = 0;

    EXPECT_EQ(element.doWrite(mockIoWrapper, littleEndian, 0, 0, 0, imageIdx), 0);

}



TEST_F(TiffBinaryElementTest_374, DoWrite_CallsWriteWithCorrectDataAndSize_374) {

    byte data[10] = {0};

    EXPECT_CALL(mockIoWrapper, write(testing::Eq(data), testing::Eq(10)))

        .WillOnce(testing::Return(10));



    tiffValue->copy(data, littleEndian);

    size_t imageIdx = 0;

    EXPECT_EQ(element.doWrite(mockIoWrapper, littleEndian, 0, 0, 0, imageIdx), 10);

}



TEST_F(TiffBinaryElementTest_374, DoWrite_ReturnsCorrectSize_374) {

    byte data[10] = {0};

    EXPECT_CALL(mockIoWrapper, write(testing::Eq(data), testing::Eq(10)))

        .WillOnce(testing::Return(10));



    tiffValue->copy(data, littleEndian);

    size_t imageIdx = 0;

    EXPECT_EQ(element.doWrite(mockIoWrapper, littleEndian, 0, 0, 0, imageIdx), 10);

}



TEST_F(TiffBinaryElementTest_374, DoWrite_HandlesBigEndianCorrectly_374) {

    byte data[10] = {0};

    EXPECT_CALL(mockIoWrapper, write(testing::Eq(data), testing::Eq(10)))

        .WillOnce(testing::Return(10));



    tiffValue->copy(data, bigEndian);

    size_t imageIdx = 0;

    EXPECT_EQ(element.doWrite(mockIoWrapper, bigEndian, 0, 0, 0, imageIdx), 10);

}
