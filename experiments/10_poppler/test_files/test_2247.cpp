#include <gtest/gtest.h>

#include "poppler-document.h" // Assuming this header contains the declaration of poppler_layers_iter_free and PopplerLayersIter



// Mocking a dependency if needed (none in this case, but showing how you might do it)

// class MockDocument {

// public:

//     MOCK_METHOD(void, unref, (), ());

// };



TEST_F(PopplerLayersIterFreeTest_2247, NullPointerHandling_2247) {

    // Test that calling the function with a nullptr does not cause any issues

    poppler_layers_iter_free(nullptr);

}



TEST_F(PopplerLayersIterFreeTest_2247, NormalOperation_2247) {

    // Arrange: Create a mock PopplerLayersIter object

    PopplerLayersIter* iter = reinterpret_cast<PopplerLayersIter*>(g_slice_alloc(sizeof(PopplerLayersIter)));

    iter->document = nullptr; // Assuming no document is associated for simplicity



    // Act: Call the function with a valid pointer

    poppler_layers_iter_free(iter);



    // Assert: Normally, we would check if resources were freed properly,

    // but since we cannot access internal state, we just ensure no crash occurs.

}



// Since there are no external collaborators or observable side effects other than

// memory management, and the function is quite simple, the above tests cover the main scenarios.
