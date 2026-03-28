#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <sstream>

// Include necessary Catch2 headers
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/internal/catch_istream.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// Mock IStream for testing
class MockIStream : public Catch::IStream {
public:
    MockIStream() : m_sstream() {}
    ~MockIStream() override = default;

    std::ostream& stream() override {
        return m_sstream;
    }

    MOCK_METHOD(bool, isConsole, (), (const, override));

private:
    std::stringstream m_sstream;
};

class MakeColourImplTest_633 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = std::make_unique<MockIStream>();
    }

    void TearDown() override {
        mockStream.reset();
    }

    std::unique_ptr<MockIStream> mockStream;
};

// Test that ColourMode::None returns a non-null implementation
TEST_F(MakeColourImplTest_633, NoneMode_ReturnsNonNull_633) {
    auto impl = Catch::makeColourImpl(Catch::ColourMode::None, mockStream.get());
    ASSERT_NE(impl, nullptr);
}

// Test that ColourMode::ANSI returns a non-null implementation
TEST_F(MakeColourImplTest_633, ANSIMode_ReturnsNonNull_633) {
    auto impl = Catch::makeColourImpl(Catch::ColourMode::ANSI, mockStream.get());
    ASSERT_NE(impl, nullptr);
}

// Test that ColourMode::PlatformDefault returns a non-null implementation
TEST_F(MakeColourImplTest_633, PlatformDefaultMode_ReturnsNonNull_633) {
    // For PlatformDefault, the implementation checks stream properties
    // It should always return some implementation (ANSI or NoColour at minimum)
    EXPECT_CALL(*mockStream, isConsole()).WillRepeatedly(::testing::Return(false));
    auto impl = Catch::makeColourImpl(Catch::ColourMode::PlatformDefault, mockStream.get());
    ASSERT_NE(impl, nullptr);
}

// Test that ColourMode::PlatformDefault with console stream returns non-null
TEST_F(MakeColourImplTest_633, PlatformDefaultMode_ConsoleStream_ReturnsNonNull_633) {
    EXPECT_CALL(*mockStream, isConsole()).WillRepeatedly(::testing::Return(true));
    auto impl = Catch::makeColourImpl(Catch::ColourMode::PlatformDefault, mockStream.get());
    ASSERT_NE(impl, nullptr);
}

// Test that ColourMode::None creates consistently (multiple calls)
TEST_F(MakeColourImplTest_633, NoneMode_MultipleCallsReturnNonNull_633) {
    auto impl1 = Catch::makeColourImpl(Catch::ColourMode::None, mockStream.get());
    auto impl2 = Catch::makeColourImpl(Catch::ColourMode::None, mockStream.get());
    ASSERT_NE(impl1, nullptr);
    ASSERT_NE(impl2, nullptr);
}

// Test that ColourMode::ANSI creates consistently (multiple calls)
TEST_F(MakeColourImplTest_633, ANSIMode_MultipleCallsReturnNonNull_633) {
    auto impl1 = Catch::makeColourImpl(Catch::ColourMode::ANSI, mockStream.get());
    auto impl2 = Catch::makeColourImpl(Catch::ColourMode::ANSI, mockStream.get());
    ASSERT_NE(impl1, nullptr);
    ASSERT_NE(impl2, nullptr);
}

// Test invalid ColourMode value throws/errors
TEST_F(MakeColourImplTest_633, InvalidColourMode_ThrowsError_633) {
    // Cast an invalid integer to ColourMode to trigger the CATCH_ERROR path
    auto invalidMode = static_cast<Catch::ColourMode>(99);
    EXPECT_THROW(
        Catch::makeColourImpl(invalidMode, mockStream.get()),
        std::exception
    );
}

// Test that different modes can be created with the same stream
TEST_F(MakeColourImplTest_633, DifferentModes_SameStream_633) {
    EXPECT_CALL(*mockStream, isConsole()).WillRepeatedly(::testing::Return(false));

    auto implNone = Catch::makeColourImpl(Catch::ColourMode::None, mockStream.get());
    auto implANSI = Catch::makeColourImpl(Catch::ColourMode::ANSI, mockStream.get());
    auto implDefault = Catch::makeColourImpl(Catch::ColourMode::PlatformDefault, mockStream.get());

    ASSERT_NE(implNone, nullptr);
    ASSERT_NE(implANSI, nullptr);
    ASSERT_NE(implDefault, nullptr);
}

#if defined(CATCH_CONFIG_COLOUR_WIN32)
// Test that ColourMode::Win32 returns a non-null implementation on Windows
TEST_F(MakeColourImplTest_633, Win32Mode_ReturnsNonNull_633) {
    auto impl = Catch::makeColourImpl(Catch::ColourMode::Win32, mockStream.get());
    ASSERT_NE(impl, nullptr);
}
#endif

// Test PlatformDefault with non-console stream falls back appropriately
TEST_F(MakeColourImplTest_633, PlatformDefaultMode_NonConsoleStream_ReturnsImpl_633) {
    EXPECT_CALL(*mockStream, isConsole()).WillRepeatedly(::testing::Return(false));
    auto impl = Catch::makeColourImpl(Catch::ColourMode::PlatformDefault, mockStream.get());
    ASSERT_NE(impl, nullptr);
}

// Test boundary: ColourMode enum value just above valid range
TEST_F(MakeColourImplTest_633, BoundaryInvalidColourMode_4_ThrowsError_633) {
    auto invalidMode = static_cast<Catch::ColourMode>(4);
    EXPECT_THROW(
        Catch::makeColourImpl(invalidMode, mockStream.get()),
        std::exception
    );
}

// Test boundary: negative ColourMode enum value
TEST_F(MakeColourImplTest_633, BoundaryInvalidColourMode_Negative_ThrowsError_633) {
    auto invalidMode = static_cast<Catch::ColourMode>(-1);
    EXPECT_THROW(
        Catch::makeColourImpl(invalidMode, mockStream.get()),
        std::exception
    );
}
