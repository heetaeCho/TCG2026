#include <gtest/gtest.h>

#include "catch2/generators/catch_generators.hpp"



// Assuming GeneratorWrapper has a template parameter T and IGenerator<T> is properly defined somewhere.

class MockIGenerator : public Catch::Generators::IGenerator<int> {

public:

    MOCK_METHOD(bool, countedNext, (), (override));

    MOCK_METHOD(int const&, get, (), (const, override));

};



class GeneratorWrapperTest_313 : public ::testing::Test {

protected:

    std::shared_ptr<MockIGenerator> mock_generator;

    Catch::Generators::GeneratorWrapper<int> generator_wrapper;



    GeneratorWrapperTest_313() : 

        mock_generator(std::make_shared<MockIGenerator>()),

        generator_wrapper(mock_generator) {}

};



TEST_F(GeneratorWrapperTest_313, NextReturnsTrueWhenMoreElementsExist_313) {

    EXPECT_CALL(*mock_generator, countedNext()).WillOnce(::testing::Return(true));

    bool result = generator_wrapper.next();

    EXPECT_TRUE(result);

}



TEST_F(GeneratorWrapperTest_313, NextReturnsFalseWhenNoMoreElementsExist_313) {

    EXPECT_CALL(*mock_generator, countedNext()).WillOnce(::testing::Return(false));

    bool result = generator_wrapper.next();

    EXPECT_FALSE(result);

}



TEST_F(GeneratorWrapperTest_313, GetInvokesUnderlyingGet_313) {

    const int expected_value = 42;

    EXPECT_CALL(*mock_generator, get()).WillOnce(::testing::ReturnRef(expected_value));

    EXPECT_CALL(*mock_generator, countedNext()).WillOnce(::testing::Return(true)).WillOnce(::testing::Return(false));



    generator_wrapper.next();

    int result = generator_wrapper.get();



    EXPECT_EQ(result, expected_value);

}



TEST_F(GeneratorWrapperTest_313, GetCalledWithoutNextThrowsException_313) {

    // Assuming that calling get() before next() returns true should throw an exception.

    EXPECT_THROW(generator_wrapper.get(), std::logic_error); 

}
