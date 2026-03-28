#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Minimal struct definitions needed by the interface under test.
typedef struct _PopplerSigningData PopplerSigningData;

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

struct _PopplerSigningData {
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
};

// Function under test (implemented in the production codebase).
void poppler_signing_data_set_document_user_password(PopplerSigningData *signing_data,
                                                     const gchar *document_user_password);
} // extern "C"

class PopplerSigningDataTest_2392 : public ::testing::Test {
protected:
    void SetUp() override {
        // Use GLib allocation so g_free is always correct for any freed pointers.
        signing_data_ = static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));
        ASSERT_NE(signing_data_, nullptr);
    }

    void TearDown() override {
        if (signing_data_) {
            // Free only what we may have allocated in tests.
            g_clear_pointer(&signing_data_->document_user_password, g_free);
            g_free(signing_data_);
            signing_data_ = nullptr;
        }
    }

    PopplerSigningData *signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataTest_2392, SetCopiesPasswordString_2392) {
    ASSERT_EQ(signing_data_->document_user_password, nullptr);

    poppler_signing_data_set_document_user_password(signing_data_, "user-pass");

    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "user-pass");
}

TEST_F(PopplerSigningDataTest_2392, SetReplacesPreviousValue_2392) {
    poppler_signing_data_set_document_user_password(signing_data_, "first");
    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "first");

    const char *prev_ptr = signing_data_->document_user_password;

    poppler_signing_data_set_document_user_password(signing_data_, "second");

    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "second");

    // Observable behavior: pointer may change when replaced (not guaranteed by API),
    // but it must at least still be a valid C string with the new content.
    // If it didn't change, that's still fine; don't assert inequality.
    (void)prev_ptr;
}

TEST_F(PopplerSigningDataTest_2392, SetSameContentStillResultsInCorrectString_2392) {
    poppler_signing_data_set_document_user_password(signing_data_, "same");
    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "same");

    // Setting again with the same textual content should keep the observable result correct.
    poppler_signing_data_set_document_user_password(signing_data_, "same");
    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "same");
}

TEST_F(PopplerSigningDataTest_2392, SetEmptyStringAllowed_2392) {
    poppler_signing_data_set_document_user_password(signing_data_, "");

    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "");
}

TEST_F(PopplerSigningDataTest_2392, SetVeryLongString_2392) {
    // Boundary-ish: long input should still be stored as a valid string.
    std::string long_pw(4096, 'a');

    poppler_signing_data_set_document_user_password(signing_data_, long_pw.c_str());

    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_EQ(strlen(signing_data_->document_user_password), long_pw.size());
    EXPECT_STREQ(signing_data_->document_user_password, long_pw.c_str());
}

TEST_F(PopplerSigningDataTest_2392, SetWithSamePointerDoesNotBreakValue_2392) {
    // Pre-seed with a GLib-allocated string so g_free would be valid if freed.
    signing_data_->document_user_password = g_strdup("ptr-same");
    ASSERT_NE(signing_data_->document_user_password, nullptr);

    const gchar *same_ptr = signing_data_->document_user_password;

    // Passing the exact same pointer is a boundary condition for "no-op" behavior.
    poppler_signing_data_set_document_user_password(signing_data_, same_ptr);

    ASSERT_NE(signing_data_->document_user_password, nullptr);
    EXPECT_STREQ(signing_data_->document_user_password, "ptr-same");
}

TEST_F(PopplerSigningDataTest_2392, NullSigningDataIsGracefullyHandled_2392) {
    // Error case: should not crash (GLib g_return_if_fail).
    poppler_signing_data_set_document_user_password(nullptr, "pw");
    SUCCEED();
}

TEST_F(PopplerSigningDataTest_2392, NullPasswordIsGracefullyHandled_2392) {
    // Error case: should not crash (GLib g_return_if_fail).
    poppler_signing_data_set_document_user_password(signing_data_, nullptr);
    SUCCEED();
}