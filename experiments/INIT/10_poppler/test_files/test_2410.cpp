// File: poppler-get-nss-dir-test-2410.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

extern "C" {
// Function under test (implemented in poppler-form-field.cc)
char *poppler_get_nss_dir(void);
}

namespace {

class PopplerGetNssDirTest_2410 : public ::testing::Test {};

}  // namespace

#if defined(ENABLE_NSS3) && ENABLE_NSS3

TEST_F(PopplerGetNssDirTest_2410, ReturnsAllocatedStringWhenNssEnabled_2410)
{
    char *dir = poppler_get_nss_dir();
    ASSERT_NE(dir, nullptr);

    // Must be a valid NUL-terminated C string (may be empty; don't assume content).
    const size_t len = std::strlen(dir);
    EXPECT_EQ(dir[len], '\0');

    g_free(dir);
}

TEST_F(PopplerGetNssDirTest_2410, MultipleCallsReturnIndependentBuffers_2410)
{
    char *dir1 = poppler_get_nss_dir();
    char *dir2 = poppler_get_nss_dir();

    ASSERT_NE(dir1, nullptr);
    ASSERT_NE(dir2, nullptr);

    // Since neither has been freed yet, independent allocations should not alias.
    EXPECT_NE(dir1, dir2);

    // Content should be stable across calls (but do not assume any specific value).
    EXPECT_STREQ(dir1, dir2);

    g_free(dir1);
    g_free(dir2);
}

TEST_F(PopplerGetNssDirTest_2410, FreeingReturnedStringIsSafe_2410)
{
    char *dir = poppler_get_nss_dir();
    ASSERT_NE(dir, nullptr);

    // Should be safe to free what we got.
    g_free(dir);

    // And subsequent calls should still work.
    char *dir2 = poppler_get_nss_dir();
    ASSERT_NE(dir2, nullptr);
    g_free(dir2);
}

#else  // !(defined(ENABLE_NSS3) && ENABLE_NSS3)

TEST_F(PopplerGetNssDirTest_2410, ReturnsNullWhenNssDisabled_2410)
{
    // When NSS3 support is not enabled at build time, the function returns nullptr.
    EXPECT_EQ(poppler_get_nss_dir(), nullptr);
}

TEST_F(PopplerGetNssDirTest_2410, MultipleCallsStillReturnNullWhenNssDisabled_2410)
{
    EXPECT_EQ(poppler_get_nss_dir(), nullptr);
    EXPECT_EQ(poppler_get_nss_dir(), nullptr);
}

#endif