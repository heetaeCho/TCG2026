#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::_;



// Mock GeneratorWrapper for testing TakeGenerator

class MockGeneratorWrapper : public IGenerator<int> {

public:

    MOCK_METHOD(bool, next, (), (override));

    MOCK_METHOD(int const&, get, (), (const override));

};



class TakeGeneratorTest_921 : public ::testing::Test {

protected:

    std::unique_ptr<MockGeneratorWrapper> mock_generator_;

    std::unique_ptr<TakeGenerator<int>> take_generator_;



    void SetUp() override {

        mock_generator_ = std::make_unique<MockGeneratorWrapper>();

        take_generator_ = std::make_unique<TakeGenerator<int>>(3, CATCH_MOVE(*mock_generator_));

    }

};



TEST_F(TakeGeneratorTest_921, NextReturnsTrueWhenTargetNotReached_921) {

    EXPECT_CALL(*mock_generator_, next()).WillOnce(::testing::Return(true));



    bool result = take_generator_->next();

    EXPECT_TRUE(result);

}



TEST_F(TakeGeneratorTest_921, NextReturnsFalseWhenTargetReached_921) {

    EXPECT_CALL(*mock_generator_, next())

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(false));



    take_generator_->next();

    take_generator_->next();



    bool result = take_generator_->next();

    EXPECT_FALSE(result);

}



TEST_F(TakeGeneratorTest_921, GetDelegatesToMockGenerator_921) {

    int expected_value = 42;

    EXPECT_CALL(*mock_generator_, next()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mock_generator_, get()).WillOnce(::testing::ReturnRef(expected_value));



    take_generator_->next();

    int result = take_generator_->get();

    EXPECT_EQ(result, expected_value);

}



TEST_F(TakeGeneratorTest_921, NextStopsCallingMockGeneratorAfterTargetReached_921) {

    EXPECT_CALL(*mock_generator_, next())

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(false));



    take_generator_->next();

    take_generator_->next();



    bool result = take_generator_->next();

    EXPECT_FALSE(result);



    EXPECT_CALL(*mock_generator_, next()).Times(0);

    result = take_generator_->next();

    EXPECT_FALSE(result);

}



TEST_F(TakeGeneratorTest_921, GetCalledAfterTargetReachedThrowsException_921) {

    EXPECT_CALL(*mock_generator_, next())

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(false));



    take_generator_->next();

    take_generator_->next();



    EXPECT_THROW(take_generator_->get(), std::runtime_error);

}
