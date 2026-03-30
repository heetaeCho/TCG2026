// File: tests/tag_alias_registry_expand_aliases_676_tests.cpp

#include <gtest/gtest.h>
#include <string>

// Production headers (interfaces only)
#include "catch2/internal/catch_tag_alias_registry.hpp"
#include "catch2/catch_tag_alias.hpp"        // for Catch::TagAlias / SourceLineInfo (constructor arg types only)

namespace {

using Catch::TagAliasRegistry;
using Catch::SourceLineInfo;

struct TagAliasRegistry_676 : ::testing::Test {
    TagAliasRegistry reg;

    // Helper to add an alias -> tag mapping using only public API.
    void addAlias(const std::string& alias, const std::string& tag) {
        // We don't assert anything about SourceLineInfo internals; we just provide plausible values.
        reg.add(alias, tag, SourceLineInfo{__FILE__, __LINE__});
    }
};

// --- Normal operation ---

TEST_F(TagAliasRegistry_676, Expand_NoAliases_ReturnsInput_676) {
    const std::string input = "[fast] && ~[slow]";
    const std::string out = reg.expandAliases(input);
    EXPECT_EQ(out, input);
}

TEST_F(TagAliasRegistry_676, Expand_SingleAlias_WholeString_676) {
    addAlias("[all]", "[fast],[slow]");
    const std::string out = reg.expandAliases("[all]");
    EXPECT_EQ(out, "[fast],[slow]");
}

TEST_F(TagAliasRegistry_676, Expand_ReplacesAliasInsideText_676) {
    addAlias("[db]", "[database]");
    const std::string out = reg.expandAliases("~[db] && [smoke]");
    EXPECT_EQ(out, "~[database] && [smoke]");
}

TEST_F(TagAliasRegistry_676, Expand_MultipleDifferentAliases_676) {
    addAlias("[smoke]", "[quick]");
    addAlias("[db]", "[database]");
    const std::string out = reg.expandAliases("[smoke] && [db]");
    EXPECT_EQ(out, "[quick] && [database]");
}

// --- Boundary conditions ---

TEST_F(TagAliasRegistry_676, Expand_EmptyInput_RemainsEmpty_676) {
    addAlias("[x]", "[y]");
    const std::string out = reg.expandAliases("");
    EXPECT_TRUE(out.empty());
}

TEST_F(TagAliasRegistry_676, Expand_AliasMappedToEmptyString_RemovesThatOccurrence_676) {
    addAlias("[temporary]", "");
    const std::string out = reg.expandAliases("pre [temporary] post");
    // Observable behavior: the mapped alias position is replaced with empty string.
    EXPECT_EQ(out, "pre  post"); // double space where alias used to be
}

// --- Observable edge behavior (without assuming internal state) ---

TEST_F(TagAliasRegistry_676, Expand_MultipleOccurrencesOfSameAlias_OnlyFirstOccurrenceIsReplaced_676) {
    addAlias("[tag]", "[expanded]");
    // Based on observable behavior of expandAliases, only one occurrence per alias
    // is replaced in a single call.
    const std::string out = reg.expandAliases("[tag] and then [tag] again");
    EXPECT_EQ(out, "[expanded] and then [tag] again");
}

TEST_F(TagAliasRegistry_676, Expand_NoChangeWhenAliasNotPresent_676) {
    addAlias("[alpha]", "[A]");
    const std::string input = "[beta] && [gamma]";
    const std::string out = reg.expandAliases(input);
    EXPECT_EQ(out, input);
}

} // namespace
