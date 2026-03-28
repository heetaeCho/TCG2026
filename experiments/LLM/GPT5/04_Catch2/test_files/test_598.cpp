// File: enuminfo_lookup_tests_598.cpp
#include <gtest/gtest.h>

#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"
// If your project exposes StringRef/literals via another header, include that instead.
#include "catch2/internal/catch_stringref.hpp"

using Catch::StringRef;
using namespace Catch::literals;   // for the "_sr" StringRef literal
using Catch::Detail::EnumInfo;

// -----------------------------
// Tests
// -----------------------------

// Normal operation: when the value exists, the mapped name is returned.
TEST(EnumInfoLookupTest_598, ReturnsMappedName_598) {
    EnumInfo ei;
    ei.m_values.push_back({1, "One"_sr});
    ei.m_values.push_back({2, "Two"_sr});

    StringRef out = ei.lookup(2);
    EXPECT_EQ(out, "Two"_sr);
}

// Boundary: empty registry should yield the documented fallback.
TEST(EnumInfoLookupTest_598, EmptyRegistryReturnsFallback_598) {
    EnumInfo ei; // no values
    StringRef out = ei.lookup(42);
    EXPECT_EQ(out, "{** unexpected enum value **}"_sr);
}

// Error/absent value case: unknown value returns the fallback.
TEST(EnumInfoLookupTest_598, UnknownValueReturnsFallback_598) {
    EnumInfo ei;
    ei.m_values.push_back({10, "Ten"_sr});

    StringRef out = ei.lookup(11);
    EXPECT_EQ(out, "{** unexpected enum value **}"_sr);
}

// Boundary: supports negative enum-like values if present.
TEST(EnumInfoLookupTest_598, NegativeValueMappedIfPresent_598) {
    EnumInfo ei;
    ei.m_values.push_back({-1, "MinusOne"_sr});
    ei.m_values.push_back({0, "Zero"_sr});

    EXPECT_EQ(ei.lookup(-1), "MinusOne"_sr);
    EXPECT_EQ(ei.lookup(0), "Zero"_sr);
}

// API contract: lookup callable on const instances (no state mutation).
TEST(EnumInfoLookupTest_598, LookupOnConstInstance_598) {
    EnumInfo ei;
    ei.m_values.push_back({7, "Seven"_sr});

    const EnumInfo& cei = ei;
    StringRef out = cei.lookup(7);
    EXPECT_EQ(out, "Seven"_sr);
}
