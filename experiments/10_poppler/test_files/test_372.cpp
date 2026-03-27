#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



class ExponentialFunctionTest_372 : public ::testing::Test {

protected:

    std::unique_ptr<ExponentialFunction> expFunc;



    void SetUp() override {

        // Assuming a mock or test dictionary is needed to create an instance of ExponentialFunction

        // For the sake of this example, we assume it can be created with nullptr.

        expFunc = std::make_unique<ExponentialFunction>(nullptr);

    }

};



TEST_F(ExponentialFunctionTest_372, GetC1_ReturnsValidPointer_372) {

    const double* c1 = expFunc->getC1();

    EXPECT_NE(c1, nullptr);

}



TEST_F(ExponentialFunctionTest_372, GetC0_ReturnsValidPointer_372) {

    const double* c0 = expFunc->getC0();

    EXPECT_NE(c0, nullptr);

}



TEST_F(ExponentialFunctionTest_372, GetE_ReturnsPositiveValue_372) {

    double e = expFunc->getE();

    EXPECT_GT(e, 0.0);

}



TEST_F(ExponentialFunctionTest_372, IsOk_ReturnsTrueForValidInstance_372) {

    bool isOk = expFunc->isOk();

    EXPECT_TRUE(isOk);

}



// Assuming getType returns a valid enum value which we can check against known values.

TEST_F(ExponentialFunctionTest_372, GetType_ReturnsExpectedType_372) {

    Function::Type type = expFunc->getType();

    EXPECT_EQ(type, Function::exponential); // Assuming exponential is the correct type for ExponentialFunction

}



// Boundary conditions and exceptional/error cases are not directly observable from the given interface,

// as they do not return error codes or throw exceptions. If such behavior were possible, tests could be added.

```


