#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.cpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest : public ::testing::Test {

protected:

    TiffEntryBase tiffEntry;

};



TEST_F(TiffEntryBaseTest_377, DoWriteData_ReturnsZero_377) {

    IoWrapper ioWrapper; // Assuming IoWrapper is a valid class in the context

    ByteOrder byteOrder = littleEndian; // Example value for ByteOrder

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_EQ(tiffEntry.doWriteData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffEntryBaseTest_377, DoWriteData_DoesNotModifyImageIdx_377) {

    IoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 42;



    tiffEntry.doWriteData(ioWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(imageIdx, 42);

}



TEST_F(TiffEntryBaseTest_377, DoWriteData_ZeroOffsetAndDataIdx_ReturnsZero_377) {

    IoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_EQ(tiffEntry.doWriteData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffEntryBaseTest_377, DoWriteData_NonZeroOffsetAndDataIdx_ReturnsZero_377) {

    IoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 10;

    size_t dataIdx = 20;

    size_t imageIdx = 0;



    EXPECT_EQ(tiffEntry.doWriteData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}



TEST_F(TiffEntryBaseTest_377, DoWriteData_LargeOffsetAndDataIdx_ReturnsZero_377) {

    IoWrapper ioWrapper;

    ByteOrder byteOrder = littleEndian;

    size_t offset = std::numeric_limits<size_t>::max();

    size_t dataIdx = std::numeric_limits<size_t>::max();

    size_t imageIdx = 0;



    EXPECT_EQ(tiffEntry.doWriteData(ioWrapper, byteOrder, offset, dataIdx, imageIdx), 0);

}
