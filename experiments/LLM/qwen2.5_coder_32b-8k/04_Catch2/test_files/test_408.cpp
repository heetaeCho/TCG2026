#include <gtest/gtest.h>

#include "catch2/internal/catch_optional.hpp"



using Catch::Optional;



class OptionalTest_408 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(OptionalTest_408, Construct_Default_408) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_408, Construct_ValueCopy_408) {

    int value = 5;

    Optional<int> opt(value);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, value);

}



TEST_F(OptionalTest_408, Construct_ValueMove_408) {

    int value = 5;

    Optional<int> opt(std::move(value));

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 5);

}



TEST_F(OptionalTest_408, Construct_Copy_408) {

    Optional<int> original(10);

    Optional<int> copy(original);

    EXPECT_TRUE(copy.some());

    EXPECT_EQ(*copy, *original);

}



TEST_F(OptionalTest_408, Construct_Move_408) {

    Optional<int> original(20);

    Optional<int> moved(std::move(original));

    EXPECT_TRUE(moved.some());

    EXPECT_FALSE(original.some());

    EXPECT_EQ(*moved, 20);

}



TEST_F(OptionalTest_408, Assign_ValueCopy_408) {

    int value = 30;

    Optional<int> opt;

    opt = value;

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, value);

}



TEST_F(OptionalTest_408, Assign_ValueMove_408) {

    int value = 40;

    Optional<int> opt;

    opt = std::move(value);

    EXPECT_TRUE(opt.some());

    EXPECT_EQ(*opt, 40);

}



TEST_F(OptionalTest_408, Assign_Copy_408) {

    Optional<int> original(50);

    Optional<int> copy;

    copy = original;

    EXPECT_TRUE(copy.some());

    EXPECT_EQ(*copy, *original);

}



TEST_F(OptionalTest_408, Assign_Move_408) {

    Optional<int> original(60);

    Optional<int> moved;

    moved = std::move(original);

    EXPECT_TRUE(moved.some());

    EXPECT_FALSE(original.some());

    EXPECT_EQ(*moved, 60);

}



TEST_F(OptionalTest_408, Reset_EmptyOptional_408) {

    Optional<int> opt;

    opt.reset();

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_408, Reset_NonEmptyOptional_408) {

    Optional<int> opt(70);

    opt.reset();

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_408, OperatorStar_AccessValue_408) {

    Optional<int> opt(80);

    EXPECT_EQ(*opt, 80);

}



TEST_F(OptionalTest_408, OperatorArrow_CallMember_408) {

    struct TestStruct { int value; };

    Optional<TestStruct> opt(TestStruct{90});

    EXPECT_EQ(opt->value, 90);

}



TEST_F(OptionalTest_408, ValueOr_DefaultValue_408) {

    Optional<int> opt;

    EXPECT_EQ(opt.valueOr(100), 100);

}



TEST_F(OptionalTest_408, Some_CheckTrue_408) {

    Optional<int> opt(110);

    EXPECT_TRUE(opt.some());

}



TEST_F(OptionalTest_408, None_CheckTrue_408) {

    Optional<int> opt;

    EXPECT_TRUE(opt.none());

}



TEST_F(OptionalTest_408, OperatorBool_CheckFalse_408) {

    Optional<int> opt;

    EXPECT_FALSE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_408, OperatorBool_CheckTrue_408) {

    Optional<int> opt(120);

    EXPECT_TRUE(static_cast<bool>(opt));

}



TEST_F(OptionalTest_408, OperatorNot_CheckFalse_408) {

    Optional<int> opt(130);

    EXPECT_FALSE(!opt);

}



TEST_F(OptionalTest_408, OperatorNot_CheckTrue_408) {

    Optional<int> opt;

    EXPECT_TRUE(!opt);

}
