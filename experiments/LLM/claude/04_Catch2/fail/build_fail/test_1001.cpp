#include <gtest/gtest.h>
#include "catch2/catch_test_case_info.hpp"

using namespace Catch;

// Helper to create TestCaseInfo objects for testing
// We need SourceLineInfo and NameAndTags to construct TestCaseInfo
// Based on the Catch2 interface

class TestCaseInfoOperatorLessTest_1001 : public ::testing::Test {
protected:
    SourceLineInfo makeLineInfo() {
        return SourceLineInfo("test_file.cpp", 1);
    }
};

TEST_F(TestCaseInfoOperatorLessTest_1001, SameNameSameClassSameTags_NotLess_1001) {
    // Two identical TestCaseInfo should not be less than each other
    TestCaseInfo a("ClassA", {"TestName", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"TestName", "[tag1]"}, makeLineInfo());

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, DifferentNames_LessByName_1001) {
    // When names differ, ordering should be by name
    TestCaseInfo a("ClassA", {"Apple", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"Banana", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, DifferentNames_ReverseLessByName_1001) {
    TestCaseInfo a("ClassA", {"Zebra", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"Apple", "[tag1]"}, makeLineInfo());

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, SameNameDifferentClassName_LessByClassName_1001) {
    // When names are the same, ordering should fall through to className
    TestCaseInfo a("Alpha", {"TestName", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("Beta", {"TestName", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, SameNameDifferentClassName_Reverse_1001) {
    TestCaseInfo a("Zeta", {"TestName", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("Alpha", {"TestName", "[tag1]"}, makeLineInfo());

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, SameNameSameClassName_DifferentTags_LessByTags_1001) {
    // When name and className are the same, ordering should fall through to tags
    TestCaseInfo a("ClassA", {"TestName", "[alpha]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"TestName", "[beta]"}, makeLineInfo());

    // Tags comparison result depends on vector<Tag> operator<
    bool aLessB = a < b;
    bool bLessA = b < a;

    // At least one direction should hold, and they shouldn't both be true
    EXPECT_FALSE(aLessB && bLessA);
    // They have different tags, so they shouldn't be equal in ordering
    EXPECT_TRUE(aLessB || bLessA);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, EmptyNameComparedToNonEmpty_1001) {
    // Empty name vs non-empty name
    // Note: empty name gets replaced by makeDefaultName(), so this tests
    // the default name behavior
    TestCaseInfo a("ClassA", {"", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"ZZZ", "[tag1]"}, makeLineInfo());

    // We don't know what makeDefaultName returns, but the comparison should be consistent
    bool aLessB = a < b;
    bool bLessA = b < a;
    EXPECT_FALSE(aLessB && bLessA); // antisymmetry
}

TEST_F(TestCaseInfoOperatorLessTest_1001, NamePrefixIsLess_1001) {
    // "Test" should be less than "TestA"
    TestCaseInfo a("ClassA", {"Test", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"TestA", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, CaseSensitiveNameComparison_1001) {
    // Uppercase letters have lower ASCII values than lowercase
    TestCaseInfo a("ClassA", {"APPLE", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"apple", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, Transitivity_1001) {
    // If a < b and b < c, then a < c
    TestCaseInfo a("ClassA", {"A", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"B", "[tag1]"}, makeLineInfo());
    TestCaseInfo c("ClassA", {"C", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, Irreflexivity_1001) {
    // a < a should always be false
    TestCaseInfo a("ClassA", {"TestName", "[tag1]"}, makeLineInfo());

    EXPECT_FALSE(a < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, SameNameEmptyClassName_VsNonEmpty_1001) {
    // Empty className vs non-empty className with same test name
    TestCaseInfo a("", {"TestName", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("ClassA", {"TestName", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, NoTags_Comparison_1001) {
    // Both with no tags, same name and className
    TestCaseInfo a("ClassA", {"TestName", ""}, makeLineInfo());
    TestCaseInfo b("ClassA", {"TestName", ""}, makeLineInfo());

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, NameDeterminesOrderBeforeClassName_1001) {
    // Even if className of a > className of b, if name of a < name of b, a < b
    TestCaseInfo a("Zeta", {"Apple", "[tag1]"}, makeLineInfo());
    TestCaseInfo b("Alpha", {"Banana", "[tag1]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(TestCaseInfoOperatorLessTest_1001, ClassNameDeterminesOrderBeforeTags_1001) {
    // Same name, different className and tags. className should take priority over tags
    TestCaseInfo a("Alpha", {"TestName", "[zzz]"}, makeLineInfo());
    TestCaseInfo b("Beta", {"TestName", "[aaa]"}, makeLineInfo());

    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}
