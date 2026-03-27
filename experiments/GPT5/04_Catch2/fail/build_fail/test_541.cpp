// File: tests/is_redirect_available_test_541.cpp

#include <gtest/gtest.h>

// Use the provided interface. We include the enum header,
// and forward-declare the function symbol we are testing.
#include "catch2/internal/catch_output_redirect.hpp"

namespace Catch {
// Forward declaration only; implementation is linked from the library/object files.
bool isRedirectAvailable(Catch::OutputRedirect::Kind kind);
}

using Catch::OutputRedirect::Kind;

class OutputRedirectTest_541 : public ::testing::Test {};

// Normal operation: None -> true
TEST_F(OutputRedirectTest_541, None_ReturnsTrue_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(Kind::None));
}

// Normal operation: Streams -> true
TEST_F(OutputRedirectTest_541, Streams_ReturnsTrue_541) {
    EXPECT_TRUE(Catch::isRedirectAvailable(Kind::Streams));
}

// Boundary/compile-time dependent behavior: FileDescriptors
TEST_F(OutputRedirectTest_541, FileDescriptors_DependsOnConfig_541) {
#if defined(CATCH_CONFIG_NEW_CAPTURE)
    EXPECT_TRUE(Catch::isRedirectAvailable(Kind::FileDescriptors));
#else
    EXPECT_FALSE(Catch::isRedirectAvailable(Kind::FileDescriptors));
#endif
}

// Exceptional/edge case via interface: invalid enum value hits default -> false
TEST_F(OutputRedirectTest_541, InvalidEnumValue_ReturnsFalse_541) {
    auto invalid = static_cast<Kind>(42); // value not defined in the enum
    EXPECT_FALSE(Catch::isRedirectAvailable(invalid));
}
