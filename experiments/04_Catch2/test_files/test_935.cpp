#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;

using ::testing::Return;



class RangeGeneratorTest_935 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }

};



TEST_F(RangeGeneratorTest_935, DefaultStepPositiveRange_935) {

    RangeGenerator<int> range(0, 5);

    EXPECT_EQ(range.get(), 0);

    for (int i = 1; i < 5; ++i) {

        ASSERT_TRUE(range.next());

        EXPECT_EQ(range.get(), i);

    }

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, DefaultStepNegativeRange_935) {

    RangeGenerator<int> range(5, 0);

    EXPECT_EQ(range.get(), 5);

    for (int i = 4; i > 0; --i) {

        ASSERT_TRUE(range.next());

        EXPECT_EQ(range.get(), i);

    }

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, CustomStepPositiveRange_935) {

    RangeGenerator<int> range(0, 10, 2);

    EXPECT_EQ(range.get(), 0);

    for (int i = 2; i < 10; i += 2) {

        ASSERT_TRUE(range.next());

        EXPECT_EQ(range.get(), i);

    }

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, CustomStepNegativeRange_935) {

    RangeGenerator<int> range(10, 0, -2);

    EXPECT_EQ(range.get(), 10);

    for (int i = 8; i > 0; i -= 2) {

        ASSERT_TRUE(range.next());

        EXPECT_EQ(range.get(), i);

    }

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, SingleElementRange_935) {

    RangeGenerator<int> range(5, 5);

    EXPECT_EQ(range.get(), 5);

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, EmptyRangePositive_935) {

    RangeGenerator<int> range(5, 4);

    EXPECT_FALSE(range.next());

}



TEST_F(RangeGeneratorTest_935, EmptyRangeNegative_935) {

    RangeGenerator<int> range(-5, -6);

    EXPECT_FALSE(range.next());

}
