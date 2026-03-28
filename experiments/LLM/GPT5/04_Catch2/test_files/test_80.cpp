// File: convert_unknown_enum_to_string_tests_80.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include <cstdint>
#include <ostream>

// Adjust include as needed for your project include paths:
#include <catch2/catch_tostring.hpp>

using Catch::Detail::convertUnknownEnumToString;

namespace {

// Helper that compares the function's output to stringify of the enum's underlying value.
template <typename E>
void ExpectMatchesUnderlyingStringify(E e) {
    using U = std::underlying_type_t<E>;
    const std::string expected = Catch::Detail::stringify(static_cast<U>(e));
    const std::string actual   = convertUnknownEnumToString(e);
    EXPECT_EQ(actual, expected);
}

// Enums for testing

// 1) Scoped enum with signed underlying (default: int)
enum class Color : int {
    Red   = 1,
    Green = 42,
    Minus = -7
};

// 2) Scoped enum with explicit unsigned long long underlying (exercise large values)
enum class Big : unsigned long long {
    Zero = 0ull,
    Half = (1ull << 63) // 2^63
};

// 3) Unscoped enum with explicit unsigned underlying (exercise high bit)
enum Flags : unsigned {
    FlagNone = 0u,
    FlagHigh = (1u << 31)
};

// 4) Enum with an overloaded operator<<; the function under test should still return numeric string
enum class Fancy : int {
    Value = 5
};

std::ostream& operator<<(std::ostream& os, Fancy) {
    // If anyone tries to stream this enum, they'll get this text,
    // but convertUnknownEnumToString should *not* use this.
    return os << "FANCY!";
}

// 5) Zero value on small unsigned underlying
enum class SmallZero : unsigned short {
    Z = 0
};

} // namespace

// ---------- Tests ----------

// Normal operation: simple positive value for scoped enum (default int)
TEST(ConvertUnknownEnumToStringTest_80, ScopedEnum_PositiveValue_80) {
    ExpectMatchesUnderlyingStringify(Color::Green);
}

// Boundary-ish (signed): negative enumerator value
TEST(ConvertUnknownEnumToStringTest_80, ScopedEnum_NegativeValue_80) {
    ExpectMatchesUnderlyingStringify(Color::Minus);
}

// Large unsigned value (64-bit): ensure big numbers round-trip via stringify
TEST(ConvertUnknownEnumToStringTest_80, UnsignedLargeUnderlying_BigValue_80) {
    ExpectMatchesUnderlyingStringify(Big::Half);
}

// Zero value for large unsigned underlying type
TEST(ConvertUnknownEnumToStringTest_80, UnsignedLargeUnderlying_Zero_80) {
    ExpectMatchesUnderlyingStringify(Big::Zero);
}

// Unscoped enum with high bit set in unsigned underlying
TEST(ConvertUnknownEnumToStringTest_80, UnscopedEnum_UnsignedHighBit_80) {
    ExpectMatchesUnderlyingStringify(Flags::FlagHigh);
}

// Interaction check: operator<< exists but function should still produce numeric string
TEST(ConvertUnknownEnumToStringTest_80, IgnoresStreamingOperator_ReturnsUnderlyingString_80) {
    ExpectMatchesUnderlyingStringify(Fancy::Value);
}

// Zero value on small unsigned underlying type
TEST(ConvertUnknownEnumToStringTest_80, SmallUnsignedUnderlying_Zero_80) {
    ExpectMatchesUnderlyingStringify(SmallZero::Z);
}
