#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included from exiv2

using namespace Exiv2::Internal;



class TiffMnEntryTest : public ::testing::Test {

protected:

    TiffMnEntry tiffMnEntry;

    MockTiffIfdMakernote* mockMn; // Assuming we can create a mock for TiffIfdMakernote



    TiffMnEntryTest() : tiffMnEntry(0x1234, ifdExif, ifdInteroperability) {

        mockMn = new MockTiffIfdMakernote();

        tiffMnEntry.mn_.reset(mockMn);

    }

};



TEST_F(TiffMnEntryTest, DoSize_ReturnsMockedSize_393) {

    EXPECT_CALL(*mockMn, size()).WillOnce(::testing::Return(42));



    size_t result = tiffMnEntry.doSize();

    EXPECT_EQ(result, 42);

}



TEST_F(TiffMnEntryTest, DoSize_ReturnsBaseDoSize_WhenMnIsNullptr_393) {

    tiffMnEntry.mn_.reset();



    size_t result = tiffMnEntry.doSize();

    // Assuming TiffEntryBase::doSize() returns a known constant for this test

    EXPECT_EQ(result, TiffEntryBase(0x1234, ifdExif, ttUndefined).doSize());

}



TEST_F(TiffMnEntryTest, DoSize_ReturnsValidSize_WhenMnIsNotNullptr_393) {

    EXPECT_CALL(*mockMn, size()).WillOnce(::testing::Return(100));



    size_t result = tiffMnEntry.doSize();

    EXPECT_EQ(result, 100);

}
