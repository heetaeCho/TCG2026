#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest_405 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if needed

    }



    void TearDown() override {

        // Teardown can be done here if needed

    }

};



TEST_F(OptionalTest_405, DefaultConstructorCreatesEmptyOptional_405) {

    Optional<int> opt;

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_405, ValueConstructorCreatesNonEmptyOptional_405) {

    Optional<int> opt(42);

    EXPECT_TRUE(opt.some());

    EXPECT_FALSE(opt.none());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_405, MoveConstructorCreatesNonEmptyOptional_405) {

    int value = 42;

    Optional<int> opt(std::move(value));

    EXPECT_TRUE(opt.some());

    EXPECT_FALSE(opt.none());

    EXPECT_EQ(*opt, 42);

}



TEST_F(OptionalTest_405, CopyAssignmentOperatorWorks_405) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    opt2 = opt1;

    EXPECT_TRUE(opt2.some());

    EXPECT_FALSE(opt2.none());

    EXPECT_EQ(*opt2, 42);

}



TEST_F(OptionalTest_405, MoveAssignmentOperatorWorks_405) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    opt2 = std::move(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_FALSE(opt2.none());

    EXPECT_EQ(*opt2, 42);

}



TEST_F(OptionalTest_405, ResetClearsOptional_405) {

    Optional<int> opt(42);

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_405, ValueOrReturnsStoredValueIfPresent_405) {

    Optional<int> opt(42);

    EXPECT_EQ(opt.valueOr(10), 42);

}



TEST_F(OptionalTest_405, ValueOrReturnsDefaultValueIfNotPresent_405) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(10), 10);

}



TEST_F(OptionalTest_405, BoolConversionOperatorWorks_405) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    EXPECT_TRUE(static_cast<bool>(opt1));

    EXPECT_FALSE(static_cast<bool>(opt2));

}



TEST_F(OptionalTest_405, NotOperatorWorks_405) {

    Optional<int> opt1(42);

    Optional<int> opt2;

    EXPECT_FALSE(!opt1);

    EXPECT_TRUE(!opt2);

}
