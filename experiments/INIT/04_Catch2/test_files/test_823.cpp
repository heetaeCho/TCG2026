// File: tests/defaultListTags_tests_823.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Catch2 internals we interact with as a *public interface for our tests*.
#include "catch2/internal/catch_list.hpp"              // Catch::TagInfo
// The declaration of defaultListTags is in helpers; if there's no header,
// we forward-declare it here matching the provided signature.
namespace Catch {
    void defaultListTags(std::ostream& out,
                         std::vector<TagInfo> const& tags,
                         bool isFiltered);
}

using namespace Catch;

namespace {

class DefaultListTagsTest_823 : public ::testing::Test {
protected:
    static bool ContainsInOrder(const std::string& text,
                                const std::string& a,
                                const std::string& b) {
        const auto posA = text.find(a);
        if (posA == std::string::npos) return false;
        const auto posB = text.find(b, posA + a.size());
        return posB != std::string::npos;
    }
};

} // namespace

// Header behavior when isFiltered = true
TEST_F(DefaultListTagsTest_823, Header_WhenFilteredTrue_823) {
    std::ostringstream oss;
    std::vector<TagInfo> tags; // empty

    defaultListTags(oss, tags, /*isFiltered=*/true);

    const std::string out = oss.str();
    // Expect filtered header
    EXPECT_NE(out.find("Tags for matching test cases:\n"), std::string::npos);
    // Expect pluralization and two trailing newlines
    EXPECT_NE(out.find("0 tags"), std::string::npos);
    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), std::string("\n\n"));
}

// Header behavior when isFiltered = false
TEST_F(DefaultListTagsTest_823, Header_WhenFilteredFalse_823) {
    std::ostringstream oss;
    std::vector<TagInfo> tags; // empty

    defaultListTags(oss, tags, /*isFiltered=*/false);

    const std::string out = oss.str();
    // Expect non-filtered header
    EXPECT_NE(out.find("All available tags:\n"), std::string::npos);
    // Expect pluralization for 0 tags
    EXPECT_NE(out.find("0 tags"), std::string::npos);
}

// Prints each tag with a 2-wide, space-padded count prefix and preserves order
TEST_F(DefaultListTagsTest_823, PrintsEachTagWithPaddedCount_AndPreservesOrder_823) {
    TagInfo t1;
    t1.add("[alpha]");
    t1.count = 3;

    TagInfo t2;
    t2.add("[beta]");
    t2.count = 12;

    std::vector<TagInfo> tags{t1, t2};

    std::ostringstream oss;
    defaultListTags(oss, tags, /*isFiltered=*/false);
    const std::string out = oss.str();

    // Counts appear in 2-wide fields: "  3 " (space-space-3-space) and " 12 " (space-1-2-space)
    EXPECT_NE(out.find("  3 "), std::string::npos);
    EXPECT_NE(out.find(" 12 "), std::string::npos);

    // Tag spellings should be present
    EXPECT_NE(out.find("[alpha]"), std::string::npos);
    EXPECT_NE(out.find("[beta]"), std::string::npos);

    // Order should match the input vector order: [alpha] before [beta]
    EXPECT_TRUE(ContainsInOrder(out, "[alpha]", "[beta]"));

    // Footer pluralization for 2 tags
    EXPECT_NE(out.find("2 tags"), std::string::npos);
}

// Multiple spellings in a single TagInfo should be surfaced by TagInfo::all()
TEST_F(DefaultListTagsTest_823, MultipleSpellingsAreListed_823) {
    TagInfo t;
    t.add("[a]");
    t.add("[alpha]");
    t.count = 1;

    std::vector<TagInfo> tags{t};

    std::ostringstream oss;
    defaultListTags(oss, tags, /*isFiltered=*/false);
    const std::string out = oss.str();

    // Both spellings should appear in the output somewhere
    EXPECT_NE(out.find("[a]"), std::string::npos);
    EXPECT_NE(out.find("[alpha]"), std::string::npos);

    // Check count formatting for 1 (2-wide)
    EXPECT_NE(out.find("  1 "), std::string::npos);

    // Footer pluralization for 1 tag
    EXPECT_NE(out.find("1 tag"), std::string::npos);
}

// Ensures the function terminates the output with two newlines (and flush)
TEST_F(DefaultListTagsTest_823, EndsWithTwoNewlines_823) {
    TagInfo t;
    t.add("[x]");
    t.count = 5;

    std::vector<TagInfo> tags{t};

    std::ostringstream oss;
    defaultListTags(oss, tags, /*isFiltered=*/true);
    const std::string out = oss.str();

    ASSERT_GE(out.size(), 2u);
    EXPECT_EQ(out.substr(out.size() - 2), std::string("\n\n"));
    // Sanity: footer should reflect 1 tag
    EXPECT_NE(out.find("1 tag"), std::string::npos);
}
