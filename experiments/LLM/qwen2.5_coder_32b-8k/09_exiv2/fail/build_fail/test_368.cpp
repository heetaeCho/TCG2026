#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(void, write, (const byte* data, size_t count), (override));

};



class TiffDataEntryTest_368 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any necessary preconditions for the tests

        value = std::make_shared<Value>(10);  // Assuming Value is a valid type that can be constructed with size

        tiffDataEntry.pValue_ = value;       // Direct access to pValue_ for testing purposes, assuming it's accessible

    }



    MockIoWrapper mockIoWrapper;

    TiffDataEntry tiffDataEntry;

    std::shared_ptr<Value> value;

};



TEST_F(TiffDataEntryTest_368, DoWriteWithNonEmptyValue_368) {

    // Arrange

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 100;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(::testing::NotNull(), ::testing::_)).Times(1);



    // Act

    size_t result = tiffDataEntry.doWrite(mockIoWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);



    // Assert

    EXPECT_EQ(result, value->size());

}



TEST_F(TiffDataEntryTest_368, DoWriteWithEmptyValue_368) {

    // Arrange

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 100;

    size_t imageIdx = 0;



    value->count(0);  // Assuming count() sets the number of elements in Value



    EXPECT_CALL(mockIoWrapper, write(::testing::NotNull(), ::testing::_)).Times(0);



    // Act

    size_t result = tiffDataEntry.doWrite(mockIoWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);



    // Assert

    EXPECT_EQ(result, 0);

}



TEST_F(TiffDataEntryTest_368, DoWriteWithOffsetOutOfRange_368) {

    // Arrange

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 100;

    size_t imageIdx = 0;



    value->toUint32(0, 10);  // Assuming toUint32 sets the value at index

    value->toUint32(1, 5);



    EXPECT_CALL(mockIoWrapper, write(::testing::NotNull(), ::testing::_)).Times(0);



    // Act & Assert

    EXPECT_THROW(tiffDataEntry.doWrite(mockIoWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx), Error);

}



TEST_F(TiffDataEntryTest_368, DoWriteWithNormalOffsets_368) {

    // Arrange

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 100;

    size_t imageIdx = 0;



    value->toUint32(0, 5);

    value->toUint32(1, 10);



    EXPECT_CALL(mockIoWrapper, write(::testing::NotNull(), ::testing::_)).Times(1);



    // Act

    size_t result = tiffDataEntry.doWrite(mockIoWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);



    // Assert

    EXPECT_EQ(result, value->size());

}
