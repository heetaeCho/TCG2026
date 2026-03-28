#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.cpp" // Assuming the file contains the TiffEntryBase class



using namespace Exiv2::Internal;

using ::testing::_;



class IoWrapperMock : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t dataSize), (override));

};



class TiffEntryBaseTest_366 : public ::testing::Test {

protected:

    std::vector<byte> sampleData = {1, 2, 3, 4};

    IoWrapperMock ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t imageIdx = 0;



    TiffEntryBase* entryWithNonEmptyValue;

    TiffEntryBase* entryWithEmptyValue;



    void SetUp() override {

        entryWithNonEmptyValue = new TiffEntryBase();

        entryWithNonEmptyValue->pValue_ = &sampleData;



        entryWithEmptyValue = new TiffEntryBase();

        entryWithEmptyValue->pValue_ = nullptr;

    }



    void TearDown() override {

        delete entryWithNonEmptyValue;

        delete entryWithEmptyValue;

    }

};



TEST_F(TiffEntryBaseTest_366, DoWrite_ReturnsSizeOfDataWritten_366) {

    EXPECT_CALL(ioWrapper, write(_, sampleData.size())).WillOnce(::testing::Return(sampleData.size()));

    size_t result = entryWithNonEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

    ASSERT_EQ(result, sampleData.size());

}



TEST_F(TiffEntryBaseTest_366, DoWrite_CallsIoWrapperWriteWithCorrectParameters_366) {

    EXPECT_CALL(ioWrapper, write(sampleData.data(), sampleData.size()));

    entryWithNonEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

}



TEST_F(TiffEntryBaseTest_366, DoWrite_ReturnsZeroForEmptyValue_366) {

    size_t result = entryWithEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

    ASSERT_EQ(result, 0);

}



TEST_F(TiffEntryBaseTest_366, DoWrite_ReturnsZeroForNullValue_366) {

    size_t result = entryWithEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

    ASSERT_EQ(result, 0);

}



TEST_F(TiffEntryBaseTest_366, DoWrite_DoesNotCallIoWrapperWriteForEmptyValue_366) {

    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);

    entryWithEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

}



TEST_F(TiffEntryBaseTest_366, DoWrite_DoesNotCallIoWrapperWriteForNullValue_366) {

    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);

    entryWithEmptyValue->doWrite(ioWrapper, byteOrder, 0, 0, 0, imageIdx);

}
