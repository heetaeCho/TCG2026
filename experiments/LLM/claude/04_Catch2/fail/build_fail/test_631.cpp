#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>

// Include necessary Catch2 headers
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_stream.hpp"

using namespace Catch;

// Mock implementation of ColourImpl to test ColourGuard behavior
class MockColourImpl : public ColourImpl {
public:
    MockColourImpl(IStream* stream) : ColourImpl(stream) {}
    
    MOCK_METHOD(void, use, (Colour::Code colourCode), (const, override));
};

// Mock IStream for testing
class MockIStream : public IStream {
public:
    MOCK_METHOD(std::ostream&, stream, (), (override));
};

class ColourGuardTest_631 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = std::make_unique<MockIStream>();
        oss = std::make_unique<std::ostringstream>();
        ON_CALL(*mockStream, stream()).WillByDefault(::testing::ReturnRef(*oss));
    }
    
    std::unique_ptr<MockIStream> mockStream;
    std::unique_ptr<std::ostringstream> oss;
};

// Test that ColourGuard can be constructed with a colour code
TEST_F(ColourGuardTest_631, ConstructWithColourCode_631) {
    MockColourImpl colourImpl(mockStream.get());
    // Construction should not call use
    EXPECT_CALL(colourImpl, use(::testing::_)).Times(0);
    
    ColourImpl::ColourGuard guard(Colour::Red, &colourImpl);
    // Guard not engaged, destructor should not call use(None)
}

// Test that destructor calls use(None) when guard is engaged
TEST_F(ColourGuardTest_631, DestructorCallsUseNoneWhenEngaged_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    // Expect use to be called with the colour code during engage, and None during destruction
    EXPECT_CALL(colourImpl, use(Colour::Red)).Times(1);
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    {
        ColourImpl::ColourGuard guard(Colour::Red, &colourImpl);
        guard.engage(*oss);
    }
    // Guard goes out of scope, destructor should call use(None)
}

// Test that destructor does NOT call use(None) when guard is not engaged
TEST_F(ColourGuardTest_631, DestructorDoesNotCallUseWhenNotEngaged_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(::testing::_)).Times(0);
    
    {
        ColourImpl::ColourGuard guard(Colour::Green, &colourImpl);
        // Not calling engage
    }
}

// Test move constructor transfers engagement
TEST_F(ColourGuardTest_631, MoveConstructorTransfersEngagement_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(Colour::Blue)).Times(1);
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    {
        ColourImpl::ColourGuard guard(Colour::Blue, &colourImpl);
        guard.engage(*oss);
        
        ColourImpl::ColourGuard movedGuard(std::move(guard));
        // Original guard should be disengaged after move
        // movedGuard destructor should call use(None)
    }
}

// Test move assignment operator
TEST_F(ColourGuardTest_631, MoveAssignmentTransfersEngagement_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(Colour::Yellow)).Times(1);
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    {
        ColourImpl::ColourGuard guard1(Colour::Yellow, &colourImpl);
        guard1.engage(*oss);
        
        ColourImpl::ColourGuard guard2(Colour::Red, &colourImpl);
        guard2 = std::move(guard1);
        // guard2 should now be engaged, guard1 should be disengaged
    }
}

// Test engage returns reference to self
TEST_F(ColourGuardTest_631, EngageReturnsSelf_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(Colour::Cyan)).Times(1);
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    ColourImpl::ColourGuard guard(Colour::Cyan, &colourImpl);
    ColourImpl::ColourGuard& ref = guard.engage(*oss);
    
    EXPECT_EQ(&ref, &guard);
}

// Test guardColour creates a properly configured guard
TEST_F(ColourGuardTest_631, GuardColourCreatesGuard_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    // guardColour should not immediately call use
    auto guard = colourImpl.guardColour(Colour::BrightRed);
    
    // When we engage and then destroy, it should use the colour and then None
    EXPECT_CALL(colourImpl, use(Colour::BrightRed)).Times(1);
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    guard.engage(*oss);
}

