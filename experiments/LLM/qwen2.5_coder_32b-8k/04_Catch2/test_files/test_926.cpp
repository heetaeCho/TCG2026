#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Generators;



class RepeatGeneratorTest_926 : public ::testing::Test {

protected:

    using MockGenerator = StrictMock<MockIGenerator<int>>;

    MockGenerator mock_generator;

    std::unique_ptr<RepeatGenerator<int>> repeat_generator;



    void SetUp() override {

        ON_CALL(mock_generator, get()).WillByDefault(testing::Return(42));

        ON_CALL(mock_generator, next()).WillByDefault(testing::Return(true));

    }



    RepeatGeneratorTest_926(size_t repeats)

        : repeat_generator(std::make_unique<RepeatGenerator<int>>(repeats, GeneratorWrapper<int>(mock_generator))) {}

};



class RepeatGenerator0RepeatsTest_926 : public RepeatGeneratorTest_926 {

public:

    RepeatGenerator0RepeatsTest_926() : RepeatGeneratorTest_926(0) {}

};



class RepeatGenerator1RepeatTest_926 : public RepeatGeneratorTest_926 {

public:

    RepeatGenerator1RepeatTest_926() : RepeatGeneratorTest_926(1) {}

};



class RepeatGeneratorMultipleRepeatsTest_926 : public RepeatGeneratorTest_926 {

public:

    RepeatGeneratorMultipleRepeatsTest_926() : RepeatGeneratorTest_926(3) {}

};



TEST_F(RepeatGenerator0RepeatsTest_926, GetAlwaysReturnsInitialValue_926) {

    EXPECT_EQ(repeat_generator->get(), 42);

}



TEST_F(RepeatGenerator0RepeatsTest_926, NextAlwaysReturnsTrue_926) {

    EXPECT_TRUE(repeat_generator->next());

}



TEST_F(RepeatGenerator1RepeatTest_926, GetReturnsInitialValueOnce_926) {

    EXPECT_EQ(repeat_generator->get(), 42);

}



TEST_F(RepeatGenerator1RepeatTest_926, NextReturnsTrueThenFalse_926) {

    EXPECT_TRUE(repeat_generator->next());

    EXPECT_FALSE(repeat_generator->next());

}



TEST_F(RepeatGeneratorMultipleRepeatsTest_926, GetReturnsInitialValueForAllRepeats_926) {

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_EQ(repeat_generator->get(), 42);

        repeat_generator->next();

    }

}



TEST_F(RepeatGeneratorMultipleRepeatsTest_926, NextReturnsTrueForAllButLastRepeat_926) {

    for (size_t i = 0; i < 2; ++i) {

        EXPECT_TRUE(repeat_generator->next());

    }

    EXPECT_FALSE(repeat_generator->next());

}
