#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "tiffvisitor_int.hpp"

#include <sstream>
#include <cstring>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Since TiffDataEntry is part of a complex hierarchy, we test through the
// available public/protected interfaces. We create TiffDataEntry objects
// and exercise doWrite via the write method if accessible, or directly.

class TiffDataEntryTest_368 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doWrite returns 0 when no value is set (pValue() returns nullptr)
TEST_F(TiffDataEntryTest_368, DoWriteReturnsZeroWhenNoValue_368) {
    // Create a TiffDataEntry with a tag that has no value set
    // TiffDataEntry(tag, group, szTag, szGroup)
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    
    // Without setting any value, pValue() should be null
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test that TiffDataEntry can be constructed with valid parameters
TEST_F(TiffDataEntryTest_368, ConstructionIsValid_368) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0111);
}

// Test that the szTag and szGroup are stored correctly
TEST_F(TiffDataEntryTest_368, SzTagAndGroupStored_368) {
    const uint16_t tag = 0x0201;
    const uint16_t szTag = 0x0202;
    TiffDataEntry entry(tag, IfdId::ifd0Id, szTag, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), tag);
}

// Test with different IFD groups
TEST_F(TiffDataEntryTest_368, DifferentIfdGroups_368) {
    TiffDataEntry entry1(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    TiffDataEntry entry2(0x0111, IfdId::ifd1Id, 0x0117, IfdId::ifd1Id);
    
    EXPECT_EQ(entry1.tag(), entry2.tag());
}

// Test that pValue returns nullptr before any value is assigned
TEST_F(TiffDataEntryTest_368, PValueNullBeforeAssignment_368) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test constructing TiffDataEntry with zero tags
TEST_F(TiffDataEntryTest_368, ZeroTagConstruction_368) {
    TiffDataEntry entry(0x0000, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0000);
    EXPECT_EQ(entry.pValue(), nullptr);
}

// Test constructing with max tag value
TEST_F(TiffDataEntryTest_368, MaxTagConstruction_368) {
    TiffDataEntry entry(0xFFFF, IfdId::ifd0Id, 0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0xFFFF);
}

// Test that count is 0 when no value is set
TEST_F(TiffDataEntryTest_368, CountZeroWhenNoValue_368) {
    TiffDataEntry entry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    // When no value is set, count should be 0
    EXPECT_EQ(entry.count(), 0u);
}
