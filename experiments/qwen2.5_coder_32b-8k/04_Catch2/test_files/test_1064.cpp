#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class ResultValueBaseTest : public ::testing::Test {

protected:

    using T = int; // Assuming T is an int for testing purposes, as it's not specified

    ResultType okResultType = ResultType::Ok;

    T testValue = 42;

};



TEST_F(ResultValueBaseTest_1064, ConstructorSetsCorrectResultType_1064) {

    ResultValueBase result(okResultType, testValue);

    EXPECT_EQ(result.getResultType(), okResultType);

}



TEST_F(ResultValueBaseTest_1064, ConstructorStoresCorrectValue_1064) {

    ResultValueBase result(okResultType, testValue);

    EXPECT_EQ(result.getValue<T>(), testValue);

}



// Assuming there are boundary conditions or error cases based on the interface,

// but since the interface is very limited and does not expose much functionality,

// we can only test the constructor behavior.



// If there were additional functions in ResultBase that could be tested, those would go here.

```


