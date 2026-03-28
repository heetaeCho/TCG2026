#include <gtest/gtest.h>

#include "poppler-page.h"



// Assuming PopplerRectangleExtended is a derived or extended struct of _PopplerRectangle

struct PopplerRectangleExtended : public _PopplerRectangle {};



TEST(PopplerRectangleFreeTest_2466, FreeNullPointer_2466) {

    // Test that calling poppler_rectangle_free with a null pointer does not cause an error

    poppler_rectangle_free(nullptr);

}



TEST(PopplerRectangleFreeTest_2466, FreeValidPointer_2466) {

    // Test that calling poppler_rectangle_free with a valid pointer frees the memory correctly

    PopplerRectangleExtended *rectangle = g_slice_new0(PopplerRectangleExtended);

    rectangle->x2 = 10;

    rectangle->y2 = 20;



    poppler_rectangle_free(reinterpret_cast<PopplerRectangle*>(rectangle));

}



TEST(PopplerRectangleFreeTest_2466, FreeTwiceSamePointer_2466) {

    // Test that calling poppler_rectangle_free twice on the same pointer does not cause an error

    PopplerRectangleExtended *rectangle = g_slice_new0(PopplerRectangleExtended);

    rectangle->x2 = 10;

    rectangle->y2 = 20;



    poppler_rectangle_free(reinterpret_cast<PopplerRectangle*>(rectangle));

    poppler_rectangle_free(reinterpret_cast<PopplerRectangle*>(rectangle)); // Should handle gracefully

}
