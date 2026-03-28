#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "sigmamn_int.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test that tagList returns a non-null pointer
TEST(SigmaMakerNoteTest_1356, TagListReturnsNonNull_1356) {
    auto tags = SigmaMakerNote::tagList();
    ASSERT_NE(tags, nullptr);
}

// Test that the first entry in tagList has a valid tag number (typically starts with a known tag)
TEST(SigmaMakerNoteTest_1356, TagListFirstEntryValid_1356) {
    auto tags = SigmaMakerNote::tagList();
    ASSERT_NE(tags, nullptr);
    // The tag list should have entries; the first entry should have a non-empty title or name
    // TagInfo typically has tag_, name_, title_, desc_, ifdId_, sectionId_, typeId_, count_, print_
    // We just verify the list is accessible and first element has a reasonable tag
    EXPECT_NE(tags[0].tag_, 0xffff); // Should not be the sentinel immediately
}

// Test that tagList is terminated (there should be a sentinel entry with tag_ == 0xffff at the end)
TEST(SigmaMakerNoteTest_1356, TagListHasSentinel_1356) {
    auto tags = SigmaMakerNote::tagList();
    ASSERT_NE(tags, nullptr);
    int count = 0;
    while (tags[count].tag_ != 0xffff) {
        count++;
        // Safety: don't iterate forever
        ASSERT_LT(count, 1000) << "Tag list seems too long or missing sentinel";
    }
    EXPECT_GT(count, 0) << "Tag list should have at least one entry before sentinel";
}

// Test printStripLabel with a normal ASCII string value
TEST(SigmaMakerNoteTest_1356, PrintStripLabelNormal_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("TestLabel");
    SigmaMakerNote::printStripLabel(os, value, nullptr);
    std::string result = os.str();
    // The function should output something based on the value
    EXPECT_FALSE(result.empty());
}

// Test printStripLabel with empty value
TEST(SigmaMakerNoteTest_1356, PrintStripLabelEmpty_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("");
    SigmaMakerNote::printStripLabel(os, value, nullptr);
    // Should not crash; output may be empty or contain default text
    // Just verify it doesn't throw
}

// Test print0x0008 with a normal value
TEST(SigmaMakerNoteTest_1356, Print0x0008Normal_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("FINE");
    SigmaMakerNote::print0x0008(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0008 with empty value
TEST(SigmaMakerNoteTest_1356, Print0x0008Empty_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("");
    SigmaMakerNote::print0x0008(os, value, nullptr);
    // Should handle gracefully
}

// Test print0x0009 with a normal value
TEST(SigmaMakerNoteTest_1356, Print0x0009Normal_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("SHI");
    SigmaMakerNote::print0x0009(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0009 with empty value
TEST(SigmaMakerNoteTest_1356, Print0x0009Empty_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("");
    SigmaMakerNote::print0x0009(os, value, nullptr);
    // Should handle gracefully
}

// Test print0x0008 returns the same ostream reference
TEST(SigmaMakerNoteTest_1356, Print0x0008ReturnsSameStream_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("RAW");
    std::ostream& ret = SigmaMakerNote::print0x0008(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test print0x0009 returns the same ostream reference
TEST(SigmaMakerNoteTest_1356, Print0x0009ReturnsSameStream_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("HI");
    std::ostream& ret = SigmaMakerNote::print0x0009(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test printStripLabel returns the same ostream reference
TEST(SigmaMakerNoteTest_1356, PrintStripLabelReturnsSameStream_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("SomeLabel");
    std::ostream& ret = SigmaMakerNote::printStripLabel(os, value, nullptr);
    EXPECT_EQ(&ret, &os);
}

// Test printStripLabel with a value that has leading/trailing spaces
TEST(SigmaMakerNoteTest_1356, PrintStripLabelStripsWhitespace_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("  Label  ");
    SigmaMakerNote::printStripLabel(os, value, nullptr);
    std::string result = os.str();
    // "Strip" in the name suggests whitespace stripping; verify no leading/trailing spaces
    if (!result.empty()) {
        EXPECT_NE(result.front(), ' ');
        EXPECT_NE(result.back(), ' ');
    }
}

// Test that tagList can be called multiple times and returns the same pointer (constexpr)
TEST(SigmaMakerNoteTest_1356, TagListConsistentAcrossCalls_1356) {
    auto tags1 = SigmaMakerNote::tagList();
    auto tags2 = SigmaMakerNote::tagList();
    EXPECT_EQ(tags1, tags2);
}

// Test print0x0008 with an unknown/unrecognized value
TEST(SigmaMakerNoteTest_1356, Print0x0008UnknownValue_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("XYZUNKNOWN");
    SigmaMakerNote::print0x0008(os, value, nullptr);
    // Should produce some output (possibly the raw value or "Unknown")
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test print0x0009 with an unknown/unrecognized value
TEST(SigmaMakerNoteTest_1356, Print0x0009UnknownValue_1356) {
    std::ostringstream os;
    AsciiValue value;
    value.read("XYZUNKNOWN");
    SigmaMakerNote::print0x0009(os, value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
