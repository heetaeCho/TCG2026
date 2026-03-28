#include <gtest/gtest.h>

// Include the header under test
#include "contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding::detail;

// A simple mock/stub type to use as SignedSignificandBits parameter
struct MockSignedSignificandBits {
    int value;
};

struct AnotherSignedSignificandBits {
    double data;
    bool flag;
};

struct EmptySignedSignificandBits {};

// Test fixture
class NearestAlwaysOpenTest_375 : public ::testing::Test {
protected:
    nearest_always_open_t policy;
};

// Test that normal_interval is callable with a simple struct and returns the expected type
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalReturnsOpenIntervalType_375) {
    MockSignedSignificandBits bits{42};
    auto result = nearest_always_open_t::normal_interval(bits);
    // The return type should be interval_type::open
    using expected_type = YAML::jkj::dragonbox::interval_type::open;
    static_assert(std::is_same<decltype(result), expected_type>::value,
                  "normal_interval should return interval_type::open");
}

// Test that normal_interval works with different SignedSignificandBits types
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalWorksWithDifferentTypes_375) {
    AnotherSignedSignificandBits bits{3.14, true};
    auto result = nearest_always_open_t::normal_interval(bits);
    using expected_type = YAML::jkj::dragonbox::interval_type::open;
    static_assert(std::is_same<decltype(result), expected_type>::value,
                  "normal_interval should return interval_type::open for any type");
}

// Test that normal_interval works with an empty struct
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalWorksWithEmptyStruct_375) {
    EmptySignedSignificandBits bits{};
    auto result = nearest_always_open_t::normal_interval(bits);
    using expected_type = YAML::jkj::dragonbox::interval_type::open;
    static_assert(std::is_same<decltype(result), expected_type>::value,
                  "normal_interval should return interval_type::open for empty struct");
}

// Test that normal_interval is constexpr
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalIsConstexpr_375) {
    constexpr auto result = nearest_always_open_t::normal_interval(MockSignedSignificandBits{0});
    using expected_type = YAML::jkj::dragonbox::interval_type::open;
    static_assert(std::is_same<decltype(result), const expected_type>::value,
                  "normal_interval should be usable in constexpr context");
    (void)result;
    SUCCEED();
}

// Test that normal_interval is noexcept
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalIsNoexcept_375) {
    MockSignedSignificandBits bits{100};
    static_assert(noexcept(nearest_always_open_t::normal_interval(bits)),
                  "normal_interval should be noexcept");
    SUCCEED();
}

// Test that the result with different input values is the same (always open)
TEST_F(NearestAlwaysOpenTest_375, NormalIntervalReturnsSameTypeRegardlessOfInput_375) {
    MockSignedSignificandBits bits1{0};
    MockSignedSignificandBits bits2{-1};
    MockSignedSignificandBits bits3{std::numeric_limits<int>::max()};
    MockSignedSignificandBits bits4{std::numeric_limits<int>::min()};

    auto result1 = nearest_always_open_t::normal_interval(bits1);
    auto result2 = nearest_always_open_t::normal_interval(bits2);
    auto result3 = nearest_always_open_t::normal_interval(bits3);
    auto result4 = nearest_always_open_t::normal_interval(bits4);

    // All should return the same type - interval_type::open
    using expected_type = YAML::jkj::dragonbox::interval_type::open;
    static_assert(std::is_same<decltype(result1), expected_type>::value, "");
    static_assert(std::is_same<decltype(result2), expected_type>::value, "");
    static_assert(std::is_same<decltype(result3), expected_type>::value, "");
    static_assert(std::is_same<decltype(result4), expected_type>::value, "");
    SUCCEED();
}

// Test that nearest_always_open_t is default constructible
TEST_F(NearestAlwaysOpenTest_375, IsDefaultConstructible_375) {
    static_assert(std::is_default_constructible<nearest_always_open_t>::value,
                  "nearest_always_open_t should be default constructible");
    SUCCEED();
}

}  // namespace
