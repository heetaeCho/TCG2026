// File: optional_some_tests_412.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_optional.hpp"

namespace {

using Catch::Optional;

struct OptionalSomeTest_412 : ::testing::Test {};

// --- Normal operation ---

TEST_F(OptionalSomeTest_412, DefaultConstructed_IsNone_SomeFalse_412) {
    Optional<int> opt;
    EXPECT_FALSE(opt.some());
}

TEST_F(OptionalSomeTest_412, ValueConstructed_IsSomeTrue_412) {
    Optional<int> opt(42);
    EXPECT_TRUE(opt.some());
}

TEST_F(OptionalSomeTest_412, AssignedValue_IsSomeTrue_412) {
    Optional<int> opt;
    opt = 123;            // operator=(T const&)
    EXPECT_TRUE(opt.some());
}

// --- State transitions via public API ---

TEST_F(OptionalSomeTest_412, Reset_MakesNone_SomeFalse_412) {
    Optional<int> opt(7);
    ASSERT_TRUE(opt.some());  // precondition sanity
    opt.reset();
    EXPECT_FALSE(opt.some());
}

// --- Copy construction / assignment ---

TEST_F(OptionalSomeTest_412, CopyConstruct_FromSome_TargetSomeTrue_412) {
    Optional<int> src(9);
    ASSERT_TRUE(src.some()); // do not assert anything about internal state
    Optional<int> dst(src);
    EXPECT_TRUE(dst.some());
}

TEST_F(OptionalSomeTest_412, CopyConstruct_FromNone_TargetSomeFalse_412) {
    Optional<int> src; // none
    Optional<int> dst(src);
    EXPECT_FALSE(dst.some());
}

TEST_F(OptionalSomeTest_412, CopyAssign_FromSome_TargetSomeTrue_412) {
    Optional<int> src(5);
    Optional<int> dst; // none
    dst = src;         // operator=(Optional const&)
    EXPECT_TRUE(dst.some());
}

TEST_F(OptionalSomeTest_412, CopyAssign_FromNone_TargetSomeFalse_412) {
    Optional<int> src;     // none
    Optional<int> dst(10); // some
    dst = src;             // assign none
    EXPECT_FALSE(dst.some());
}

// --- Move construction / assignment ---
// We only assert the destination's observable state; we make NO claims about the source post-move.

TEST_F(OptionalSomeTest_412, MoveConstruct_FromSome_TargetSomeTrue_412) {
    Optional<int> src(77);
    Optional<int> dst(std::move(src));
    EXPECT_TRUE(dst.some());
}

TEST_F(OptionalSomeTest_412, MoveConstruct_FromNone_TargetSomeFalse_412) {
    Optional<int> src; // none
    Optional<int> dst(std::move(src));
    EXPECT_FALSE(dst.some());
}

TEST_F(OptionalSomeTest_412, MoveAssign_FromSome_TargetSomeTrue_412) {
    Optional<int> src(314);
    Optional<int> dst; // none
    dst = std::move(src);
    EXPECT_TRUE(dst.some());
}

TEST_F(OptionalSomeTest_412, MoveAssign_FromNone_TargetSomeFalse_412) {
    Optional<int> src;     // none
    Optional<int> dst(1);  // some
    dst = std::move(src);  // assign none
    EXPECT_FALSE(dst.some());
}

// --- Different T types (boundary: non-POD / larger objects) ---

TEST_F(OptionalSomeTest_412, WorksWithStdString_SomeReflectsPresence_412) {
    Optional<std::string> opt(std::string("abc"));
    EXPECT_TRUE(opt.some());
    opt.reset();
    EXPECT_FALSE(opt.some());
}

} // namespace
