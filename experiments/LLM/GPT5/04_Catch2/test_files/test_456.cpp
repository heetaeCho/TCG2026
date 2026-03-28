// File: tests/session_configdata_test_456.cpp

#include <gtest/gtest.h>
#include "catch2/catch_session.hpp"  // Adjust include path as needed
#include <type_traits>
#include <utility>

namespace {

class SessionConfigDataTest_456 : public ::testing::Test {
protected:
    Catch::Session session_;
};

// Verifies the return type is a non-const reference (API contract of configData()).
TEST_F(SessionConfigDataTest_456, ReturnsNonConstReference_456) {
    using ReturnT = decltype(std::declval<Catch::Session&>().configData());
    static_assert(std::is_reference<ReturnT>::value,
                  "configData() must return a reference");
    static_assert(!std::is_const<std::remove_reference_t<ReturnT>>::value,
                  "configData() must return a non-const reference");

    // Also exercise the call at runtime to satisfy test coverage.
    auto& ref = session_.configData();
    (void)ref;
}

// Ensures calling configData() does not throw (observable behavior).
TEST_F(SessionConfigDataTest_456, NoThrowOnAccess_456) {
    EXPECT_NO_THROW({
        auto& ref = session_.configData();
        (void)ref;
    });
}

// Confirms repeated calls return the same underlying object (observable via address equality).
TEST_F(SessionConfigDataTest_456, SameObjectOnRepeatedCalls_456) {
    auto& first  = session_.configData();
    auto& second = session_.configData();
    EXPECT_EQ(&first, &second) << "configData() should consistently reference the same object";
}

} // namespace
