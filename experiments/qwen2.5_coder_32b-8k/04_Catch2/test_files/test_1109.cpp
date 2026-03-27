#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;



// Mock GeneratorWrapper for testing RepeatGenerator

template <typename T>

class MockGeneratorWrapper : public IGenerator<T> {

public:

    MOCK_METHOD(T const&, get, (), (const, override));

    MOCK_METHOD(bool, next, (), (override));

};



TEST(RepeatGeneratorTest_1109, SingleRepeat_ReturnsSingleValue_1109) {

    MockGeneratorWrapper<int> mockGen;

    EXPECT_CALL(mockGen, get()).WillOnce(testing::Return(42));

    EXPECT_CALL(mockGen, next()).WillOnce(testing::Return(false));



    RepeatGenerator<int> repeatGen(1, GeneratorWrapper<int>(mockGen));



    ASSERT_TRUE(repeatGen.next());

    EXPECT_EQ(repeatGen.get(), 42);

    EXPECT_FALSE(repeatGen.next());

}



TEST(RepeatGeneratorTest_1109, MultipleRepeats_ReturnsRepeatedValues_1109) {

    MockGeneratorWrapper<int> mockGen;

    EXPECT_CALL(mockGen, get()).WillOnce(testing::Return(42));

    EXPECT_CALL(mockGen, next()).WillOnce(testing::Return(false));



    RepeatGenerator<int> repeatGen(3, GeneratorWrapper<int>(mockGen));



    for (int i = 0; i < 3; ++i) {

        ASSERT_TRUE(repeatGen.next());

        EXPECT_EQ(repeatGen.get(), 42);

    }

    EXPECT_FALSE(repeatGen.next());

}



TEST(RepeatGeneratorTest_1109, ZeroRepeats_ConstructorThrows_1109) {

    MockGeneratorWrapper<int> mockGen;

    EXPECT_THROW({

        RepeatGenerator<int> repeatGen(0, GeneratorWrapper<int>(mockGen));

    }, std::logic_error);

}



TEST(RepeatGeneratorTest_1109, UnderlyingGeneratorFalse_ReturnsSingleValue_1109) {

    MockGeneratorWrapper<int> mockGen;

    EXPECT_CALL(mockGen, get()).WillOnce(testing::Return(42));

    EXPECT_CALL(mockGen, next()).WillOnce(testing::Return(false));



    RepeatGenerator<int> repeatGen(3, GeneratorWrapper<int>(mockGen));



    for (int i = 0; i < 1; ++i) {

        ASSERT_TRUE(repeatGen.next());

        EXPECT_EQ(repeatGen.get(), 42);

    }

    EXPECT_FALSE(repeatGen.next());

}



TEST(RepeatGeneratorTest_1109, UnderlyingGeneratorTrue_ReturnsMultipleValues_1109) {

    MockGeneratorWrapper<int> mockGen;

    EXPECT_CALL(mockGen, get())

        .WillOnce(testing::Return(42))

        .WillOnce(testing::Return(84));

    EXPECT_CALL(mockGen, next())

        .WillOnce(testing::Return(true))

        .WillOnce(testing::Return(false));



    RepeatGenerator<int> repeatGen(3, GeneratorWrapper<int>(mockGen));



    ASSERT_TRUE(repeatGen.next());

    EXPECT_EQ(repeatGen.get(), 42);

    ASSERT_TRUE(repeatGen.next());

    EXPECT_EQ(repeatGen.get(), 84);

    ASSERT_TRUE(repeatGen.next());

    EXPECT_EQ(repeatGen.get(), 84); // Repeats the last value since underlying generator is exhausted

    EXPECT_FALSE(repeatGen.next());

}
