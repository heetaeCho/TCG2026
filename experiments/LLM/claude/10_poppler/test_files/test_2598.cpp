#include <gtest/gtest.h>
#include <cstring>

// Declaration of the function under test
extern "C" {
const char *poppler_get_version(void);
}

class PopplerGetVersionTest_2598 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerGetVersionTest_2598, ReturnsNonNull_2598)
{
    const char *version = poppler_get_version();
    ASSERT_NE(version, nullptr);
}

TEST_F(PopplerGetVersionTest_2598, ReturnsExpectedVersionString_2598)
{
    const char *version = poppler_get_version();
    EXPECT_STREQ(version, "26.01.90");
}

TEST_F(PopplerGetVersionTest_2598, ReturnedStringIsNotEmpty_2598)
{
    const char *version = poppler_get_version();
    EXPECT_GT(std::strlen(version), 0u);
}

TEST_F(PopplerGetVersionTest_2598, ConsecutiveCallsReturnSamePointer_2598)
{
    const char *version1 = poppler_get_version();
    const char *version2 = poppler_get_version();
    EXPECT_EQ(version1, version2);
}

TEST_F(PopplerGetVersionTest_2598, VersionStringContainsDots_2598)
{
    const char *version = poppler_get_version();
    EXPECT_NE(std::strchr(version, '.'), nullptr);
}

TEST_F(PopplerGetVersionTest_2598, VersionStringHasExpectedLength_2598)
{
    const char *version = poppler_get_version();
    EXPECT_EQ(std::strlen(version), 8u);
}

TEST_F(PopplerGetVersionTest_2598, VersionStringIsNullTerminated_2598)
{
    const char *version = poppler_get_version();
    size_t len = std::strlen(version);
    EXPECT_EQ(version[len], '\0');
}

TEST_F(PopplerGetVersionTest_2598, VersionStringMatchesMajorMinorPatchFormat_2598)
{
    const char *version = poppler_get_version();
    int major = 0, minor = 0, patch = 0;
    int parsed = sscanf(version, "%d.%d.%d", &major, &minor, &patch);
    EXPECT_EQ(parsed, 3);
    EXPECT_EQ(major, 26);
    EXPECT_EQ(minor, 1);
    EXPECT_EQ(patch, 90);
}
