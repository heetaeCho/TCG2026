#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockValue : public Value {

public:

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(size_t, copy, (byte *buf, ByteOrder byteOrder), (override));

};



class TiffEntryBaseTest_300 : public ::testing::Test {

protected:

    std::unique_ptr<MockValue> mockValue;

    TiffEntryBase tiffEntry;



    TiffEntryBaseTest_300()

        : mockValue(std::make_unique<MockValue>()),

          tiffEntry(0, IfdId::ifdExif, TiffType::undefined) {}

};



TEST_F(TiffEntryBaseTest_300, UpdateValueWithNullPtr_300) {

    tiffEntry.updateValue(nullptr, ByteOrder::big);

    // Expect no change in state as value is nullptr

}



TEST_F(TiffEntryBaseTest_300, UpdateValueWithSmallerSize_300) {

    const size_t initialSize = 10;

    byte buffer[initialSize];

    tiffEntry.setData(buffer, initialSize, std::make_shared<DataBuf>(buffer, initialSize));



    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(5));

    EXPECT_CALL(*mockValue, copy(::testing::NotNull(), ByteOrder::big)).WillOnce(::testing::Return(5));



    tiffEntry.updateValue(std::move(mockValue), ByteOrder::big);

}



TEST_F(TiffEntryBaseTest_300, UpdateValueWithSameSize_300) {

    const size_t initialSize = 10;

    byte buffer[initialSize];

    tiffEntry.setData(buffer, initialSize, std::make_shared<DataBuf>(buffer, initialSize));



    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(initialSize));

    EXPECT_CALL(*mockValue, copy(::testing::NotNull(), ByteOrder::big)).WillOnce(::testing::Return(initialSize));



    tiffEntry.updateValue(std::move(mockValue), ByteOrder::big);

}



TEST_F(TiffEntryBaseTest_300, UpdateValueWithLargerSize_300) {

    const size_t initialSize = 10;

    byte buffer[initialSize];

    tiffEntry.setData(buffer, initialSize, std::make_shared<DataBuf>(buffer, initialSize));



    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(20));

    EXPECT_CALL(*mockValue, copy(::testing::NotNull(), ByteOrder::big)).WillOnce(::testing::Return(20));



    tiffEntry.updateValue(std::move(mockValue), ByteOrder::big);

}



TEST_F(TiffEntryBaseTest_300, UpdateValueResizesStorage_300) {

    const size_t initialSize = 10;

    byte buffer[initialSize];

    tiffEntry.setData(buffer, initialSize, std::make_shared<DataBuf>(buffer, initialSize));



    EXPECT_CALL(*mockValue, size()).WillOnce(::testing::Return(20));

    EXPECT_CALL(*mockValue, copy(::testing::NotNull(), ByteOrder::big)).WillOnce(::testing::Return(20));



    tiffEntry.updateValue(std::move(mockValue), ByteOrder::big);

}
