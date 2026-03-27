#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_generators.hpp"



using namespace Catch::Generators;

using ::testing::_;



class GeneratorWrapperTest : public ::testing::Test {

protected:

    class MockGenerator : public IGenerator<int> {

    public:

        MOCK_METHOD(int const&, get, (), (const override));

        MOCK_METHOD(bool, next, (), (override));

    };



    std::shared_ptr<MockGenerator> mock_generator;

    GeneratorWrapper<int> generator_wrapper;



    GeneratorWrapperTest() : mock_generator(std::make_shared<MockGenerator>()), 

                             generator_wrapper(mock_generator) {}

};



TEST_F(GeneratorWrapperTest_312, GetDelegatesToGenerator_312) {

    EXPECT_CALL(*mock_generator, get()).WillOnce(::testing::Return(42));

    EXPECT_EQ(generator_wrapper.get(), 42);

}



TEST_F(GeneratorWrapperTest_312, NextDelegatesToGenerator_312) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(generator_wrapper.next());

}



TEST_F(GeneratorWrapperTest_312, NextReturnsFalseWhenGeneratorExhausted_312) {

    EXPECT_CALL(*mock_generator, next()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(generator_wrapper.next());

}



TEST_F(GeneratorWrapperTest_312, GetAndNextMultipleTimesConsistent_312) {

    EXPECT_CALL(*mock_generator, get())

        .WillOnce(::testing::Return(42))

        .WillOnce(::testing::Return(84));

    EXPECT_CALL(*mock_generator, next())

        .WillOnce(::testing::Return(true))

        .WillOnce(::testing::Return(false));



    EXPECT_EQ(generator_wrapper.get(), 42);

    EXPECT_TRUE(generator_wrapper.next());

    EXPECT_EQ(generator_wrapper.get(), 84);

    EXPECT_FALSE(generator_wrapper.next());

}



TEST_F(GeneratorWrapperTest_312, GetCalledWithoutNextThrowsNoException_312) {

    EXPECT_CALL(*mock_generator, get()).WillOnce(::testing::Return(42));

    EXPECT_NO_THROW(generator_wrapper.get());

}
