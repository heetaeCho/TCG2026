// File: test_convert_into_653.cpp

#include <gtest/gtest.h>
#include <string>

// Prefer including the public header that declares the involved types.
// In typical Catch2 layouts, ParserResult + ParseResultType live here.
#include "catch2/internal/catch_clara.hpp"

// Forward declare the function under test in its proper namespace.
// (Declaration only; no reimplementation.)
namespace Catch { namespace Clara { namespace Detail {
    // Signature from the provided partial code.
    auto convertInto(std::string const& source, std::string& target) -> ParserResult;
}}}

using Catch::Clara::Detail::convertInto;

//
// Tests
//

// Normal operation: ensures target receives source content and the result is truthy.
TEST(ConvertIntoTest_653, CopiesValueAndReturnsOk_653) {
    std::string source = "hello world";
    std::string target = "initial value";

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result)) << "Expected successful (truthy) ParserResult";
    EXPECT_EQ(target, source) << "Target should match source after conversion";
}

// Boundary: empty source should leave target as empty and still be a successful result.
TEST(ConvertIntoTest_653, HandlesEmptySource_653) {
    std::string source = "";
    std::string target = "non-empty-before";

    auto result = convertInto(source, target);

    EXPECT_TRUE(static_cast<bool>(result)) << "Expected success when converting empty string";
    EXPECT_EQ(target, source) << "Target should be empty after conversion from empty source";
}

// Edge case: passing the same string object as both source and target should be safe.
// (Observable behavior: content remains unchanged and result is success.)
TEST(ConvertIntoTest_653, SupportsSelfAssignment_653) {
    std::string s = "self";
    // Using the same object for both parameters is legal:
    // source binds to const&, target binds to non-const&.
    auto result = convertInto(s, s);

    EXPECT_TRUE(static_cast<bool>(result)) << "Expected success on self-assignment";
    EXPECT_EQ(s, "self") << "Content should remain unchanged on self-assignment";
}
