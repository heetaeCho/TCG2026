#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"



namespace {

using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockThumbnail : public Exiv2::Thumbnail {

public:

    MOCK_METHOD(const Exiv2::DataBuf, copy, (const Exiv2::ExifData & exifData), (const, override));

    MOCK_METHOD(const char*, mimeType, (), (const, override));

    MOCK_METHOD(const char*, extension, (), (const, override));

};



class ExifThumbCTest : public ::testing::Test {

protected:

    NiceMock<MockThumbnail> mock_thumbnail;

    std::unique_ptr<Exiv2::Thumbnail> thumbnail_ptr;

    Exiv2::ExifData exif_data;

    Exiv2::ExifThumbC exif_thumb_c;



    void SetUp() override {

        ON_CALL(mock_thumbnail, copy(_)).WillByDefault(Return(Exiv2::DataBuf()));

        ON_CALL(mock_thumbnail, mimeType()).WillByDefault(Return("image/jpeg"));

        ON_CALL(mock_thumbnail, extension()).WillByDefault(Return("jpg"));

        thumbnail_ptr = std::make_unique<MockThumbnail>(mock_thumbnail);

        Exiv2::Thumbnail::create = [](const Exiv2::ExifData & exifData) -> Exiv2::Thumbnail::UniquePtr {

            return std::make_unique<MockThumbnail>();

        };

        exif_thumb_c = Exiv2::ExifThumbC(exif_data);

    }

};



TEST_F(ExifThumbCTest, CopyReturnsEmptyBuffer_766) {

    EXPECT_CALL(mock_thumbnail, copy(_)).WillOnce(Return(Exiv2::DataBuf()));

    Exiv2::DataBuf result = exif_thumb_c.copy();

    EXPECT_EQ(result.pData_, nullptr);

    EXPECT_EQ(result.size_, 0u);

}



TEST_F(ExifThumbCTest, CopyReturnsValidBuffer_766) {

    const char* data = "dummy_data";

    size_t size = 10;

    Exiv2::DataBuf expected_buffer{const_cast<char*>(data), size};

    EXPECT_CALL(mock_thumbnail, copy(_)).WillOnce(Return(expected_buffer));

    Exiv2::DataBuf result = exif_thumb_c.copy();

    EXPECT_EQ(result.pData_, data);

    EXPECT_EQ(result.size_, size);

}



TEST_F(ExifThumbCTest, MimeTypeReturnsValidString_766) {

    const char* expected_mime_type = "image/jpeg";

    EXPECT_CALL(mock_thumbnail, mimeType()).WillOnce(Return(expected_mime_type));

    const char* result = exif_thumb_c.mimeType();

    EXPECT_STREQ(result, expected_mime_type);

}



TEST_F(ExifThumbCTest, ExtensionReturnsValidString_766) {

    const char* expected_extension = "jpg";

    EXPECT_CALL(mock_thumbnail, extension()).WillOnce(Return(expected_extension));

    const char* result = exif_thumb_c.extension();

    EXPECT_STREQ(result, expected_extension);

}

}  // namespace
