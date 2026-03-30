// File: tests/from_range_container_overload_942.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"
#include <vector>
#include <list>
#include <initializer_list>

using namespace Catch;

// A tiny ADL test namespace: free begin/end increment counters.
// This lets us *observe* that the container overload calls ADL begin/end exactly once each.
namespace adl_probe_942 {
    struct Box {
        std::vector<int> data;
    };

    static int begin_calls = 0;
    static int end_calls   = 0;

    // ADL-visible free functions
    inline auto begin(Box const& b) {
        ++begin_calls;
        return b.data.begin();
    }
    inline auto end(Box const& b) {
        ++end_calls;
        return b.data.end();
    }

    inline void reset_counters() {
        begin_calls = 0;
        end_calls   = 0;
    }
} // namespace adl_probe_942

// Test suite for TEST_ID 942
// NOTE: We treat generators as a black box and only use the public GeneratorWrapper interface:
//   - get() returns current value (const ref)
//   - next() advances; returns true if moved to a valid value, false if at end
// This is Catch2 public, observable behavior.
class FromRangeTest_942 : public ::testing::Test {};

TEST(FromRangeTest_942, ForwardsToAdlBeginEnd_942) {
    using namespace adl_probe_942;

    reset_counters();
    Box b{{1, 2, 3}};

    // Call the container overload; it should resolve free begin/end via ADL exactly once each.
    auto gen = Catch::Generators::from_range(b);

    // Do not rely on internal behavior of the returned generator here.
    // The *observable* thing we can assert is that our ADL begin/end were invoked.
    EXPECT_EQ(begin_calls, 1) << "from_range(Container const&) should call ADL begin exactly once";
    EXPECT_EQ(end_calls,   1) << "from_range(Container const&) should call ADL end exactly once";

    // Optionally touch the generator to ensure it is “used” (avoid over-optimization warnings).
    // We won't assert further behavior in this test.
    (void)gen;
}

TEST(FromRangeTest_942, IteratesVectorValuesInOrder_942) {
    std::vector<int> v{10, 20, 30};
    auto gen = Catch::Generators::from_range(v);

    // First value is immediately available via get()
    EXPECT_EQ(gen.get(), 10);

    // Advance through the rest
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    // Past the end
    EXPECT_FALSE(gen.next());
}

TEST(FromRangeTest_942, IteratesListSingleElement_942) {
    std::list<std::string> lst{"only"};
    auto gen = Catch::Generators::from_range(lst);

    EXPECT_EQ(gen.get(), "only");
    EXPECT_FALSE(gen.next()); // single element — no more values
}

TEST(FromRangeTest_942, IteratesInitializerList_942) {
    const std::initializer_list<char> il = {'a', 'b'};
    auto gen = Catch::Generators::from_range(il);

    EXPECT_EQ(gen.get(), 'a');
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 'b');
    EXPECT_FALSE(gen.next());
}

// Empty range behavior is observable via the public API.
// Catch2 generators constructed from an empty range are expected to throw a GeneratorException.
TEST(FromRangeTest_942, EmptyRangeThrows_942) {
    std::vector<int> empty;
    EXPECT_THROW(
        {
            auto gen = Catch::Generators::from_range(empty);
            (void)gen;
        },
        Catch::Generators::GeneratorException
    );
}
