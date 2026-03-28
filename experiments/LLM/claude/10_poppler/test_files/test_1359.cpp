#include <gtest/gtest.h>

// Forward declare the namespace and function as it appears in the interface
namespace Poppler {
    bool isCmsAvailable();
}

TEST(PopplerDocumentTest_1359, IsCmsAvailableReturnsBool_1359)
{
    // The function should return either true or false (a valid bool)
    bool result = Poppler::isCmsAvailable();
    EXPECT_TRUE(result == true || result == false);
}

TEST(PopplerDocumentTest_1359, IsCmsAvailableConsistentResult_1359)
{
    // Calling the function multiple times should return the same result
    // since it's compile-time determined
    bool result1 = Poppler::isCmsAvailable();
    bool result2 = Poppler::isCmsAvailable();
    EXPECT_EQ(result1, result2);
}

TEST(PopplerDocumentTest_1359, IsCmsAvailableIdempotent_1359)
{
    // Verify the function is idempotent - calling it many times yields same result
    bool firstResult = Poppler::isCmsAvailable();
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(firstResult, Poppler::isCmsAvailable());
    }
}

#ifdef USE_CMS
TEST(PopplerDocumentTest_1359, IsCmsAvailableWhenCmsEnabled_1359)
{
    // When USE_CMS is defined, isCmsAvailable should return true
    EXPECT_TRUE(Poppler::isCmsAvailable());
}
#else
TEST(PopplerDocumentTest_1359, IsCmsAvailableWhenCmsDisabled_1359)
{
    // When USE_CMS is not defined, isCmsAvailable should return false
    EXPECT_FALSE(Poppler::isCmsAvailable());
}
#endif
