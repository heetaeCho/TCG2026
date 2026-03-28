// poppler-signing-data-set-password-test.cc
#include <glib.h>

#include <cstring>
#include <string>

#include <gtest/gtest.h>

extern "C" {

// Minimal public structs needed by the provided interface (mirrors snippet in prompt).
// We DO NOT implement any function logic here; only define the data layout to allow
// black-box calls and observable effects through public fields.
typedef struct _PopplerRectangle {
    double x1;
    double y1;
    double x2;
    double y2;
} PopplerRectangle;

typedef struct _PopplerColor {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerSigningData {
public:
    char *destination_filename;
    char *signature_text;
    char *signature_text_left;
    PopplerRectangle signature_rect;
    int left_font_size;
    PopplerColor border_color;
    int border_width;
    PopplerColor background_color;
    char *field_partial_name;
    char *reason;
    char *location;
    char *image_path;
    char *password;
    char *document_owner_password;
    char *document_user_password;
} PopplerSigningData;

// Function under test (implemented in the real codebase).
void poppler_signing_data_set_password(PopplerSigningData *signing_data, const gchar *password);

} // extern "C"

namespace {

class PopplerSigningDataSetPasswordTest_2388 : public ::testing::Test {
protected:
    void SetUp() override {
        std::memset(&sd_, 0, sizeof(sd_));
    }

    void TearDown() override {
        // Free only what tests may allocate. We keep this conservative.
        if (sd_.password) {
            g_free(sd_.password);
            sd_.password = nullptr;
        }
    }

    PopplerSigningData sd_{};
};

TEST_F(PopplerSigningDataSetPasswordTest_2388, SetsPasswordFromNull_2388) {
    ASSERT_EQ(sd_.password, nullptr);

    poppler_signing_data_set_password(&sd_, "secret");

    ASSERT_NE(sd_.password, nullptr);
    EXPECT_STREQ(sd_.password, "secret");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, ReplacesExistingPassword_2388) {
    sd_.password = g_strdup("old");
    ASSERT_NE(sd_.password, nullptr);
    ASSERT_STREQ(sd_.password, "old");

    poppler_signing_data_set_password(&sd_, "new");

    ASSERT_NE(sd_.password, nullptr);
    EXPECT_STREQ(sd_.password, "new");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, AcceptsEmptyStringPassword_2388) {
    poppler_signing_data_set_password(&sd_, "");

    ASSERT_NE(sd_.password, nullptr);
    EXPECT_STREQ(sd_.password, "");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, CopiesInputStringSoLaterMutationDoesNotAffectStored_2388) {
    // Boundary-ish: prove we do not just store caller buffer pointer by mutating it after call.
    gchar buf[] = "abcd";

    poppler_signing_data_set_password(&sd_, buf);

    ASSERT_NE(sd_.password, nullptr);
    EXPECT_STREQ(sd_.password, "abcd");

    buf[0] = 'z';
    // If implementation copies, stored password remains unchanged.
    EXPECT_STREQ(sd_.password, "abcd");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, SameContentDifferentPointerStillResultsInSameValue_2388) {
    // This is observable: calling with same text but from a different buffer should yield that text.
    // We don't assume whether it reallocates; only verify final observable value.
    sd_.password = g_strdup("pw");
    ASSERT_NE(sd_.password, nullptr);
    ASSERT_STREQ(sd_.password, "pw");

    gchar buf[] = "pw"; // different pointer from sd_.password
    poppler_signing_data_set_password(&sd_, buf);

    ASSERT_NE(sd_.password, nullptr);
    EXPECT_STREQ(sd_.password, "pw");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, NoChangeWhenSamePointerProvided_2388) {
    // Observable boundary: when the same pointer is passed back, value stays same.
    // We also check pointer identity remains stable (observable through public field).
    sd_.password = g_strdup("sameptr");
    char *original_ptr = sd_.password;
    ASSERT_NE(original_ptr, nullptr);

    poppler_signing_data_set_password(&sd_, original_ptr);

    EXPECT_EQ(sd_.password, original_ptr);
    EXPECT_STREQ(sd_.password, "sameptr");
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, ErrorCaseNullSigningDataDoesNotCrash_2388) {
    // g_return_if_fail should short-circuit. We assert no crash.
    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_password(nullptr, "pw"));
}

TEST_F(PopplerSigningDataSetPasswordTest_2388, ErrorCaseNullPasswordDoesNotCrashOrModifyExisting_2388) {
    sd_.password = g_strdup("keep");
    char *before_ptr = sd_.password;
    ASSERT_NE(before_ptr, nullptr);
    ASSERT_STREQ(before_ptr, "keep");

    EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_password(&sd_, nullptr));

    // Should be unchanged if it returns early.
    EXPECT_EQ(sd_.password, before_ptr);
    EXPECT_STREQ(sd_.password, "keep");
}

} // namespace