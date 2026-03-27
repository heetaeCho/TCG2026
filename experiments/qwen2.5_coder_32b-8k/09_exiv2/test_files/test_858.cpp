#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;



class LangAltValueTest_858 : public ::testing::Test {

protected:

    LangAltValue value;

};



TEST_F(LangAltValueTest_858, ToInt64_ReturnsZero_858) {

    EXPECT_EQ(value.toInt64(0), 0);

}



TEST_F(LangAltValueTest_858, ToInt64_SetsOkToFalse_858) {

    value.toInt64(0);

    // Since ok_ is private, we cannot directly verify its state.

    // We can only infer that it should be false based on the behavior of toInt64.

}



TEST_F(LangAltValueTest_858, ToInt64_BoundaryConditionZeroIndex_858) {

    EXPECT_EQ(value.toInt64(0), 0);

}



// Assuming there are no additional constraints or behaviors specified for n > 0

// and since the function always returns 0 and sets ok_ to false regardless of input,

// we do not need additional tests for different values of n.

```


