// rangeToString_tests_89.cpp
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <array>
#include <initializer_list>

// ---- Test doubles & instrumentation ----
// We provide a test double for the dependency that Catch::rangeToString calls:
// ::Catch::Detail::rangeToString(begin(range), end(range))
namespace Catch { namespace Detail {
struct RangeToStringSpy {
    static inline int calls = 0;
    static inline std::string next_return = "detail-called";
    static inline ptrdiff_t last_distance = -1; // distance between iterators when they are pointers
    static void reset() {
        calls = 0;
        next_return = "detail-called";
        last_distance = -1;
    }
};

// Generic template that matches what the wrapper calls.
// It records that it was invoked and (if possible) the distance for pointer iterators.
template <typename It>
std::string rangeToString(It b, It e) {
    ++RangeToStringSpy::calls;
    // If iterators are pointers (common in our custom ADL range), record distance.
    if constexpr (std::is_pointer_v<It>) {
        RangeToStringSpy::last_distance = e - b;
    } else {
        RangeToStringSpy::last_distance = -1; // unknown / not a raw pointer
    }
    return RangeToStringSpy::next_return;
}
}} // namespace Catch::Detail
// ---------------------------------------

// A custom range whose begin/end are found via ADL and which instrument calls.
namespace myrng {
static inline int begin_calls = 0;
static inline int end_calls = 0;
static inline const int* last_begin_ptr = nullptr;
static inline const int* last_end_ptr = nullptr;

struct Range {
    const int* data = nullptr;
    std::size_t sz = 0;
};

inline void reset_instrumentation() {
    begin_calls = end_calls = 0;
    last_begin_ptr = last_end_ptr = nullptr;
}

inline const int* begin(const Range& r) {
    ++begin_calls;
    last_begin_ptr = r.data;
    return r.data;
}

inline const int* end(const Range& r) {
    ++end_calls;
    last_end_ptr = r.data + r.sz;
    return r.data + r.sz;
}
} // namespace myrng

// Include the header-under-test *after* introducing the dependency test double.
#include "Catch2/src/catch2/catch_tostring.hpp"

// --------------- Tests ------------------

TEST(RangeToStringTest_89, ReturnsDependencyResult_89) {
    using Catch::Detail::RangeToStringSpy;

    RangeToStringSpy::reset();
    RangeToStringSpy::next_return = "expected-from-dependency";

    std::vector<int> v{1,2,3};

    // Call the function under test
    std::string out = Catch::rangeToString(v);

    // It should just return whatever the dependency returned
    EXPECT_EQ(out, "expected-from-dependency");
    EXPECT_EQ(RangeToStringSpy::calls, 1);
}

TEST(RangeToStringTest_89, UsesADLBeginEnd_AndForwardsIterators_89) {
    using Catch::Detail::RangeToStringSpy;
    using namespace myrng;

    RangeToStringSpy::reset();
    reset_instrumentation();

    const int buf[] = {10, 20, 30, 40};
    Range r{buf, 4};

    std::string out = Catch::rangeToString(r);
    (void)out; // value already covered by previous test; here we focus on forwarding/ADL

    // ADL begin/end must have been invoked exactly once each
    EXPECT_EQ(begin_calls, 1);
    EXPECT_EQ(end_calls, 1);

    // Our dependency spy should have been called once
    EXPECT_EQ(RangeToStringSpy::calls, 1);

    // Because our ADL begin/end return raw pointers, the spy records distance
    EXPECT_EQ(RangeToStringSpy::last_distance, 4);

    // Sanity: the begin/end functions saw the correct pointers
    EXPECT_EQ(last_begin_ptr, &buf[0]);
    EXPECT_EQ(last_end_ptr, &buf[0] + 4);
}

TEST(RangeToStringTest_89, WorksWithEmptyRange_89) {
    using Catch::Detail::RangeToStringSpy;
    using namespace myrng;

    RangeToStringSpy::reset();
    reset_instrumentation();

    const int* empty_data = nullptr;
    Range r{empty_data, 0};

    std::string s = Catch::rangeToString(r);
    EXPECT_EQ(s, "detail-called"); // default spy return

    // ADL begin/end called, and pointers should be equal (empty)
    EXPECT_EQ(begin_calls, 1);
    EXPECT_EQ(end_calls, 1);
    EXPECT_EQ(last_begin_ptr, empty_data);
    EXPECT_EQ(last_end_ptr, empty_data);

    // Dependency invoked once; distance = 0 for pointer iterators
    EXPECT_EQ(RangeToStringSpy::calls, 1);
    EXPECT_EQ(RangeToStringSpy::last_distance, 0);
}

TEST(RangeToStringTest_89, AcceptsCommonRangeTypes_VectorArrayInitList_89) {
    using Catch::Detail::RangeToStringSpy;

    // vector
    {
        RangeToStringSpy::reset();
        std::vector<int> v{1,2};
        (void)Catch::rangeToString(v);
        EXPECT_EQ(RangeToStringSpy::calls, 1);
    }

    // std::array
    {
        RangeToStringSpy::reset();
        std::array<int,3> a{{1,2,3}};
        (void)Catch::rangeToString(a);
        EXPECT_EQ(RangeToStringSpy::calls, 1);
    }

    // initializer_list
    {
        RangeToStringSpy::reset();
        (void)Catch::rangeToString({4,5,6});
        EXPECT_EQ(RangeToStringSpy::calls, 1);
    }
}
