#include <gtest/gtest.h>

// Define the types and constants needed to test the function
typedef unsigned long UniCodePoint;

#define UCP(x) x

// Re-declare the function under test (it's static inline in the original,
// so we need to include/define it here for testing purposes)
static inline bool IsClosingingQuote(UniCodePoint uniChar, UniCodePoint openQuote, UniCodePoint closeQuote)
{
    if ((uniChar == closeQuote) ||
        ((openQuote == UCP(0x301D)) && ((uniChar == UCP(0x301E)) || (uniChar == UCP(0x301F))))) {
        return true;
    } else {
        return false;
    }
}

class IsClosingingQuoteTest_1916 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: uniChar matches closeQuote exactly — should return true
TEST_F(IsClosingingQuoteTest_1916, UniCharMatchesCloseQuote_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x0022, 0x0022, 0x0022));
}

// Test: uniChar matches closeQuote with different openQuote — should return true
TEST_F(IsClosingingQuoteTest_1916, UniCharMatchesCloseQuoteDifferentOpen_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x0029, 0x0028, 0x0029));
}

// Test: uniChar does not match closeQuote and openQuote is not 0x301D — should return false
TEST_F(IsClosingingQuoteTest_1916, UniCharDoesNotMatchCloseQuoteNonSpecialOpen_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0x0041, 0x0028, 0x0029));
}

// Test: openQuote is 0x301D and uniChar is 0x301E — should return true (special case)
TEST_F(IsClosingingQuoteTest_1916, SpecialOpenQuote301D_UniChar301E_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x301E, 0x301D, 0x301E));
}

// Test: openQuote is 0x301D and uniChar is 0x301F — should return true (special case)
TEST_F(IsClosingingQuoteTest_1916, SpecialOpenQuote301D_UniChar301F_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x301F, 0x301D, 0x9999));
}

// Test: openQuote is 0x301D and uniChar is 0x301E, closeQuote is different — still true
TEST_F(IsClosingingQuoteTest_1916, SpecialOpenQuote301D_UniChar301E_CloseQuoteDifferent_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x301E, 0x301D, 0x1234));
}

// Test: openQuote is 0x301D but uniChar is neither 0x301E nor 0x301F nor closeQuote — false
TEST_F(IsClosingingQuoteTest_1916, SpecialOpenQuote301D_UniCharNotSpecial_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0x301D, 0x301D, 0x9999));
}

// Test: openQuote is 0x301D but uniChar is 0x301D and closeQuote is 0x301D — true (matches closeQuote)
TEST_F(IsClosingingQuoteTest_1916, SpecialOpenQuote301D_UniCharMatchesCloseQuote_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x301D, 0x301D, 0x301D));
}

// Test: openQuote is NOT 0x301D, uniChar is 0x301E — should return false (no special handling)
TEST_F(IsClosingingQuoteTest_1916, NonSpecialOpenQuote_UniChar301E_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0x301E, 0x0022, 0x0022));
}

// Test: openQuote is NOT 0x301D, uniChar is 0x301F — should return false
TEST_F(IsClosingingQuoteTest_1916, NonSpecialOpenQuote_UniChar301F_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0x301F, 0x0028, 0x0029));
}

// Test: All zeros — uniChar matches closeQuote (both 0) — true
TEST_F(IsClosingingQuoteTest_1916, AllZeros_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0, 0, 0));
}

// Test: uniChar is 0, openQuote is 0x301D, closeQuote is something else — false
TEST_F(IsClosingingQuoteTest_1916, UniCharZero_SpecialOpen_NonMatchingClose_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0, 0x301D, 0x301E));
}

// Test: Large values — uniChar equals closeQuote
TEST_F(IsClosingingQuoteTest_1916, LargeValuesMatch_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0xFFFFFFFF, 0x12345678, 0xFFFFFFFF));
}

// Test: Large values — uniChar does not equal closeQuote, not special case
TEST_F(IsClosingingQuoteTest_1916, LargeValuesNoMatch_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0xFFFFFFFE, 0x12345678, 0xFFFFFFFF));
}

// Test: openQuote is 0x301D, uniChar is 0x3020 — not a special close quote, not matching closeQuote — false
TEST_F(IsClosingingQuoteTest_1916, SpecialOpen_NonSpecialUniChar_1916)
{
    EXPECT_FALSE(IsClosingingQuote(0x3020, 0x301D, 0x5555));
}

// Test: closeQuote matches uniChar regardless of openQuote value
TEST_F(IsClosingingQuoteTest_1916, CloseQuoteMatchOverridesAll_1916)
{
    EXPECT_TRUE(IsClosingingQuote(42, 100, 42));
}

// Test: uniChar is 0x301F with openQuote 0x301D and closeQuote also 0x301F — true (both conditions)
TEST_F(IsClosingingQuoteTest_1916, BothConditionsTrue_1916)
{
    EXPECT_TRUE(IsClosingingQuote(0x301F, 0x301D, 0x301F));
}
