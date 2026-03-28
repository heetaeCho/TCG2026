#include <gtest/gtest.h>
#include "XRef.h"

class XRefEntryTest_255 : public ::testing::Test {
protected:
    XRefEntry entry;

    void SetUp() override {
        entry.flags = 0;
    }
};

// Test that getFlag returns false when no flags are set
TEST_F(XRefEntryTest_255, GetFlagReturnsFalseWhenNoFlagsSet_255) {
    entry.flags = 0;
    // Test all known flag values - Flag is an enum, we test with common bit positions
    for (int i = 0; i < 8; i++) {
        EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(i)))
            << "Flag at position " << i << " should be false when flags=0";
    }
}

// Test that getFlag returns true when specific flag bit is set
TEST_F(XRefEntryTest_255, GetFlagReturnsTrueWhenFlagIsSet_255) {
    entry.flags = 1; // bit 0 set
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
}

// Test that getFlag returns true for flag at position 1
TEST_F(XRefEntryTest_255, GetFlagReturnsTrueForFlagPosition1_255) {
    entry.flags = 2; // bit 1 set
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
}

// Test that getFlag returns false for unset flag when other flags are set
TEST_F(XRefEntryTest_255, GetFlagReturnsFalseForUnsetFlagWhenOthersSet_255) {
    entry.flags = 2; // only bit 1 set
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
}

// Test that getFlag works when multiple flags are set
TEST_F(XRefEntryTest_255, GetFlagWorksWithMultipleFlagsSet_255) {
    entry.flags = 0x05; // bits 0 and 2 set
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(3)));
}

// Test that getFlag works when all bits are set
TEST_F(XRefEntryTest_255, GetFlagReturnsTrueWhenAllBitsSet_255) {
    entry.flags = 0xFF;
    for (int i = 0; i < 8; i++) {
        EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(i)))
            << "Flag at position " << i << " should be true when flags=0xFF";
    }
}

// Test setFlag sets a flag to true
TEST_F(XRefEntryTest_255, SetFlagSetsToTrue_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(0), true);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
}

// Test setFlag sets a flag to false
TEST_F(XRefEntryTest_255, SetFlagSetsToFalse_255) {
    entry.flags = 0xFF;
    entry.setFlag(static_cast<XRefEntry::Flag>(0), false);
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    // Other flags should remain set
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
}

// Test setFlag does not affect other flags when setting true
TEST_F(XRefEntryTest_255, SetFlagDoesNotAffectOtherFlagsWhenSettingTrue_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(2), true);
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(3)));
}

// Test setFlag does not affect other flags when setting false
TEST_F(XRefEntryTest_255, SetFlagDoesNotAffectOtherFlagsWhenSettingFalse_255) {
    entry.flags = 0x07; // bits 0, 1, 2 set
    entry.setFlag(static_cast<XRefEntry::Flag>(1), false);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
}

// Test setFlag then getFlag roundtrip for multiple flags
TEST_F(XRefEntryTest_255, SetAndGetMultipleFlags_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(0), true);
    entry.setFlag(static_cast<XRefEntry::Flag>(3), true);
    entry.setFlag(static_cast<XRefEntry::Flag>(5), true);

    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(3)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(4)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(5)));
}

// Test setting the same flag twice to true is idempotent
TEST_F(XRefEntryTest_255, SetFlagTrueIsIdempotent_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(2), true);
    entry.setFlag(static_cast<XRefEntry::Flag>(2), true);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
}

// Test setting the same flag twice to false is idempotent
TEST_F(XRefEntryTest_255, SetFlagFalseIsIdempotent_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(2), false);
    entry.setFlag(static_cast<XRefEntry::Flag>(2), false);
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(2)));
}

// Test toggling a flag
TEST_F(XRefEntryTest_255, ToggleFlag_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(1), true);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    entry.setFlag(static_cast<XRefEntry::Flag>(1), false);
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
    entry.setFlag(static_cast<XRefEntry::Flag>(1), true);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(1)));
}

// Test boundary: flag at high bit position
TEST_F(XRefEntryTest_255, GetFlagAtHighBitPosition_255) {
    entry.flags = (1 << 7); // bit 7 set
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(0)));
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(7)));
}

// Test setFlag at high bit position
TEST_F(XRefEntryTest_255, SetFlagAtHighBitPosition_255) {
    entry.flags = 0;
    entry.setFlag(static_cast<XRefEntry::Flag>(7), true);
    EXPECT_TRUE(entry.getFlag(static_cast<XRefEntry::Flag>(7)));
    EXPECT_FALSE(entry.getFlag(static_cast<XRefEntry::Flag>(6)));
}
