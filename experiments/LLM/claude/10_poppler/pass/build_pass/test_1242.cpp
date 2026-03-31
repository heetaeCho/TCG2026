#include <gtest/gtest.h>

// Include the necessary headers
// First, we need to define the Poppler namespace's ErrorStringType before including the header
// that uses it, since poppler-private.h expects it to exist.

// From the known dependency
namespace {
// We need the global ::ErrorStringType from Error.h
}

// Define the global ErrorStringType as seen in Error.h
enum class ErrorStringType { ErrorCodeString = 0, UserString = 1 };

// Define the Poppler namespace ErrorStringType (the Qt6 wrapper version)
namespace Poppler {
enum class ErrorStringType { ErrorCodeString = 0, UserString = 1 };
}

// Now include/define the function under test (from poppler-private.h)
namespace Poppler {
inline Poppler::ErrorStringType fromPopplerCore(::ErrorStringType type)
{
    switch (type) {
    case ::ErrorStringType::ErrorCodeString:
        return Poppler::ErrorStringType::ErrorCodeString;
    case ::ErrorStringType::UserString:
        return Poppler::ErrorStringType::UserString;
    }
    return Poppler::ErrorStringType::ErrorCodeString;
}
}

// Test fixture
class FromPopplerCoreTest_1242 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(FromPopplerCoreTest_1242, ErrorCodeStringMapsCorrectly_1242)
{
    auto result = Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString);
    EXPECT_EQ(result, Poppler::ErrorStringType::ErrorCodeString);
}

TEST_F(FromPopplerCoreTest_1242, UserStringMapsCorrectly_1242)
{
    auto result = Poppler::fromPopplerCore(::ErrorStringType::UserString);
    EXPECT_EQ(result, Poppler::ErrorStringType::UserString);
}

// Boundary / edge case: verify that the two enum values produce distinct results
TEST_F(FromPopplerCoreTest_1242, DifferentInputsProduceDifferentOutputs_1242)
{
    auto resultError = Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString);
    auto resultUser = Poppler::fromPopplerCore(::ErrorStringType::UserString);
    EXPECT_NE(resultError, resultUser);
}

// Exceptional case: pass an invalid enum value (not ErrorCodeString or UserString)
// The default branch should return ErrorCodeString
TEST_F(FromPopplerCoreTest_1242, InvalidEnumValueReturnsErrorCodeString_1242)
{
    // Cast an integer that doesn't correspond to any valid enum value
    auto result = Poppler::fromPopplerCore(static_cast<::ErrorStringType>(42));
    EXPECT_EQ(result, Poppler::ErrorStringType::ErrorCodeString);
}

TEST_F(FromPopplerCoreTest_1242, AnotherInvalidEnumValueReturnsErrorCodeString_1242)
{
    auto result = Poppler::fromPopplerCore(static_cast<::ErrorStringType>(-1));
    EXPECT_EQ(result, Poppler::ErrorStringType::ErrorCodeString);
}

// Verify the numeric values of the returned enum match expectations
TEST_F(FromPopplerCoreTest_1242, ErrorCodeStringHasValueZero_1242)
{
    auto result = Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString);
    EXPECT_EQ(static_cast<int>(result), 0);
}

TEST_F(FromPopplerCoreTest_1242, UserStringHasValueOne_1242)
{
    auto result = Poppler::fromPopplerCore(::ErrorStringType::UserString);
    EXPECT_EQ(static_cast<int>(result), 1);
}

// Test consistency: calling the function multiple times with the same input yields the same result
TEST_F(FromPopplerCoreTest_1242, ConsistentResultsForErrorCodeString_1242)
{
    auto result1 = Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString);
    auto result2 = Poppler::fromPopplerCore(::ErrorStringType::ErrorCodeString);
    EXPECT_EQ(result1, result2);
}

TEST_F(FromPopplerCoreTest_1242, ConsistentResultsForUserString_1242)
{
    auto result1 = Poppler::fromPopplerCore(::ErrorStringType::UserString);
    auto result2 = Poppler::fromPopplerCore(::ErrorStringType::UserString);
    EXPECT_EQ(result1, result2);
}
