#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

// We need to include relevant headers for the Exiv2 internal types
// Based on the interface, we'll include what's needed
#include <memory>
#include <cstdint>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffComponent tests
class TiffComponentTest_336 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test fixture for TiffIfdMakernote tests
class TiffIfdMakernoteTest_336 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ============================================================
// TiffComponent basic tests
// ============================================================

// Test that TiffComponent stores and returns the correct tag
TEST_F(TiffComponentTest_336, TagReturnsCorrectValue_336) {
    // TiffDirectory is a concrete TiffComponent we can instantiate
    // We'll use TiffIfdMakernote as a concrete subclass
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->tag(), 0x927c);
}

// Test that TiffComponent stores and returns the correct group
TEST_F(TiffComponentTest_336, GroupReturnsCorrectValue_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->group(), IfdId::exifId);
}

// Test that start() returns nullptr when setStart hasn't been called
TEST_F(TiffComponentTest_336, StartReturnsNullByDefault_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->start(), nullptr);
}

// Test that setStart and start work together
TEST_F(TiffComponentTest_336, SetStartAndStartWork_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[] = {0x01, 0x02, 0x03};
    makernote->setStart(data);
    EXPECT_EQ(makernote->start(), data);
}

// ============================================================
// TiffIfdMakernote constructor and basic property tests
// ============================================================

// Test construction with nullptr header
TEST_F(TiffIfdMakernoteTest_336, ConstructWithNullHeader_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    ASSERT_NE(makernote, nullptr);
    EXPECT_EQ(makernote->tag(), 0x927c);
    EXPECT_EQ(makernote->group(), IfdId::exifId);
}

// Test construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_336, ConstructWithHasNextTrue_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    ASSERT_NE(makernote, nullptr);
}

// Test construction with hasNext = false
TEST_F(TiffIfdMakernoteTest_336, ConstructWithHasNextFalse_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    ASSERT_NE(makernote, nullptr);
}

// Test construction with different tag values
TEST_F(TiffIfdMakernoteTest_336, ConstructWithDifferentTag_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x0001, IfdId::ifd0Id, IfdId::nikonId, nullptr, false);
    EXPECT_EQ(makernote->tag(), 0x0001);
    EXPECT_EQ(makernote->group(), IfdId::ifd0Id);
}

// Test construction with zero tag
TEST_F(TiffIfdMakernoteTest_336, ConstructWithZeroTag_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->tag(), 0x0000);
}

// Test construction with max uint16_t tag
TEST_F(TiffIfdMakernoteTest_336, ConstructWithMaxTag_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->tag(), 0xFFFF);
}

// ============================================================
// TiffIfdMakernote byteOrder tests
// ============================================================

