// poppler_text_span_get_font_name_test_2549.cc
#include <gtest/gtest.h>

#include <glib.h>

// Include the implementation directly so the test can construct PopplerTextSpan
// instances and set public fields without re-implementing any logic.
#include "poppler-structure-element.cc"

namespace {

class PopplerTextSpanTest_2549 : public ::testing::Test {};

TEST_F(PopplerTextSpanTest_2549, NullSpanReturnsNull_2549)
{
    EXPECT_EQ(poppler_text_span_get_font_name(nullptr), nullptr);
}

TEST_F(PopplerTextSpanTest_2549, ReturnsStoredFontNamePointer_2549)
{
    PopplerTextSpan span{};
    span.font_name = const_cast<gchar *>("TestFont-Regular");

    const gchar *result = poppler_text_span_get_font_name(&span);

    // Observable behavior: returns the stored pointer (no copy implied by interface).
    EXPECT_EQ(result, span.font_name);
    EXPECT_STREQ(result, "TestFont-Regular");
}

TEST_F(PopplerTextSpanTest_2549, EmptyStringFontNameIsReturned_2549)
{
    PopplerTextSpan span{};
    span.font_name = const_cast<gchar *>("");

    const gchar *result = poppler_text_span_get_font_name(&span);

    EXPECT_EQ(result, span.font_name);
    EXPECT_STREQ(result, "");
}

TEST_F(PopplerTextSpanTest_2549, NullFontNameMemberIsReturnedAsNull_2549)
{
    PopplerTextSpan span{};
    span.font_name = nullptr;

    EXPECT_EQ(poppler_text_span_get_font_name(&span), nullptr);
}

TEST_F(PopplerTextSpanTest_2549, DoesNotModifySpan_2549)
{
    PopplerTextSpan span{};
    span.font_name = const_cast<gchar *>("ImmutableFont");

    const gchar *before = span.font_name;
    const gchar *result = poppler_text_span_get_font_name(&span);

    EXPECT_EQ(result, before);
    EXPECT_EQ(span.font_name, before);
    EXPECT_STREQ(result, "ImmutableFont");
}

} // namespace