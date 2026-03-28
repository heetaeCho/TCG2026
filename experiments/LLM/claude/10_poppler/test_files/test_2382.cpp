#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and struct definition based on known dependencies
struct _PopplerSigningData {
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    // PopplerRectangle signature_rect; -- skipping complex types for minimal test setup
    int left_font_size;
    // PopplerColor border_color;
    int border_width;
    // PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
};

typedef struct _PopplerSigningData PopplerSigningData;

// Declare the function under test
extern "C" {
void poppler_signing_data_set_reason(PopplerSigningData *signing_data, const gchar *reason);
}

class PopplerSigningDataSetReasonTest_2382 : public ::testing::Test {
protected:
    PopplerSigningData *signing_data;

    void SetUp() override {
        signing_data = g_new0(PopplerSigningData, 1);
        signing_data->reason = nullptr;
    }

    void TearDown() override {
        if (signing_data) {
            g_free(signing_data->reason);
            g_free(signing_data);
        }
    }
};

// Test: Setting reason on a valid signing_data with a valid string
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonNormal_2382) {
    poppler_signing_data_set_reason(signing_data, "Test Reason");
    EXPECT_STREQ(signing_data->reason, "Test Reason");
}

// Test: Setting reason replaces previous reason
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonReplacesPrevious_2382) {
    poppler_signing_data_set_reason(signing_data, "First Reason");
    EXPECT_STREQ(signing_data->reason, "First Reason");

    poppler_signing_data_set_reason(signing_data, "Second Reason");
    EXPECT_STREQ(signing_data->reason, "Second Reason");
}

// Test: Setting reason with an empty string
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonEmptyString_2382) {
    poppler_signing_data_set_reason(signing_data, "");
    EXPECT_STREQ(signing_data->reason, "");
}

// Test: Setting reason creates a copy (not the same pointer)
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonCreatesACopy_2382) {
    const char *original = "Copy Test";
    poppler_signing_data_set_reason(signing_data, original);
    EXPECT_STREQ(signing_data->reason, original);
    // The stored reason should be a different pointer (a copy)
    EXPECT_NE(signing_data->reason, original);
}

// Test: Setting reason with the same pointer (self-assignment) should not crash or change value
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonSelfAssignment_2382) {
    poppler_signing_data_set_reason(signing_data, "Self Assign");
    EXPECT_STREQ(signing_data->reason, "Self Assign");

    // Now set reason to the same pointer it already holds
    poppler_signing_data_set_reason(signing_data, signing_data->reason);
    EXPECT_STREQ(signing_data->reason, "Self Assign");
}

// Test: Null signing_data should not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataSetReasonTest_2382, NullSigningDataDoesNotCrash_2382) {
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_reason(nullptr, "Some Reason");
    // If we reach here, the function handled the null gracefully
    SUCCEED();
}

// Test: Null reason should not crash (g_return_if_fail handles it)
TEST_F(PopplerSigningDataSetReasonTest_2382, NullReasonDoesNotCrash_2382) {
    signing_data->reason = g_strdup("Original");
    // This should trigger g_return_if_fail and return without crashing
    poppler_signing_data_set_reason(signing_data, nullptr);
    // The original reason should be unchanged
    EXPECT_STREQ(signing_data->reason, "Original");
}

// Test: Setting reason with a long string
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonLongString_2382) {
    std::string long_reason(10000, 'A');
    poppler_signing_data_set_reason(signing_data, long_reason.c_str());
    EXPECT_STREQ(signing_data->reason, long_reason.c_str());
}

// Test: Setting reason with special characters
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonSpecialCharacters_2382) {
    const char *special = "Reason with special chars: !@#$%^&*()_+-=[]{}|;':\",./<>?";
    poppler_signing_data_set_reason(signing_data, special);
    EXPECT_STREQ(signing_data->reason, special);
}

// Test: Setting reason with UTF-8 characters
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonUTF8_2382) {
    const char *utf8_reason = "Raison: données protégées 数据保护";
    poppler_signing_data_set_reason(signing_data, utf8_reason);
    EXPECT_STREQ(signing_data->reason, utf8_reason);
}

// Test: Multiple consecutive sets
TEST_F(PopplerSigningDataSetReasonTest_2382, MultipleConsecutiveSets_2382) {
    for (int i = 0; i < 100; i++) {
        std::string reason = "Reason " + std::to_string(i);
        poppler_signing_data_set_reason(signing_data, reason.c_str());
        EXPECT_STREQ(signing_data->reason, reason.c_str());
    }
}

// Test: Setting reason when previous reason was nullptr
TEST_F(PopplerSigningDataSetReasonTest_2382, SetReasonFromNullptr_2382) {
    ASSERT_EQ(signing_data->reason, nullptr);
    poppler_signing_data_set_reason(signing_data, "From Null");
    EXPECT_STREQ(signing_data->reason, "From Null");
}
