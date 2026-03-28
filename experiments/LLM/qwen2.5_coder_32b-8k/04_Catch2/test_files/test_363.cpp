#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Clara::Detail;



class ResultValueBaseTest_363 : public ::testing::Test {

protected:

    T value;

    ResultType type = ResultType::Ok;

};



TEST_F(ResultValueBaseTest_363, ConstructorWithValidTypeAndValue_363) {

    ResultValueBase<T> result(type, value);

    // No observable behavior to test directly, but ensure no exceptions are thrown.

}



TEST_F(ResultValueBaseTest_363, CopyConstructor_363) {

    ResultValueBase<T> original(type, value);

    ResultValueBase<T> copy = original;

    // No observable behavior to test directly, but ensure no exceptions are thrown.

}



TEST_F(ResultValueBaseTest_363, MoveConstructor_363) {

    ResultValueBase<T> original(type, value);

    ResultValueBase<T> moved = std::move(original);

    // No observable behavior to test directly, but ensure no exceptions are thrown.

}



TEST_F(ResultValueBaseTest_363, CopyAssignmentOperator_363) {

    ResultValueBase<T> original(type, value);

    ResultValueBase<T> assigned;

    assigned = original;

    // No observable behavior to test directly, but ensure no exceptions are thrown.

}



TEST_F(ResultValueBaseTest_363, MoveAssignmentOperator_363) {

    ResultValueBase<T> original(type, value);

    ResultValueBase<T> moved;

    moved = std::move(original);

    // No observable behavior to test directly, but ensure no exceptions are thrown.

}



TEST_F(ResultValueBaseTest_363, ValueAccess_363) {

    ResultValueBase<T> result(type, value);

    EXPECT_EQ(result.value(), value);

}



TEST_F(ResultValueBaseTest_363, DestructorCalledOnOkType_363) {

    // No observable behavior to test directly, but ensure no memory leaks or exceptions are thrown.

}

```


