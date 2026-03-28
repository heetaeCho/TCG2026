#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a minimal TiffEncoder for testing
// We need a TiffHeaderBase to provide byte order
class MinimalTiffHeader : public TiffHeaderBase {
public:
    MinimalTiffHeader(ByteOrder bo) : TiffHeaderBase(42, 8, bo, 0) {}
    ~MinimalTiffHeader() override = default;
    bool read(const byte* pData, size_t size) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

class TiffEncoderVisitBinaryElementTest_1678 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Helper function to create a TiffEncoder with given byte order
std::unique_ptr<TiffEncoder> createEncoder(ByteOrder bo, MinimalTiffHeader& header,
                                            ExifData& exifData, IptcData& iptcData,
                                            XmpData& xmpData) {
    PrimaryGroups primaryGroups;
    // Use nullptr for pRoot since we're testing visitBinaryElement only
    return std::make_unique<TiffEncoder>(
        exifData, iptcData, xmpData,
        nullptr, false, std::move(primaryGroups),
        &header, nullptr);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, ByteOrderRestoredAfterVisit_InvalidElementByteOrder_1678) {
    // Test that when element has invalidByteOrder, the encoder's byte order stays the same
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    MinimalTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        nullptr, false, std::move(primaryGroups),
                        &header, nullptr);

    ByteOrder originalOrder = encoder.byteOrder();
    EXPECT_EQ(originalOrder, littleEndian);

    // Create a TiffBinaryElement with invalidByteOrder (default)
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    // Default elByteOrder should be invalidByteOrder
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

    // After visiting, byte order should be restored
    encoder.visitBinaryElement(&element);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, ByteOrderRestoredAfterVisit_DifferentElementByteOrder_1678) {
    // Test that when element has a specific byte order, encoder's byte order is restored after visit
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    MinimalTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        nullptr, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_EQ(encoder.byteOrder(), littleEndian);

    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);

    // After visiting, byte order should be restored to original
    encoder.visitBinaryElement(&element);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, ByteOrderRestoredAfterVisit_BigEndianOriginal_1678) {
    // Test with big endian as original byte order
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    MinimalTiffHeader header(bigEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        nullptr, false, std::move(primaryGroups),
                        &header, nullptr);

    EXPECT_EQ(encoder.byteOrder(), bigEndian);

    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    element.setElByteOrder(littleEndian);

    encoder.visitBinaryElement(&element);
    EXPECT_EQ(encoder.byteOrder(), bigEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, ElementByteOrderSameAsEncoder_1678) {
    // Test when element byte order matches encoder byte order
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    MinimalTiffHeader header(bigEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        nullptr, false, std::move(primaryGroups),
                        &header, nullptr);

    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    element.setElByteOrder(bigEndian);

    encoder.visitBinaryElement(&element);
    EXPECT_EQ(encoder.byteOrder(), bigEndian);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, SetElByteOrderAndQuery_1678) {
    // Test TiffBinaryElement's setElByteOrder/elByteOrder interface
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);

    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);

    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);

    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);

    element.setElByteOrder(invalidByteOrder);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}

TEST_F(TiffEncoderVisitBinaryElementTest_1678, MultipleVisitsRestoreByteOrder_1678) {
    // Test that multiple visits all properly restore byte order
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    MinimalTiffHeader header(littleEndian);
    PrimaryGroups primaryGroups;

    TiffEncoder encoder(exifData, iptcData, xmpData,
                        nullptr, false, std::move(primaryGroups),
                        &header, nullptr);

    TiffBinaryElement elem1(0x0001, IfdId::ifd0Id);
    elem1.setElByteOrder(bigEndian);

    TiffBinaryElement elem2(0x0002, IfdId::ifd0Id);
    elem2.setElByteOrder(littleEndian);

    TiffBinaryElement elem3(0x0003, IfdId::ifd0Id);
    // elem3 uses default invalidByteOrder

    encoder.visitBinaryElement(&elem1);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);

    encoder.visitBinaryElement(&elem2);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);

    encoder.visitBinaryElement(&elem3);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

} // namespace
