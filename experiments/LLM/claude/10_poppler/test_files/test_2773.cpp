#include <gtest/gtest.h>

// Include the header under test
#include "Movie.h"

// Test MovieTime default constructor initializes units_per_second to 0
TEST(MovieTimeTest_2773, DefaultConstructorInitializesUnitsPerSecondToZero_2773)
{
    MovieActivationParameters::MovieTime mt;
    EXPECT_EQ(mt.units_per_second, 0);
}

// Test that multiple MovieTime instances are independent
TEST(MovieTimeTest_2773, MultipleInstancesAreIndependent_2773)
{
    MovieActivationParameters::MovieTime mt1;
    MovieActivationParameters::MovieTime mt2;

    mt1.units_per_second = 30;
    mt1.units = 100;

    EXPECT_EQ(mt2.units_per_second, 0);
    EXPECT_EQ(mt1.units_per_second, 30);
    EXPECT_EQ(mt1.units, 100UL);
}

// Test that units field is accessible and writable
TEST(MovieTimeTest_2773, UnitsFieldIsAccessible_2773)
{
    MovieActivationParameters::MovieTime mt;
    mt.units = 12345UL;
    EXPECT_EQ(mt.units, 12345UL);
}

// Test that units_per_second field is writable after construction
TEST(MovieTimeTest_2773, UnitsPerSecondIsWritable_2773)
{
    MovieActivationParameters::MovieTime mt;
    EXPECT_EQ(mt.units_per_second, 0);
    mt.units_per_second = 24;
    EXPECT_EQ(mt.units_per_second, 24);
}

// Test boundary: large values for units
TEST(MovieTimeTest_2773, LargeUnitsValue_2773)
{
    MovieActivationParameters::MovieTime mt;
    mt.units = ULONG_MAX;
    EXPECT_EQ(mt.units, ULONG_MAX);
}

// Test boundary: negative units_per_second
TEST(MovieTimeTest_2773, NegativeUnitsPerSecond_2773)
{
    MovieActivationParameters::MovieTime mt;
    mt.units_per_second = -1;
    EXPECT_EQ(mt.units_per_second, -1);
}

// Test boundary: zero values
TEST(MovieTimeTest_2773, ZeroValues_2773)
{
    MovieActivationParameters::MovieTime mt;
    mt.units = 0;
    mt.units_per_second = 0;
    EXPECT_EQ(mt.units, 0UL);
    EXPECT_EQ(mt.units_per_second, 0);
}

// Test copy behavior
TEST(MovieTimeTest_2773, CopyBehavior_2773)
{
    MovieActivationParameters::MovieTime mt1;
    mt1.units = 500;
    mt1.units_per_second = 25;

    MovieActivationParameters::MovieTime mt2 = mt1;
    EXPECT_EQ(mt2.units, 500UL);
    EXPECT_EQ(mt2.units_per_second, 25);
}

// Test assignment behavior
TEST(MovieTimeTest_2773, AssignmentBehavior_2773)
{
    MovieActivationParameters::MovieTime mt1;
    mt1.units = 1000;
    mt1.units_per_second = 30;

    MovieActivationParameters::MovieTime mt2;
    mt2 = mt1;
    EXPECT_EQ(mt2.units, 1000UL);
    EXPECT_EQ(mt2.units_per_second, 30);
}

// Test MovieActivationParameters can be instantiated
TEST(MovieActivationParametersTest_2773, CanBeInstantiated_2773)
{
    MovieActivationParameters params;
    // Just verify it can be constructed without error
    SUCCEED();
}
