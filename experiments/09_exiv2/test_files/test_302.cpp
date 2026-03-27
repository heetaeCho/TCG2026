#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking Value class for testing purposes

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(size_t, count, (), (const, override));

    MOCK_METHOD(uint32_t, toUint32, (size_t n), (const, override));

};



TEST_F(TiffDataEntryTest_302, SetStrips_NormalOperation_302) {

    MockValue mockSize;

    MockValue mockValue;



    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(1));

    EXPECT_CALL(mockSize, toUint32(0)).WillOnce(testing::Return(10));

    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[10] = {0};

    entry.setStrips(&mockSize, data, sizeof(data), 0);



    // Assuming setStrips sets pDataArea_ and sizeDataArea_

    EXPECT_EQ(entry.dataArea().pData_, data);

    EXPECT_EQ(entry.dataArea().size_, 10);

}



TEST_F(TiffDataEntryTest_302, SetStrips_NullSizePointer_302) {

    MockValue mockValue;



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[10] = {0};

    EXPECT_NO_THROW(entry.setStrips(nullptr, data, sizeof(data), 0));

}



TEST_F(TiffDataEntryTest_302, SetStrips_NullDataPointer_302) {

    MockValue mockSize;



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(1));



    EXPECT_NO_THROW(entry.setStrips(&mockSize, nullptr, 0, 0));

}



TEST_F(TiffDataEntryTest_302, SetStrips_EmptySizeCount_302) {

    MockValue mockSize;

    MockValue mockValue;



    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(0));



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[10] = {0};

    EXPECT_NO_THROW(entry.setStrips(&mockSize, data, sizeof(data), 0));

}



TEST_F(TiffDataEntryTest_302, SetStrips_DifferentComponentCounts_302) {

    MockValue mockSize;

    MockValue mockValue;



    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(1));

    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[10] = {0};

    EXPECT_NO_THROW(entry.setStrips(&mockSize, data, sizeof(data), 0));

}



TEST_F(TiffDataEntryTest_302, SetStrips_DataAreaExceedsBuffer_302) {

    MockValue mockSize;

    MockValue mockValue;



    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(1));

    EXPECT_CALL(mockSize, toUint32(0)).WillOnce(testing::Return(20));

    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(1));



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[10] = {0};

    EXPECT_NO_THROW(entry.setStrips(&mockSize, data, sizeof(data), 0));

}



TEST_F(TiffDataEntryTest_302, SetStrips_DataAreaNotContiguous_302) {

    MockValue mockSize;

    MockValue mockValue;



    EXPECT_CALL(mockSize, count()).WillOnce(testing::Return(2));

    EXPECT_CALL(mockSize, toUint32(0)).WillOnce(testing::Return(5));

    EXPECT_CALL(mockSize, toUint32(1)).WillOnce(testing::Return(5));

    EXPECT_CALL(mockValue, count()).WillOnce(testing::Return(2));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(testing::Return(0));

    EXPECT_CALL(mockValue, toUint32(1)).WillOnce(testing::Return(10));



    Exiv2::Internal::TiffDataEntry entry(/*tag*/, /*group*/, /*tiffType*/);

    entry.setValue(std::make_unique<MockValue>(mockValue));



    byte data[15] = {0};

    EXPECT_NO_THROW(entry.setStrips(&mockSize, data, sizeof(data), 0));

}
