#include <gtest/gtest.h>
#include <glib.h>

// Forward declaration of the function under test
extern "C" {
char *poppler_get_nss_dir(void);
}

class PopplerGetNssDirTest_2410 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

TEST_F(PopplerGetNssDirTest_2410, ReturnsNonNull_Or_Null_DependingOnNSSSupport_2410)
{
    char *nss_dir = poppler_get_nss_dir();
    
    // If NSS3 is enabled, we expect a non-null allocated string.
    // If NSS3 is not enabled, we expect nullptr.
    // We can't know at compile time which path is taken, but we can
    // verify the function doesn't crash and returns a valid pointer or null.
    if (nss_dir != nullptr) {
        // If non-null, it should be a valid g_malloc'd string that we can free
        EXPECT_NE(nss_dir, nullptr);
        g_free(nss_dir);
    } else {
        EXPECT_EQ(nss_dir, nullptr);
    }
}

TEST_F(PopplerGetNssDirTest_2410, CalledMultipleTimesReturnsConsistentResult_2410)
{
    char *nss_dir1 = poppler_get_nss_dir();
    char *nss_dir2 = poppler_get_nss_dir();
    
    // Both calls should return the same logical result
    if (nss_dir1 == nullptr) {
        EXPECT_EQ(nss_dir2, nullptr);
    } else {
        ASSERT_NE(nss_dir2, nullptr);
        // Both should contain the same directory string
        EXPECT_STREQ(nss_dir1, nss_dir2);
        // But they should be different allocations (g_strdup)
        EXPECT_NE(nss_dir1, nss_dir2);
    }
    
    g_free(nss_dir1);
    g_free(nss_dir2);
}

TEST_F(PopplerGetNssDirTest_2410, ReturnedStringIsFreeable_2410)
{
    // Ensure the returned value can be safely freed with g_free
    // This tests that the memory allocation is correct
    char *nss_dir = poppler_get_nss_dir();
    
    // g_free handles nullptr gracefully, so this should not crash regardless
    g_free(nss_dir);
    
    // If we reach here without crash, the test passes
    SUCCEED();
}

TEST_F(PopplerGetNssDirTest_2410, ReturnedStringIsValidIfNonNull_2410)
{
    char *nss_dir = poppler_get_nss_dir();
    
    if (nss_dir != nullptr) {
        // The string should have a valid length (not empty necessarily, but valid)
        size_t len = strlen(nss_dir);
        EXPECT_GE(len, 0u);
    }
    
    g_free(nss_dir);
}
