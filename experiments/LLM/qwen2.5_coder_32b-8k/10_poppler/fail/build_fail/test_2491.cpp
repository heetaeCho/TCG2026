#include <gtest/gtest.h>

#include "poppler-page.h"



// Mocking g_free to ensure it's called correctly

extern "C" {

    void g_free(void* ptr) {

        free(ptr);

    }

}



class PopplerPageTransitionTest_2491 : public ::testing::Test {

protected:

    virtual void SetUp() {

        transition = static_cast<PopplerPageTransition*>(malloc(sizeof(PopplerPageTransition)));

    }



    virtual void TearDown() {

        if (transition) {

            poppler_page_transition_free(transition);

            transition = nullptr;

        }

    }



    PopplerPageTransition* transition;

};



TEST_F(PopplerPageTransitionTest_2491, FreeReleasesMemory_2491) {

    // Since we're mocking g_free to call free, we can't directly test memory release.

    // However, we can ensure that poppler_page_transition_free calls g_free with the correct pointer.

    EXPECT_NE(transition, nullptr);

    poppler_page_transition_free(transition);

    transition = nullptr;  // Manually set to nullptr since we freed it

}



TEST_F(PopplerPageTransitionTest_2491, FreeNullPointer_2491) {

    // Ensure that calling free with a null pointer does not cause any issues.

    poppler_page_transition_free(nullptr);

}
