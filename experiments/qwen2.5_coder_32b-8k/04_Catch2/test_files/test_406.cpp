#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



class OptionalTest : public ::testing::Test {

protected:

    using TestType = int;

};



TEST_F(OptionalTest_406, DefaultConstructorInitializesEmpty_406) {

    Optional<TestType> opt;

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_406, ValueConstructorInitializesWithValue_406) {

    TestType value = 42;

    Optional<TestType> opt(value);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, value);

}



TEST_F(OptionalTest_406, MoveConstructorTransfersValue_406) {

    TestType value = 42;

    Optional<TestType> opt1(value);

    Optional<TestType> opt2(std::move(opt1));

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, value);

}



TEST_F(OptionalTest_406, CopyConstructorCopiesValue_406) {

    TestType value = 42;

    Optional<TestType> opt1(value);

    Optional<TestType> opt2(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, value);

}



TEST_F(OptionalTest_406, CopyAssignmentCopiesValue_406) {

    TestType value = 42;

    Optional<TestType> opt1(value);

    Optional<TestType> opt2;

    opt2 = opt1;

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, value);

}



TEST_F(OptionalTest_406, MoveAssignmentTransfersValue_406) {

    TestType value = 42;

    Optional<TestType> opt1(value);

    Optional<TestType> opt2;

    opt2 = std::move(opt1);

    EXPECT_TRUE(opt2.some());

    EXPECT_EQ(*opt2, value);

}



TEST_F(OptionalTest_406, ResetClearsValue_406) {

    TestType value = 42;

    Optional<TestType> opt(value);

    opt.reset();

    EXPECT_FALSE(opt.some());

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_406, ValueOrReturnsDefaultValueWhenEmpty_406) {

    TestType defaultValue = 99;

    Optional<TestType> opt;

    EXPECT_EQ(opt.valueOr(defaultValue), defaultValue);

}



TEST_F(OptionalTest_406, ValueOrReturnsStoredValueWhenNotEmpty_406) {

    TestType value = 42;

    Optional<TestType> opt(value);

    EXPECT_EQ(opt.valueOr(99), value);

}



TEST_F(OptionalTest_406, BoolConversionReflectsPresenceOfValue_406) {

    Optional<TestType> emptyOpt;

    Optional<TestType> nonEmptyOpt(42);



    EXPECT_FALSE(static_cast<bool>(emptyOpt));

    EXPECT_TRUE(static_cast<bool>(nonEmptyOpt));

}



TEST_F(OptionalTest_406, DereferenceOperatorsWorkWhenNotEmpty_406) {

    TestType value = 42;

    Optional<TestType> opt(value);

    EXPECT_EQ(*opt, value);

    EXPECT_EQ(opt->operator=(value), value);

}