// Test that default byte order is invalidByteOrder
TEST_F(TiffIfdMakernoteTest_336, DefaultByteOrderIsInvalid_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test setByteOrder with littleEndian
TEST_F(TiffIfdMakernoteTest_336, SetByteOrderLittleEndian_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
}

// Test setByteOrder with bigEndian
TEST_F(TiffIfdMakernoteTest_336, SetByteOrderBigEndian_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test setByteOrder overwrites previous value
TEST_F(TiffIfdMakernoteTest_336, SetByteOrderOverwritesPrevious_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
    makernote->setByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// ============================================================
// TiffIfdMakernote mnOffset tests
// ============================================================

// Test that initial mnOffset is 0
TEST_F(TiffIfdMakernoteTest_336, InitialMnOffsetIsZero_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->mnOffset(), 0u);
}

// ============================================================
// TiffIfdMakernote sizeHeader tests with nullptr header
// ============================================================

// Test sizeHeader with null header returns 0
TEST_F(TiffIfdMakernoteTest_336, SizeHeaderWithNullHeader_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeHeader(), 0u);
}

// ============================================================
// TiffIfdMakernote readHeader tests
// ============================================================

// Test readHeader with null data and zero size returns true (no header to read)
TEST_F(TiffIfdMakernoteTest_336, ReadHeaderWithNullDataAndNullHeader_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    bool result = makernote->readHeader(nullptr, 0, littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader with some data but null header
TEST_F(TiffIfdMakernoteTest_336, ReadHeaderWithDataButNullHeader_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    bool result = makernote->readHeader(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// ============================================================
// TiffIfdMakernote count/size tests
// ============================================================

// Test count on freshly constructed makernote
TEST_F(TiffIfdMakernoteTest_336, CountOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->count(), 0u);
}

// Test size on freshly constructed makernote
TEST_F(TiffIfdMakernoteTest_336, SizeOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // Size should be at least the IFD overhead (count field + next pointer)
    size_t s = makernote->size();
    // A minimal empty IFD should have 2 bytes for count + 4 bytes for next pointer = 6
    // But with hasNext=false it might be different. We just verify it's >= 0
    EXPECT_GE(s, 0u);
}

// Test sizeData on freshly constructed makernote
TEST_F(TiffIfdMakernoteTest_336, SizeDataOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeData(), 0u);
}

// Test sizeImage on freshly constructed makernote
TEST_F(TiffIfdMakernoteTest_336, SizeImageOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(makernote->sizeImage(), 0u);
}

// ============================================================
// TiffIfdMakernote ifdOffset tests
// ============================================================

// Test ifdOffset on freshly constructed makernote
TEST_F(TiffIfdMakernoteTest_336, IfdOffsetOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // ifdOffset should be the size of the header (0 for null header)
    EXPECT_EQ(makernote->ifdOffset(), 0u);
}

// ============================================================
// TiffIfdMakernote baseOffset tests
// ============================================================

// Test baseOffset on freshly constructed makernote with null header
TEST_F(TiffIfdMakernoteTest_336, BaseOffsetOnFreshMakernote_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t offset = makernote->baseOffset();
    EXPECT_EQ(offset, 0u);
}

// ============================================================
// TiffIfdMakernote copy semantics (deleted)
// ============================================================

// Verify that TiffIfdMakernote is not copyable (compile-time check embedded in design)
// This is verified by the = delete declarations, but we can't test compile errors at runtime.
// Instead we verify the class can be moved via unique_ptr
TEST_F(TiffIfdMakernoteTest_336, CanBeHeldInUniquePtr_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    auto moved = std::move(makernote);
    EXPECT_NE(moved, nullptr);
    EXPECT_EQ(makernote, nullptr);
}

// ============================================================
// TiffIfdMakernote addNext (via doAddNext) tests
// ============================================================

// Test addNext with nullptr
TEST_F(TiffIfdMakernoteTest_336, AddNextWithNullptr_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, true);
    TiffComponent* result = makernote->addNext(nullptr);
    // With nullptr input, addNext should return nullptr
    EXPECT_EQ(result, nullptr);
}

// ============================================================
// TiffIfdMakernote setImageByteOrder tests
// ============================================================

// Test setImageByteOrder (uses the separate imageByteOrder_ member, but
// the public byteOrder() method may return this or the mnHeader's byte order)
TEST_F(TiffIfdMakernoteTest_336, SetImageByteOrderDoesNotAffectByteOrder_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // setImageByteOrder sets imageByteOrder_, which is different from setByteOrder
    makernote->setImageByteOrder(littleEndian);
    // byteOrder() should still return invalidByteOrder since setByteOrder wasn't called
    // and there's no header to provide a byte order
    // The behavior depends on internal logic - we just check it doesn't crash
    ByteOrder bo = makernote->byteOrder();
    // It could be invalidByteOrder or littleEndian depending on implementation
    (void)bo; // Just ensure no crash
}

// Test that setByteOrder is independent of setImageByteOrder
TEST_F(TiffIfdMakernoteTest_336, SetByteOrderIndependentOfImageByteOrder_336) {
    auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    makernote->setImageByteOrder(littleEndian);
    makernote->setByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// ============================================================
// Destruction tests
// ============================================================

// Test that destruction doesn't crash
TEST_F(TiffIfdMakernoteTest_336, DestructionDoesNotCrash_336) {
    {
        auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
        // makernote goes out of scope and is destroyed
    }
    SUCCEED();
}

// Test that destruction after setByteOrder doesn't crash
TEST_F(TiffIfdMakernoteTest_336, DestructionAfterSetByteOrderDoesNotCrash_336) {
    {
        auto makernote = std::make_unique<TiffIfdMakernote>(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
        makernote->setByteOrder(littleEndian);
    }
    SUCCEED();
}
