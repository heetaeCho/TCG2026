#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "tiffvisitor_int.hpp"

#include <stack>
#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// TiffPath is typically a std::stack<TiffPathItem>
// We use the actual types from the library

class TiffMnEntryTest_322 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that when tiffPath has only one element, doAddPath returns 'this'
TEST_F(TiffMnEntryTest_322, AddPathWithSingleElementReturnsThis_322) {
    // Create a TiffMnEntry with some tag, group, and mnGroup
    const uint16_t tag = 0x927c;  // MakerNote tag
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);

    // Create a TiffPath with a single element
    TiffPath tiffPath;
    TiffPathItem item(tag, group);
    tiffPath.push(item);

    // Call addPath - since tiffPath has only 1 element, after pop it's empty,
    // so it should return 'this'
    TiffComponent* result = entry.addPath(tag, tiffPath, nullptr, nullptr);

    EXPECT_EQ(result, &entry);
}

// Test that TiffMnEntry can be constructed with valid parameters
TEST_F(TiffMnEntryTest_322, ConstructionIsValid_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);

    EXPECT_EQ(entry.tag(), tag);
    EXPECT_EQ(entry.group(), group);
}

// Test that tag() returns the correct tag value
TEST_F(TiffMnEntryTest_322, TagReturnsCorrectValue_322) {
    const uint16_t tag = 0x0001;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);
    EXPECT_EQ(entry.tag(), tag);
}

// Test that group() returns the correct group value
TEST_F(TiffMnEntryTest_322, GroupReturnsCorrectValue_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::exifId;
    const IfdId mnGroup = IfdId::nikonId;

    TiffMnEntry entry(tag, group, mnGroup);
    EXPECT_EQ(entry.group(), group);
}

// Test addPath with empty tiffPath - edge case
// When tiffPath is empty, addPath on TiffComponent base typically returns nullptr
// or has defined behavior. Since doAddPath pops immediately, empty path would be UB
// We skip this as it would cause undefined behavior.

// Test that calling addPath with a path of exactly one element multiple times
// consistently returns this
TEST_F(TiffMnEntryTest_322, AddPathSingleElementIdempotent_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);

    // First call
    {
        TiffPath tiffPath;
        TiffPathItem item(tag, group);
        tiffPath.push(item);
        TiffComponent* result = entry.addPath(tag, tiffPath, nullptr, nullptr);
        EXPECT_EQ(result, &entry);
    }

    // Second call
    {
        TiffPath tiffPath;
        TiffPathItem item(tag, group);
        tiffPath.push(item);
        TiffComponent* result = entry.addPath(tag, tiffPath, nullptr, nullptr);
        EXPECT_EQ(result, &entry);
    }
}

// Test TiffPathItem accessors
TEST_F(TiffMnEntryTest_322, TiffPathItemAccessors_322) {
    const uint32_t extendedTag = 0x927c;
    const IfdId group = IfdId::exifId;

    TiffPathItem item(extendedTag, group);

    EXPECT_EQ(item.extendedTag(), extendedTag);
    EXPECT_EQ(item.group(), group);
    EXPECT_EQ(item.tag(), static_cast<uint16_t>(extendedTag & 0xffff));
}

// Test TiffPathItem with different tag values
TEST_F(TiffMnEntryTest_322, TiffPathItemDifferentTags_322) {
    const uint32_t extendedTag = 0x0110;
    const IfdId group = IfdId::ifd0Id;

    TiffPathItem item(extendedTag, group);

    EXPECT_EQ(item.extendedTag(), extendedTag);
    EXPECT_EQ(item.group(), group);
}

// Test that start() returns nullptr by default (no data set)
TEST_F(TiffMnEntryTest_322, StartIsNullByDefault_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);
    EXPECT_EQ(entry.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffMnEntryTest_322, SetStartAndStart_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);

    byte data[] = {0x01, 0x02, 0x03};
    entry.setStart(data);
    EXPECT_EQ(entry.start(), data);
}

// Test destruction doesn't crash
TEST_F(TiffMnEntryTest_322, DestructionSafe_322) {
    auto entry = std::make_unique<TiffMnEntry>(0x927c, IfdId::ifd0Id, IfdId::canonId);
    // Simply destroy - no crash expected
    entry.reset();
    SUCCEED();
}

// Test addPath with single element and non-null root
TEST_F(TiffMnEntryTest_322, AddPathSingleElementWithRoot_322) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::ifd0Id;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);
    TiffMnEntry root(0x0000, IfdId::ifd0Id, IfdId::canonId);

    TiffPath tiffPath;
    TiffPathItem item(tag, group);
    tiffPath.push(item);

    TiffComponent* result = entry.addPath(tag, tiffPath, &root, nullptr);
    EXPECT_EQ(result, &entry);
}
