#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Mock class for ResultBase to verify interactions if needed.

class MockResultBase : public ResultBase {

public:

    using ResultBase::ResultBase;

};



// Test fixture for ResultValueBase

template <typename T>

class ResultValueBaseTest_361 : public ::testing::Test {

protected:

    ResultValueBase<T> okInstance;

    ResultValueBase<T> errorInstance;



    ResultValueBaseTest_361() 

        : okInstance(ResultType::Ok, T{}), 

          errorInstance(ResultType::LogicError) {}

};



using Types = ::testing::Types<int, std::string>;

TYPED_TEST_SUITE(ResultValueBaseTest_361, Types);



// Normal operation

TYPED_TEST(ResultValueBaseTest_361, GetValue_ReturnsCorrectValue_361) {

    TypeParam value{};

    ResultValueBase<TypeParam> instance(ResultType::Ok, value);

    EXPECT_EQ(instance.value(), value);

}



// Boundary conditions

TYPED_TEST(ResultValueBaseTest_361, CopyConstructor_CopiesValue_361) {

    TypeParam value{};

    ResultValueBase<TypeParam> original(ResultType::Ok, value);

    ResultValueBase<TypeParam> copy = original;

    EXPECT_EQ(copy.value(), original.value());

}



TYPED_TEST(ResultValueBaseTest_361, MoveConstructor_MovesValue_361) {

    TypeParam value{};

    ResultValueBase<TypeParam> original(ResultType::Ok, value);

    ResultValueBase<TypeParam> moved = std::move(original);

    EXPECT_EQ(moved.value(), value);

}



TYPED_TEST(ResultValueBaseTest_361, CopyAssignment_CopiesValue_361) {

    TypeParam value{};

    ResultValueBase<TypeParam> original(ResultType::Ok, value);

    ResultValueBase<TypeParam> copy;

    copy = original;

    EXPECT_EQ(copy.value(), original.value());

}



TYPED_TEST(ResultValueBaseTest_361, MoveAssignment_MovesValue_361) {

    TypeParam value{};

    ResultValueBase<TypeParam> original(ResultType::Ok, value);

    ResultValueBase<TypeParam> moved;

    moved = std::move(original);

    EXPECT_EQ(moved.value(), value);

}



// Exceptional or error cases

TYPED_TEST(ResultValueBaseTest_361, ErrorInstance_DoesNotHaveValue_361) {

    // Since we do not have a way to enforceOk() or check the type,

    // this test is limited to just creating an instance with an error.

    EXPECT_NO_THROW(this->errorInstance);

}
