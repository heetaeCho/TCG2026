#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-page.h"



class PopplerQuadrilateralTest_2472 : public ::testing::Test {

protected:

    void SetUp() override {

        quadrilateral = poppler_quadrilateral_new();

    }



    void TearDown() override {

        g_slice_free(PopplerQuadrilateral, quadrilateral);

    }



    PopplerQuadrilateral* quadrilateral;

};



TEST_F(PopplerQuadrilateralTest_2472, NewQuadrilateralIsNotNull_2472) {

    EXPECT_NE(quadrilateral, nullptr);

}



// Assuming no boundary conditions or exceptional cases are observable for this simple allocation function.

```


