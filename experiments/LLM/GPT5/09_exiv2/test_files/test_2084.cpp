// =================================================================================================
// TEST_ID: 2084
// Unit tests for UTF16Swp_to_UTF32Swp (static) in UnicodeConversions.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>
#include <limits>

// Include the implementation file to access the TU-local static function.
// (This is a common technique for unit-testing static functions.)
#include "TestProjects/exiv2/xmpsdk/src/UnicodeConversions.cpp"

namespace {

static inline UTF16Unit Swap16(UTF16Unit v) {
    const uint16_t x = static_cast<uint16_t>(v);
    const uint16_t y = static_cast<uint16_t>(((x & 0x00FFu) << 8) | ((x & 0xFF00u) >> 8));
    return static_cast<UTF16Unit>(y);
}

static inline UTF32Unit Swap32(UTF32Unit v) {
    const uint32_t x = static_cast<uint32_t>(v);
    const uint32_t y =
        ((x & 0x000000FFu) << 24) |
        ((x & 0x0000FF00u) << 8)  |
        ((x & 0x00FF0000u) >> 8)  |
        ((x & 0xFF000000u) >> 24);
    return static_cast<UTF32Unit>(y);
}

static inline void AppendUTF16NativeForCodePoint(uint32_t cp, std::vector<UTF16Unit>& out) {
    if (cp <= 0xFFFFu) {
        out.push_back(static_cast<UTF16Unit>(cp));
        return;
    }
    // Surrogate pair.
    const uint32_t v = cp - 0x10000u;
    const uint16_t hi = static_cast<uint16_t>(0xD800u + ((v >> 10) & 0x3FFu));
    const uint16_t lo = static_cast<uint16_t>(0xDC00u + (v & 0x3FFu));
    out.push_back(static_cast<UTF16Unit>(hi));
    out.push_back(static_cast<UTF16Unit>(lo));
}

static inline std::vector<UTF16Unit> MakeUTF16SwpFromCodePoints(const std::vector<uint32_t>& cps) {
    std::vector<UTF16Unit> native;
    for (uint32_t cp : cps) AppendUTF16NativeForCodePoint(cp, native);

    std::vector<UTF16Unit> swp;
    swp.reserve(native.size());
    for (UTF16Unit u : native) swp.push_back(Swap16(u));
    return swp;
}

static inline std::vector<uint32_t> ReadUTF32SwpAsCodePoints(const UTF32Unit* buf, size_t len) {
    std::vector<uint32_t> cps;
    cps.reserve(len);
    for (size_t i = 0; i < len; ++i) {
        cps.push_back(static_cast<uint32_t>(Swap32(buf[i])));
    }
    return cps;
}

class UTF16Swp_to_UTF32SwpTest_2084 : public ::testing::Test {};

}  // namespace

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, ConvertsOnlyBMPNonSurrogates_2084) {
    const std::vector<uint32_t> expectedCps = { 0x0041u, 0x03A9u, 0xAC00u };  // 'A', 'Ω', '가'
    const std::vector<UTF16Unit> utf16Swp = MakeUTF16SwpFromCodePoints(expectedCps);

    std::vector<UTF32Unit> utf32SwpOut(expectedCps.size(), static_cast<UTF32Unit>(0));
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), utf32SwpOut.size(),
        &utf16Read, &utf32Written);

    EXPECT_EQ(utf16Read, utf16Swp.size());
    EXPECT_EQ(utf32Written, expectedCps.size());

    const std::vector<uint32_t> got = ReadUTF32SwpAsCodePoints(utf32SwpOut.data(), utf32Written);
    EXPECT_EQ(got, expectedCps);
}

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, ConvertsIncludingSurrogatePair_2084) {
    // U+1F600 GRINNING FACE 😀, surrounded by BMP.
    const std::vector<uint32_t> expectedCps = { 0x0041u, 0x1F600u, 0x0062u };  // 'A', 😀, 'b'
    const std::vector<UTF16Unit> utf16Swp = MakeUTF16SwpFromCodePoints(expectedCps);

    std::vector<UTF32Unit> utf32SwpOut(expectedCps.size(), static_cast<UTF32Unit>(0));
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), utf32SwpOut.size(),
        &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, expectedCps.size());
    EXPECT_EQ(utf16Read, utf16Swp.size());

    const std::vector<uint32_t> got = ReadUTF32SwpAsCodePoints(utf32SwpOut.data(), utf32Written);
    EXPECT_EQ(got, expectedCps);
}

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, OutputBufferLimitsProcessing_2084) {
    const std::vector<uint32_t> inputCps = { 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u };
    const std::vector<UTF16Unit> utf16Swp = MakeUTF16SwpFromCodePoints(inputCps);

    // Only room for 2 UTF-32 code points.
    std::vector<UTF32Unit> utf32SwpOut(2, static_cast<UTF32Unit>(0));
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), utf32SwpOut.size(),
        &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 2u);
    // With only BMP input here, each code point is one UTF-16 unit.
    EXPECT_EQ(utf16Read, 2u);

    const std::vector<uint32_t> got = ReadUTF32SwpAsCodePoints(utf32SwpOut.data(), utf32Written);
    EXPECT_EQ(got, (std::vector<uint32_t>{ 0x0041u, 0x0042u }));
}

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, StopsWhenInputEndsMidSurrogatePair_2084) {
    // Provide only a high surrogate (swapped).
    const UTF16Unit hiNative = static_cast<UTF16Unit>(0xD83Du); // high surrogate used by many emoji
    const UTF16Unit hiSwp = Swap16(hiNative);
    const std::vector<UTF16Unit> utf16Swp = { hiSwp };

    std::vector<UTF32Unit> utf32SwpOut(4, static_cast<UTF32Unit>(0));
    size_t utf16Read = 999, utf32Written = 999;

    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), utf32SwpOut.size(),
        &utf16Read, &utf32Written);

    // Observable behavior: no complete code point can be produced.
    EXPECT_EQ(utf32Written, 0u);

    // It should not claim to have consumed beyond the available (incomplete) surrogate.
    EXPECT_LE(utf16Read, utf16Swp.size());
}

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, ConvertsPrefixThenStopsOnDanglingHighSurrogate_2084) {
    // 'A' then a dangling high surrogate.
    std::vector<UTF16Unit> utf16Swp;
    utf16Swp.push_back(Swap16(static_cast<UTF16Unit>(0x0041u)));
    utf16Swp.push_back(Swap16(static_cast<UTF16Unit>(0xD83Du))); // dangling high surrogate

    std::vector<UTF32Unit> utf32SwpOut(4, static_cast<UTF32Unit>(0));
    size_t utf16Read = 0, utf32Written = 0;

    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), utf32SwpOut.size(),
        &utf16Read, &utf32Written);

    // Should at least produce the 'A' before encountering the incomplete surrogate.
    ASSERT_GE(utf32Written, 1u);
    const std::vector<uint32_t> got = ReadUTF32SwpAsCodePoints(utf32SwpOut.data(), utf32Written);
    EXPECT_EQ(got.front(), 0x0041u);

    // Should not report consuming more UTF-16 units than provided.
    EXPECT_LE(utf16Read, utf16Swp.size());
    // Usually it consumes exactly 1 unit ('A'), then stops; we assert the safe minimum.
    EXPECT_GE(utf16Read, 1u);
}

TEST_F(UTF16Swp_to_UTF32SwpTest_2084, ZeroOutputCapacityWritesNothing_2084) {
    const std::vector<uint32_t> inputCps = { 0x0041u, 0x1F600u, 0x0062u };
    const std::vector<UTF16Unit> utf16Swp = MakeUTF16SwpFromCodePoints(inputCps);

    size_t utf16Read = 123, utf32Written = 456;

    // Valid pointers, but zero output length.
    std::vector<UTF32Unit> utf32SwpOut(1, static_cast<UTF32Unit>(0));
    UTF16Swp_to_UTF32Swp(
        utf16Swp.data(), utf16Swp.size(),
        utf32SwpOut.data(), 0,
        &utf16Read, &utf32Written);

    EXPECT_EQ(utf32Written, 0u);
    EXPECT_EQ(utf16Read, 0u);
}