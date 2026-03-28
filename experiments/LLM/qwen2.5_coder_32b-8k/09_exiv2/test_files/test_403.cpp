#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffIfdMakernoteTest_403 : public ::testing::Test {

protected:

    std::unique_ptr<MnHeader> pHeader = nullptr;

    TiffIfdMakernote tiffIfdMakernote = TiffIfdMakernote(0x123, ifdGroupNone, ifdGroupExif, std::move(pHeader), false);

};



TEST_F(TiffIfdMakernoteTest_403, DoSizeData_ReturnsZero_403) {

    EXPECT_EQ(tiffIfdMakernote.doSizeData(), 0U);

}



TEST_F(TiffIfdMakernoteTest_403, SetByteOrder_DoesNotThrow_403) {

    EXPECT_NO_THROW(tiffIfdMakernote.setByteOrder(littleEndian));

}



TEST_F(TiffIfdMakernoteTest_403, ByteOrder_ReturnsSetByteOrder_403) {

    tiffIfdMakernote.setByteOrder(bigEndian);

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), bigEndian);

}



TEST_F(TiffIfdMakernoteTest_403, MnOffset_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.mnOffset(), 0U);

}



TEST_F(TiffIfdMakernoteTest_403, IfdOffset_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.ifdOffset(), 0U);

}



TEST_F(TiffIfdMakernoteTest_403, BaseOffset_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.baseOffset(), 0U);

}



TEST_F(TiffIfdMakernoteTest_403, SizeHeader_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.sizeHeader(), 0U);

}



// Mock IoWrapper for testing writeHeader

class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

};



TEST_F(TiffIfdMakernoteTest_403, WriteHeader_DoesNotThrow_403) {

    MockIoWrapper mockIoWrapper;

    EXPECT_NO_THROW(tiffIfdMakernote.writeHeader(mockIoWrapper, littleEndian));

}



// Mock TiffVisitor for testing doAccept

class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visit, (TiffComponent&), (override));

};



TEST_F(TiffIfdMakernoteTest_403, DoAccept_VisitsComponent_403) {

    MockTiffVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, visit(::testing::Ref(tiffIfdMakernote)));

    tiffIfdMakernote.doAccept(mockVisitor);

}



TEST_F(TiffIfdMakernoteTest_403, DoCount_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.doCount(), 0U);

}



// Mock IoWrapper for testing doWrite

TEST_F(TiffIfdMakernoteTest_403, DoWrite_DoesNotThrow_403) {

    MockIoWrapper mockIoWrapper;

    size_t imageIdx = 0;

    EXPECT_NO_THROW(tiffIfdMakernote.doWrite(mockIoWrapper, littleEndian, 0, 0, 0, imageIdx));

}



// Mock IoWrapper for testing doWriteData

TEST_F(TiffIfdMakernoteTest_403, DoWriteData_DoesNotThrow_403) {

    MockIoWrapper mockIoWrapper;

    size_t imageIdx = 0;

    EXPECT_NO_THROW(tiffIfdMakernote.doWriteData(mockIoWrapper, littleEndian, 0, 0, imageIdx));

}



// Mock IoWrapper for testing doWriteImage

TEST_F(TiffIfdMakernoteTest_403, DoWriteImage_DoesNotThrow_403) {

    MockIoWrapper mockIoWrapper;

    EXPECT_NO_THROW(tiffIfdMakernote.doWriteImage(mockIoWrapper, littleEndian));

}



TEST_F(TiffIfdMakernoteTest_403, DoSize_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.doSize(), 0U);

}



TEST_F(TiffIfdMakernoteTest_403, DoSizeImage_ReturnsZeroByDefault_403) {

    EXPECT_EQ(tiffIfdMakernote.doSizeImage(), 0U);

}
