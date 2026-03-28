// File: test_from_range_941.cpp

#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <forward_list>
#include <sstream>
#include <iterator>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::from_range;

class FromRangeTest_941 : public ::testing::Test {
protected:
    template <typename Gen>
    static std::vector<typename std::remove_cv<typename std::remove_reference<decltype(std::declval<Gen>().get())>::type>::type>
    Drain(Gen& gen) {
        using T = typename std::remove_cv<typename std::remove_reference<decltype(gen.get())>::type>::type;
        std::vector<T> out;
        // As observable by the Generator interface: get() gives current value,
        // next() advances and returns whether there is a new current value.
        out.push_back(gen.get());
        while (gen.next()) {
            out.push_back(gen.get());
        }
        return out;
    }
};

// Normal operation: iterates full range in order (random-access iterators)
TEST_F(FromRangeTest_941, ReturnsAllElementsInOrder_Vector_941) {
    std::vector<int> v{1, 2, 3, 4, 5};

    auto gen = from_range(v.begin(), v.end());

    auto values = Drain(gen);
    ASSERT_EQ(values.size(), v.size());
    EXPECT_EQ(values, v);
}

// Normal operation: works with forward iterators (e.g., std::forward_list)
TEST_F(FromRangeTest_941, WorksWithForwardIterators_ForwardList_941) {
    std::forward_list<int> fl{7, 8, 9};

    auto gen = from_range(fl.begin(), fl.end());

    auto values = Drain(gen);
    std::vector<int> expected{7, 8, 9};
    EXPECT_EQ(values, expected);
}

// Normal operation: works with input iterators (single-pass) such as istream_iterator
TEST_F(FromRangeTest_941, WorksWithInputIterators_IstreamIterator_941) {
    std::istringstream iss("10 20 30");
    std::istream_iterator<int> first(iss);
    std::istream_iterator<int> last; // end sentinel

    auto gen = from_range(first, last);

    auto values = Drain(gen);
    std::vector<int> expected{10, 20, 30};
    EXPECT_EQ(values, expected);
}

// Boundary condition: single-element range
TEST_F(FromRangeTest_941, SingleElementRange_941) {
    std::list<std::string> one{"only"};

    auto gen = from_range(one.begin(), one.end());

    // get() should give the only element, and next() should immediately return false
    EXPECT_EQ(gen.get(), "only");
    EXPECT_FALSE(gen.next());
    EXPECT_EQ(gen.get(), "only"); // observable behavior in Catch2: current remains last yielded
}

// Exceptional / error case (observable): constructing from an empty range throws
TEST_F(FromRangeTest_941, EmptyRangeThrows_941) {
    std::vector<int> empty;

    // We do not assume a specific exception type beyond std::exception to avoid
    // coupling to internals; we only assert that construction via from_range is not allowed.
    EXPECT_THROW({
        // Wrap in an IIFE so we only test construction
        auto gen = from_range(empty.begin(), empty.end());
        (void)gen;
    }, std::exception);
}
