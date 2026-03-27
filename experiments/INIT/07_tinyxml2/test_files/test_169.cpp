// File: test_xmlutil_tostr_double_169.cpp

#include <gtest/gtest.h>

#include <bit>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <limits>
#include <string>
#include <vector>

#include "tinyxml2.h"

namespace {

class XMLUtilToStrDoubleTest_169 : public ::testing::Test {
protected:
    static std::string ToStrWithBufferSize(double v, int bufferSize) {
        EXPECT_GT(bufferSize, 0);

        std::vector<char> buf(static_cast<size_t>(bufferSize), '\x7F'); // sentinel
        tinyxml2::XMLUtil::ToStr(v, buf.data(), bufferSize);

        // For snprintf-like APIs: should always be NUL-terminated when bufferSize > 0.
        EXPECT_EQ(buf[static_cast<size_t>(bufferSize - 1)], '\0');

        // Construct as C-string (stops at first NUL).
        return std::string(buf.data());
    }

    static std::string ToLowerAscii(std::string s) {
        for (char& ch : s) {
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
        return s;
    }

    static uint64_t Bits(double v) {
        return std::bit_cast<uint64_t>(v);
    }
};

TEST_F(XMLUtilToStrDoubleTest_169, FormatsCommonFiniteValuesAndRoundTrips_169) {
    const double values[] = {
        0.0,
        -1.0,
        1.0,
        0.1,
        1.234567890123456,     // many significant digits
        1e-300,
        -1e-300,
        1e300,
        -1e300
    };

    for (double v : values) {
        const std::string s = ToStrWithBufferSize(v, 128);

        // Must produce some text (except extremely small buffer cases; here buffer is large).
        ASSERT_FALSE(s.empty()) << "Unexpected empty output for v=" << v;

        // Round-trip back to double should reproduce the original double for finite values.
        // (Using bitwise equality to avoid tolerance hiding formatting issues.)
        char* end = nullptr;
        const double parsed = std::strtod(s.c_str(), &end);
        ASSERT_NE(end, s.c_str()) << "strtod failed to parse output: '" << s << "'";
        ASSERT_TRUE(end && *end == '\0') << "Output not fully parseable as a double: '" << s << "'";

        // Finite -> finite check, then exact bit match.
        ASSERT_TRUE(std::isfinite(parsed)) << "Parsed value not finite from '" << s << "'";
        EXPECT_EQ(Bits(parsed), Bits(v)) << "Round-trip mismatch. v=" << v << " str='" << s << "'";
    }
}

TEST_F(XMLUtilToStrDoubleTest_169, HandlesNegativeZero_169) {
    const double negZero = -0.0;
    const std::string s = ToStrWithBufferSize(negZero, 32);

    // Accept common library outputs for "%.17g" with -0.0: "-0" or "0"
    EXPECT_TRUE(s == "0" || s == "-0") << "Unexpected -0 output: '" << s << "'";

    char* end = nullptr;
    const double parsed = std::strtod(s.c_str(), &end);
    ASSERT_NE(end, s.c_str());
    ASSERT_TRUE(end && *end == '\0');

    // Parsed value should be zero; sign may or may not survive parsing depending on platform.
    EXPECT_EQ(parsed, 0.0);
}

TEST_F(XMLUtilToStrDoubleTest_169, HandlesInfinityAndNaN_169) {
    {
        const double pinf = std::numeric_limits<double>::infinity();
        const std::string s = ToStrWithBufferSize(pinf, 64);
        const std::string lower = ToLowerAscii(s);

        // Different CRTs may print "inf", "infinity", "1.#inf", etc.
        EXPECT_TRUE(lower.find("inf") != std::string::npos)
            << "Expected infinity-like output, got: '" << s << "'";

        char* end = nullptr;
        const double parsed = std::strtod(s.c_str(), &end);
        // Some platforms parse "1.#INF" etc.; if parsing fails, at least the formatting check above holds.
        if (end != s.c_str()) {
            EXPECT_TRUE(std::isinf(parsed));
            EXPECT_GT(parsed, 0.0);
        }
    }
    {
        const double ninf = -std::numeric_limits<double>::infinity();
        const std::string s = ToStrWithBufferSize(ninf, 64);
        const std::string lower = ToLowerAscii(s);

        EXPECT_TRUE(lower.find("inf") != std::string::npos)
            << "Expected infinity-like output, got: '" << s << "'";

        char* end = nullptr;
        const double parsed = std::strtod(s.c_str(), &end);
        if (end != s.c_str()) {
            EXPECT_TRUE(std::isinf(parsed));
            EXPECT_LT(parsed, 0.0);
        }
    }
    {
        const double nan = std::numeric_limits<double>::quiet_NaN();
        const std::string s = ToStrWithBufferSize(nan, 64);
        const std::string lower = ToLowerAscii(s);

        EXPECT_TRUE(lower.find("nan") != std::string::npos)
            << "Expected NaN-like output, got: '" << s << "'";

        char* end = nullptr;
        const double parsed = std::strtod(s.c_str(), &end);
        if (end != s.c_str()) {
            EXPECT_TRUE(std::isnan(parsed));
        }
    }
}

TEST_F(XMLUtilToStrDoubleTest_169, MinimalBufferSizeIsNullTerminated_169) {
    char buf[1];
    buf[0] = 'X'; // sentinel
    tinyxml2::XMLUtil::ToStr(123.0, buf, 1);

    // With a 1-byte buffer, only NUL can fit.
    EXPECT_EQ(buf[0], '\0');
}

TEST_F(XMLUtilToStrDoubleTest_169, TruncatesOutputWithoutOverflowAndIsPrefixOfFullOutput_169) {
    const double v = 1.234567890123456e200;

    const std::string full = ToStrWithBufferSize(v, 128);
    ASSERT_FALSE(full.empty());

    // Small buffers: ensure output is safely truncated and prefix-consistent.
    for (int smallSize : {2, 3, 4, 8, 12}) {
        std::vector<char> small(static_cast<size_t>(smallSize), '\x7E');
        tinyxml2::XMLUtil::ToStr(v, small.data(), smallSize);

        ASSERT_EQ(small[static_cast<size_t>(smallSize - 1)], '\0');

        const std::string truncated(small.data());
        ASSERT_LT(truncated.size(), static_cast<size_t>(smallSize));

        const std::string expectedPrefix = full.substr(0, static_cast<size_t>(smallSize - 1));
        EXPECT_EQ(truncated, expectedPrefix)
            << "Truncated output not a prefix of full output for size=" << smallSize
            << " full='" << full << "' truncated='" << truncated << "'";
    }
}

}  // namespace
