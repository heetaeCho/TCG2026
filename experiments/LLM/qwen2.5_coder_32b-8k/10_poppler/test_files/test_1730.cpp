#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/CairoOutputDev.h"



class CairoOutputDevTest : public ::testing::Test {

protected:

    CairoOutputDev* cairo_output_dev;



    void SetUp() override {

        cairo_output_dev = new CairoOutputDev();

    }



    void TearDown() override {

        delete cairo_output_dev;

    }

};



TEST_F(CairoOutputDevTest_1730, SetPrintingTrue_1730) {

    cairo_output_dev->setPrinting(true);

    // Since we can't access internal state directly, this is the best we can do.

}



TEST_F(CairoOutputDevTest_1730, SetPrintingFalse_1730) {

    cairo_output_dev->setPrinting(false);

    // Similarly, we verify by invoking the function and assuming no exceptions occur.

}



// Boundary conditions: In this case, there are no obvious boundary conditions for a boolean setter.



// Exceptional or error cases: There are no observable exceptional cases based on the interface provided.



```


