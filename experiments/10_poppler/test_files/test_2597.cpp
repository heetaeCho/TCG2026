#include <gtest/gtest.h>

#include "poppler.h"



class PopplerBackendTest_2597 : public ::testing::Test {

protected:

    // No additional setup needed for this simple function

};



TEST_F(PopplerBackendTest_2597, GetBackendReturnsCairo_2597) {

    EXPECT_EQ(poppler_get_backend(), POPPLER_BACKEND_CAIRO);

}



// Since the function always returns a constant value, there are no boundary conditions or error cases to test.
