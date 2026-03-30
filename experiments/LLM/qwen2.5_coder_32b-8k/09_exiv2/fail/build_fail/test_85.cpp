#include <gtest/gtest.h>

#include "jp2image.hpp"

#include "basicio.hpp"

#include "types.hpp"

#include "error.hpp"

#include <array>

#include <memory>



namespace Exiv2 {

namespace {



class MockBasicIo : public BasicIo {

public:

    MockBasicIo() = default;



    int open() override { return 0; }

    int close() override { return 0; }



    size_t write(const byte* data, size_t wcount) override {

        writtenData.insert(writtenData.end(), data, data + wcount);

        return wcount;

    }



    size_t read(byte* buf, size_t rcount) override {

        size_t bytesRead = std::min(rcount, availableData.size() - readPosition);

        std::copy(availableData.begin() + readPosition, availableData.begin() + readPosition + bytesRead, buf);

        readPosition += bytesRead;

        return bytesRead;

    }



    int seek(int64_t offset, Position pos) override {

        switch (pos) {

            case beg:

                readPosition = offset;

                break;

            case cur:

                readPosition += offset;

                break;

            case end:

                readPosition = availableData.size() + offset;

                break;

        }

        return 0;

    }



    size_t tell() const override { return readPosition; }

    size_t size() const override { return availableData.size(); }

    bool isopen() const override { return true; }

    int error() const override { return 0; }

    bool eof() const override { return readPosition >= availableData.size(); }

    const std::string& path() const override { static const std::string dummyPath = "dummy"; return dummyPath; }



    void populateFakeData(const std::vector<byte>& data) {

        availableData = data;

    }



    std::vector<byte> writtenData;

private:

    size_t readPosition = 0;

