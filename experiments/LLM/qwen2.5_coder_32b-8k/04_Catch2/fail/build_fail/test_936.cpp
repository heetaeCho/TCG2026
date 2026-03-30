#include <gtest/gtest.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Generators;



class RangeGeneratorTest_936 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(RangeGeneratorTest_936, PositiveStepNextReturnsTrueUntilEnd_936) {

    RangeGenerator<int> gen(0, 5, 1);

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(gen.next());

        EXPECT_EQ(i, gen.get());

    }

    EXPECT_FALSE(gen.next()); // Should stop at 4

}



TEST_F(RangeGeneratorTest_936, NegativeStepNextReturnsTrueUntilEnd_936) {

    RangeGenerator<int> gen(5, 0, -1);

    for (int i = 5; i > 0; --i) {

        EXPECT_TRUE(gen.next());

        EXPECT_EQ(i-1, gen.get());

    }

    EXPECT_FALSE(gen.next()); // Should stop at 1

}



TEST_F(RangeGeneratorTest_936, PositiveStepWithCustomStartEnd_936) {

    RangeGenerator<int> gen(2, 8, 2);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(2, gen.get());

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(4, gen.get());

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(6, gen.get());

    EXPECT_FALSE(gen.next()); // Should stop at 6

}



TEST_F(RangeGeneratorTest_936, NegativeStepWithCustomStartEnd_936) {

    RangeGenerator<int> gen(8, 2, -2);

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(8, gen.get());

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(6, gen.get());

    EXPECT_TRUE(gen.next());

    EXPECT_EQ(4, gen.get());

    EXPECT_FALSE(gen.next()); // Should stop at 4

}



TEST_F(RangeGeneratorTest_936, SingleElementRange_936) {

    RangeGenerator<int> gen(5, 5);

    EXPECT_FALSE(gen.next()); // No elements to iterate over

}



TEST_F(RangeGeneratorTest_936, DefaultStepPositiveRange_936) {

    RangeGenerator<int> gen(0, 5);

    for (int i = 0; i < 5; ++i) {

        EXPECT_TRUE(gen.next());

        EXPECT_EQ(i, gen.get());

    }

    EXPECT_FALSE(gen.next()); // Should stop at 4

}



TEST_F(RangeGeneratorTest_936, DefaultStepNegativeRange_936) {

    RangeGenerator<int> gen(5, 0);

    for (int i = 5; i > 0; --i) {

        EXPECT_TRUE(gen.next());

        EXPECT_EQ(i-1, gen.get());

    }

    EXPECT_FALSE(gen.next()); // Should stop at 1

}



TEST_F(RangeGeneratorTest_936, ZeroStepShouldNotProgress_936) {

    RangeGenerator<int> gen(0, 5, 0);

    EXPECT_FALSE(gen.next()); // Should not progress with zero step

}
