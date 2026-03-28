#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/catch_all.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <type_traits>
#include <utility>

namespace {

class ColourGuardTest_630 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that ColourGuard is not copy constructible (deleted)
TEST_F(ColourGuardTest_630, IsNotCopyConstructible_630) {
    EXPECT_FALSE(std::is_copy_constructible<Catch::ColourImpl::ColourGuard>::value);
}

// Test that ColourGuard is not copy assignable (deleted)
TEST_F(ColourGuardTest_630, IsNotCopyAssignable_630) {
    EXPECT_FALSE(std::is_copy_assignable<Catch::ColourImpl::ColourGuard>::value);
}

// Test that ColourGuard is move constructible
TEST_F(ColourGuardTest_630, IsMoveConstructible_630) {
    EXPECT_TRUE(std::is_move_constructible<Catch::ColourImpl::ColourGuard>::value);
}

// Test that ColourGuard is move assignable
TEST_F(ColourGuardTest_630, IsMoveAssignable_630) {
    EXPECT_TRUE(std::is_move_assignable<Catch::ColourImpl::ColourGuard>::value);
}

// Test that ColourGuard is nothrow move constructible
TEST_F(ColourGuardTest_630, IsNothrowMoveConstructible_630) {
    EXPECT_TRUE(std::is_nothrow_move_constructible<Catch::ColourImpl::ColourGuard>::value);
}

// Test that ColourGuard is nothrow move assignable
TEST_F(ColourGuardTest_630, IsNothrowMoveAssignable_630) {
    EXPECT_TRUE(std::is_nothrow_move_assignable<Catch::ColourImpl::ColourGuard>::value);
}

// Test constructing a ColourGuard with nullptr ColourImpl and using it without crash
TEST_F(ColourGuardTest_630, ConstructWithNullptrDoesNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::None, nullptr);
    });
}

// Test move constructor from a guard with nullptr impl
TEST_F(ColourGuardTest_630, MoveConstructFromNullImplDoesNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard guard1(Catch::Colour::None, nullptr);
        Catch::ColourImpl::ColourGuard guard2(std::move(guard1));
    });
}

// Test move assignment with nullptr impl
TEST_F(ColourGuardTest_630, MoveAssignWithNullImplDoesNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard guard1(Catch::Colour::None, nullptr);
        Catch::ColourImpl::ColourGuard guard2(Catch::Colour::None, nullptr);
        guard2 = std::move(guard1);
    });
}

// Test self-move-assignment scenario (edge case)
TEST_F(ColourGuardTest_630, SelfMoveAssignDoesNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::None, nullptr);
        guard = std::move(guard);
    });
}

// Test engage returns reference to same guard (chainability)
TEST_F(ColourGuardTest_630, EngageReturnsReferenceToSelf_630) {
    std::ostringstream oss;
    Catch::ColourImpl::ColourGuard guard(Catch::Colour::None, nullptr);
    auto& result = guard.engage(oss);
    EXPECT_EQ(&result, &guard);
}

// Test that destruction after move does not cause issues
TEST_F(ColourGuardTest_630, DestructionAfterMoveDoesNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard guard1(Catch::Colour::None, nullptr);
        Catch::ColourImpl::ColourGuard guard2(std::move(guard1));
        // guard1 is now moved-from, both will be destroyed
    });
}

// Test multiple move assignments in sequence
TEST_F(ColourGuardTest_630, MultipleMoveAssignmentsDoNotCrash_630) {
    EXPECT_NO_THROW({
        Catch::ColourImpl::ColourGuard g1(Catch::Colour::None, nullptr);
        Catch::ColourImpl::ColourGuard g2(Catch::Colour::None, nullptr);
        Catch::ColourImpl::ColourGuard g3(Catch::Colour::None, nullptr);
        g2 = std::move(g1);
        g3 = std::move(g2);
    });
}

} // anonymous namespace
