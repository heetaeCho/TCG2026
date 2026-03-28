#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



using namespace Exiv2::Internal;



class TiffComponentTest_388 : public ::testing::Test {

protected:

    TiffComponent component{1, IfdId::rootIfd};

};



TEST_F(TiffComponentTest_388, SizeReturnsZeroByDefault_388) {

    EXPECT_EQ(component.size(), 0);

}



TEST_F(TiffComponentTest_388, CountReturnsZeroByDefault_388) {

    EXPECT_EQ(component.count(), 0);

}



TEST_F(TiffComponentTest_388, SizeDataReturnsZeroByDefault_388) {

    EXPECT_EQ(component.sizeData(), 0);

}



TEST_F(TiffComponentTest_388, SizeImageReturnsZeroByDefault_388) {

    EXPECT_EQ(component.sizeImage(), 0);

}



TEST_F(TiffComponentTest_388, TagReturnsProvidedValue_388) {

    EXPECT_EQ(component.tag(), 1);

}



TEST_F(TiffComponentTest_388, GroupReturnsProvidedValue_388) {

    EXPECT_EQ(component.group(), IfdId::rootIfd);

}



TEST_F(TiffComponentTest_388, StartReturnsNullByDefault_388) {

    EXPECT_EQ(component.start(), nullptr);

}



TEST_F(TiffComponentTest_388, SetStartSetsThePointerCorrectly_388) {

    byte buffer[10];

    component.setStart(buffer);

    EXPECT_EQ(component.start(), buffer);

}



// Mocks for IoWrapper, TiffPath, SharedPtr, UniquePtr, and TiffVisitor

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t offset, size_t count), (override));

};



class MockTiffPath : public TiffPath {

public:

    // No additional methods needed for this test

};



TEST_F(TiffComponentTest_388, WriteDoesNotThrowOnDefaultState_388) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = bigEndian;

    size_t offset = 0;

    size_t valueIdx = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_NO_THROW(component.write(mockIoWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx));

}



TEST_F(TiffComponentTest_388, WriteDataDoesNotThrowOnDefaultState_388) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = bigEndian;

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_NO_THROW(component.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx));

}



TEST_F(TiffComponentTest_388, WriteImageDoesNotThrowOnDefaultState_388) {

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = bigEndian;



    EXPECT_NO_THROW(component.writeImage(mockIoWrapper, byteOrder));

}
