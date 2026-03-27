#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

namespace Internal {



class IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte* data, size_t count), ());

};



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_ReturnsZeroForNormalOperation_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    size_t result = makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_DoesNotModifyImageIdxForNormalOperation_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 42;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(imageIdx, 42);

}



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_HandlesZeroOffsetCorrectly_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    size_t result = makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_HandlesNonZeroOffsetCorrectly_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 1024;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    size_t result = makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_HandlesZeroDataIdxCorrectly_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 0;

    size_t dataIdx = 0;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    size_t result = makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



TEST_F(TiffIfdMakernoteTest_381, DoWriteData_HandlesNonZeroDataIdxCorrectly_381) {

    TiffIfdMakernote makernote;

    IoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian, doesn't matter for this test

    size_t offset = 0;

    size_t dataIdx = 512;

    size_t imageIdx = 0;



    EXPECT_CALL(mockIoWrapper, write(_, _)).Times(0); // Ensure no writes occur



    size_t result = makernote.doWriteData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);



    EXPECT_EQ(result, 0);

}



} // namespace Internal

} // namespace Exiv2
