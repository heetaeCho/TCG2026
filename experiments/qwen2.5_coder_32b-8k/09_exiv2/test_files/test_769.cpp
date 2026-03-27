#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;

using ::testing::Return;



class MockThumbnail : public Thumbnail {

public:

    MOCK_METHOD(const char*, extension, (), (const, override));

};



TEST_F(ExifThumbCTest_769, ExtensionReturnsEmptyStringWhenThumbnailIsNull_769) {

    const ExifData exifData;

    ExifThumbC exifThumbC(exifData);



    EXPECT_CALL(*Thumbnail::create(exifData), extension()).WillOnce(Return(""));



    EXPECT_STREQ("", exifThumbC.extension());

}



TEST_F(ExifThumbCTest_769, ExtensionReturnsValidStringWhenThumbnailIsNotNull_769) {

    const ExifData exifData;

    ExifThumbC exifThumbC(exifData);



    auto mockThumbnail = std::make_unique<MockThumbnail>();

    EXPECT_CALL(*mockThumbnail, extension()).WillOnce(Return("jpg"));



    // Replace the actual create method to return our mock object

    Thumbnail::UniquePtr (*createOriginal)(const Exiv2::ExifData&) = &Thumbnail::create;

    Thumbnail::create = [&](const Exiv2::ExifData& exifData) -> Thumbnail::UniquePtr {

        return std::move(mockThumbnail);

    };



    EXPECT_STREQ("jpg", exifThumbC.extension());



    // Restore the original create method

    Thumbnail::create = createOriginal;

}
