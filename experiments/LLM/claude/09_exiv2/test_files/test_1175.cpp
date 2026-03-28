#include <gtest/gtest.h>
#include <cstdint>
#include <sstream>

// Include necessary headers from the project
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffHeaderBase is abstract-like (has virtual methods) but not purely abstract,
// we can create a concrete instance for testing. However, the copy constructor and
// assignment operator are deleted, so we use pointers.

// A simple concrete subclass if TiffHeaderBase cannot be instantiated directly
class ConcreteTiffHeader : public TiffHeaderBase {
public:
    ConcreteTiffHeader(uint16_t tag, uint32_t size, ByteOrder byteOrder, uint32_t offset)
        : TiffHeaderBase(tag, size, byteOrder, offset) {}
};

class TiffHeaderBaseTest_1175 : public ::testing::Test {
protected:
    void SetUp() override {
        // Common tag value for TIFF: 42 (0x002A)
        header_ = std::make_unique<ConcreteTiffHeader>(42, 8, littleEndian, 8);
    }

    std::unique_ptr<ConcreteTiffHeader> header_;
};

// Test that setOffset correctly updates the offset value
TEST_F(TiffHeaderBaseTest_1175, SetOffsetUpdatesOffset_1175) {
    header_->setOffset(16);
    EXPECT_EQ(header_->offset(), 16u);
}

// Test setOffset with zero
TEST_F(TiffHeaderBaseTest_1175, SetOffsetToZero_1175) {
    header_->setOffset(0);
    EXPECT_EQ(header_->offset(), 0u);
}

// Test setOffset with maximum uint32_t value
TEST_F(TiffHeaderBaseTest_1175, SetOffsetToMaxUint32_1175) {
    header_->setOffset(UINT32_MAX);
    EXPECT_EQ(header_->offset(), UINT32_MAX);
}

// Test that the initial offset is what was passed in the constructor
TEST_F(TiffHeaderBaseTest_1175, InitialOffsetFromConstructor_1175) {
    EXPECT_EQ(header_->offset(), 8u);
}

// Test setOffset called multiple times
TEST_F(TiffHeaderBaseTest_1175, SetOffsetMultipleTimes_1175) {
    header_->setOffset(100);
    EXPECT_EQ(header_->offset(), 100u);
    header_->setOffset(200);
    EXPECT_EQ(header_->offset(), 200u);
    header_->setOffset(0);
    EXPECT_EQ(header_->offset(), 0u);
}

// Test that initial byte order is correct
TEST_F(TiffHeaderBaseTest_1175, InitialByteOrder_1175) {
    EXPECT_EQ(header_->byteOrder(), littleEndian);
}

// Test setByteOrder
TEST_F(TiffHeaderBaseTest_1175, SetByteOrder_1175) {
    header_->setByteOrder(bigEndian);
    EXPECT_EQ(header_->byteOrder(), bigEndian);
}

// Test that tag returns the correct value
TEST_F(TiffHeaderBaseTest_1175, TagReturnsCorrectValue_1175) {
    EXPECT_EQ(header_->tag(), 42u);
}

// Test that size returns the correct value
TEST_F(TiffHeaderBaseTest_1175, SizeReturnsCorrectValue_1175) {
    EXPECT_EQ(header_->size(), 8u);
}

// Test setOffset does not affect other fields
TEST_F(TiffHeaderBaseTest_1175, SetOffsetDoesNotAffectOtherFields_1175) {
    header_->setOffset(999);
    EXPECT_EQ(header_->tag(), 42u);
    EXPECT_EQ(header_->size(), 8u);
    EXPECT_EQ(header_->byteOrder(), littleEndian);
    EXPECT_EQ(header_->offset(), 999u);
}

// Test setByteOrder does not affect offset
TEST_F(TiffHeaderBaseTest_1175, SetByteOrderDoesNotAffectOffset_1175) {
    header_->setOffset(123);
    header_->setByteOrder(bigEndian);
    EXPECT_EQ(header_->offset(), 123u);
}

// Test construction with big endian byte order
TEST_F(TiffHeaderBaseTest_1175, ConstructWithBigEndian_1175) {
    ConcreteTiffHeader bigEndianHeader(42, 8, bigEndian, 16);
    EXPECT_EQ(bigEndianHeader.byteOrder(), bigEndian);
    EXPECT_EQ(bigEndianHeader.offset(), 16u);
}

// Test construction with different offset values
TEST_F(TiffHeaderBaseTest_1175, ConstructWithDifferentOffsets_1175) {
    ConcreteTiffHeader h1(42, 8, littleEndian, 0);
    EXPECT_EQ(h1.offset(), 0u);

    ConcreteTiffHeader h2(42, 8, littleEndian, 1024);
    EXPECT_EQ(h2.offset(), 1024u);
}

// Test setOffset with value 1 (boundary near zero)
TEST_F(TiffHeaderBaseTest_1175, SetOffsetToOne_1175) {
    header_->setOffset(1);
    EXPECT_EQ(header_->offset(), 1u);
}

// Test setOffset with large power-of-two value
TEST_F(TiffHeaderBaseTest_1175, SetOffsetLargePowerOfTwo_1175) {
    header_->setOffset(1u << 31);
    EXPECT_EQ(header_->offset(), 1u << 31);
}

// Test print outputs something (basic smoke test)
TEST_F(TiffHeaderBaseTest_1175, PrintDoesNotCrash_1175) {
    std::ostringstream oss;
    EXPECT_NO_THROW(header_->print(oss, ""));
    // We just verify it doesn't crash and produces some output
    EXPECT_FALSE(oss.str().empty());
}

// Test isImageTag returns false by default
TEST_F(TiffHeaderBaseTest_1175, IsImageTagReturnsFalse_1175) {
    PrimaryGroups pg;
    EXPECT_FALSE(header_->isImageTag(0, IfdId::ifd0Id, pg));
}

// Test write produces a non-empty buffer
TEST_F(TiffHeaderBaseTest_1175, WriteProducesData_1175) {
    DataBuf buf = header_->write();
    EXPECT_GT(buf.size(), 0u);
}
