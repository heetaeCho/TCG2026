#include <gtest/gtest.h>

#include "poppler-annot.h"



// Mocking external collaborators if needed (none in this case)



class PopplerAnnotInkTest : public ::testing::Test {

protected:

    // Setup and teardown can be used to initialize objects before each test

    virtual void SetUp() {

        // Initialize the PopplerAnnotInk object here if necessary

        annot = static_cast<PopplerAnnotInk*>(g_malloc0(sizeof(PopplerAnnotInk)));

    }



    virtual void TearDown() {

        // Clean up after each test

        g_free(annot);

    }



    PopplerAnnotInk* annot;

};



TEST_F(PopplerAnnotInkTest, GetDrawBelow_ReturnsFalse_2134) {

    // Test the normal behavior where getDrawBelow returns false

    EXPECT_EQ(poppler_annot_ink_get_draw_below(annot), FALSE);

}



TEST_F(PopplerAnnotInkTest, GetDrawBelow_ReturnsTrue_2134) {

    // Assuming there's a way to set draw below to true for testing purposes

    // Since we can't modify internal state, this test is hypothetical

    // In practice, you would need an additional function to set this value

    EXPECT_EQ(poppler_annot_ink_get_draw_below(annot), TRUE);

}



// Additional tests for boundary conditions and exceptional cases if applicable

// However, based on the given interface, there aren't clear boundaries or exceptions to test



TEST_F(PopplerAnnotInkTest, GetDrawBelow_NullPointer_2134) {

    // Test the behavior when a null pointer is passed

    EXPECT_EQ(poppler_annot_ink_get_draw_below(nullptr), FALSE);

}
