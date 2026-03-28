// tests/has_size_matcher_test_232.cpp
#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <string>

#include "catch2/matchers/catch_matchers_container_properties.hpp"

using Catch::Matchers::HasSizeMatcher;

// A custom range-like type that exposes ONLY a non-member `size` found via ADL.
// It has no member .size(), ensuring we don't rely on member access.
namespace adl_only_ns {
    struct OnlyFreeSizeRange {
        int sentinel; // any payload
    };

    // Non-member size, to be found via ADL
    inline std::size_t size(const OnlyFreeSizeRange&) {
        return 7u;
    }
} // namespace adl_only_ns

// ---------- Normal operation ----------

TEST(HasSizeMatcherTest_232, VectorExactMatch_232) {
    HasSizeMatcher m{3u};
    std::vector<int> v{1, 2, 3};
    EXPECT_TRUE(m.match(v));
}

TEST(HasSizeMatcherTest_232, StringExactMatch_232) {
    HasSizeMatcher m{5u};
    std::string s = "hello";
    EXPECT_TRUE(m.match(s));
}

TEST(HasSizeMatcherTest_232, RValueContainerMatch_232) {
    HasSizeMatcher m{2u};
    // Pass a temporary (rvalue) to exercise forwarding in match(RangeLike&&)
    EXPECT_TRUE(m.match(std::vector<int>{10, 20}));
}

// ---------- Mismatch cases ----------

TEST(HasSizeMatcherTest_232, VectorSizeMismatch_232) {
    HasSizeMatcher m{4u};
    std::vector<int> v{1, 2, 3};
    EXPECT_FALSE(m.match(v));
}

TEST(HasSizeMatcherTest_232, StringSizeMismatch_232) {
    HasSizeMatcher m{0u};
    std::string s = "x";
    EXPECT_FALSE(m.match(s));
}

// ---------- Boundary conditions ----------

TEST(HasSizeMatcherTest_232, EmptyContainerMatch_232) {
    HasSizeMatcher m{0u};
    std::vector<int> empty;
    EXPECT_TRUE(m.match(empty));
}

TEST(HasSizeMatcherTest_232, CArrayExactMatch_232) {
    HasSizeMatcher m{3u};
    int arr[3] = {1, 2, 3};
    EXPECT_TRUE(m.match(arr));
}

TEST(HasSizeMatcherTest_232, ZeroSizedStdArrayMatch_232) {
    HasSizeMatcher m{0u};
    std::array<int, 0> a{};
    EXPECT_TRUE(m.match(a));
}

// ---------- ADL-based non-member size ----------

TEST(HasSizeMatcherTest_232, NonMemberSizeFoundViaADL_232) {
    using adl_only_ns::OnlyFreeSizeRange;
    HasSizeMatcher m{7u};
    OnlyFreeSizeRange rng{42};
    // Should locate adl_only_ns::size(rng) and compare to 7
    EXPECT_TRUE(m.match(rng));
}

TEST(HasSizeMatcherTest_232, NonMemberSizeADLMismatch_232) {
    using adl_only_ns::OnlyFreeSizeRange;
    HasSizeMatcher m{6u};
    OnlyFreeSizeRange rng{42};
    EXPECT_FALSE(m.match(rng));
}

// ---------- Describe (observable string presence without assuming exact wording) ----------

TEST(HasSizeMatcherTest_232, DescribeReturnsNonEmptyString_232) {
    HasSizeMatcher m{3u};
    // We do not assert exact text; only that some description is provided.
    std::string desc = m.describe();
    EXPECT_FALSE(desc.empty());
}
