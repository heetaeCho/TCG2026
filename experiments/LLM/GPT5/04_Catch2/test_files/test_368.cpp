// File: test_basic_result_bool_368.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include "catch2/internal/catch_clara.hpp"

namespace CCD = Catch::Clara::Detail;

using BRVoid = CCD::BasicResult<void>;
using BRInt  = CCD::BasicResult<int>;

TEST(BasicResultBoolTest_368, OkVoid_ConvertsToTrue_368) {
    auto r = BRVoid::ok();
    EXPECT_TRUE(static_cast<bool>(r));
    // Also exercise control-flow usage of explicit operator bool()
    int hits = 0;
    if (r) { ++hits; }
    EXPECT_EQ(hits, 1);
}

TEST(BasicResultBoolTest_368, OkWithZeroValue_StillTrue_368) {
    auto r = BRInt::ok(0); // value is 0 but result should be "Ok"
    EXPECT_TRUE(static_cast<bool>(r));
    int hits = 0;
    if (r) { ++hits; }
    EXPECT_EQ(hits, 1);
}

TEST(BasicResultBoolTest_368, LogicError_ConvertsToFalse_368) {
    auto r = BRVoid::logicError(std::string{"bad logic"});
    EXPECT_FALSE(static_cast<bool>(r));
    int hits = 0;
    if (r) { ++hits; }  // should not execute
    EXPECT_EQ(hits, 0);
}

TEST(BasicResultBoolTest_368, RuntimeError_ConvertsToFalse_368) {
    auto r = BRVoid::runtimeError(std::string{"runtime oops"});
    EXPECT_FALSE(static_cast<bool>(r));
    int hits = 0;
    if (r) { ++hits; }  // should not execute
    EXPECT_EQ(hits, 0);
}

TEST(BasicResultBoolTest_368, ExplicitnessTraits_AreCorrect_368) {
    // The conversion should be explicit:
    static_assert(!std::is_convertible<BRVoid, bool>::value,
                  "BasicResult must not be implicitly convertible to bool");
    static_assert(std::is_constructible<bool, BRVoid>::value,
                  "BasicResult should be explicitly convertible to bool");
    // And the explicit conversion should not throw
    auto ok = BRVoid::ok();
    EXPECT_NO_THROW( { (void)static_cast<bool>(ok); } );
}

TEST(BasicResultBoolTest_368, BoolResultPreservedAcrossCopyAndMove_368) {
    // Copy
    auto ok = BRVoid::ok();
    BRVoid ok_copy = ok;
    EXPECT_TRUE(static_cast<bool>(ok_copy));

    // Move
    BRVoid ok_moved = std::move(ok_copy);
    EXPECT_TRUE(static_cast<bool>(ok_moved));

    // Error copy & move
    auto err = BRVoid::runtimeError(std::string{"x"});
    BRVoid err_copy = err;
    EXPECT_FALSE(static_cast<bool>(err_copy));

    BRVoid err_moved = std::move(err_copy);
    EXPECT_FALSE(static_cast<bool>(err_moved));
}
