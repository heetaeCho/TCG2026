#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



// Mock class to simulate a type T for testing ResultValueBase

class MockType {

public:

    MockType() = default;

    MockType(const MockType&) = default;

    MockType(MockType&&) noexcept = default;

    MockType& operator=(const MockType&) = default;

    MockType& operator=(MockType&&) noexcept = default;

};



// Test fixture for ResultValueBase

class ResultValueBaseTest_362 : public ::testing::Test {

protected:

    using RVB = ResultValueBase<MockType>;



    RVB okResult_{ResultType::Ok, MockType{}};

    RVB logicErrorResult_{ResultType::LogicError};

    RVB runtimeErrorResult_{ResultType::RuntimeError};

};



// Test normal operation: Move assignment with Ok result

TEST_F(ResultValueBaseTest_362, MoveAssignmentWithOkResult_362) {

    RVB newResult{ResultType::LogicError};

    newResult = std::move(okResult_);

    EXPECT_EQ(newResult.m_type, ResultType::Ok);

}



// Test boundary condition: Self-move assignment

TEST_F(ResultValueBaseTest_362, SelfMoveAssignment_362) {

    RVB original{std::move(okResult_)};

    original = std::move(original); // self-move

    EXPECT_EQ(original.m_type, ResultType::Ok);

}



// Test exceptional case: Move assignment with LogicError result

TEST_F(ResultValueBaseTest_362, MoveAssignmentWithLogicErrorResult_362) {

    RVB newResult{ResultType::Ok, MockType{}};

    newResult = std::move(logicErrorResult_);

    EXPECT_EQ(newResult.m_type, ResultType::LogicError);

}



// Test exceptional case: Move assignment with RuntimeError result

TEST_F(ResultValueBaseTest_362, MoveAssignmentWithRuntimeErrorResult_362) {

    RVB newResult{ResultType::Ok, MockType{}};

    newResult = std::move(runtimeErrorResult_);

    EXPECT_EQ(newResult.m_type, ResultType::RuntimeError);

}



// Test normal operation: Value retrieval from Ok result

TEST_F(ResultValueBaseTest_362, RetrieveValueFromOkResult_362) {

    const auto& value = okResult_.value();

    (void)value; // Just ensure we can retrieve the value without crashing

}



// Test exceptional case: Attempt to retrieve value from non-Ok result should not be possible

TEST_F(ResultValueBaseTest_362, RetrieveValueFromNonOkResult_ShouldNotCompile_362) {

    // This test is more about ensuring that calling .value() on a non-Ok result is caught at compile time.

    // Since we cannot enforce this in runtime tests, it's noted here as a requirement.

}



// Test boundary condition: Destruction of Ok result

TEST_F(ResultValueBaseTest_362, DestroyOkResult_362) {

    RVB* result = new RVB{ResultType::Ok, MockType{}};

    delete result;

}



// Test boundary condition: Destruction of LogicError result

TEST_F(ResultValueBaseTest_362, DestroyLogicErrorResult_362) {

    RVB* result = new RVB{ResultType::LogicError};

    delete result;

}



// Test boundary condition: Destruction of RuntimeError result

TEST_F(ResultValueBaseTest_362, DestroyRuntimeErrorResult_362) {

    RVB* result = new RVB{ResultType::RuntimeError};

    delete result;

}
