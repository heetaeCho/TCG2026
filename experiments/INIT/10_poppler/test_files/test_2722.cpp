// File: default_end_of_line_test_2722.cc

#include <gtest/gtest.h>

#include "poppler/TextOutputDev.h" // EndOfLineKind, eolUnix/eolDOS/eolMac

// NOTE: defaultEndOfLine() has internal linkage (static) in pdftotext.cc,
// so the test includes the .cc to access it without re-implementing logic.
#include "utils/pdftotext.cc"

namespace {

// Compile-time (constexpr) sanity check: should always be a valid EndOfLineKind.
constexpr EndOfLineKind kDefaultEol_2722 = defaultEndOfLine();
static_assert(kDefaultEol_2722 == eolUnix || kDefaultEol_2722 == eolDOS || kDefaultEol_2722 == eolMac,
              "defaultEndOfLine() must return a valid EndOfLineKind enum value");

class DefaultEndOfLineTest_2722 : public ::testing::Test {};

TEST_F(DefaultEndOfLineTest_2722, ReturnsPlatformDefault_2722)
{
    const EndOfLineKind eol = defaultEndOfLine();

#ifdef _WIN32
    EXPECT_EQ(eol, eolDOS);
#else
    EXPECT_EQ(eol, eolUnix);
#endif
}

TEST_F(DefaultEndOfLineTest_2722, IsDeterministicAcrossCalls_2722)
{
    const EndOfLineKind first = defaultEndOfLine();
    const EndOfLineKind second = defaultEndOfLine();
    EXPECT_EQ(first, second);
}

TEST_F(DefaultEndOfLineTest_2722, ReturnsAValidEnumValue_2722)
{
    const EndOfLineKind eol = defaultEndOfLine();
    EXPECT_TRUE(eol == eolUnix || eol == eolDOS || eol == eolMac);
}

} // namespace