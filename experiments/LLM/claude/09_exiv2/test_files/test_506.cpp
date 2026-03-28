#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon3MakerNoteTest_506 : public ::testing::Test {
protected:
    Nikon3MakerNote maker_;
    std::ostringstream os_;
};

// Test: When value count is not 10, raw value is printed
TEST_F(Nikon3MakerNoteTest_506, WrongCountPrintsRawValue_506) {
    UShortValue value;
    // Only add 5 values instead of 10
    for (int i = 0; i < 5; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    // Should print raw value representation
    std::string result = os_.str();
    // Just verify it doesn't crash and produces some output
    EXPECT_FALSE(result.empty() || result == "");
}

// Test: When value type is not unsignedShort, raw value is printed
TEST_F(Nikon3MakerNoteTest_506, WrongTypePrintsRawValue_506) {
    AsciiValue value;
    value.read("test string");
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_FALSE(result.empty());
}

// Test: All zeros - should produce a single "None" or known label for 0
TEST_F(Nikon3MakerNoteTest_506, AllZerosProducesSingleEntry_506) {
    UShortValue value;
    for (int i = 0; i < 10; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    // With all zeros, trimming removes indices 9 down to 1, index 0 remains
    // Should have exactly one entry (no semicolons)
    EXPECT_EQ(result.find(';'), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: First element non-zero, rest zero - should produce single entry
TEST_F(Nikon3MakerNoteTest_506, FirstNonZeroRestZero_506) {
    UShortValue value;
    value.value_.push_back(3); // index 0: some known retouch value
    for (int i = 1; i < 10; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    // Trailing zeros trimmed, only index 0 remains
    EXPECT_EQ(result.find(';'), std::string::npos);
    EXPECT_FALSE(result.empty());
}

// Test: Multiple non-zero entries produce semicolon-separated output
TEST_F(Nikon3MakerNoteTest_506, MultipleNonZeroEntries_506) {
    UShortValue value;
    value.value_.push_back(3); // index 0
    value.value_.push_back(4); // index 1
    for (int i = 2; i < 10; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    // Should have at least one semicolon separator
    EXPECT_NE(result.find(';'), std::string::npos);
}

// Test: Unknown retouch value produces "Unknown" in output
TEST_F(Nikon3MakerNoteTest_506, UnknownRetouchValue_506) {
    UShortValue value;
    value.value_.push_back(9999); // index 0: likely unknown
    for (int i = 1; i < 10; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    EXPECT_NE(result.find("9999"), std::string::npos);
}

// Test: Last element non-zero - all 10 entries should appear
TEST_F(Nikon3MakerNoteTest_506, LastElementNonZero_506) {
    UShortValue value;
    for (int i = 0; i < 9; ++i) {
        value.value_.push_back(0);
    }
    value.value_.push_back(3); // index 9: non-zero
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    // All 10 entries should be present, so 9 semicolons
    size_t count = 0;
    for (size_t pos = 0; (pos = result.find(';', pos)) != std::string::npos; ++pos) {
        ++count;
    }
    EXPECT_EQ(count, 9u);
}

// Test: Nullptr ExifData doesn't cause crash
TEST_F(Nikon3MakerNoteTest_506, NullExifDataDoesNotCrash_506) {
    UShortValue value;
    for (int i = 0; i < 10; ++i) {
        value.value_.push_back(0);
    }
    EXPECT_NO_THROW(maker_.print0x009e(os_, value, nullptr));
}

// Test: Returns reference to the same ostream
TEST_F(Nikon3MakerNoteTest_506, ReturnsOstreamReference_506) {
    UShortValue value;
    for (int i = 0; i < 10; ++i) {
        value.value_.push_back(0);
    }
    std::ostream& ref = maker_.print0x009e(os_, value, nullptr);
    EXPECT_EQ(&ref, &os_);
}

// Test: Wrong count also returns ostream reference
TEST_F(Nikon3MakerNoteTest_506, WrongCountReturnsOstreamReference_506) {
    UShortValue value;
    value.value_.push_back(1);
    std::ostream& ref = maker_.print0x009e(os_, value, nullptr);
    EXPECT_EQ(&ref, &os_);
}

// Test: Non-zero value at middle position, zeros elsewhere
TEST_F(Nikon3MakerNoteTest_506, MiddleNonZeroValue_506) {
    UShortValue value;
    for (int i = 0; i < 5; ++i) {
        value.value_.push_back(0);
    }
    value.value_.push_back(3); // index 5
    for (int i = 6; i < 10; ++i) {
        value.value_.push_back(0);
    }
    maker_.print0x009e(os_, value, nullptr);
    std::string result = os_.str();
    // Entries from index 0 to 5 should appear (6 entries, 5 semicolons)
    size_t count = 0;
    for (size_t pos = 0; (pos = result.find(';', pos)) != std::string::npos; ++pos) {
        ++count;
    }
    EXPECT_EQ(count, 5u);
}
