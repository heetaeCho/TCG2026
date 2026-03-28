#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>
#include "nikonmn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class Nikon1MakerNoteTest_417 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Test that tagList returns a non-null pointer
TEST_F(Nikon1MakerNoteTest_417, TagListIsNotNull_417) {
    auto tags = Nikon1MakerNote::tagList();
    ASSERT_NE(tags, nullptr);
}

// Test that the first entry in tag list has a valid tag number (typically 0 or positive)
TEST_F(Nikon1MakerNoteTest_417, TagListFirstEntryValid_417) {
    auto tags = Nikon1MakerNote::tagList();
    ASSERT_NE(tags, nullptr);
    // The tag list should have at least one entry with a non-empty title
    EXPECT_NE(tags[0].title_, nullptr);
}

// Test print0x0002 with a valid value containing multiple entries
TEST_F(Nikon1MakerNoteTest_417, Print0x0002WithMultipleValues_417) {
    UShortValue value;
    value.read("0 1 2");
    Nikon1MakerNote::print0x0002(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0002 with a single value
TEST_F(Nikon1MakerNoteTest_417, Print0x0002WithSingleValue_417) {
    UShortValue value;
    value.read("1");
    Nikon1MakerNote::print0x0002(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0002 with empty value
TEST_F(Nikon1MakerNoteTest_417, Print0x0002WithEmptyValue_417) {
    UShortValue value;
    Nikon1MakerNote::print0x0002(os, value, nullptr);
    // Should still produce some output or handle gracefully
    // No crash is the minimum expectation
}

// Test print0x0007 with a string value
TEST_F(Nikon1MakerNoteTest_417, Print0x0007WithStringValue_417) {
    AsciiValue value;
    value.read("BASIC");
    Nikon1MakerNote::print0x0007(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0007 with empty string
TEST_F(Nikon1MakerNoteTest_417, Print0x0007WithEmptyString_417) {
    AsciiValue value;
    value.read("");
    Nikon1MakerNote::print0x0007(os, value, nullptr);
    // Should handle gracefully without crash
}

// Test print0x0085 with a rational value (lens info)
TEST_F(Nikon1MakerNoteTest_417, Print0x0085WithRationalValue_417) {
    URationalValue value;
    value.read("500/10");
    Nikon1MakerNote::print0x0085(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0085 with zero value
TEST_F(Nikon1MakerNoteTest_417, Print0x0085WithZeroValue_417) {
    URationalValue value;
    value.read("0/1");
    Nikon1MakerNote::print0x0085(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0086 with a rational value (digital zoom)
TEST_F(Nikon1MakerNoteTest_417, Print0x0086WithRationalValue_417) {
    URationalValue value;
    value.read("100/100");
    Nikon1MakerNote::print0x0086(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0086 with zero denominator or zero value
TEST_F(Nikon1MakerNoteTest_417, Print0x0086WithZeroValue_417) {
    URationalValue value;
    value.read("0/1");
    Nikon1MakerNote::print0x0086(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0088 with a known AF value
TEST_F(Nikon1MakerNoteTest_417, Print0x0088WithKnownValue_417) {
    UShortValue value;
    value.read("0");
    Nikon1MakerNote::print0x0088(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0088 with another known value
TEST_F(Nikon1MakerNoteTest_417, Print0x0088WithAnotherValue_417) {
    UShortValue value;
    value.read("1");
    Nikon1MakerNote::print0x0088(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test printBarValue with typical byte data
TEST_F(Nikon1MakerNoteTest_417, PrintBarValueWithByteData_417) {
    DataBuf buf(10);
    std::memset(buf.data(), 0, 10);
    DataValue value(TypeId::undefined);
    value.read(buf.data(), buf.size(), invalidByteOrder);
    Nikon1MakerNote::printBarValue(os, value, nullptr);
    // Should handle the byte data gracefully
}

// Test printBarValue with empty data
TEST_F(Nikon1MakerNoteTest_417, PrintBarValueWithEmptyData_417) {
    DataValue value(TypeId::undefined);
    Nikon1MakerNote::printBarValue(os, value, nullptr);
    // Should handle empty value gracefully
}

// Test printBarValue with single byte
TEST_F(Nikon1MakerNoteTest_417, PrintBarValueWithSingleByte_417) {
    uint8_t byte = 42;
    DataValue value(TypeId::undefined);
    value.read(&byte, 1, invalidByteOrder);
    Nikon1MakerNote::printBarValue(os, value, nullptr);
    std::string result = os.str();
    // Should produce some output
}

// Test print0x0085 with large rational value
TEST_F(Nikon1MakerNoteTest_417, Print0x0085WithLargeRational_417) {
    URationalValue value;
    value.read("99999/1");
    Nikon1MakerNote::print0x0085(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0086 with large zoom value
TEST_F(Nikon1MakerNoteTest_417, Print0x0086WithLargeZoom_417) {
    URationalValue value;
    value.read("1000/100");
    Nikon1MakerNote::print0x0086(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test that multiple calls to tagList return the same pointer
TEST_F(Nikon1MakerNoteTest_417, TagListConsistentAcrossCalls_417) {
    auto tags1 = Nikon1MakerNote::tagList();
    auto tags2 = Nikon1MakerNote::tagList();
    EXPECT_EQ(tags1, tags2);
}

// Test print0x0088 with a boundary / unknown value
TEST_F(Nikon1MakerNoteTest_417, Print0x0088WithUnknownValue_417) {
    UShortValue value;
    value.read("255");
    Nikon1MakerNote::print0x0088(os, value, nullptr);
    std::string result = os.str();
    // Should handle unknown value, possibly printing it as-is or as "Unknown"
    EXPECT_FALSE(result.empty());
}

// Test print0x0002 with large count of values
TEST_F(Nikon1MakerNoteTest_417, Print0x0002WithManyValues_417) {
    UShortValue value;
    value.read("1 2 3 4 5 6 7 8 9 10");
    Nikon1MakerNote::print0x0002(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
