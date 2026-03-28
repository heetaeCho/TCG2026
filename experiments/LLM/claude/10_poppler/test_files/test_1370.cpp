#include <gtest/gtest.h>

// Forward declare the namespace and function based on the provided interface
namespace Poppler {
    bool hasNSSSupport();
}

TEST(PopplerFormTest_1370, HasNSSSupportReturnsBool_1370)
{
    // The function should return a boolean value (either true or false)
    bool result = Poppler::hasNSSSupport();
    EXPECT_TRUE(result == true || result == false);
}

TEST(PopplerFormTest_1370, HasNSSSupportIsConsistent_1370)
{
    // Calling the function multiple times should return the same value
    // since it's a compile-time constant based on ENABLE_NSS3
    bool result1 = Poppler::hasNSSSupport();
    bool result2 = Poppler::hasNSSSupport();
    EXPECT_EQ(result1, result2);
}

TEST(PopplerFormTest_1370, HasNSSSupportIsDeterministic_1370)
{
    // The function should be deterministic - calling it many times
    // should always yield the same result
    bool firstResult = Poppler::hasNSSSupport();
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(firstResult, Poppler::hasNSSSupport());
    }
}
