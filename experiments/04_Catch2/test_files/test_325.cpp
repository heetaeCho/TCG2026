#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_generators.hpp"



// Assuming there's a class or interface we need to test that uses makeGenerators

// Since no specific class is provided, I'll create a mock class that uses makeGenerators



class GeneratorUser {

public:

    virtual ~GeneratorUser() = default;

    virtual void processGenerators(int val) = 0;

};



class MockGeneratorUser : public GeneratorUser {

public:

    MOCK_METHOD(void, processGenerators, (int val), (override));

};



// Test fixture

class CatchGeneratorsTest_325 : public ::testing::Test {

protected:

    MockGeneratorUser mockGeneratorUser;

};



// Test normal operation with a single generator

TEST_F(CatchGeneratorsTest_325, SingleValueProcessed_325) {

    EXPECT_CALL(mockGeneratorUser, processGenerators(42));

    Catch::Generators::makeGenerators(42);

}



// Test normal operation with multiple generators

TEST_F(CatchGeneratorsTest_325, MultipleValuesProcessed_325) {

    EXPECT_CALL(mockGeneratorUser, processGenerators(1));

    EXPECT_CALL(mockGeneratorUser, processGenerators(2));

    EXPECT_CALL(mockGeneratorUser, processGenerators(3));

    Catch::Generators::makeGenerators(1, 2, 3);

}



// Test boundary condition with zero generators

TEST_F(CatchGeneratorsTest_325, ZeroValuesProcessed_325) {

    // No calls to processGenerators expected

    Catch::Generators::makeGenerators();

}



// Test boundary condition with a single negative value

TEST_F(CatchGeneratorsTest_325, NegativeValueProcessed_325) {

    EXPECT_CALL(mockGeneratorUser, processGenerators(-1));

    Catch::Generators::makeGenerators(-1);

}



// Test boundary condition with multiple values including negative and zero

TEST_F(CatchGeneratorsTest_325, MixedValuesProcessed_325) {

    EXPECT_CALL(mockGeneratorUser, processGenerators(0));

    EXPECT_CALL(mockGeneratorUser, processGenerators(-5));

    EXPECT_CALL(mockGeneratorUser, processGenerators(10));

    Catch::Generators::makeGenerators(0, -5, 10);

}

```


