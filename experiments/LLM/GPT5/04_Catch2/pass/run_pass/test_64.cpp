// File: should_suppress_failure_test.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_result_type.hpp"

using Catch::shouldSuppressFailure;
using Flags = Catch::ResultDisposition::Flags;

TEST(ShouldSuppressFailureTest_64, ReturnsFalse_ForZero_64) {
    EXPECT_FALSE(shouldSuppressFailure(0));
}

TEST(ShouldSuppressFailureTest_64, ReturnsTrue_ForSuppressOnly_64) {
    EXPECT_TRUE(shouldSuppressFailure(Flags::SuppressFail));
}

TEST(ShouldSuppressFailureTest_64, ReturnsFalse_ForNormalOnly_64) {
    EXPECT_FALSE(shouldSuppressFailure(Flags::Normal));
}

TEST(ShouldSuppressFailureTest_64, ReturnsFalse_ForContinueOnFailureOnly_64) {
    EXPECT_FALSE(shouldSuppressFailure(Flags::ContinueOnFailure));
}

TEST(ShouldSuppressFailureTest_64, ReturnsFalse_ForFalseTestOnly_64) {
    EXPECT_FALSE(shouldSuppressFailure(Flags::FalseTest));
}

TEST(ShouldSuppressFailureTest_64, ReturnsFalse_ForCombinationWithoutSuppress_64) {
    const int combo = Flags::Normal | Flags::ContinueOnFailure | Flags::FalseTest;
    EXPECT_FALSE(shouldSuppressFailure(combo));
}

TEST(ShouldSuppressFailureTest_64, ReturnsTrue_ForCombinationWithSuppress_64) {
    const int combo = Flags::Normal | Flags::ContinueOnFailure | Flags::SuppressFail;
    EXPECT_TRUE(shouldSuppressFailure(combo));
}

TEST(ShouldSuppressFailureTest_64, ReturnsTrue_ForAllKnownFlagsCombined_64) {
    const int combo = Flags::Normal | Flags::ContinueOnFailure | Flags::FalseTest | Flags::SuppressFail;
    EXPECT_TRUE(shouldSuppressFailure(combo));
}
