#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_generatortracker.hpp"



using namespace Catch::Generators;



class MockGeneratorUntypedBase : public GeneratorUntypedBase {

public:

    MOCK_METHOD(bool, next, (), (override));

    MOCK_METHOD(const std::string, stringifyImpl, (), (const, override));

};



class GeneratorUntypedBaseTest_58 : public ::testing::Test {

protected:

    MockGeneratorUntypedBase mock_generator;

};



TEST_F(GeneratorUntypedBaseTest_58, countedNext_ReturnsTrueAndUpdatesIndex_58) {

    EXPECT_CALL(mock_generator, next()).WillOnce(::testing::Return(true));

    ASSERT_TRUE(mock_generator.countedNext());

    EXPECT_EQ(mock_generator.currentElementIndex(), 1);

}



TEST_F(GeneratorUntypedBaseTest_58, countedNext_ReturnsFalseDoesNotUpdateIndex_58) {

    EXPECT_CALL(mock_generator, next()).WillOnce(::testing::Return(false));

    ASSERT_FALSE(mock_generator.countedNext());

    EXPECT_EQ(mock_generator.currentElementIndex(), 0);

}



TEST_F(GeneratorUntypedBaseTest_58, countedNext_CallsStringifyImplAfterNext_58) {

    EXPECT_CALL(mock_generator, next()).WillOnce(::testing::Return(true));

    EXPECT_CALL(mock_generator, stringifyImpl()).Times(1);

    mock_generator.countedNext();

}
