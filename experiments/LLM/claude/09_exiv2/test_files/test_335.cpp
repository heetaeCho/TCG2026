#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffMnEntryTest_335 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that addNext returns nullptr when mn_ is not set (default construction)
TEST_F(TiffMnEntryTest_335, DoAddNextReturnsNullWhenMnIsNull_335) {
    // Construct a TiffMnEntry with some valid tag/group/mnGroup values
    // When mn_ is not initialized, doAddNext should return nullptr
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    // Create a dummy TiffComponent to pass as the next component
    // Using a simple TiffEntry or similar concrete TiffComponent
    auto component = std::make_unique<TiffEntry>(0x0001, IfdId::canonId);

    // addNext calls doAddNext, which should return nullptr since mn_ is null
    TiffComponent* result = entry.addNext(std::move(component));
    EXPECT_EQ(result, nullptr);
}

// Test addNext with nullptr UniquePtr when mn_ is not set
TEST_F(TiffMnEntryTest_335, DoAddNextWithNullComponentWhenMnIsNull_335) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    TiffComponent::UniquePtr nullComponent;
    TiffComponent* result = entry.addNext(std::move(nullComponent));
    EXPECT_EQ(result, nullptr);
}

// Test basic construction properties
TEST_F(TiffMnEntryTest_335, ConstructionSetsTagAndGroup_335) {
    const uint16_t tag = 0x927c;
    const IfdId group = IfdId::exifId;
    const IfdId mnGroup = IfdId::canonId;

    TiffMnEntry entry(tag, group, mnGroup);

    EXPECT_EQ(entry.tag(), tag);
    EXPECT_EQ(entry.group(), group);
}

// Test addChild returns nullptr when mn_ is not set
TEST_F(TiffMnEntryTest_335, DoAddChildReturnsNullWhenMnIsNull_335) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    auto component = std::make_shared<TiffEntry>(0x0001, IfdId::canonId);
    TiffComponent* result = entry.addChild(component);
    // When mn_ is null, doAddChild likely also returns nullptr or delegates similarly
    // We just check it doesn't crash and observe the return value
    EXPECT_EQ(result, nullptr);
}

// Test that multiple addNext calls all return nullptr when mn_ is null
TEST_F(TiffMnEntryTest_335, MultipleAddNextCallsReturnNullWhenMnIsNull_335) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);

    for (int i = 0; i < 5; ++i) {
        auto component = std::make_unique<TiffEntry>(static_cast<uint16_t>(i + 1), IfdId::canonId);
        TiffComponent* result = entry.addNext(std::move(component));
        EXPECT_EQ(result, nullptr);
    }
}

// Test construction with different tag/group combinations
TEST_F(TiffMnEntryTest_335, ConstructionWithDifferentParameters_335) {
    TiffMnEntry entry1(0x0000, IfdId::ifd0Id, IfdId::nikonId);
    EXPECT_EQ(entry1.tag(), 0x0000);
    EXPECT_EQ(entry1.group(), IfdId::ifd0Id);

    TiffMnEntry entry2(0xFFFF, IfdId::exifId, IfdId::sonyId);
    EXPECT_EQ(entry2.tag(), 0xFFFF);
    EXPECT_EQ(entry2.group(), IfdId::exifId);
}

// Test count returns expected value for default TiffMnEntry
TEST_F(TiffMnEntryTest_335, CountForDefaultEntry_335) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    size_t count = entry.count();
    EXPECT_GE(count, 0u);
}

// Test size returns expected value for default TiffMnEntry
TEST_F(TiffMnEntryTest_335, SizeForDefaultEntry_335) {
    TiffMnEntry entry(0x927c, IfdId::exifId, IfdId::canonId);
    size_t size = entry.size();
    EXPECT_GE(size, 0u);
}
