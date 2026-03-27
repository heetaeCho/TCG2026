#include <gtest/gtest.h>

#include "poppler-page.h"



// Assuming poppler_image_mapping_free is declared in a header file included above



TEST(poppler_image_mapping_free_Test_2488, FreesMemoryCorrectly_2488) {

    // Create a PopplerImageMapping instance to test

    PopplerImageMapping* mapping = static_cast<PopplerImageMapping*>(g_slice_alloc(sizeof(PopplerImageMapping)));

    

    // Call the function under test

    poppler_image_mapping_free(mapping);

    

    // Since g_slice_free is used, we don't have a direct way to verify memory deallocation.

    // However, this test ensures that the function call does not crash and behaves as expected.

}



TEST(poppler_image_mapping_free_Test_2488, HandlesNullPointerGracefully_2488) {

    // Test with a null pointer

    PopplerImageMapping* mapping = nullptr;

    

    // Call the function under test

    poppler_image_mapping_free(mapping);

    

    // Expect no crash and graceful handling of null input.

}



// Additional tests can be added if there are more observable behaviors or edge cases,

// but based on the given information, these two tests cover normal and boundary conditions.
