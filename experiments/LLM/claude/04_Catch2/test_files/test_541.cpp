#include "gtest/gtest.h"
#include "catch2/internal/catch_output_redirect.hpp"

// We need to declare the function since it's defined in the .cpp file
namespace Catch {
    bool isRedirectAvailable(OutputRedirect::Kind kind);
}

class IsRedirectAvailableTest_541 : public ::testing::Test {
protected:
};

// Test that None kind is always available
TEST_F(IsRedirectAvailableTest_541, NoneIsAlwaysAvailable_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(Catch::OutputRedirect::None));
}

// Test that Streams kind is always available
TEST_F(IsRedirectAvailableTest_541, StreamsIsAlwaysAvailable_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(Catch::OutputRedirect::Streams));
}

// Test FileDescriptors kind - availability depends on CATCH_CONFIG_NEW_CAPTURE
TEST_F(IsRedirectAvailableTest_541, FileDescriptorsAvailabilityDependsOnConfig_541) {
    bool result = Catch::isRedirectAvailable(Catch::OutputRedirect::FileDescriptors);
#if defined(CATCH_CONFIG_NEW_CAPTURE)
    EXPECT_TRUE(result);
#else
    EXPECT_FALSE(result);
#endif
}

// Test that an invalid/unknown kind returns false
TEST_F(IsRedirectAvailableTest_541, UnknownKindReturnsFalse_541) {
    // Use a value that doesn't correspond to any known enum value
    Catch::OutputRedirect::Kind unknownKind = static_cast<Catch::OutputRedirect::Kind>(99);
    EXPECT_FALSE(Catch::isRedirectAvailable(unknownKind));
}

// Test another invalid kind value
TEST_F(IsRedirectAvailableTest_541, AnotherUnknownKindReturnsFalse_541) {
    Catch::OutputRedirect::Kind unknownKind = static_cast<Catch::OutputRedirect::Kind>(3);
    EXPECT_FALSE(Catch::isRedirectAvailable(unknownKind));
}

// Test with negative cast value (boundary)
TEST_F(IsRedirectAvailableTest_541, NegativeKindReturnsFalse_541) {
    Catch::OutputRedirect::Kind negativeKind = static_cast<Catch::OutputRedirect::Kind>(-1);
    EXPECT_FALSE(Catch::isRedirectAvailable(negativeKind));
}

// Test with large enum value (boundary)
TEST_F(IsRedirectAvailableTest_541, LargeKindValueReturnsFalse_541) {
    Catch::OutputRedirect::Kind largeKind = static_cast<Catch::OutputRedirect::Kind>(1000);
    EXPECT_FALSE(Catch::isRedirectAvailable(largeKind));
}

// Test enum value 0 explicitly (same as None)
TEST_F(IsRedirectAvailableTest_541, ZeroValueIsAvailable_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(static_cast<Catch::OutputRedirect::Kind>(0)));
}

// Test enum value 1 explicitly (same as Streams)
TEST_F(IsRedirectAvailableTest_541, OneValueIsAvailable_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(static_cast<Catch::OutputRedirect::Kind>(1)));
}
