#include <gtest/gtest.h>

// Minimal definitions needed to compile the tests based on the known interface

enum XRefEntryType {
    xrefEntryFree,
    xrefEntryUncompressed,
    xrefEntryCompressed,
    xrefEntryNone
};

// Forward-declare enough to match the interface
// We need the Flag enum and the XRefEntry struct

struct XRefEntry {
    enum Flag {
        Updated = 0,
        Parsing = 1,
        // Add more flags if needed for boundary testing
    };

    XRefEntryType type;
    int flags;

    bool getFlag(Flag flag) const
    {
        const int mask = (1 << (int)flag);
        return (flags & mask) != 0;
    }

    void setFlag(Flag flag, bool value)
    {
        const int mask = (1 << (int)flag);
        if (value) {
            flags |= mask;
        } else {
            flags &= ~mask;
        }
    }
};

class XRefEntryTest_256 : public ::testing::Test {
protected:
    XRefEntry entry;

    void SetUp() override
    {
        entry.type = xrefEntryNone;
        entry.flags = 0;
    }
};

// Test setting a flag to true
TEST_F(XRefEntryTest_256, SetFlagUpdatedTrue_256)
{
    entry.setFlag(XRefEntry::Updated, true);
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
}

// Test setting a flag to false
TEST_F(XRefEntryTest_256, SetFlagUpdatedFalse_256)
{
    entry.flags = 0;
    entry.setFlag(XRefEntry::Updated, false);
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
}

// Test setting flag true then back to false
TEST_F(XRefEntryTest_256, SetFlagTrueThenFalse_256)
{
    entry.setFlag(XRefEntry::Updated, true);
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
    entry.setFlag(XRefEntry::Updated, false);
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
}

// Test that setting one flag does not affect another
TEST_F(XRefEntryTest_256, SetFlagDoesNotAffectOtherFlags_256)
{
    entry.setFlag(XRefEntry::Updated, true);
    entry.setFlag(XRefEntry::Parsing, false);
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
    EXPECT_FALSE(entry.getFlag(XRefEntry::Parsing));
}

// Test setting multiple flags independently
TEST_F(XRefEntryTest_256, SetMultipleFlagsIndependently_256)
{
    entry.setFlag(XRefEntry::Updated, true);
    entry.setFlag(XRefEntry::Parsing, true);
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
    EXPECT_TRUE(entry.getFlag(XRefEntry::Parsing));

    // Clear only Updated
    entry.setFlag(XRefEntry::Updated, false);
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
    EXPECT_TRUE(entry.getFlag(XRefEntry::Parsing));
}

// Test initial state with flags = 0, all flags should be false
TEST_F(XRefEntryTest_256, InitialFlagsAllFalse_256)
{
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
    EXPECT_FALSE(entry.getFlag(XRefEntry::Parsing));
}

// Test setting the same flag true multiple times is idempotent
TEST_F(XRefEntryTest_256, SetFlagTrueIdempotent_256)
{
    entry.setFlag(XRefEntry::Updated, true);
    entry.setFlag(XRefEntry::Updated, true);
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
}

// Test setting the same flag false multiple times is idempotent
TEST_F(XRefEntryTest_256, SetFlagFalseIdempotent_256)
{
    entry.setFlag(XRefEntry::Updated, false);
    entry.setFlag(XRefEntry::Updated, false);
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
}

// Test that pre-existing bits in flags are preserved when setting a different flag
TEST_F(XRefEntryTest_256, PreExistingBitsPreserved_256)
{
    entry.flags = 0xFF; // all bits set
    entry.setFlag(XRefEntry::Updated, false);
    // Only bit 0 should be cleared
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
    EXPECT_TRUE(entry.getFlag(XRefEntry::Parsing));
}

// Test getFlag on flags with all bits set
TEST_F(XRefEntryTest_256, GetFlagAllBitsSet_256)
{
    entry.flags = ~0; // all bits set
    EXPECT_TRUE(entry.getFlag(XRefEntry::Updated));
    EXPECT_TRUE(entry.getFlag(XRefEntry::Parsing));
}

// Test clearing a flag when flags field has only that flag set
TEST_F(XRefEntryTest_256, ClearOnlySetFlag_256)
{
    entry.flags = (1 << (int)XRefEntry::Parsing);
    entry.setFlag(XRefEntry::Parsing, false);
    EXPECT_EQ(entry.flags, 0);
}

// Test that setFlag with true on already-zero other bits doesn't corrupt
TEST_F(XRefEntryTest_256, SetFlagOnZeroFlags_256)
{
    entry.flags = 0;
    entry.setFlag(XRefEntry::Parsing, true);
    EXPECT_EQ(entry.flags, (1 << (int)XRefEntry::Parsing));
    EXPECT_FALSE(entry.getFlag(XRefEntry::Updated));
    EXPECT_TRUE(entry.getFlag(XRefEntry::Parsing));
}

// Boundary: test with flag value corresponding to bit position 0
TEST_F(XRefEntryTest_256, FlagBitPositionZero_256)
{
    entry.setFlag(XRefEntry::Updated, true); // Updated = 0, so bit 0
    EXPECT_EQ(entry.flags & 1, 1);
}

// Boundary: test with flag value corresponding to bit position 1
TEST_F(XRefEntryTest_256, FlagBitPositionOne_256)
{
    entry.setFlag(XRefEntry::Parsing, true); // Parsing = 1, so bit 1
    EXPECT_EQ(entry.flags & 2, 2);
}
