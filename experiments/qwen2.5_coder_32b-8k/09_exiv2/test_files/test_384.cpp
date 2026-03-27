#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(void, write, (const byte* data, size_t dataSize), (override));

};



class TiffEntryBaseTest_384 : public ::testing::Test {

protected:

    TiffEntryBase tiffEntry;

    MockIoWrapper mockIoWrapper;

};



TEST_F(TiffEntryBaseTest_384, DoWriteImage_ReturnsZeroForNormalOperation_384) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // No interaction expected with IoWrapper

    size_t result = tiffEntry.doWriteImage(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, 0);

}



TEST_F(TiffEntryBaseTest_384, DoWriteImage_ReturnsZeroForBoundaryConditions_384) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // No interaction expected with IoWrapper

    size_t result = tiffEntry.doWriteImage(mockIoWrapper, bigEndian);

    EXPECT_EQ(result, 0);

}



TEST_F(TiffEntryBaseTest_384, DoWriteImage_VerifiesNoExternalInteractions_384) {

    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // No interaction expected with IoWrapper

    tiffEntry.doWriteImage(mockIoWrapper, littleEndian);

}
