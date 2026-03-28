#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "catch2/internal/catch_console_colour.hpp"

// We need to work with the Catch namespace
using namespace Catch;

// Since ColourImpl is abstract/base, we need a concrete implementation for testing.
// We'll create a minimal mock/stub that allows us to construct ColourGuard objects.

class MockColourImpl : public ColourImpl {
public:
    // We need to implement whatever pure virtual methods ColourImpl has.
    // Based on the interface, ColourImpl likely has methods that ColourGuard calls.
    // We mock what we can observe.
    MOCK_METHOD(void, use, (Colour::Code, std::ostream&), (const));
    
    // If ColourImpl has a guardColour method or similar, we provide it
    ColourGuard guardColour(Colour::Code code) const {
        return ColourGuard(code, this);
    }
};

class ColourGuardTest_426 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that a ColourGuard can be constructed and destroyed without crashing
TEST_F(ColourGuardTest_426, ConstructAndDestroy_426) {
    MockColourImpl impl;
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard(Colour::None, &impl);
    });
}

// Test that a ColourGuard can be constructed with nullptr ColourImpl
TEST_F(ColourGuardTest_426, ConstructWithNullColourImpl_426) {
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard(Colour::None, nullptr);
    });
}

// Test that engage returns a reference to itself
TEST_F(ColourGuardTest_426, EngageReturnsSelf_426) {
    MockColourImpl impl;
    ColourImpl::ColourGuard guard(Colour::None, &impl);
    ColourImpl::ColourGuard& ref = guard.engage(oss);
    EXPECT_EQ(&ref, &guard);
}

// Test that the stream operator works with ColourGuard rvalue
TEST_F(ColourGuardTest_426, StreamOperatorWorks_426) {
    MockColourImpl impl;
    ColourImpl::ColourGuard guard(Colour::None, &impl);
    EXPECT_NO_THROW({
        oss << std::move(guard);
    });
}

// Test move constructor
TEST_F(ColourGuardTest_426, MoveConstructor_426) {
    MockColourImpl impl;
    ColourImpl::ColourGuard guard1(Colour::None, &impl);
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard2(std::move(guard1));
    });
}

// Test move assignment operator
TEST_F(ColourGuardTest_426, MoveAssignment_426) {
    MockColourImpl impl;
    ColourImpl::ColourGuard guard1(Colour::Red, &impl);
    ColourImpl::ColourGuard guard2(Colour::None, &impl);
    EXPECT_NO_THROW({
        guard2 = std::move(guard1);
    });
}

// Test engage with nullptr ColourImpl doesn't crash
TEST_F(ColourGuardTest_426, EngageWithNullImplDoesNotCrash_426) {
    ColourImpl::ColourGuard guard(Colour::Red, nullptr);
    EXPECT_NO_THROW({
        guard.engage(oss);
    });
}

// Test stream operator with nullptr ColourImpl
TEST_F(ColourGuardTest_426, StreamOperatorWithNullImpl_426) {
    ColourImpl::ColourGuard guard(Colour::Red, nullptr);
    EXPECT_NO_THROW({
        oss << std::move(guard);
    });
}

// Test that engage can be chained (returns reference)
TEST_F(ColourGuardTest_426, EngageChaining_426) {
    MockColourImpl impl;
    ColourImpl::ColourGuard guard(Colour::Green, &impl);
    // engage returns ColourGuard&, so we can chain with stream operator
    EXPECT_NO_THROW({
        oss << std::move(guard.engage(oss));
    });
}

// Test different colour codes
TEST_F(ColourGuardTest_426, DifferentColourCodes_426) {
    MockColourImpl impl;
    
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard1(Colour::Red, &impl);
        guard1.engage(oss);
    });
    
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard2(Colour::Green, &impl);
        guard2.engage(oss);
    });
    
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard3(Colour::Blue, &impl);
        guard3.engage(oss);
    });
}

// Test that moved-from guard can be safely destroyed
TEST_F(ColourGuardTest_426, MovedFromGuardSafelyDestroys_426) {
    MockColourImpl impl;
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard1(Colour::Red, &impl);
        guard1.engage(oss);
        ColourImpl::ColourGuard guard2(std::move(guard1));
        // guard1 is moved-from, should be safely destructible
    });
}

// Test move assignment after engage
TEST_F(ColourGuardTest_426, MoveAssignmentAfterEngage_426) {
    MockColourImpl impl;
    EXPECT_NO_THROW({
        ColourImpl::ColourGuard guard1(Colour::Red, &impl);
        guard1.engage(oss);
        ColourImpl::ColourGuard guard2(Colour::Blue, &impl);
        guard2 = std::move(guard1);
    });
}
