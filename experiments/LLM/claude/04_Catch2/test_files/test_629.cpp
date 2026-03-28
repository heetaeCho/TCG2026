#include <catch2/internal/catch_console_colour.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <sstream>

namespace {

// Mock IStream for dependency injection
class MockIStream : public Catch::IStream {
public:
    MOCK_METHOD(std::ostream&, stream, (), (override));
    
    MockIStream() {
        ON_CALL(*this, stream()).WillByDefault(::testing::ReturnRef(m_oss));
    }
    
    std::ostringstream m_oss;
};

// A testable subclass of ColourImpl to test the interface
// Since ColourImpl has a private virtual `use`, we create a derived class for testing
class TestableColourImpl : public Catch::ColourImpl {
public:
    TestableColourImpl(Catch::IStream* stream)
        : ColourImpl(stream) {}
    
    // Track calls to use()
    mutable std::vector<Catch::Colour::Code> useCalls;
    
private:
    void use(Catch::Colour::Code colourCode) const override {
        useCalls.push_back(colourCode);
    }
};

class ColourImplTest_629 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = std::make_unique<MockIStream>();
    }
    
    std::unique_ptr<MockIStream> mockStream;
};

// Test that ColourImpl can be constructed with a stream
TEST_F(ColourImplTest_629, ConstructWithStream_629) {
    EXPECT_NO_THROW({
        TestableColourImpl impl(mockStream.get());
    });
}

// Test that guardColour returns a ColourGuard object without throwing
TEST_F(ColourImplTest_629, GuardColourReturnsColourGuard_629) {
    TestableColourImpl impl(mockStream.get());
    EXPECT_NO_THROW({
        auto guard = impl.guardColour(Catch::Colour::Red);
    });
}

// Test that guardColour triggers the use method with the given colour code
TEST_F(ColourImplTest_629, GuardColourCallsUseWithColourCode_629) {
    TestableColourImpl impl(mockStream.get());
    {
        auto guard = impl.guardColour(Catch::Colour::Green);
    }
    // After guard is created and destroyed, use should have been called
    EXPECT_FALSE(impl.useCalls.empty());
}

// Test that guardColour with None colour code works
TEST_F(ColourImplTest_629, GuardColourWithNoneColour_629) {
    TestableColourImpl impl(mockStream.get());
    EXPECT_NO_THROW({
        auto guard = impl.guardColour(Catch::Colour::None);
    });
}

// Test multiple sequential guards
TEST_F(ColourImplTest_629, MultipleSequentialGuards_629) {
    TestableColourImpl impl(mockStream.get());
    {
        auto guard1 = impl.guardColour(Catch::Colour::Red);
    }
    {
        auto guard2 = impl.guardColour(Catch::Colour::Blue);
    }
    // Both should have triggered use calls
    EXPECT_GE(impl.useCalls.size(), 2u);
}

// Test that ColourImpl destructor works properly
TEST_F(ColourImplTest_629, DestructorDoesNotThrow_629) {
    EXPECT_NO_THROW({
        auto impl = std::make_unique<TestableColourImpl>(mockStream.get());
        impl.reset();
    });
}

// Test guardColour with various colour codes
TEST_F(ColourImplTest_629, GuardColourWithDifferentCodes_629) {
    TestableColourImpl impl(mockStream.get());
    
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::White); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Red); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Green); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Blue); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Cyan); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Yellow); });
    EXPECT_NO_THROW({ auto g = impl.guardColour(Catch::Colour::Grey); });
}

// Test that guard resets colour on destruction
TEST_F(ColourImplTest_629, GuardResetsColourOnDestruction_629) {
    TestableColourImpl impl(mockStream.get());
    impl.useCalls.clear();
    {
        auto guard = impl.guardColour(Catch::Colour::Red);
        // At this point, Red should have been applied
    }
    // After guard destruction, colour should be reset (None called)
    // Check that the last call was None
    if (!impl.useCalls.empty()) {
        EXPECT_EQ(impl.useCalls.back(), Catch::Colour::None);
    }
}

// Test constructing with nullptr stream
TEST_F(ColourImplTest_629, ConstructWithNullStream_629) {
    // This tests boundary: what happens with null stream
    EXPECT_NO_THROW({
        TestableColourImpl impl(nullptr);
    });
}

} // anonymous namespace
