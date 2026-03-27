#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace Exiv2 {

namespace Internal {



class MockIoWrapper : public IoWrapper {

public:

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

};



class TiffIfdMakernoteTest_372 : public ::testing::Test {

protected:

    MockIoWrapper mockIoWrapper;

    ByteOrder byteOrder = littleEndian; // or bigEndian as needed

    size_t offset = 0;

    size_t imageIdx = 0;

    TiffIfdMakernote tiffIfdMakernote;



    void SetUp() override {

        // Setup any necessary initial state here if needed

    }

};



TEST_F(TiffIfdMakernoteTest_372, DoWrite_ReturnsCorrectLength_372) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(4));

    

    size_t result = tiffIfdMakernote.doWrite(mockIoWrapper, byteOrder, offset, 0, 0, imageIdx);

    EXPECT_EQ(result, 4); // Assuming writeHeader returns 4 and ifd_.write returns 0

}



TEST_F(TiffIfdMakernoteTest_372, DoWrite_SetsCorrectOffsetAndByteOrder_372) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(4));



    tiffIfdMakernote.doWrite(mockIoWrapper, byteOrder, offset, 0, 0, imageIdx);

    

    // Verify mnOffset_ and byteOrder are set correctly

    EXPECT_EQ(tiffIfdMakernote.mnOffset_, offset);

    EXPECT_EQ(tiffIfdMakernote.byteOrder(), byteOrder);

}



TEST_F(TiffIfdMakernoteTest_372, DoWrite_ZeroOffset_ReturnsCorrectLength_372) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(4));



    size_t result = tiffIfdMakernote.doWrite(mockIoWrapper, byteOrder, 0, 0, 0, imageIdx);

    EXPECT_EQ(result, 4); // Assuming writeHeader returns 4 and ifd_.write returns 0

}



TEST_F(TiffIfdMakernoteTest_372, DoWrite_NonZeroOffset_ReturnsCorrectLength_372) {

    offset = 10;

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(4));



    size_t result = tiffIfdMakernote.doWrite(mockIoWrapper, byteOrder, offset, 0, 0, imageIdx);

    EXPECT_EQ(result, 4); // Assuming writeHeader returns 4 and ifd_.write returns 0

}



TEST_F(TiffIfdMakernoteTest_372, DoWrite_MockFailure_ReturnsZeroLength_372) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).Times(1).WillOnce(::testing::Return(0));



    size_t result = tiffIfdMakernote.doWrite(mockIoWrapper, byteOrder, offset, 0, 0, imageIdx);

    EXPECT_EQ(result, 0); // Assuming writeHeader returns 0 and ifd_.write returns 0

}



} // namespace Internal

} // namespace Exiv2
