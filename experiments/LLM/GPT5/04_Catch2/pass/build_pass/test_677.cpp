// File: tests/tag_alias_registry_add_tests_677.cpp

#include <gtest/gtest.h>

#include "Catch2/src/catch2/internal/catch_tag_alias_registry.hpp"
#include "Catch2/src/catch2/catch_tag_alias.hpp"
#include "Catch2/src/catch2/internal/catch_source_line_info.hpp"

using namespace Catch;

class TagAliasRegistryTest_677 : public ::testing::Test {
protected:
    TagAliasRegistry reg;
};

// Normal operation: a valid alias is registered and find() returns the mapping
TEST_F(TagAliasRegistryTest_677, Add_ValidAliasRegistersAndFinds_677) {
    const std::string alias = "[@fast]";
    const std::string tag   = "[fast]";
    const SourceLineInfo where(__FILE__, static_cast<std::size_t>(__LINE__));

    EXPECT_NO_THROW(reg.add(alias, tag, where));

    TagAlias const* found = reg.find(alias);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->tag, tag);
    EXPECT_STREQ(found->lineInfo.file, where.file);
    EXPECT_EQ(found->lineInfo.line, where.line);
}

// Boundary-ish invalid format: alias missing the "@"
TEST_F(TagAliasRegistryTest_677, Add_InvalidAliasFormat_NoAtOpen_Throws_677) {
    const std::string alias = "[fast]"; // not of the form [@name]
    const std::string tag   = "[fast]";
    const SourceLineInfo where(__FILE__, static_cast<std::size_t>(__LINE__));

    EXPECT_THROW(reg.add(alias, tag, where), std::exception);
    // Not registered
    EXPECT_EQ(reg.find(alias), nullptr);
}

// Invalid format: alias missing closing bracket
TEST_F(TagAliasRegistryTest_677, Add_InvalidAliasFormat_MissingCloseBracket_Throws_677) {
    const std::string alias = "[@fast"; // no trailing ']'
    const std::string tag   = "[fast]";
    const SourceLineInfo where(__FILE__, static_cast<std::size_t>(__LINE__));

    EXPECT_THROW(reg.add(alias, tag, where), std::exception);
    EXPECT_EQ(reg.find(alias), nullptr);
}

// Exceptional case: adding the same alias twice throws, original mapping remains
TEST_F(TagAliasRegistryTest_677, Add_DuplicateAlias_SecondAddThrows_LeavesOriginalIntact_677) {
    const std::string alias = "[@dup]";
    const std::string firstTag  = "[first]";
    const std::string secondTag = "[second]";

    const SourceLineInfo firstWhere(__FILE__, static_cast<std::size_t>(__LINE__));
    ASSERT_NO_THROW(reg.add(alias, firstTag, firstWhere));

    const SourceLineInfo secondWhere(__FILE__, static_cast<std::size_t>(__LINE__));
    EXPECT_THROW(reg.add(alias, secondTag, secondWhere), std::exception);

    // Verify the original registration is still present and unchanged
    TagAlias const* found = reg.find(alias);
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->tag, firstTag);
    EXPECT_STREQ(found->lineInfo.file, firstWhere.file);
    EXPECT_EQ(found->lineInfo.line, firstWhere.line);
}

// Multiple independent aliases can be registered and found
TEST_F(TagAliasRegistryTest_677, Add_MultipleAliases_Independent_677) {
    const SourceLineInfo loc1(__FILE__, static_cast<std::size_t>(__LINE__));
    const SourceLineInfo loc2(__FILE__, static_cast<std::size_t>(__LINE__));

    ASSERT_NO_THROW(reg.add("[@a]", "[tag-a]", loc1));
    ASSERT_NO_THROW(reg.add("[@b]", "[tag-b]", loc2));

    TagAlias const* fa = reg.find("[@a]");
    TagAlias const* fb = reg.find("[@b]");
    ASSERT_NE(fa, nullptr);
    ASSERT_NE(fb, nullptr);

    EXPECT_EQ(fa->tag, "[tag-a]");
    EXPECT_EQ(fb->tag, "[tag-b]");
    EXPECT_STREQ(fa->lineInfo.file, loc1.file);
    EXPECT_STREQ(fb->lineInfo.file, loc2.file);
    EXPECT_EQ(fa->lineInfo.line, loc1.line);
    EXPECT_EQ(fb->lineInfo.line, loc2.line);
}
