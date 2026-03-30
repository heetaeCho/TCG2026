#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"



// Assuming the correct struct definition for PopplerTextSpan

struct _PopplerTextSpan {

    char *text;

    char *font_name;

};



typedef struct _PopplerTextSpan PopplerTextSpan;



TEST(PopplerTextSpanTest_2542, CopyValidTextSpan_2542) {

    PopplerTextSpan original_span;

    original_span.text = g_strdup("Sample text");

    original_span.font_name = g_strdup("Arial");



    PopplerTextSpan *copied_span = poppler_text_span_copy(&original_span);



    EXPECT_STREQ(copied_span->text, "Sample text");

    EXPECT_STREQ(copied_span->font_name, "Arial");



    g_free(original_span.text);

    g_free(original_span.font_name);

    g_free(copied_span->text);

    g_free(copied_span->font_name);

    g_slice_free(PopplerTextSpan, copied_span);

}



TEST(PopplerTextSpanTest_2542, CopyNullFontName_2542) {

    PopplerTextSpan original_span;

    original_span.text = g_strdup("Sample text");

    original_span.font_name = nullptr;



    PopplerTextSpan *copied_span = poppler_text_span_copy(&original_span);



    EXPECT_STREQ(copied_span->text, "Sample text");

    EXPECT_EQ(copied_span->font_name, nullptr);



    g_free(original_span.text);

    g_free(copied_span->text);

    g_slice_free(PopplerTextSpan, copied_span);

}



TEST(PopplerTextSpanTest_2542, CopyNullText_2542) {

    PopplerTextSpan original_span;

    original_span.text = nullptr;

    original_span.font_name = g_strdup("Arial");



    PopplerTextSpan *copied_span = poppler_text_span_copy(&original_span);



    EXPECT_EQ(copied_span->text, nullptr);

    EXPECT_STREQ(copied_span->font_name, "Arial");



    g_free(original_span.font_name);

    g_free(copied_span->font_name);

    g_slice_free(PopplerTextSpan, copied_span);

}



TEST(PopplerTextSpanTest_2542, CopyNullSpan_2542) {

    PopplerTextSpan *copied_span = poppler_text_span_copy(nullptr);



    EXPECT_EQ(copied_span, nullptr);

}



TEST(PopplerTextSpanTest_2542, CopyEmptyTextAndFontName_2542) {

    PopplerTextSpan original_span;

    original_span.text = g_strdup("");

    original_span.font_name = g_strdup("");



    PopplerTextSpan *copied_span = poppler_text_span_copy(&original_span);



    EXPECT_STREQ(copied_span->text, "");

    EXPECT_STREQ(copied_span->font_name, "");



    g_free(original_span.text);

    g_free(original_span.font_name);

    g_free(copied_span->text);

    g_free(copied_span->font_name);

    g_slice_free(PopplerTextSpan, copied_span);

}
