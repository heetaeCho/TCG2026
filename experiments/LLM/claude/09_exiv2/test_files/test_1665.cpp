#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Default finder function that returns nullptr (no special decoder)
static DecoderFct findDecoderFctDefault(const std::string& make,
                                         uint32_t extendedTag,
                                         IfdId group) {
    return nullptr;
}

class TiffDecoderVisitBinaryElementTest_1665 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = std::make_unique<ExifData>();
        iptcData_ = std::make_unique<IptcData>();
        xmpData_ = std::make_unique<XmpData>();
    }

    void TearDown() override {
    }

    std::unique_ptr<ExifData> exifData_;
    std::unique_ptr<IptcData> iptcData_;
    std::unique_ptr<XmpData> xmpData_;
};

// Test that visitBinaryElement can be called with a valid TiffBinaryElement without crashing
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementDoesNotCrash_1665) {
    // Create a TiffBinaryElement with some tag and group
    uint16_t tag = 0x0001;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    // Create decoder with no special decoder function
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    // visitBinaryElement should call decodeTiffEntry internally
    // With no data set on the element, it should handle gracefully
    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that visitBinaryElement with a properly configured element processes without error
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementWithElDef_1665) {
    uint16_t tag = 0x0002;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    // Set element definition
    ArrayDef def = {0, ttUnsignedByte, 1};
    element.setElDef(def);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that visitBinaryElement with byte order set on element
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementWithByteOrder_1665) {
    uint16_t tag = 0x0003;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    element.setElByteOrder(littleEndian);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that visitBinaryElement with bigEndian byte order
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementBigEndian_1665) {
    uint16_t tag = 0x0004;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    element.setElByteOrder(bigEndian);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that visitBinaryElement with invalidByteOrder (default)
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementInvalidByteOrder_1665) {
    uint16_t tag = 0x0005;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    element.setElByteOrder(invalidByteOrder);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that TiffBinaryElement elDef and elByteOrder accessors work correctly
TEST_F(TiffDecoderVisitBinaryElementTest_1665, BinaryElementAccessors_1665) {
    uint16_t tag = 0x0010;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    // Default byte order should be invalidByteOrder
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);

    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);
}

// Test setting ArrayDef on a BinaryElement
TEST_F(TiffDecoderVisitBinaryElementTest_1665, BinaryElementSetElDef_1665) {
    uint16_t tag = 0x0020;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    ArrayDef def = {5, ttUnsignedShort, 2};
    element.setElDef(def);

    const ArrayDef* retrieved = element.elDef();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->idx_, 5u);
    EXPECT_EQ(retrieved->tiffType_, ttUnsignedShort);
    EXPECT_EQ(retrieved->count_, 2u);
}

// Test multiple calls to visitBinaryElement
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementMultipleCalls_1665) {
    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    uint16_t tag1 = 0x0001;
    uint16_t tag2 = 0x0002;
    IfdId group = ifdIdNotSet;

    TiffBinaryElement element1(tag1, group);
    TiffBinaryElement element2(tag2, group);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element1));
    EXPECT_NO_THROW(decoder.visitBinaryElement(&element2));
}

// Test that visitBinaryElement with zero tag
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementZeroTag_1665) {
    uint16_t tag = 0x0000;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}

// Test that visitBinaryElement with max tag value
TEST_F(TiffDecoderVisitBinaryElementTest_1665, VisitBinaryElementMaxTag_1665) {
    uint16_t tag = 0xFFFF;
    IfdId group = ifdIdNotSet;
    TiffBinaryElement element(tag, group);

    TiffDecoder decoder(*exifData_, *iptcData_, *xmpData_, nullptr, findDecoderFctDefault);

    EXPECT_NO_THROW(decoder.visitBinaryElement(&element));
}
