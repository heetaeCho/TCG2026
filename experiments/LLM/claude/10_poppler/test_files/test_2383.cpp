#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-form-field.h"
}

// We need the poppler glib headers. Based on the interface, we use the public API.
// The functions we need to test: poppler_signing_data_get_reason
// We also need: poppler_signing_data_new, poppler_signing_data_free, poppler_signing_data_set_reason

class PopplerSigningDataGetReasonTest_2383 : public ::testing::Test {
protected:
    void SetUp() override {
        signing_data = poppler_signing_data_new();
    }

    void TearDown() override {
        if (signing_data) {
            poppler_signing_data_free(signing_data);
            signing_data = nullptr;
        }
    }

    PopplerSigningData *signing_data = nullptr;
};

// Test that a newly created signing data returns nullptr for reason
TEST_F(PopplerSigningDataGetReasonTest_2383, NewSigningDataReturnsNullReason_2383)
{
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    EXPECT_EQ(reason, nullptr);
}

// Test that after setting a reason, get_reason returns the same string
TEST_F(PopplerSigningDataGetReasonTest_2383, SetAndGetReason_2383)
{
    poppler_signing_data_set_reason(signing_data, "Test Reason");
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "Test Reason");
}

// Test that passing nullptr returns nullptr (with g_return_val_if_fail)
TEST_F(PopplerSigningDataGetReasonTest_2383, NullSigningDataReturnsNull_2383)
{
    const gchar *reason = poppler_signing_data_get_reason(nullptr);
    EXPECT_EQ(reason, nullptr);
}

// Test setting reason to an empty string
TEST_F(PopplerSigningDataGetReasonTest_2383, EmptyStringReason_2383)
{
    poppler_signing_data_set_reason(signing_data, "");
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "");
}

// Test overwriting the reason with a new value
TEST_F(PopplerSigningDataGetReasonTest_2383, OverwriteReason_2383)
{
    poppler_signing_data_set_reason(signing_data, "First Reason");
    const gchar *reason1 = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason1, nullptr);
    EXPECT_STREQ(reason1, "First Reason");

    poppler_signing_data_set_reason(signing_data, "Second Reason");
    const gchar *reason2 = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason2, nullptr);
    EXPECT_STREQ(reason2, "Second Reason");
}

// Test setting reason to nullptr after having a value
TEST_F(PopplerSigningDataGetReasonTest_2383, SetReasonToNull_2383)
{
    poppler_signing_data_set_reason(signing_data, "Some Reason");
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "Some Reason");

    poppler_signing_data_set_reason(signing_data, nullptr);
    reason = poppler_signing_data_get_reason(signing_data);
    EXPECT_EQ(reason, nullptr);
}

// Test with a long string reason
TEST_F(PopplerSigningDataGetReasonTest_2383, LongStringReason_2383)
{
    std::string long_reason(1000, 'A');
    poppler_signing_data_set_reason(signing_data, long_reason.c_str());
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, long_reason.c_str());
}

// Test with special characters in reason
TEST_F(PopplerSigningDataGetReasonTest_2383, SpecialCharactersReason_2383)
{
    const gchar *special = "Reason with spëcial chars: @#$%^&*()_+{}|:<>?/\\\"'";
    poppler_signing_data_set_reason(signing_data, special);
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, special);
}

// Test with UTF-8 characters
TEST_F(PopplerSigningDataGetReasonTest_2383, Utf8Reason_2383)
{
    const gchar *utf8_reason = "理由テスト причина";
    poppler_signing_data_set_reason(signing_data, utf8_reason);
    const gchar *reason = poppler_signing_data_get_reason(signing_data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, utf8_reason);
}

// Test that copying signing data preserves reason
TEST_F(PopplerSigningDataGetReasonTest_2383, CopyPreservesReason_2383)
{
    poppler_signing_data_set_reason(signing_data, "Copy Test Reason");

    PopplerSigningData *copy = poppler_signing_data_copy(signing_data);
    ASSERT_NE(copy, nullptr);

    const gchar *reason = poppler_signing_data_get_reason(copy);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "Copy Test Reason");

    poppler_signing_data_free(copy);
}