    std::vector<byte> availableData;

};



TEST(Jp2ImageTest, ReadMetadata_ImageHeaderBox) {

    MockBasicIo io;

    Jp2Image image(std::make_unique<MockBasicIo>(), false);



    // JP2 Signature Box (12 bytes)

    std::array<byte, 12> signatureBox = {0x00, 0x00, 0x00, 0x0C, 'j', 'P', ' ', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    // File Type Box (24 bytes)

    std::array<byte, 24> fileTypeBox = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'j', 'p', '2', ' ', 'j', 'p', '2', 'h'};

    // Header Box (36 bytes)

    std::array<byte, 36> headerBox = {0x00, 0x00, 0x00, 0x1C, 'h', 'l', ' ', ' ', 0x00, 0x00, 0x00, 0x0E, 'j', 'p', '2', 'c'};

    // Image Header Box (34 bytes)

    std::array<byte, 34> imageHeaderBox = {

        0x00, 0x00, 0x00, 0x16, 'i', 'h', 'd', 'r',

        0x00, 0x00, 0x07, 0xD0, // imageHeight = 2000

        0x00, 0x00, 0x08, 0x34, // imageWidth = 2100

        0x01,                   // componentCount = 1

        0x08,                   // bpc = 8

        0x06,                   // c = 6

        0x00,                   // unkC = 0

        0x00                    // ipr = 0

    };



    std::vector<byte> data;

    data.insert(data.end(), signatureBox.begin(), signatureBox.end());

    data.insert(data.end(), fileTypeBox.begin(), fileTypeBox.end());

    data.insert(data.end(), headerBox.begin(), headerBox.end());

    data.insert(data.end(), imageHeaderBox.begin(), imageHeaderBox.end());



    io.populateFakeData(data);

    image.io() = std::move(io);



    EXPECT_NO_THROW(image.readMetadata());

    EXPECT_EQ(image.pixelWidth(), 2100u);

    EXPECT_EQ(image.pixelHeight(), 2000u);

}



TEST(Jp2ImageTest, ReadMetadata_UuidBox_Exif) {

    MockBasicIo io;

    Jp2Image image(std::make_unique<MockBasicIo>(), false);



    // JP2 Signature Box (12 bytes)

    std::array<byte, 12> signatureBox = {0x00, 0x00, 0x00, 0x0C, 'j', 'P', ' ', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    // File Type Box (24 bytes)

    std::array<byte, 24> fileTypeBox = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'j', 'p', '2', ' ', 'j', 'p', '2', 'h'};

    // Header Box (36 bytes)

    std::array<byte, 36> headerBox = {0x00, 0x00, 0x00, 0x1C, 'h', 'l', ' ', ' ', 0x00, 0x00, 0x00, 0x0E, 'j', 'p', '2', 'c'};

    // Uuid Box for Exif (34 bytes)

    std::array<byte, 34> uuidBoxExif = {

        0x00, 0x00, 0x00, 0x16, 'u', 'u', 'i', 'd',

        74, 112, 103, 84, 105, 102, 102, 69, 120, 105, 102, 45, 62, 74, 80, 50,

        // Exif data placeholder

        0x00, 0x00, 0x00, 0x00

    };



    std::vector<byte> data;

    data.insert(data.end(), signatureBox.begin(), signatureBox.end());

    data.insert(data.end(), fileTypeBox.begin(), fileTypeBox.end());

    data.insert(data.end(), headerBox.begin(), headerBox.end());

    data.insert(data.end(), uuidBoxExif.begin(), uuidBoxExif.end());



    io.populateFakeData(data);

    image.io() = std::move(io);



    EXPECT_NO_THROW(image.readMetadata());

}



TEST(Jp2ImageTest, ReadMetadata_UuidBox_Iptc) {

    MockBasicIo io;

    Jp2Image image(std::make_unique<MockBasicIo>(), false);



    // JP2 Signature Box (12 bytes)

    std::array<byte, 12> signatureBox = {0x00, 0x00, 0x00, 0x0C, 'j', 'P', ' ', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    // File Type Box (24 bytes)

    std::array<byte, 24> fileTypeBox = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'j', 'p', '2', ' ', 'j', 'p', '2', 'h'};

    // Header Box (36 bytes)

    std::array<byte, 36> headerBox = {0x00, 0x00, 0x00, 0x1C, 'h', 'l', ' ', ' ', 0x00, 0x00, 0x00, 0x0E, 'j', 'p', '2', 'c'};

    // Uuid Box for IPTC (34 bytes)

    std::array<byte, 34> uuidBoxIptc = {

        0x00, 0x00, 0x00, 0x16, 'u', 'u', 'i', 'd',

        51, 199, 164, 210, 184, 29, 71, 35, 160, 186, 241, 163, 224, 151, 173, 56,

        // IPTC data placeholder

        0x00, 0x00, 0x00, 0x00

    };



    std::vector<byte> data;

    data.insert(data.end(), signatureBox.begin(), signatureBox.end());

    data.insert(data.end(), fileTypeBox.begin(), fileTypeBox.end());

    data.insert(data.end(), headerBox.begin(), headerBox.end());

    data.insert(data.end(), uuidBoxIptc.begin(), uuidBoxIptc.end());



    io.populateFakeData(data);

    image.io() = std::move(io);



    EXPECT_NO_THROW(image.readMetadata());

}



TEST(Jp2ImageTest, ReadMetadata_UuidBox_Xmp) {

    MockBasicIo io;

    Jp2Image image(std::make_unique<MockBasicIo>(), false);



    // JP2 Signature Box (12 bytes)

    std::array<byte, 12> signatureBox = {0x00, 0x00, 0x00, 0x0C, 'j', 'P', ' ', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    // File Type Box (24 bytes)

    std::array<byte, 24> fileTypeBox = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'j', 'p', '2', ' ', 'j', 'p', '2', 'h'};

    // Header Box (36 bytes)

    std::array<byte, 36> headerBox = {0x00, 0x00, 0x00, 0x1C, 'h', 'l', ' ', ' ', 0x00, 0x00, 0x00, 0x0E, 'j', 'p', '2', 'c'};

    // Uuid Box for XMP (34 bytes)

    std::array<byte, 34> uuidBoxXmp = {

        0x00, 0x00, 0x00, 0x16, 'u', 'u', 'i', 'd',

        190, 122, 207, 203, 151, 169, 66, 232, 156, 113, 153, 148, 145, 227, 175, 172,

        // XMP data placeholder

        0x00, 0x00, 0x00, 0x00

    };



    std::vector<byte> data;

    data.insert(data.end(), signatureBox.begin(), signatureBox.end());

    data.insert(data.end(), fileTypeBox.begin(), fileTypeBox.end());

    data.insert(data.end(), headerBox.begin(), headerBox.end());

    data.insert(data.end(), uuidBoxXmp.begin(), uuidBoxXmp.end());



    io.populateFakeData(data);

    image.io() = std::move(io);



    EXPECT_NO_THROW(image.readMetadata());

}



TEST(Jp2ImageTest, ReadMetadata_InvalidBoxType) {

    MockBasicIo io;

    Jp2Image image(std::make_unique<MockBasicIo>(), false);



    // JP2 Signature Box (12 bytes)

    std::array<byte, 12> signatureBox = {0x00, 0x00, 0x00, 0x0C, 'j', 'P', ' ', ' ', 0x0D, 0x0A, 0x87, 0x0A};

    // File Type Box (24 bytes)

    std::array<byte, 24> fileTypeBox = {0x00, 0x00, 0x00, 0x14, 'f', 't', 'y', 'p', 'j', 'p', '2', ' ', 'j', 'p', '2', 'h'};

    // Header Box (36 bytes)

    std::array<byte, 36> headerBox = {0x00, 0x00, 0x00, 0x1C, 'h', 'l', ' ', ' ', 0x00, 0x00, 0x00, 0x0E, 'j', 'p', '2', 'c'};

    // Invalid Box (34 bytes)

    std::array<byte, 34> invalidBox = {

        0x00, 0x00, 0x00, 0x16, 'i', 'n', 'v', 'l',

        0x00, 0x00, 0x00, 0x00,

        // Invalid data placeholder

        0x00, 0x00, 0x00, 0x00

    };



    std::vector<byte> data;

    data.insert(data.end(), signatureBox.begin(), signatureBox.end());

    data.insert(data.end(), fileTypeBox.begin(), fileTypeBox.end());

    data.insert(data.end(), headerBox.begin(), headerBox.end());

    data.insert(data.end(), invalidBox.begin(), invalidBox.end());



    io.populateFakeData(data);

    image.io() = std::move(io);



    EXPECT_NO_THROW(image.readMetadata());

}



} // namespace

} // namespace Exiv2
