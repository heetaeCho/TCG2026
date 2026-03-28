#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock IoWrapper for testing purposes

class MockIoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t dataSize), ());

    MOCK_METHOD(void, putb, (byte data), ());

};



namespace Exiv2 { namespace Internal {



TEST_F(TiffDataEntryTest_379, DoWriteData_ReturnsZeroWhenNoValue_379) {

    TiffDataEntry entry;

    MockIoWrapper ioWrapper;

    size_t imageIdx = 0;



    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);



    EXPECT_EQ(result, 0);

    EXPECT_EQ(imageIdx, 0);

}



TEST_F(TiffDataEntryTest_379, DoWriteData_WritesDataAndAligns_379) {

    TiffDataEntry entry;

    MockIoWrapper ioWrapper;

    size_t imageIdx = 0;



    // Assuming pValue() is set to a valid DataBuf with some data

    // For simplicity, we mock the behavior of pValue()

    DataBuf testData = {0x1, 0x2, 0x3};

    entry.pValue_ = std::make_unique<DataBuf>(testData);



    EXPECT_CALL(ioWrapper, write(testData.c_data(), testData.size())).Times(1).WillOnce(::testing::Return(testData.size()));

    EXPECT_CALL(ioWrapper, putb(0x0)).Times(1);



    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);



    EXPECT_EQ(result, testData.size() + 1); // Data size + alignment byte

}



TEST_F(TiffDataEntryTest_379, DoWriteData_WritesDataWithoutAlignment_379) {

    TiffDataEntry entry;

    MockIoWrapper ioWrapper;

    size_t imageIdx = 0;



    // Assuming pValue() is set to a valid DataBuf with even data size

    DataBuf testData = {0x1, 0x2};

    entry.pValue_ = std::make_unique<DataBuf>(testData);



    EXPECT_CALL(ioWrapper, write(testData.c_data(), testData.size())).Times(1).WillOnce(::testing::Return(testData.size()));

    EXPECT_CALL(ioWrapper, putb(0x0)).Times(0); // No alignment byte needed



    size_t result = entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);



    EXPECT_EQ(result, testData.size());

}



TEST_F(TiffDataEntryTest_379, DoWriteData_VerifiesExternalInteractions_379) {

    TiffDataEntry entry;

    MockIoWrapper ioWrapper;

    size_t imageIdx = 0;



    // Assuming pValue() is set to a valid DataBuf with some data

    DataBuf testData = {0x1, 0x2};

    entry.pValue_ = std::make_unique<DataBuf>(testData);



    EXPECT_CALL(ioWrapper, write(testData.c_data(), testData.size())).Times(1).WillOnce(::testing::Return(testData.size()));

    EXPECT_CALL(ioWrapper, putb(0x0)).Times(0); // No alignment byte needed



    entry.doWriteData(ioWrapper, littleEndian, 0, 0, imageIdx);

}



}} // namespace Exiv2::Internal
