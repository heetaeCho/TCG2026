#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "value.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class TiffImageEntryTest : public Test {

protected:

    std::unique_ptr<TiffImageEntry> tiffImageEntry;

    NiceMock<MockValue> mockSizeValue;

    NiceMock<MockValue> mockOffsetValue;



    void SetUp() override {

        tiffImageEntry = std::make_unique<TiffImageEntry>(0x123, ifdExif, ttLong);

        ON_CALL(mockSizeValue, count()).WillByDefault(Return(2));

        ON_CALL(mockOffsetValue, count()).WillByDefault(Return(2));

    }

};



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

};



TEST_F(TiffImageEntryTest_303, SetStripsWithValidData_303) {

    const byte data[] = {1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_CALL(mockSizeValue, toUint32(0)).WillOnce(Return(2));

    EXPECT_CALL(mockSizeValue, toUint32(1)).WillOnce(Return(2));

    EXPECT_CALL(mockOffsetValue, toUint32(0)).WillOnce(Return(0));

    EXPECT_CALL(mockOffsetValue, toUint32(1)).WillOnce(Return(4));



    tiffImageEntry->setStrips(&mockSizeValue, data, sizeof(data), 0);



    // Assuming that the internal state is correctly modified and accessible via some public method

}



TEST_F(TiffImageEntryTest_303, SetStripsWithNullPointerForSize_303) {

    const byte data[] = {1, 2, 3, 4, 5, 6, 7, 8};

    EXPECT_CALL(mockOffsetValue, count()).WillOnce(Return(2));



    tiffImageEntry->setStrips(nullptr, data, sizeof(data), 0);



    // Assuming that the internal state remains unchanged and accessible via some public method

}



TEST_F(TiffImageEntryTest_303, SetStripsWithNullPointerForData_303) {

    EXPECT_CALL(mockSizeValue, count()).WillOnce(Return(2));



    tiffImageEntry->setStrips(&mockSizeValue, nullptr, 0, 0);



    // Assuming that the internal state remains unchanged and accessible via some public method

}



TEST_F(TiffImageEntryTest_303, SetStripsWithMismatchedCounts_303) {

    const byte data[] = {1, 2, 3, 4, 5, 6, 7, 8};

    ON_CALL(mockSizeValue, count()).WillByDefault(Return(1));



    tiffImageEntry->setStrips(&mockSizeValue, data, sizeof(data), 0);



    // Assuming that the internal state remains unchanged and accessible via some public method

}



TEST_F(TiffImageEntryTest_303, SetStripsWithStripOutsideDataArea_303) {

    const byte data[] = {1, 2, 3, 4};

    EXPECT_CALL(mockSizeValue, toUint32(0)).WillOnce(Return(2));

    EXPECT_CALL(mockOffsetValue, toUint32(0)).WillOnce(Return(5));



    tiffImageEntry->setStrips(&mockSizeValue, data, sizeof(data), 0);



    // Assuming that the internal state remains unchanged and accessible via some public method

}



TEST_F(TiffImageEntryTest_303, SetStripsWithBaseOffsetOutsideDataArea_303) {

    const byte data[] = {1, 2, 3, 4};

    EXPECT_CALL(mockSizeValue, toUint32(0)).WillOnce(Return(2));

    EXPECT_CALL(mockOffsetValue, toUint32(0)).WillOnce(Return(0));



    tiffImageEntry->setStrips(&mockSizeValue, data, sizeof(data), 5);



    // Assuming that the internal state remains unchanged and accessible via some public method

}
