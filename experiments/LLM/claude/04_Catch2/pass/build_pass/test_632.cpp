#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <utility>

#include "catch2/internal/catch_console_colour.hpp"

namespace Catch {

// We need a concrete ColourImpl to test ColourGuard.
// Since ColourImpl is the base, we create a minimal test double.
// However, since we're testing ColourGuard's public interface as a black box,
// we only need to construct valid ColourGuard instances and invoke public methods.

class ColourGuardTest_632 : public ::testing::Test {
protected:
    std::ostringstream stream;
};

// Test that ColourGuard can be constructed with a Colour::Code and a nullptr ColourImpl
TEST_F(ColourGuardTest_632, ConstructWithNullColourImpl_632) {
    // Constructing with nullptr should not crash immediately
    // The guard just holds pointers/state
    Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
    // If we get here without crashing, construction succeeded
    SUCCEED();
}

// Test that engage returns a reference to the same ColourGuard object
TEST_F(ColourGuardTest_632, EngageReturnsSelfReference_632) {
    // With nullptr ColourImpl, engage might not do anything meaningful
    // but should still return *this
    Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
    auto& ref = guard.engage(stream);
    EXPECT_EQ(&ref, &guard);
}

// Test move constructor transfers state
TEST_F(ColourGuardTest_632, MoveConstructor_632) {
    Catch::ColourImpl::ColourGuard original(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard moved(std::move(original));
    // moved guard should be usable
    auto& ref = moved.engage(stream);
    EXPECT_EQ(&ref, &moved);
}

// Test move assignment operator
TEST_F(ColourGuardTest_632, MoveAssignment_632) {
    Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::None, nullptr);
    Catch::ColourImpl::ColourGuard guard2(Catch::Colour::Code::None, nullptr);
    guard2 = std::move(guard1);
    auto& ref = guard2.engage(stream);
    EXPECT_EQ(&ref, &guard2);
}

// Test that destructor can be called without issues on a non-engaged guard
TEST_F(ColourGuardTest_632, DestructorNonEngaged_632) {
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
        // Let it go out of scope without engaging
    }
    SUCCEED();
}

// Test that destructor can be called on an engaged guard with null impl
TEST_F(ColourGuardTest_632, DestructorAfterEngage_632) {
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
        guard.engage(stream);
        // Let it go out of scope after engaging
    }
    SUCCEED();
}

// Test with different Colour::Code values
TEST_F(ColourGuardTest_632, DifferentColourCodes_632) {
    // Test construction with various colour codes
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::Red, nullptr);
        SUCCEED();
    }
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::Green, nullptr);
        SUCCEED();
    }
    {
        Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::Blue, nullptr);
        SUCCEED();
    }
}

// Test that moved-from guard's destructor is safe
TEST_F(ColourGuardTest_632, MovedFromGuardDestructorSafe_632) {
    {
        Catch::ColourImpl::ColourGuard guard1(Catch::Colour::Code::None, nullptr);
        guard1.engage(stream);
        Catch::ColourImpl::ColourGuard guard2(std::move(guard1));
        // Both guards go out of scope - moved-from should be safe to destroy
    }
    SUCCEED();
}

// Test engage with different streams
TEST_F(ColourGuardTest_632, EngageWithDifferentStreams_632) {
    std::ostringstream stream1;
    std::ostringstream stream2;
    
    Catch::ColourImpl::ColourGuard guard(Catch::Colour::Code::None, nullptr);
    auto& ref = guard.engage(stream1);
    EXPECT_EQ(&ref, &guard);
}

// Test copy constructor is deleted (compile-time check - this test just documents the intent)
// ColourGuard(ColourGuard const&) = delete;
// ColourGuard& operator=(ColourGuard const&) = delete;
// These are compile-time constraints, verified by the fact that the following would not compile:
// Catch::ColourImpl::ColourGuard copy(guard); // Should not compile

} // namespace Catch
