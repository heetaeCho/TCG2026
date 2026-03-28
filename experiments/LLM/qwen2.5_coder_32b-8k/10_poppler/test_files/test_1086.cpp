#include <gtest/gtest.h>

#include "OutputDev.h"



class OutputDevTest : public ::testing::Test {

protected:

    OutputDev* outputDev;



    void SetUp() override {

        outputDev = new OutputDev();

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(OutputDevTest_1086, GetIccColorSpaceCache_ReturnsValidPointer_1086) {

    EXPECT_NE(outputDev->getIccColorSpaceCache(), nullptr);

}



// No other specific functionality is exposed through the getIccColorSpaceCache method,

// so we can't test much more than it returning a non-null pointer.

```


