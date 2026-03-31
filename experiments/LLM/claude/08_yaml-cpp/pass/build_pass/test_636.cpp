#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"
#include "emitterutils.h"

namespace YAML {
namespace Utils {

// Helper to get the output string from ostream_wrapper
std::string GetOutput(ostream_wrapper& out) {
    const char* s = out.str();
    if (s) {
        return std::string(s, out.pos());
    }
    return "";
}

std::string GetStreamOutput(std::ostream& stream) {
    std::ostringstream& oss = dynamic_cast<std::ostringstream&>(stream);
    return oss.str();
}

// ============================================================
// Tests for WriteTag with verbatim = false (non-verbatim / tag)
// ============================================================

class WriteTagNonVerbatimTest_636 : public ::testing::Test {
protected:
    ostream_wrapper out;
};

TEST_F(WriteTagNonVerbatimTest_636, SimpleTagReturnsTrue_636) {
    // A simple valid tag string
    bool result = WriteTag(out, "yaml", false);
    EXPECT_TRUE(result);
}

TEST_F(WriteTagNonVerbatimTest_636, SimpleTagOutputStartsWithBang_636) {
    WriteTag(out, "yaml", false);
    std::string output = GetOutput(out);
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output[0], '!');
}

TEST_F(WriteTagNonVerbatimTest_636, SimpleTagOutputContainsTag_636) {
    WriteTag(out, "yaml", false);
    std::string output = GetOutput(out);
    // Should be "!yaml"
    EXPECT_EQ(output, "!yaml");
}

TEST_F(WriteTagNonVerbatimTest_636, EmptyStringReturnsTrue_636) {
    // Empty string - no characters to match, loop doesn't execute
    bool result = WriteTag(out, "", false);
    EXPECT_TRUE(result);
}

TEST_F(WriteTagNonVerbatimTest_636, EmptyStringOutputOnlyBang_636) {
    WriteTag(out, "", false);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!");
}

TEST_F(WriteTagNonVerbatimTest_636, AlphanumericTag_636) {
    bool result = WriteTag(out, "tag123", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!tag123");
}

TEST_F(WriteTagNonVerbatimTest_636, TagWithHyphen_636) {
    bool result = WriteTag(out, "my-tag", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!my-tag");
}

TEST_F(WriteTagNonVerbatimTest_636, TagWithPercentEncoding_636) {
    // Percent-encoded characters should be valid in tags
    bool result = WriteTag(out, "tag%20name", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!tag%20name");
}

TEST_F(WriteTagNonVerbatimTest_636, TagWithExclamation_636) {
    bool result = WriteTag(out, "!secondary", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!!secondary");
}

TEST_F(WriteTagNonVerbatimTest_636, SingleCharTag_636) {
    bool result = WriteTag(out, "a", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!a");
}

// ============================================================
// Tests for WriteTag with verbatim = true
// ============================================================

class WriteTagVerbatimTest_636 : public ::testing::Test {
protected:
    ostream_wrapper out;
};

TEST_F(WriteTagVerbatimTest_636, SimpleURIReturnsTrue_636) {
    bool result = WriteTag(out, "tag:yaml.org,2002:str", true);
    EXPECT_TRUE(result);
}

TEST_F(WriteTagVerbatimTest_636, SimpleURIOutputFormat_636) {
    WriteTag(out, "tag:yaml.org,2002:str", true);
    std::string output = GetOutput(out);
    // Should be "!<tag:yaml.org,2002:str>"
    EXPECT_EQ(output, "!<tag:yaml.org,2002:str>");
}

TEST_F(WriteTagVerbatimTest_636, VerbatimStartsWithBangAngle_636) {
    WriteTag(out, "something", true);
    std::string output = GetOutput(out);
    ASSERT_GE(output.size(), 2u);
    EXPECT_EQ(output.substr(0, 2), "!<");
}

TEST_F(WriteTagVerbatimTest_636, VerbatimEndsWithClosingAngle_636) {
    WriteTag(out, "something", true);
    std::string output = GetOutput(out);
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '>');
}

TEST_F(WriteTagVerbatimTest_636, EmptyStringVerbatim_636) {
    bool result = WriteTag(out, "", true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!<>");
}

TEST_F(WriteTagVerbatimTest_636, URIWithSlashes_636) {
    bool result = WriteTag(out, "http://example.com/tag", true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!<http://example.com/tag>");
}

TEST_F(WriteTagVerbatimTest_636, URIWithPercentEncoding_636) {
    bool result = WriteTag(out, "tag%20name", true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!<tag%20name>");
}

// ============================================================
// Tests for invalid characters that should cause failure
// ============================================================

class WriteTagInvalidTest_636 : public ::testing::Test {
protected:
    ostream_wrapper out;
};

TEST_F(WriteTagInvalidTest_636, InvalidCharReturnsFalse_NonVerbatim_636) {
    // Space is not valid in a tag
    bool result = WriteTag(out, "invalid tag", false);
    EXPECT_FALSE(result);
}

TEST_F(WriteTagInvalidTest_636, TabCharReturnsFalse_NonVerbatim_636) {
    bool result = WriteTag(out, "invalid\ttag", false);
    EXPECT_FALSE(result);
}

TEST_F(WriteTagInvalidTest_636, NewlineReturnsFalse_NonVerbatim_636) {
    bool result = WriteTag(out, "invalid\ntag", false);
    EXPECT_FALSE(result);
}

TEST_F(WriteTagInvalidTest_636, SpaceInVerbatim_636) {
    // Space is also not valid in URI
    bool result = WriteTag(out, "invalid tag", true);
    EXPECT_FALSE(result);
}

// ============================================================
// Tests using ostream_wrapper with a stream
// ============================================================

class WriteTagWithStreamTest_636 : public ::testing::Test {
protected:
    std::ostringstream ss;
};

TEST_F(WriteTagWithStreamTest_636, NonVerbatimWritesToStream_636) {
    ostream_wrapper out(ss);
    bool result = WriteTag(out, "mytag", false);
    EXPECT_TRUE(result);
    // Flush by checking the stream
    // Note: ostream_wrapper writes to stream directly
    EXPECT_EQ(ss.str(), "!mytag");
}

TEST_F(WriteTagWithStreamTest_636, VerbatimWritesToStream_636) {
    ostream_wrapper out(ss);
    bool result = WriteTag(out, "mytag", true);
    EXPECT_TRUE(result);
    EXPECT_EQ(ss.str(), "!<mytag>");
}

// ============================================================
// Additional edge cases
// ============================================================

class WriteTagEdgeCasesTest_636 : public ::testing::Test {
protected:
    ostream_wrapper out;
};

TEST_F(WriteTagEdgeCasesTest_636, TagWithDot_636) {
    bool result = WriteTag(out, "yaml.org", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!yaml.org");
}

TEST_F(WriteTagEdgeCasesTest_636, TagWithUnderscore_636) {
    bool result = WriteTag(out, "my_tag", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!my_tag");
}

TEST_F(WriteTagEdgeCasesTest_636, NullCharInMiddle_636) {
    // String with null character - the string constructor handles this
    std::string s("ab");
    s += '\0';
    s += "cd";
    bool result = WriteTag(out, s, false);
    // Null char is likely not a valid tag character
    EXPECT_FALSE(result);
}

TEST_F(WriteTagEdgeCasesTest_636, LongValidTag_636) {
    std::string longTag(1000, 'a');
    bool result = WriteTag(out, longTag, false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.size(), 1001u);  // '!' + 1000 'a's
    EXPECT_EQ(output[0], '!');
}

TEST_F(WriteTagEdgeCasesTest_636, LongValidVerbatimTag_636) {
    std::string longTag(1000, 'a');
    bool result = WriteTag(out, longTag, true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output.size(), 1003u);  // "!<" + 1000 'a's + ">"
    EXPECT_EQ(output.substr(0, 2), "!<");
    EXPECT_EQ(output.back(), '>');
}

TEST_F(WriteTagEdgeCasesTest_636, InvalidCharAtStart_NonVerbatim_636) {
    bool result = WriteTag(out, " invalid", false);
    EXPECT_FALSE(result);
}

TEST_F(WriteTagEdgeCasesTest_636, TagWithColon_Verbatim_636) {
    // Colon should be valid in URI (verbatim)
    bool result = WriteTag(out, "tag:yaml.org", true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!<tag:yaml.org>");
}

TEST_F(WriteTagEdgeCasesTest_636, PartialOutputOnFailure_636) {
    // When WriteTag fails midway, partial output may have been written
    // The function returns false but some chars may have been output
    ostream_wrapper out2;
    bool result = WriteTag(out2, "valid invalid", false);
    EXPECT_FALSE(result);
    // We just verify it returns false; we don't mandate specific partial output
}

TEST_F(WriteTagEdgeCasesTest_636, TagWithNumbers_636) {
    bool result = WriteTag(out, "12345", false);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!12345");
}

TEST_F(WriteTagEdgeCasesTest_636, VerbatimTagWithHashFragment_636) {
    bool result = WriteTag(out, "http://example.com#frag", true);
    EXPECT_TRUE(result);
    std::string output = GetOutput(out);
    EXPECT_EQ(output, "!<http://example.com#frag>");
}

}  // namespace Utils
}  // namespace YAML
