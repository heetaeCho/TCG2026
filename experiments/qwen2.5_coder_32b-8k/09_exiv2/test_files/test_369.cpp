#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::InSequence;

using ::testing::Return;



class IoWrapperMock : public IoWrapper {

public:

    MOCK_METHOD(void, write, (const byte* data, size_t count), (override));

};



TEST_F(TiffImageEntryTest_369, PutWritesCorrectBuffer_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry;

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 20;

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, 4)).Times(1);



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

}



TEST_F(TiffImageEntryTest_369, PutUpdatesImageIndex_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry;

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 20;

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, _)).WillOnce(Return());



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

    EXPECT_EQ(imageIdx, 4); // Assuming strips_ size is 1 and off is even

}



TEST_F(TiffImageEntryTest_369, PutCalculatesOffsetCorrectlyForGroupGreaterThanMnId_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry;

    entry.setGroup(IfdId::exif); // Assuming exif > mnId

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 20;

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, _)).WillOnce(Return());



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

    // Since group > mnId, o2 should be offset + dataIdx initially

}



TEST_F(TiffImageEntryTest_369, PutHandlesOddOffsetCorrectly_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry;

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 21; // Making dataIdx odd

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, _)).WillOnce(Return());



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

    // o2 should be adjusted for the odd off value

}



TEST_F(TiffImageEntryTest_369, PutWritesMultipleOffsetsIfStripsExist_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry;

    entry.strips_.emplace(0, 4);

    entry.strips_.emplace(1, 8);

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 20;

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, _)).Times(2);



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

}



TEST_F(TiffImageEntryTest_369, PutHandlesZeroStripsGracefully_369) {

    IoWrapperMock ioWrapper;

    TiffImageEntry entry; // Assuming strips_ is empty

    size_t imageIdx = 0;

    size_t offset = 10;

    size_t dataIdx = 20;

    byteOrder byteOrder = littleEndian;



    EXPECT_CALL(ioWrapper, write(_, _)).Times(0);



    entry.doWrite(ioWrapper, byteOrder, offset, /*valueIdx*/0, dataIdx, imageIdx);

}

```


