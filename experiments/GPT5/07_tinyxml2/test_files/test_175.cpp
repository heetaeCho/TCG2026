// File: test_xmlutil_tofloat_175.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstdio>
#include <limits>

#include "tinyxml2.h"

class XMLUtilToFloatTest_175 : public ::testing::Test {
protected:
    tinyxml2::XMLUtil util;
};

TEST_F(XMLUtilToFloatTest_175, ParsesSimplePositiveFloat_175)
{
    float v = 0.0f;
    const bool ok = util.ToFloat("3.5", &v);

    EXPECT_TRUE(ok);
    EXPECT_NEAR(v, 3.5f, 1e-6f);
}

TEST_F(XMLUtilToFloatTest_175, ParsesNegativeFloat_175)
{
    float v = 0.0f;
    const bool ok = util.ToFloat("-2.25", &v);

    EXPECT_TRUE(ok);
    EXPECT_NEAR(v, -2.25f, 1e-6f);
}

TEST_F(XMLUtilToFloatTest_175, ParsesScientificNotation_175)
{
    float v = 0.0f;
    const bool ok = util.ToFloat("1.25e2", &v);

    EXPECT_TRUE(ok);
    EXPECT_NEAR(v, 125.0f, 1e-4f);
}

TEST_F(XMLUtilToFloatTest_175, ParsesWithLeadingWhitespace_175)
{
    float v = 0.0f;
    const bool ok = util.ToFloat("   \t\n4.0", &v);

    EXPECT_TRUE(ok);
    EXPECT_NEAR(v, 4.0f, 1e-6f);
}

TEST_F(XMLUtilToFloatTest_175, ParsesWithTrailingCharacters_175)
{
    float v = 0.0f;
    const bool ok = util.ToFloat("7.75xyz", &v);

    // Observable behavior of common numeric parsing APIs: a numeric prefix may be accepted.
    // If the implementation accepts it, value should be parsed accordingly.
    EXPECT_TRUE(ok);
    EXPECT_NEAR(v, 7.75f, 1e-6f);
}

TEST_F(XMLUtilToFloatTest_175, ReturnsFalseForEmptyString_175)
{
    float v = 123.0f; // sentinel; do not assert it is unchanged on failure
    const bool ok = util.ToFloat("", &v);

    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilToFloatTest_175, ReturnsFalseForNonNumeric_175)
{
    float v = 123.0f; // sentinel; do not assert it is unchanged on failure
    const bool ok = util.ToFloat("not_a_number", &v);

    EXPECT_FALSE(ok);
}

TEST_F(XMLUtilToFloatTest_175, ParsesMaxFloatFormatted_175)
{
    // Format a float max value into a string and ensure parsing succeeds and yields a finite value.
    char buf[64] = {};
    std::snprintf(buf, sizeof(buf), "%.9g", std::numeric_limits<float>::max());

    float v = 0.0f;
    const bool ok = util.ToFloat(buf, &v);

    EXPECT_TRUE(ok);
    EXPECT_TRUE(std::isfinite(v));
    // Avoid overly strict equality due to formatting/rounding; just ensure it's large and positive.
    EXPECT_GT(v, 0.0f);
}

TEST_F(XMLUtilToFloatTest_175, DeathOnNullValuePointerIfSupported_175)
{
#if GTEST_HAS_DEATH_TEST
    // Passing a null output pointer is an error; behavior is expected to terminate/crash.
    EXPECT_DEATH({ (void)util.ToFloat("1.0", nullptr); }, ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/toolchain.";
#endif
}

TEST_F(XMLUtilToFloatTest_175, DeathOnNullInputStringIfSupported_175)
{
#if GTEST_HAS_DEATH_TEST
    float v = 0.0f;
    // Passing a null input pointer is an error; behavior is expected to terminate/crash.
    EXPECT_DEATH({ (void)util.ToFloat(nullptr, &v); }, ".*");
#else
    GTEST_SKIP() << "Death tests are not supported on this platform/toolchain.";
#endif
}
