

```cpp

#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"

#include "error.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



// Mock classes and functions for testing purposes

class MockTiffImageEntry : public TiffImageEntry {

public:

    MockTiffImageEntry(uint16_t tag, IfdId group, uint16_t szTag, IfdId szGroup)

        : TiffImageEntry(tag, group, szTag, szGroup) {}



    void setStripsMock(const Value* pSize, const byte* pData, size_t sizeData, size_t baseOffset) {

        setStrips(pSize, pData, sizeData, baseOffset);

    }

};



class MockExifdatum : public Exifdatum {

public:

    MockExifdatum(uint16_t tag, IfdId group)

        : Exifdatum(tag, group), pValue_(nullptr) {}



    const Value* value() const override { return pValue_; }



    void setValueMock(Value* value) {

        pValue_ = std::unique_ptr<Value>(value);

    }



private:

    std::unique_ptr<Value> pValue_;

};



// Test case 1: VisitImageEntry with valid data

TEST(TiffEncoderVisitImageEntry, ValidData) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value

    std::vector<long> sizes = {100};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte data[100] = {0}; // Mock image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(new TiffImageEntry(imageEntry));



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with valid data

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 1);

    EXPECT_EQ(imageEntry.strips_[0].pData_, data);

    EXPECT_EQ(imageEntry.strips_[0].size_, 100);

}



// Test case 2: VisitImageEntry with no size data

TEST(TiffEncoderVisitImageEntry, NoSizeData) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value with no sizes

    std::vector<long> sizes = {};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte data[100] = {0}; // Mock image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(new TiffImageEntry(imageEntry));



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with no size data

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 0);

}



// Test case 3: VisitImageEntry with zero-sized data

TEST(TiffEncoderVisitImageEntry, ZeroSizedData) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value with zero size

    std::vector<long> sizes = {0};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte data[100] = {0}; // Mock image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(new TiffImageEntry(imageEntry));



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with zero-sized data

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 1);

    EXPECT_EQ(imageEntry.strips_[0].pData_, nullptr);

    EXPECT_EQ(imageEntry.strips_[0].size_, 0);

}



// Test case 4: VisitImageEntry with multiple sizes

TEST(TiffEncoderVisitImageEntry, MultipleSizes) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value with multiple sizes

    std::vector<long> sizes = {50, 30};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte data[100] = {0}; // Mock image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(new TiffImageEntry(imageEntry));



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with multiple sizes

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 2);

    EXPECT_EQ(imageEntry.strips_[0].pData_, data);

    EXPECT_EQ(imageEntry.strips_[0].size_, 50);

    EXPECT_EQ(imageEntry.strips_[1].pData_, data + 50);

    EXPECT_EQ(imageEntry.strips_[1].size_, 30);

}



// Test case 5: VisitImageEntry with no source tree

TEST(TiffEncoderVisitImageEntry, NoSourceTree) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value with multiple sizes

    std::vector<long> sizes = {50, 30};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte data[100] = {0}; // Mock image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(nullptr);



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with no source tree

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 2);

    EXPECT_EQ(imageEntry.strips_[0].pData_, data);

    EXPECT_EQ(imageEntry.strips_[0].size_, 50);

    EXPECT_EQ(imageEntry.strips_[1].pData_, data + 50);

    EXPECT_EQ(imageEntry.strips_[1].size_, 30);

}



// Test case 6: VisitImageEntry with no data

TEST(TiffEncoderVisitImageEntry, NoData) {

    MockTiffImageEntry imageEntry(0x011A, ifdExif, 0x0128, ifdExif);

    MockExifdatum exifDatum(0x011A, ifdExif);



    // Create a mock value with multiple sizes

    std::vector<long> sizes = {50, 30};

    auto pSize = new Exiv2::RationalValue(sizes.begin(), sizes.end());

    exifDatum.setValueMock(pSize);



    byte* data = nullptr; // No image data



    TiffEncoder encoder(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    encoder.pSourceTree_.reset(new TiffImageEntry(imageEntry));



    // Set strips on the mock image entry

    imageEntry.setStripsMock(pSize, data, 100, 0);



    // Visit the image entry with no data

    encoder.visitImageEntry(&imageEntry);



    EXPECT_EQ(imageEntry.strips_.size(), 2);

    EXPECT_EQ(imageEntry.strips_[0].pData_, nullptr);

    EXPECT_EQ(imageEntry.strips_[0].size_, 50);

    EXPECT_EQ(imageEntry.strips_[1].pData_, nullptr);

    EXPECT_EQ(imageEntry.strips_[1].size_, 30);

}

```


