#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "catch2/internal/catch_console_colour.hpp"

using namespace Catch;

class ColourGuardTest_425 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that ColourGuard can be constructed with a Colour::Code and nullptr ColourImpl
TEST_F(ColourGuardTest_425, ConstructWithNullColourImpl_425) {
    // Constructing with nullptr should not crash
    ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    // Just verifying construction doesn't throw/crash
}

// Test that ColourGuard can be move-constructed
TEST_F(ColourGuardTest_425, MoveConstruction_425) {
    ColourImpl::ColourGuard guard1(Colour::Code::None, nullptr);
    ColourImpl::ColourGuard guard2(std::move(guard1));
    // Verify move construction doesn't crash
}

// Test that ColourGuard can be move-assigned
TEST_F(ColourGuardTest_425, MoveAssignment_425) {
    ColourImpl::ColourGuard guard1(Colour::Code::None, nullptr);
    ColourImpl::ColourGuard guard2(Colour::Code::None, nullptr);
    guard2 = std::move(guard1);
    // Verify move assignment doesn't crash
}

// Test that engage returns a reference to self
TEST_F(ColourGuardTest_425, EngageReturnsSelf_425) {
    ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    ColourImpl::ColourGuard& ref = guard.engage(oss);
    EXPECT_EQ(&ref, &guard);
}

// Test that operator<< returns the ostream reference
TEST_F(ColourGuardTest_425, OperatorStreamReturnsOstream_425) {
    ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    std::ostream& result = (oss << guard);
    EXPECT_EQ(&result, &oss);
}

// Test that operator<< can be chained with string output
TEST_F(ColourGuardTest_425, OperatorStreamChaining_425) {
    ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    oss << guard << "test";
    // The stream should contain at least "test" after the guard output
    std::string output = oss.str();
    EXPECT_NE(output.find("test"), std::string::npos);
}

// Test engage with a valid stream and nullptr impl
TEST_F(ColourGuardTest_425, EngageWithNullImpl_425) {
    ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    // Engaging with a nullptr ColourImpl should be safe (no-op for colour)
    guard.engage(oss);
}

// Test that destruction after engage doesn't crash
TEST_F(ColourGuardTest_425, DestructionAfterEngage_425) {
    {
        ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
        guard.engage(oss);
    }
    // Guard destroyed, should not crash
}

// Test that destruction without engage doesn't crash
TEST_F(ColourGuardTest_425, DestructionWithoutEngage_425) {
    {
        ColourImpl::ColourGuard guard(Colour::Code::None, nullptr);
    }
    // Guard destroyed without engaging, should not crash
}

// Test move construction transfers engaged state properly
TEST_F(ColourGuardTest_425, MoveFromEngagedGuard_425) {
    ColourImpl::ColourGuard guard1(Colour::Code::None, nullptr);
    guard1.engage(oss);
    ColourImpl::ColourGuard guard2(std::move(guard1));
    // Destruction of both should be safe
}

// Test operator<< with different Colour::Code values
TEST_F(ColourGuardTest_425, StreamWithDifferentColourCodes_425) {
    ColourImpl::ColourGuard guardRed(Colour::Code::Red, nullptr);
    ColourImpl::ColourGuard guardGreen(Colour::Code::Green, nullptr);
    
    std::ostringstream oss1, oss2;
    oss1 << guardRed;
    oss2 << guardGreen;
    // Should not crash with different colour codes
}
