// File: tests/tag_alias_registry_find_675_tests.cpp

#include <gtest/gtest.h>

// Include the public interface only (treat implementation as a black box)
#include "Catch2/src/catch2/internal/catch_tag_alias_registry.hpp"
// If SourceLineInfo is declared in a different header in your tree, include it instead.
// e.g. #include "Catch2/src/catch2/internal/catch_source_line_info.hpp"

namespace {

using Catch::TagAliasRegistry;
using Catch::TagAlias;
using Catch::SourceLineInfo;

class TagAliasRegistryTest_675 : public ::testing::Test {
protected:
    TagAliasRegistry registry;

    // Helper to make a SourceLineInfo without relying on internals
    static SourceLineInfo MakeLine(const char* file = "dummy_file.cpp", std::size_t line = 123) {
        return SourceLineInfo{file, line};
    }
};

// [Normal] find on an empty registry should return nullptr for any alias
TEST_F(TagAliasRegistryTest_675, FindUnknownReturnsNullptr_675) {
    TagAlias const* result = registry.find("[does_not_exist]");
    EXPECT_EQ(result, nullptr);
}

// [Normal] after adding an alias, find should return a non-null pointer for that alias
TEST_F(TagAliasRegistryTest_675, AddThenFindReturnsNonNull_675) {
    registry.add("[my_alias]", "[my_tag]", MakeLine());
    TagAlias const* result = registry.find("[my_alias]");
    EXPECT_NE(result, nullptr);
}

// [Boundary] exact-match behavior: similar-looking but different alias should not resolve
TEST_F(TagAliasRegistryTest_675, FindRequiresExactMatch_675) {
    registry.add("[lowercase]", "[t]", MakeLine());
    // Different casing should not match unless the implementation explicitly normalizes (we assume exact match by observation)
    TagAlias const* sameCase   = registry.find("[lowercase]");
    TagAlias const* otherCase  = registry.find("[LOWERCASE]");
    EXPECT_NE(sameCase, nullptr);
    EXPECT_EQ(otherCase, nullptr);
}

// [Normal/Independence] multiple aliases can coexist; unknown aliases still return nullptr
TEST_F(TagAliasRegistryTest_675, MultipleAliasesIndependentAndUnknownIsNull_675) {
    registry.add("[alias_a]", "[tag_a]", MakeLine("a.cpp", 10));
    registry.add("[alias_b]", "[tag_b]", MakeLine("b.cpp", 20));

    TagAlias const* a = registry.find("[alias_a]");
    TagAlias const* b = registry.find("[alias_b]");
    TagAlias const* c = registry.find("[alias_c]");

    EXPECT_NE(a, nullptr);
    EXPECT_NE(b, nullptr);
    EXPECT_EQ(c, nullptr);
}

} // namespace
