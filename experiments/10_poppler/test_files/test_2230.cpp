#include <gtest/gtest.h>

#include "poppler-document.h"

#include <gmock/gmock.h>



// Mocking necessary dependencies

class MockPopplerFontsIter : public PopplerFontsIter {

public:

    MOCK_METHOD(void, free, (), (override));

};



TEST(poppler_fonts_iter_free_Test_2230, NullPointerTest_2230) {

    // Testing the behavior when null pointer is passed to poppler_fonts_iter_free

    poppler_fonts_iter_free(nullptr);

    // No assertion needed as function should simply return without any effect

}



TEST(poppler_fonts_iter_free_Test_2230, NormalOperationTest_2230) {

    // Setting up a typical PopplerFontsIter object for testing normal behavior

    PopplerFontsIter* iter = static_cast<PopplerFontsIter*>(g_slice_alloc(sizeof(PopplerFontsIter)));

    iter->items = std::vector<FontInfo*>();  // Assuming FontInfo is default-constructible



    // Adding some mock FontInfo objects to test deletion logic

    iter->items.push_back(new FontInfo());

    iter->items.push_back(new FontInfo());



    poppler_fonts_iter_free(iter);

    // No assertion needed as function should properly free all resources and itself

}



TEST(poppler_fonts_iter_free_Test_2230, BoundaryConditionTest_2230) {

    // Testing the behavior when an empty vector is passed to poppler_fonts_iter_free

    PopplerFontsIter* iter = static_cast<PopplerFontsIter*>(g_slice_alloc(sizeof(PopplerFontsIter)));

    iter->items = std::vector<FontInfo*>();  // Empty vector



    poppler_fonts_iter_free(iter);

    // No assertion needed as function should properly free the empty vector and itself

}

```


