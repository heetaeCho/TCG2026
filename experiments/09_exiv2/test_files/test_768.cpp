#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



using namespace ::testing;



namespace Exiv2 {

    class MockThumbnail : public Thumbnail {

    public:

        MOCK_METHOD(const char*, mimeType, (), (const, override));

        static UniquePtr create(const ExifData & exifData) {

            auto mock = std::make_unique<MockThumbnail>();

            return mock;

        }

    };

}



class ExifThumbCTest : public ::testing::Test {

protected:

    class MockExifData {};

    Exiv2::ExifThumbC exifThumbC{exifData};



    ExifThumbCTest() {

        EXPECT_CALL(mockThumbnail, mimeType()).WillOnce(Return("image/jpeg"));

        ON_CALL(*mockThumbnailPtr, mimeType()).WillByDefault(Return("image/jpeg"));

    }



    ~ExifThumbCTest() override {}



    MockExifData exifData;

    NiceMock<Exiv2::MockThumbnail> mockThumbnail;

    std::shared_ptr<Exiv2::MockThumbnail> mockThumbnailPtr = std::make_shared<NiceMock<Exiv2::MockThumbnail>>();

};



TEST_F(ExifThumbCTest, MimeTypeReturnsNonNull_768) {

    EXPECT_NE(exifThumbC.mimeType(), nullptr);

}



TEST_F(ExifThumbCTest, MimeTypeMatchesExpectedValue_768) {

    EXPECT_STREQ(exifThumbC.mimeType(), "image/jpeg");

}



TEST_F(ExifThumbCTest, MimeTypeReturnsEmptyStringWhenThumbnailIsNull_768) {

    EXPECT_CALL(mockThumbnail, mimeType()).WillOnce(Return(nullptr));

    exifThumbC = Exiv2::ExifThumbC{exifData};

    EXPECT_STREQ(exifThumbC.mimeType(), "");

}



TEST_F(ExifThumbCTest, MimeTypeCallsMimeTypeOnThumbnail_768) {

    EXPECT_CALL(mockThumbnail, mimeType()).Times(1);

    exifThumbC.mimeType();

}
