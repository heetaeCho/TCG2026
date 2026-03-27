#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    class MockExifKey : public ExifKey {

    public:

        MOCK_METHOD(uint16_t, tag, (), (const) override);

        MOCK_METHOD(IfdId, ifdId, (), (const) override);

    };

}



class ExifTagsTest_1323 : public ::testing::Test {

protected:

    Exiv2::ExifTags exifTags;

};



TEST_F(ExifTagsTest_1323, DefaultCount_ReturnsKnownTagCount_1323) {

    Exiv2::MockExifKey key;

    EXPECT_CALL(key, tag()).WillOnce(::testing::Return(0x9003)); // Known tag for DateTimeOriginal

    EXPECT_CALL(key, ifdId()).WillOnce(::testing::Return(Exiv2::IfdId::exifIFD));



    uint16_t count = exifTags.defaultCount(key);

    EXPECT_EQ(count, 1); // DateTimeOriginal has a count of 1

}



TEST_F(ExifTagsTest_1323, DefaultCount_ReturnsUnknownTagCount_1323) {

    Exiv2::MockExifKey key;

    EXPECT_CALL(key, tag()).WillOnce(::testing::Return(0xFFFF)); // Unknown tag

    EXPECT_CALL(key, ifdId()).WillOnce(::testing::Return(Exiv2::IfdId::exifIFD));



    uint16_t count = exifTags.defaultCount(key);

    EXPECT_EQ(count, Exiv2::Internal::unknownTag.count_);

}



TEST_F(ExifTagsTest_1323, DefaultCount_BoundaryCondition_1323) {

    Exiv2::MockExifKey key;

    EXPECT_CALL(key, tag()).WillOnce(::testing::Return(0x0000)); // Minimum valid tag

    EXPECT_CALL(key, ifdId()).WillOnce(::testing::Return(Exiv2::IfdId::exifIFD));



    uint16_t count = exifTags.defaultCount(key);

    // Assuming 0x0000 is not a known tag in this context

    EXPECT_EQ(count, Exiv2::Internal::unknownTag.count_);

}



TEST_F(ExifTagsTest_1323, DefaultCount_ExceptionalCase_1323) {

    Exiv2::MockExifKey key;

    EXPECT_CALL(key, tag()).WillOnce(::testing::Return(0x9003)); // Known tag for DateTimeOriginal

    EXPECT_CALL(key, ifdId()).WillOnce(::testing::Return(static_cast<Exiv2::IfdId>(-1))); // Invalid IfdId



    uint16_t count = exifTags.defaultCount(key);

    EXPECT_EQ(count, Exiv2::Internal::unknownTag.count_);

}
