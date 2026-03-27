#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;



class TakeGeneratorTest_1107 : public ::testing::Test {

protected:

    using T = int;

    GeneratorWrapper<T> generatorWrapper;

    std::unique_ptr<TakeGenerator<T>> takeGenerator;



    void SetUp() override {

        // Initialize the GeneratorWrapper with some values

        std::vector<int> initialValues = {1, 2, 3, 4, 5};

        generatorWrapper = GeneratorWrapper<T>([initialValues]() mutable -> T* {

            static size_t index = 0;

            if (index < initialValues.size()) {

                return &initialValues[index++];

            }

            return nullptr;

        });

    }



    void setupTakeGenerator(size_t target) {

        takeGenerator = std::make_unique<TakeGenerator<T>>(target, CATCH_MOVE(generatorWrapper));

    }

};



TEST_F(TakeGeneratorTest_1107, GetReturnsCorrectValue_1107) {

    setupTakeGenerator(3);

    EXPECT_EQ(takeGenerator->get(), 1);

    takeGenerator->next();

    EXPECT_EQ(takeGenerator->get(), 2);

}



TEST_F(TakeGeneratorTest_1107, NextAdvancesToNextValue_1107) {

    setupTakeGenerator(3);

    EXPECT_TRUE(takeGenerator->next());

    EXPECT_EQ(takeGenerator->get(), 2);

    EXPECT_TRUE(takeGenerator->next());

    EXPECT_EQ(takeGenerator->get(), 3);

}



TEST_F(TakeGeneratorTest_1107, NextReturnsFalseAfterTargetReached_1107) {

    setupTakeGenerator(3);

    takeGenerator->next();

    takeGenerator->next();

    takeGenerator->next();

    EXPECT_FALSE(takeGenerator->next());

}



TEST_F(TakeGeneratorTest_1107, GetThrowsOnExceedingTarget_1107) {

    setupTakeGenerator(2);

    takeGenerator->next();

    takeGenerator->next();

    EXPECT_THROW(takeGenerator->get(), std::runtime_error);

}



TEST_F(TakeGeneratorTest_1107, BoundaryConditionZeroTarget_1107) {

    EXPECT_THROW(setupTakeGenerator(0), std::assertion_failure);

}



TEST_F(TakeGeneratorTest_1107, BoundaryConditionExactTargetMatch_1107) {

    setupTakeGenerator(5);

    for (size_t i = 0; i < 5; ++i) {

        EXPECT_TRUE(takeGenerator->next());

        EXPECT_EQ(takeGenerator->get(), i + 1);

    }

    EXPECT_FALSE(takeGenerator->next());

}



TEST_F(TakeGeneratorTest_1107, BoundaryConditionTargetGreaterThanInitialValues_1107) {

    setupTakeGenerator(10);

    for (size_t i = 0; i < 5; ++i) {

        EXPECT_TRUE(takeGenerator->next());

        EXPECT_EQ(takeGenerator->get(), i + 1);

    }

    EXPECT_FALSE(takeGenerator->next());

}
