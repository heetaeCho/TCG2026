#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"



using namespace Catch::Generators;



class GeneratorUntypedBaseTest_57 : public ::testing::Test {

protected:

    GeneratorUntypedBase generator;

};



TEST_F(GeneratorUntypedBaseTest_57, InitialCurrentElementIndexIsZero_57) {

    EXPECT_EQ(generator.currentElementIndex(), 0);

}



TEST_F(GeneratorUntypedBaseTest_57, CountedNextIncrementsCurrentElementIndex_57) {

    // Assuming countedNext() returns true to simulate successful increment

    generator.countedNext();

    EXPECT_EQ(generator.currentElementIndex(), 1);

}



TEST_F(GeneratorUntypedBaseTest_57, CountedNextReturnsFalseDoesNotIncrementIndex_57) {

    // Mocking the behavior of next() to return false

    EXPECT_CALL(*reinterpret_cast<testing::NiceMock<GeneratorUntypedBase>*>(&generator), next())

        .WillOnce(testing::Return(false));



    bool result = generator.countedNext();

    EXPECT_FALSE(result);

    EXPECT_EQ(generator.currentElementIndex(), 0);

}



TEST_F(GeneratorUntypedBaseTest_57, CurrentElementAsStringReturnsEmptyStringRefInitially_57) {

    Catch::StringRef ref = generator.currentElementAsString();

    EXPECT_TRUE(ref.empty());

}
