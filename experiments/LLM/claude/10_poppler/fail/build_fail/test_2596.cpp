#include <glib.h>
#include <gtest/gtest.h>

// Declaration of the function under test
extern "C" {
GQuark poppler_error_quark(void);
}

class PopplerErrorQuarkTest_2596 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_error_quark returns a non-zero value
TEST_F(PopplerErrorQuarkTest_2596, ReturnsNonZeroQuark_2596)
{
    GQuark q = poppler_error_quark();
    EXPECT_NE(q, 0u);
}

// Test that poppler_error_quark returns the same value on repeated calls (singleton behavior)
TEST_F(PopplerErrorQuarkTest_2596, ReturnsSameQuarkOnRepeatedCalls_2596)
{
    GQuark q1 = poppler_error_quark();
    GQuark q2 = poppler_error_quark();
    GQuark q3 = poppler_error_quark();
    EXPECT_EQ(q1, q2);
    EXPECT_EQ(q2, q3);
}

// Test that the quark corresponds to the expected string "poppler-quark"
TEST_F(PopplerErrorQuarkTest_2596, QuarkCorrespondsToCorrectString_2596)
{
    GQuark q = poppler_error_quark();
    const gchar *str = g_quark_to_string(q);
    ASSERT_NE(str, nullptr);
    EXPECT_STREQ(str, "poppler-quark");
}

// Test that the quark matches what g_quark_from_static_string would return for the same string
TEST_F(PopplerErrorQuarkTest_2596, MatchesGQuarkFromStaticString_2596)
{
    GQuark expected = g_quark_from_static_string("poppler-quark");
    GQuark actual = poppler_error_quark();
    EXPECT_EQ(actual, expected);
}

// Test that the quark matches what g_quark_from_string would return for the same string
TEST_F(PopplerErrorQuarkTest_2596, MatchesGQuarkFromString_2596)
{
    GQuark expected = g_quark_from_string("poppler-quark");
    GQuark actual = poppler_error_quark();
    EXPECT_EQ(actual, expected);
}

// Test that the quark can be looked up via g_quark_try_string after initialization
TEST_F(PopplerErrorQuarkTest_2596, QuarkCanBeLookedUpViaTryString_2596)
{
    // Ensure the quark is initialized
    poppler_error_quark();

    GQuark looked_up = g_quark_try_string("poppler-quark");
    EXPECT_NE(looked_up, 0u);
    EXPECT_EQ(looked_up, poppler_error_quark());
}

// Test that poppler_error_quark is different from a quark for a different string
TEST_F(PopplerErrorQuarkTest_2596, DifferentFromOtherQuarks_2596)
{
    GQuark poppler_q = poppler_error_quark();
    GQuark other_q = g_quark_from_static_string("some-other-quark");
    EXPECT_NE(poppler_q, other_q);
}
