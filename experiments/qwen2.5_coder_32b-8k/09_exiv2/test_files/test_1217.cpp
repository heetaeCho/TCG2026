#include <gtest/gtest.h>

#include "jpgimage.hpp"

#include "basicio.hpp"

#include <memory>



namespace Exiv2 {



class MockBasicIo : public BasicIo {

public:

    MockBasicIo(const std::string& data) : data_(data), pos_(0) {}



    int open() override { return 0; }

    int close() override { return 0; }

    size_t read(byte* buf, size_t rcount) override {

        if (pos_ >= data_.size()) return 0;

        size_t toRead = std::min(rcount, data_.size() - pos_);

        std::memcpy(buf, &data_[pos_], toRead);

        pos_ += toRead;

        return toRead;

    }

    void seekOrThrow(int64_t offset, Position pos, ErrorCode err) override {

        if (pos == beg)

            pos_ = offset;

        else if (pos == cur)

            pos_ += offset;

        else if (pos == end)

            pos_ = data_.size() + offset;



        if (pos_ < 0 || static_cast<size_t>(pos_) > data_.size())

            throw Error(err);

    }



private:

    std::string data_;

    size_t pos_;

};



TEST(JpegBaseTest, ReadMetadataExifPresent) {

    // Create a mock BasicIo object with an EXIF segment

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00\xff\xe1\x00\x1aExif\x00\x00II*\x00\x08\x00\x00\x00\x09\x00\x03\x00\x01\x00\x00\x00\x01\x00\x00\x00\x12";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



TEST(JpegBaseTest, ReadMetadataXmpPresent) {

    // Create a mock BasicIo object with an XMP segment

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00"

                          "\xff\xe1\x00\x1aExif\x00\x00II*\x00\x08\x00\x00\x00\x09\x00\x03\x00\x01\x00\x00\x00\x01\x00\x00\x00\x12"

                          "\xff\xe1\x01\x6chttp://ns.adobe.com/xap/1.0/\x00<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\x00";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



TEST(JpegBaseTest, ReadMetadataNoExifNoXmp) {

    // Create a mock BasicIo object without EXIF or XMP segments

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



TEST(JpegBaseTest, ReadMetadataInvalidJpeg) {

    // Create a mock BasicIo object with invalid JPEG data

    std::string jpegData = "This is not a JPEG file";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_THROW(jpeg.readMetadata(), Error);

}



TEST(JpegBaseTest, ReadMetadataCorruptedExif) {

    // Create a mock BasicIo object with corrupted EXIF data

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00"

                          "\xff\xe1\x00\x1aExif\x00\x00II*\x00";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_THROW(jpeg.readMetadata(), Error);

}



TEST(JpegBaseTest, ReadMetadataLargeSegment) {

    // Create a mock BasicIo object with an excessively large segment (should throw error)

    std::string jpegData = "\xff\xd8\xff\xe1\x7fff";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_THROW(jpeg.readMetadata(), Error);

}



TEST(JpegBaseTest, ReadMetadataIptcPresent) {

    // Create a mock BasicIo object with an IPTC segment

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00"

                          "\xff\xe1\x00\x1aExif\x00\x00II*\x00\x08\x00\x00\x00\x09\x00\x03\x00\x01\x00\x00\x00\x01\x00\x00\x00\x12"

                          "\xff\xed\x00\x5cPhotoshop 3.0 \x008BIM\x04\x04\x00\x00\x00\x01\x00\x00\x00\x00";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



TEST(JpegBaseTest, ReadMetadataCommentPresent) {

    // Create a mock BasicIo object with a comment segment

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00"

                          "\xff\xfe\x00\x1cThis is a comment segment in the JPEG file";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



TEST(JpegBaseTest, ReadMetadataIccProfilePresent) {

    // Create a mock BasicIo object with an ICC profile segment

    std::string jpegData = "\xff\xd8\xff\xe0\x00\x10JFIF\x00\x02\x01\x01\x00H\x00H\x00\x00"

                          "\xff\xe2\x00\x0eICC_PROFILE";

    MockBasicIo io(jpegData);

    JpegBase jpeg(ImageType::jpeg, std::make_unique<MockBasicIo>(jpegData), false, nullptr, 0);



    EXPECT_NO_THROW(jpeg.readMetadata());

}



} // namespace Exiv2
