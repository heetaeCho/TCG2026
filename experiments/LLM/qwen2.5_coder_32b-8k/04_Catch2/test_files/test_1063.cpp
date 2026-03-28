#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



TEST_F(ResultValueBaseTest_1063, ConstructorOkTypeWithLvalue_1063) {

    int value = 42;

    ResultValueBase<int> result(ResultType::Ok, value);

    EXPECT_EQ(result.value(), 42);

}



TEST_F(ResultValueBaseTest_1063, ConstructorOkTypeWithRvalue_1063) {

    ResultValueBase<std::string> result(ResultType::Ok, std::string("test"));

    EXPECT_EQ(result.value(), "test");

}



TEST_F(ResultValueBaseTest_1063, MoveConstructorSameType_1063) {

    int value = 42;

    ResultValueBase<int> original(ResultType::Ok, value);

    ResultValueBase<int> moved(std::move(original));

    EXPECT_EQ(moved.value(), 42);

}



TEST_F(ResultValueBaseTest_1063, MoveConstructorDifferentType_1063) {

    std::string str = "test";

    ResultValueBase<std::string> original(ResultType::Ok, std::move(str));

    ResultValueBase<std::string> moved(std::move(original));

    EXPECT_EQ(moved.value(), "test");

}



TEST_F(ResultValueBaseTest_1063, MoveAssignmentSameType_1063) {

    int value = 42;

    ResultValueBase<int> original(ResultType::Ok, value);

    ResultValueBase<int> assigned(ResultType::RuntimeError);

    assigned = std::move(original);

    EXPECT_EQ(assigned.value(), 42);

}



TEST_F(ResultValueBaseTest_1063, MoveAssignmentDifferentType_1063) {

    std::string str = "test";

    ResultValueBase<std::string> original(ResultType::Ok, std::move(str));

    ResultValueBase<std::string> assigned(ResultType::LogicError);

    assigned = std::move(original);

    EXPECT_EQ(assigned.value(), "test");

}



TEST_F(ResultValueBaseTest_1063, CopyConstructorSameType_1063) {

    int value = 42;

    ResultValueBase<int> original(ResultType::Ok, value);

    ResultValueBase<int> copied(original);

    EXPECT_EQ(copied.value(), 42);

}



TEST_F(ResultValueBaseTest_1063, CopyConstructorDifferentType_1063) {

    std::string str = "test";

    ResultValueBase<std::string> original(ResultType::Ok, std::move(str));

    ResultValueBase<std::string> copied(original);

    EXPECT_EQ(copied.value(), "test");

}



TEST_F(ResultValueBaseTest_1063, CopyAssignmentSameType_1063) {

    int value = 42;

    ResultValueBase<int> original(ResultType::Ok, value);

    ResultValueBase<int> assigned(ResultType::RuntimeError);

    assigned = original;

    EXPECT_EQ(assigned.value(), 42);

}



TEST_F(ResultValueBaseTest_1063, CopyAssignmentDifferentType_1063) {

    std::string str = "test";

    ResultValueBase<std::string> original(ResultType::Ok, std::move(str));

    ResultValueBase<std::string> assigned(ResultType::LogicError);

    assigned = original;

    EXPECT_EQ(assigned.value(), "test");

}



TEST_F(ResultValueBaseTest_1063, LogicErrorConstruction_1063) {

    ResultValueBase<int> result(ResultType::LogicError);

    // Assuming no observable behavior for non-Ok types, just ensure it constructs.

}



TEST_F(ResultValueBaseTest_1063, RuntimeErrorConstruction_1063) {

    ResultValueBase<std::string> result(ResultType::RuntimeError);

    // Assuming no observable behavior for non-Ok types, just ensure it constructs.

}
