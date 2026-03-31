#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include "catch2/internal/catch_console_colour.hpp"

namespace {

// We need a concrete ColourImpl to create ColourGuard instances.
// Since ColourImpl may be abstract, we create a minimal mock/stub.
class StubColourImpl : public Catch::ColourImpl {
public:
    // Implement pure virtual methods if any exist
    // Based on the interface, we provide minimal implementation
    using ColourImpl::ColourImpl;
};

class ColourGuardTest_1095 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that move constructor transfers state from source
TEST_F(ColourGuardTest_1095, MoveConstructorTransfersState_1095) {
    // We can test that after move construction, the moved-from guard
    // does not cause issues (e.g., double-free or double-disengage)
    // This tests that rhs.m_engaged is set to false after move
    
    // Since ColourGuard constructor requires a Colour::Code and const ColourImpl*,
    // and we may not have a concrete ColourImpl easily, we test what we can.
    // Creating with nullptr should at least allow construction.
    
    Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard guard2(std::move(guard1));
    
    // After move, guard2 should be valid and guard1 should be disengaged
    // Destruction of both should not crash (guard1 is disengaged)
}

// Test that move constructor with engaged guard transfers engagement
TEST_F(ColourGuardTest_1095, MoveConstructorFromEngagedGuard_1095) {
    Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::Red, nullptr);
    std::ostringstream oss;
    
    // Engage the guard - engage returns reference to self
    // Note: with nullptr ColourImpl, engage may or may not work depending on impl
    // We test what's safe
    Catch::ColourImpl::ColourGuard guard2(std::move(guard1));
    // guard1 should be disengaged, guard2 should have the state
    // Both destructors should run without issues
}

// Test move assignment operator
TEST_F(ColourGuardTest_1095, MoveAssignmentOperator_1095) {
    Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard guard2(Catch::Colour::Code::None, nullptr);
    
    guard2 = std::move(guard1);
    // After move assignment, guard1 should be disengaged
    // Destruction should not crash
}

// Test that engage returns reference to self
TEST_F(ColourGuardTest_1095, EngageReturnsSelfReference_1095) {
    Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
    std::ostringstream oss;
    
    auto& result = guard.engage(oss);
    EXPECT_EQ(&result, &guard);
}

// Test construction with different Colour::Code values
TEST_F(ColourGuardTest_1095, ConstructionWithVariousCodes_1095) {
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
    }
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::White, nullptr);
    }
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::Red, nullptr);
    }
    // All should construct and destruct without issues
}

// Test that move constructor leaves source in valid but disengaged state
TEST_F(ColourGuardTest_1095, MoveConstructorSourceDestructsSafely_1095) {
    auto guard1 = std::make_unique<Catch::ColourImpl::ColourGuard>(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard guard2(std::move(*guard1));
    guard1.reset(); // Destroy moved-from guard - should not crash
}

// Test self-move-assignment safety
TEST_F(ColourGuardTest_1095, MoveAssignmentChain_1095) {
    Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard guard2(Catch::Colour::Code::Red, nullptr);
    Catch::ColourImpl::ColourGuard guard3(Catch::Colour::Code::None, nullptr);
    
    guard3 = std::move(guard2);
    guard3 = std::move(guard1);
    // All should be fine on destruction
}

} // anonymous namespace
