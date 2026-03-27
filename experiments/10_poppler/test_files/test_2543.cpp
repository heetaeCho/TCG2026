#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the correct definition of PopplerTextSpan based on context and typical usage.

struct _PopplerTextSpan {

    char *text;

    char *font_name; // Adding this as per typical structure of text spans

};

typedef struct _PopplerTextSpan PopplerTextSpan;



extern "C" void poppler_text_span_free(PopplerTextSpan *poppler_text_span);



TEST(poppler_text_span_free_2543, NullPointerHandling_2543) {

    // Test that passing a null pointer does not cause any issues

    poppler_text_span_free(nullptr);

}



TEST(poppler_text_span_free_2543, NormalOperationWithAllocatedMemory_2543) {

    // Test normal operation with allocated memory for text and font_name

    PopplerTextSpan *span = static_cast<PopplerTextSpan*>(g_slice_new(PopplerTextSpan));

    span->text = g_strdup("Sample Text");

    span->font_name = g_strdup("Arial");



    poppler_text_span_free(span);



    // No assertion needed here as we're just checking for lack of crash

}



TEST(poppler_text_span_free_2543, BoundaryConditionWithEmptyStrings_2543) {

    // Test boundary condition with empty strings

    PopplerTextSpan *span = static_cast<PopplerTextSpan*>(g_slice_new(PopplerTextSpan));

    span->text = g_strdup("");

    span->font_name = g_strdup("");



    poppler_text_span_free(span);



    // No assertion needed here as we're just checking for lack of crash

}



TEST(poppler_text_span_free_2543, ExceptionalCaseWithUnallocatedMemory_2543) {

    // Test exceptional case where text and font_name are not allocated

    PopplerTextSpan *span = static_cast<PopplerTextSpan*>(g_slice_new(PopplerTextSpan));

    span->text = nullptr;

    span->font_name = nullptr;



    poppler_text_span_free(span);



    // No assertion needed here as we're just checking for lack of crash

}