// Test with Colour::None
TEST_F(ColourGuardTest_631, EngageWithNoneColour_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(::testing::AtLeast(1));
    
    {
        ColourImpl::ColourGuard guard(Colour::None, &colourImpl);
        guard.engage(*oss);
    }
}

// Test various colour codes
TEST_F(ColourGuardTest_631, DifferentColourCodes_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    std::vector<Colour::Code> codes = {
        Colour::White, Colour::Red, Colour::Green, Colour::Blue,
        Colour::Cyan, Colour::Yellow, Colour::Grey,
        Colour::BrightRed, Colour::BrightGreen, Colour::BrightWhite,
        Colour::BrightYellow, Colour::LightGrey
    };
    
    for (auto code : codes) {
        EXPECT_CALL(colourImpl, use(code)).Times(1);
        EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
        
        {
            ColourImpl::ColourGuard guard(code, &colourImpl);
            guard.engage(*oss);
        }
        
        ::testing::Mock::VerifyAndClearExpectations(&colourImpl);
    }
}

// Test that moved-from guard does not call use(None) on destruction
TEST_F(ColourGuardTest_631, MovedFromGuardDoesNotCallUse_631) {
    MockColourImpl colourImpl(mockStream.get());
    
    EXPECT_CALL(colourImpl, use(Colour::Red)).Times(1);
    // Only one call to use(None) - from the moved-to guard
    EXPECT_CALL(colourImpl, use(Colour::None)).Times(1);
    
    {
        ColourImpl::ColourGuard guard(Colour::Red, &colourImpl);
        guard.engage(*oss);
        
        ColourImpl::ColourGuard movedGuard(std::move(guard));
        // guard destructor should NOT call use(None)
        // movedGuard destructor should call use(None)
    }
}

// Test Colour::Code enum values
TEST(ColourCodeTest_631, EnumValues_631) {
    EXPECT_EQ(static_cast<int>(Colour::None), 0);
    EXPECT_EQ(static_cast<int>(Colour::White), 1);
    EXPECT_EQ(static_cast<int>(Colour::Red), 2);
    EXPECT_EQ(static_cast<int>(Colour::Green), 3);
    EXPECT_EQ(static_cast<int>(Colour::Blue), 4);
    EXPECT_EQ(static_cast<int>(Colour::Cyan), 5);
    EXPECT_EQ(static_cast<int>(Colour::Yellow), 6);
    EXPECT_EQ(static_cast<int>(Colour::Grey), 7);
    EXPECT_EQ(static_cast<int>(Colour::Bright), 16);
    EXPECT_EQ(static_cast<int>(Colour::BrightRed), 18);
    EXPECT_EQ(static_cast<int>(Colour::BrightGreen), 19);
    EXPECT_EQ(static_cast<int>(Colour::BrightWhite), 17);
    EXPECT_EQ(static_cast<int>(Colour::BrightYellow), 22);
    EXPECT_EQ(static_cast<int>(Colour::LightGrey), 23);
}

// Test semantic colour aliases match their expected values
TEST(ColourCodeAliasTest_631, SemanticAliases_631) {
    EXPECT_EQ(Colour::FileName, Colour::LightGrey);
    EXPECT_EQ(Colour::Warning, Colour::BrightYellow);
    EXPECT_EQ(Colour::ResultError, Colour::BrightRed);
    EXPECT_EQ(Colour::ResultSuccess, Colour::BrightGreen);
    EXPECT_EQ(Colour::ResultExpectedFailure, Colour::BrightYellow);
    EXPECT_EQ(Colour::Error, Colour::BrightRed);
    EXPECT_EQ(Colour::Success, Colour::Green);
    EXPECT_EQ(Colour::Skip, Colour::LightGrey);
    EXPECT_EQ(Colour::OriginalExpression, Colour::Cyan);
    EXPECT_EQ(Colour::ReconstructedExpression, Colour::BrightYellow);
    EXPECT_EQ(Colour::SecondaryText, Colour::LightGrey);
    EXPECT_EQ(Colour::Headers, Colour::White);
}
