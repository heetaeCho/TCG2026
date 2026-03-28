#include <gtest/gtest.h>

#include "poppler-annot.h"



// Assuming necessary setup for PopplerAnnotInk creation and destruction



class PopplerAnnotInkTest_2133 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code to create a PopplerAnnotInk instance

        m_poppler_annot_ink = reinterpret_cast<PopplerAnnotInk*>(g_malloc(sizeof(PopplerAnnotInk)));

        // Additional setup if needed

    }



    void TearDown() override {

        // Cleanup code to destroy the PopplerAnnotInk instance

        g_free(m_poppler_annot_ink);

        // Additional cleanup if needed

    }



    PopplerAnnotInk* m_poppler_annot_ink;

};



TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowTrue_2133) {

    poppler_annot_ink_set_draw_below(m_poppler_annot_ink, TRUE);

    // Verification of behavior or state change if observable

}



TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowFalse_2133) {

    poppler_annot_ink_set_draw_below(m_poppler_annot_ink, FALSE);

    // Verification of behavior or state change if observable

}



TEST_F(PopplerAnnotInkTest_2133, BoundaryConditionTrue_2133) {

    poppler_annot_ink_set_draw_below(m_poppler_annot_ink, static_cast<gboolean>(1));

    // Verification of behavior or state change if observable

}



TEST_F(PopplerAnnotInkTest_2133, BoundaryConditionFalse_2133) {

    poppler_annot_ink_set_draw_below(m_poppler_annot_ink, static_cast<gboolean>(0));

    // Verification of behavior or state change if observable

}



// Assuming no exceptional cases are observable through the interface for this function



```


