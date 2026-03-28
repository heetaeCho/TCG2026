// File: test_stringmaker_const_charptr_262.cpp
#include <gtest/gtest.h>

// Include the interface under test
#include "catch2/catch_tostring.hpp"

namespace {

using Catch::StringMaker;

constexpr const char* kNullMarker = "{null string}";

// --- Normal / Error cases ---

// Verifies that a null C-string pointer is rendered as the exact "{null string}" marker.
TEST(StringMakerConstCharPtr_262, NullPointerYieldsNullString_262) {
    const char* ptr = nullptr;
    const std::string out = StringMaker<const char*>::convert(ptr);
    EXPECT_EQ(out, kNullMarker);
}

// Verifies that a non-null C-string does NOT produce the null marker.
// We do not assume or inspect any particular formatting of non-null strings.
TEST(StringMakerConstCharPtr_262, NonNullDoesNotYieldNullMarker_262) {
    const char* ptr = "hello";
    const std::string out = StringMaker<const char*>::convert(ptr);
    EXPECT_NE(out, kNullMarker);
}

// --- Boundary conditions ---

// Verifies that an empty but non-null C-string is treated as non-null (i.e., not the null marker).
TEST(StringMakerConstCharPtr_262, EmptyCStringIsNotNull_262) {
    const char* ptr = "";
    const std::string out = StringMaker<const char*>::convert(ptr);
    EXPECT_NE(out, kNullMarker);
}

// A longer string should still be handled as non-null without returning the null marker.
TEST(StringMakerConstCharPtr_262, LongCStringIsNotNull_262) {
    static const char kLong[] =
        "This is a reasonably long C-string used to ensure handling "
        "does not degrade for longer inputs in observable behavior tests.";
    const std::string out = StringMaker<const char*>::convert(kLong);
    EXPECT_NE(out, kNullMarker);
}

} // namespace
