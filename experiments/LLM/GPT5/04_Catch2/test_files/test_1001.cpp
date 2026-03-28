// File: tests/test_testcaseinfo_less_1001.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Catch2 headers (public interface)
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>

using namespace Catch;

namespace {

// Small helper to build a TestCaseInfo through its public constructor.
inline TestCaseInfo makeTCI(const std::string& name,
                            const std::string& classNameStr = "",
                            const std::string& tagString = "",
                            const SourceLineInfo& sli = SourceLineInfo{__FILE__, __LINE__}) {
    NameAndTags nt;
    nt.name = name;
    nt.tags = tagString; // Tag parsing is an internal detail; we only pass the string as allowed by the interface.
    TestCaseInfo tci{ StringRef{classNameStr.c_str(), classNameStr.size()}, nt, sli };
    return tci;
}

// Best-effort helper to create a Tag via public API surface.
// We avoid depending on internal state/logic and only rely on ability to construct and compare.
inline Tag makeTag(const std::string& original) {
    // Tag typically has a constructor taking StringRef in Catch2 public headers.
    return Tag{ StringRef{original.c_str(), original.size()} };
}

} // namespace

class TestCaseInfoLess_1001 : public ::testing::Test {};

// --- Compare by name ---

TEST_F(TestCaseInfoLess_1001, NamePrimaryOrder_Less_1001) {
    auto a = makeTCI("Alpha", "C1");
    auto b = makeTCI("Beta",  "C1");

    // Expect lexicographic ordering by name first.
    EXPECT_TRUE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

TEST_F(TestCaseInfoLess_1001, NamePrimaryOrder_EqualNames_1001) {
    auto a = makeTCI("Same", "C1");
    auto b = makeTCI("Same", "C1");

    // With equal names and equal className and no tags difference, neither is less.
    EXPECT_FALSE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

// --- Tie on name -> compare className ---

TEST_F(TestCaseInfoLess_1001, ClassNameTieBreaksOnEqualNames_1001) {
    auto a = makeTCI("Same", "AClass");
    auto b = makeTCI("Same", "BClass");

    // Names equal, className decides.
    EXPECT_TRUE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

TEST_F(TestCaseInfoLess_1001, ClassNameEqual_NoLessWhenNamesAndClassEqual_1001) {
    auto a = makeTCI("Same", "SameClass");
    auto b = makeTCI("Same", "SameClass");

    // No observable difference yet; should not be less either way.
    EXPECT_FALSE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

// --- Tie on name & className -> compare tags ---

TEST_F(TestCaseInfoLess_1001, TagsLexicographicOrderAsFinalTieBreaker_1001) {
    auto a = makeTCI("Same", "SameClass");
    auto b = makeTCI("Same", "SameClass");

    // Make tags distinct. We only rely on public members:
    // - tags is public std::vector<Tag>
    // - Tag has a public constructor taking StringRef (public header surface)
    a.tags.clear();
    b.tags.clear();

    a.tags.push_back( makeTag("alpha") );
    a.tags.push_back( makeTag("zulu") );

    b.tags.push_back( makeTag("bravo") );
    b.tags.push_back( makeTag("charlie") );

    // With same name and class, ordering must be determined by tags vector's ordering.
    EXPECT_TRUE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

TEST_F(TestCaseInfoLess_1001, TagsEqual_NoLessWhenAllKeysEqual_1001) {
    auto a = makeTCI("Same", "SameClass");
    auto b = makeTCI("Same", "SameClass");

    a.tags = { makeTag("one"), makeTag("two") };
    b.tags = { makeTag("one"), makeTag("two") };

    EXPECT_FALSE( operator<(a, b) );
    EXPECT_FALSE( operator<(b, a) );
}

// --- Boundary conditions ---

TEST_F(TestCaseInfoLess_1001, EmptyNameIsLessThanNonEmptyName_1001) {
    auto emptyName = makeTCI("", "C1");
    auto nonEmpty  = makeTCI("X", "C1");

    EXPECT_TRUE( operator<(emptyName, nonEmpty) );
    EXPECT_FALSE( operator<(nonEmpty, emptyName) );
}

TEST_F(TestCaseInfoLess_1001, EmptyClassNameTiesOnlyIfNamesEqual_1001) {
    // Names equal; className "" vs "A"
    auto a = makeTCI("Same", "");
    auto b = makeTCI("Same", "A");

    EXPECT_TRUE( operator<(a, b) );     // "" < "A" lexicographically
    EXPECT_FALSE( operator<(b, a) );
}

// --- Strict-weak-ordering sanity checks ---

TEST_F(TestCaseInfoLess_1001, AntiSymmetry_Holds_1001) {
    auto a = makeTCI("A", "C");
    auto b = makeTCI("B", "C");

    const bool a_lt_b = operator<(a, b);
    const bool b_lt_a = operator<(b, a);

    EXPECT_NE(a_lt_b, b_lt_a);
    EXPECT_TRUE(a_lt_b);
    EXPECT_FALSE(b_lt_a);
}

TEST_F(TestCaseInfoLess_1001, SortProducesExpectedOrder_1001) {
    auto t1 = makeTCI("Gamma", "Z");
    auto t2 = makeTCI("Alpha", "Z");
    auto t3 = makeTCI("Alpha", "A"); // same name as t2; className breaks ties
    auto t4 = makeTCI("Alpha", "A"); // equal to t3; tags break ties

    // Distinguish t3 and t4 only via tags as the final tiebreaker
    t3.tags = { makeTag("bravo") };
    t4.tags = { makeTag("charlie") };

    std::vector<TestCaseInfo> v{ t1, t2, t3, t4 };
    std::sort(v.begin(), v.end(), [](const TestCaseInfo& lhs, const TestCaseInfo& rhs) {
        return operator<(lhs, rhs);
    });

    // Expected order:
    // 1) t3:  name "Alpha", class "A", tags ["bravo"]
    // 2) t4:  name "Alpha", class "A", tags ["charlie"]
    // 3) t2:  name "Alpha", class "Z"
    // 4) t1:  name "Gamma", class "Z"
    ASSERT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0].className, StringRef("A"));
    EXPECT_EQ(v[1].className, StringRef("A"));
    EXPECT_EQ(v[2].className, StringRef("Z"));
    EXPECT_EQ(v[3].className, StringRef("Z"));

    // Confirm the two "A" entries are ordered by tags (bravo < charlie).
    // We rely only on observable ordering result, not internal tag comparison details.
    EXPECT_TRUE( operator<(v[0], v[1]) );
    EXPECT_FALSE( operator<(v[1], v[0]) );
}
