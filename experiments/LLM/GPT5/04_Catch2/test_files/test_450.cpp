// File: session_libidentify_test.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Use the provided header so we only rely on the public interface.
#include "Catch2/src/catch2/catch_session.hpp"

// Forward declare Catch::cout(), which is used by libIdentify().
// (This is part of Catch2's public surface used in the implementation.)
namespace Catch {
    std::ostream& cout();
}

namespace {

// Small RAII helper to capture and restore the stream buffer of Catch::cout()
class CoutCapture {
public:
    CoutCapture() : old_buf_(Catch::cout().rdbuf(oss_.rdbuf())) {}
    ~CoutCapture() { Catch::cout().rdbuf(old_buf_); }

    std::string str() const { return oss_.str(); }

private:
    std::ostringstream oss_;
    std::streambuf* old_buf_;
};

} // namespace

// Fixture kept simple for readability/consistency
class SessionLibIdentifyTest_450 : public ::testing::Test {
protected:
    // Utility to run libIdentify and return everything it wrote
    std::string RunOnceAndCollect() {
        CoutCapture cap;
        Catch::Session s;
        s.libIdentify();
        return cap.str();
    }
};

// Verifies the 3 stable lines (description/category/framework) are exactly correct,
// and the version line begins with the expected padded label and ends with '\n'.
TEST_F(SessionLibIdentifyTest_450, PrintsExpectedLinesAndVersionPrefix_450) {
    const std::string out = RunOnceAndCollect();

    // Build the expected first three lines (with exact padding to width 16)
    const std::string expected_first3 =
        std::string("description:   ") + "A Catch2 test executable\n" +  // "description: " (13 chars) -> pad 3
        std::string("category:      ") + "testframework\n" +              // "category: " (10 chars) -> pad 6
        std::string("framework:     ") + "Catch2\n";                      // "framework: " (11 chars) -> pad 5

    ASSERT_GE(out.size(), expected_first3.size()) << "Output shorter than expected first three lines";

    // First three lines must match exactly
    EXPECT_EQ(out.substr(0, expected_first3.size()), expected_first3);

    // The remainder must start with the version line's padded label
    const std::string remainder = out.substr(expected_first3.size());
    const std::string version_prefix = "version:       "; // "version: " (9 chars) -> pad 7
    ASSERT_TRUE(remainder.rfind(version_prefix, 0) == 0)
        << "Version line must start with exactly '" << version_prefix << "'";

    // Must contain a trailing newline after some non-empty version text
    const auto nl_pos = remainder.find('\n');
    ASSERT_NE(nl_pos, std::string::npos) << "Version line must end with a newline";
    ASSERT_GT(nl_pos, version_prefix.size())
        << "Version text should be non-empty between prefix and newline";
    
    // Nothing after the version line
    EXPECT_EQ(remainder.size(), nl_pos + 1) << "Unexpected extra output after version line";
}

// Verifies the values begin at column 16 (i.e., labels are exactly width 16, left-justified).
TEST_F(SessionLibIdentifyTest_450, LabelsAreWidth16LeftJustified_450) {
    const std::string out = RunOnceAndCollect();

    // Split lines
    auto first_nl = out.find('\n');
    ASSERT_NE(first_nl, std::string::npos);
    const std::string line1 = out.substr(0, first_nl);

    auto second_nl = out.find('\n', first_nl + 1);
    ASSERT_NE(second_nl, std::string::npos);
    const std::string line2 = out.substr(first_nl + 1, second_nl - (first_nl + 1));

    auto third_nl = out.find('\n', second_nl + 1);
    ASSERT_NE(third_nl, std::string::npos);
    const std::string line3 = out.substr(second_nl + 1, third_nl - (second_nl + 1));

    auto fourth_nl = out.find('\n', third_nl + 1);
    ASSERT_NE(fourth_nl, std::string::npos);
    const std::string line4 = out.substr(third_nl + 1, fourth_nl - (third_nl + 1));

    // For the first three lines we know the values exactly
    EXPECT_EQ(line1.find("A Catch2 test executable"), 16u);
    EXPECT_EQ(line2.find("testframework"), 16u);
    EXPECT_EQ(line3.find("Catch2"), 16u);

    // For the version line we don't know the version text, but we know the padded label
    const std::string expected_label4 = "version:       "; // 16 characters
    ASSERT_GE(line4.size(), expected_label4.size());
    EXPECT_EQ(line4.substr(0, expected_label4.size()), expected_label4);
    // Also ensure there is at least one character after the label (the version)
    EXPECT_GT(line4.size(), expected_label4.size());
}

// Verifies that calling libIdentify() multiple times appends the same block each time.
TEST_F(SessionLibIdentifyTest_450, MultipleCallsProduceRepeatedBlocks_450) {
    // Capture two consecutive calls and compare with a single call repeated
    CoutCapture cap;
    Catch::Session s;

    s.libIdentify();
    const std::string first = cap.str();

    s.libIdentify();
    const std::string both = cap.str();

    ASSERT_FALSE(first.empty()) << "First call should produce output";
    ASSERT_EQ(both.size(), first.size() * 2)
        << "Two calls should produce exactly two blocks of output";
    EXPECT_EQ(both.substr(0, first.size()), first);
    EXPECT_EQ(both.substr(first.size(), first.size()), first);
}
