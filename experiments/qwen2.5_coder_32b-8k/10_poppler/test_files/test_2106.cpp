#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming poppler-annot.h contains the necessary declarations

extern "C" {

    #include "poppler-annot.h"

}



class PopplerAnnotCalloutLineTest_2106 : public ::testing::Test {

protected:

    void SetUp() override {

        callout_line = poppler_annot_callout_line_new();

    }



    void TearDown() override {

        g_free(callout_line);

    }



    PopplerAnnotCalloutLine* callout_line;

};



TEST_F(PopplerAnnotCalloutLineTest_2106, NewReturnsNonNullPointer_2106) {

    EXPECT_NE(callout_line, nullptr);

}



// Assuming there are no other observable behaviors or parameters for this simple constructor

// If there were more functions in the PopplerAnnotCalloutLine interface, additional tests would be needed.
