// File: taginfo_add_tests_602.cpp
#include <gtest/gtest.h>
#include <string>
#include <set>

// Include the production headers
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::TagInfo;
using Catch::StringRef;

class TagInfoTest_602 : public ::testing::Test {
protected:
    TagInfo info;
};

// Normal operation: adding a single spelling updates count and spellings
TEST_F(TagInfoTest_602, AddSingleSpelling_602) {
    EXPECT_EQ(info.count, 0u);
    EXPECT_TRUE(info.spellings.empty());

    info.add(StringRef("fast"));

    EXPECT_EQ(info.count, 1u);                 // observable counter behavior
    EXPECT_EQ(info.spellings.size(), 1u);      // unique spelling stored
    EXPECT_NE(info.spellings.find(StringRef("fast")), info.spellings.end());
}

// Boundary/normal: adding two different spellings increases both count and set size
TEST_F(TagInfoTest_602, AddTwoDifferentSpellings_602) {
    info.add(StringRef("alpha"));
    info.add(StringRef("beta"));

    EXPECT_EQ(info.count, 2u);
    EXPECT_EQ(info.spellings.size(), 2u);
    EXPECT_NE(info.spellings.find(StringRef("alpha")), info.spellings.end());
    EXPECT_NE(info.spellings.find(StringRef("beta")), info.spellings.end());
}

// Duplicates: repeated add of the same spelling increments count but not set size
TEST_F(TagInfoTest_602, AddDuplicateIncrementsCountOnly_602) {
    info.add(StringRef("dup"));
    info.add(StringRef("dup"));

    EXPECT_EQ(info.count, 2u);             // both calls observed via count
    EXPECT_EQ(info.spellings.size(), 1u);  // set remains unique
    EXPECT_NE(info.spellings.find(StringRef("dup")), info.spellings.end());
}

// Interop: adding via std::string and C-string should refer to the same spelling
TEST_F(TagInfoTest_602, AddStdStringAndCStringSameSpelling_602) {
    std::string s = "mixed";
    info.add(StringRef(s));          // from std::string
    info.add(StringRef("mixed"));    // from const char*

    EXPECT_EQ(info.count, 2u);
    EXPECT_EQ(info.spellings.size(), 1u);
    EXPECT_NE(info.spellings.find(StringRef("mixed")), info.spellings.end());
}

// Boundary: adding empty spellings (default StringRef / empty C-string)
TEST_F(TagInfoTest_602, AddEmptySpellings_602) {
    StringRef empty_default;     // default-constructed (empty)
    StringRef empty_cstr("");    // from empty C-string

    info.add(empty_default);
    info.add(empty_cstr);

    EXPECT_EQ(info.count, 2u);             // both adds observed
    EXPECT_EQ(info.spellings.size(), 1u);  // only one unique empty spelling
    EXPECT_NE(info.spellings.find(StringRef("")), info.spellings.end());
}
