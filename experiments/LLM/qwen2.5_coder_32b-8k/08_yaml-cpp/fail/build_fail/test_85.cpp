#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"



// Assuming a class that might use the BAD_SUBSCRIPT_WITH_KEY function internally

class DummyClass {

public:

    std::string getErrorMessage(const std::string& key) {

        try {

            // Simulate throwing an exception using BAD_SUBSCRIPT_WITH_KEY

            throw YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key);

        } catch (const std::runtime_error& e) {

            return e.what();

        }

    }

};



class ExceptionsTest_85 : public ::testing::Test {

protected:

    DummyClass dummy;

};



TEST_F(ExceptionsTest_85, BadSubscriptWithKey_NormalOperation_85) {

    EXPECT_EQ(dummy.getErrorMessage("test_key"), YAML::ErrorMsg::BAD_SUBSCRIPT);

}



TEST_F(ExceptionsTest_85, BadSubscriptWithKey_BoundaryCondition_EmptyString_85) {

    EXPECT_EQ(dummy.getErrorMessage(""), YAML::ErrorMsg::BAD_SUBSCRIPT);

}



TEST_F(ExceptionsTest_85, BadSubscriptWithKey_ExceptionalCase_NonNumericType_85) {

    EXPECT_EQ(dummy.getErrorMessage("non_numeric_key"), YAML::ErrorMsg::BAD_SUBSCRIPT);

}

```



In this test setup:

- A `DummyClass` is created to simulate a class that might use the `BAD_SUBSCRIPT_WITH_KEY` function.

- The `ExceptionsTest_85` fixture sets up the environment for testing.

- Three test cases are provided:

  - Normal operation with a typical key.

  - Boundary condition with an empty string as the key.

  - Exceptional case with a non-numeric type (string) as the key. 


