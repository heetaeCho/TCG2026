// poppler-signing-data-set-signature-text-left-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>
#include <string>

// ---- Minimal type surface needed by the partial code under test ----
// We intentionally only model what is required to construct PopplerSigningData.
// The function under test only touches signature_text_left.
extern "C" {

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

// Function under test
void poppler_signing_data_set_signature_text_left(PopplerSigningData *signing_data,
                                                 const gchar *signature_text_left);

} // extern "C"

// ---- GLib critical log capture helper (for g_return_if_fail observable behavior) ----
class GlibCriticalCapture {
public:
    GlibCriticalCapture()
    {
        handler_id_ = g_log_set_handler(
            "GLib",
            static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL | G_LOG_FLAG_FATAL | G_LOG_FLAG_RECURSION),
            &GlibCriticalCapture::HandlerThunk,
            this);
    }

    ~GlibCriticalCapture()
    {
        if (handler_id_ != 0) {
            g_log_remove_handler("GLib", handler_id_);
        }
    }

    int critical_count() const { return critical_count_; }

private:
    static void HandlerThunk(const gchar *log_domain,
                             GLogLevelFlags log_level,
                             const gchar *message,
                             gpointer user_data)
    {
        auto *self = static_cast<GlibCriticalCapture *>(user_data);
        self->OnLog(log_domain, log_level, message);
    }

    void OnLog(const gchar * /*log_domain*/, GLogLevelFlags log_level, const gchar * /*message*/)
    {
        if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
            ++critical_count_;
        }
    }

    guint handler_id_ = 0;
    int critical_count_ = 0;
};

class PopplerSigningDataTest_2364 : public ::testing::Test {
protected:
    void SetUp() override
    {
        signing_data_ = static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));
    }

    void TearDown() override
    {
        if (signing_data_) {
            // Free only heap-owned strings we may have set in tests.
            g_free(signing_data_->signature_text_left);
            signing_data_->signature_text_left = nullptr;
            g_free(signing_data_);
            signing_data_ = nullptr;
        }
    }

    PopplerSigningData *signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataTest_2364, SetsTextLeftWhenInitiallyNull_2364)
{
    ASSERT_NE(signing_data_, nullptr);
    ASSERT_EQ(signing_data_->signature_text_left, nullptr);

    poppler_signing_data_set_signature_text_left(signing_data_, "Left Text");

    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data_->signature_text_left, "Left Text");
}

TEST_F(PopplerSigningDataTest_2364, OverwritesExistingTextLeftWithNewValue_2364)
{
    ASSERT_NE(signing_data_, nullptr);

    signing_data_->signature_text_left = g_strdup("Old");
    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    char *old_ptr = signing_data_->signature_text_left;

    poppler_signing_data_set_signature_text_left(signing_data_, "New");

    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data_->signature_text_left, "New");
    EXPECT_NE(signing_data_->signature_text_left, old_ptr); // observable pointer change
}

TEST_F(PopplerSigningDataTest_2364, DoesNothingWhenSamePointerIsPassed_2364)
{
    ASSERT_NE(signing_data_, nullptr);

    gchar *p = g_strdup("SamePtr");
    signing_data_->signature_text_left = p;

    poppler_signing_data_set_signature_text_left(signing_data_, p);

    // The function should early-return (observable as pointer unchanged).
    EXPECT_EQ(signing_data_->signature_text_left, p);
    EXPECT_STREQ(signing_data_->signature_text_left, "SamePtr");

    // Prevent TearDown from double-freeing: it will free signature_text_left once.
    // (No additional cleanup needed.)
}

TEST_F(PopplerSigningDataTest_2364, AcceptsEmptyString_2364)
{
    ASSERT_NE(signing_data_, nullptr);

    poppler_signing_data_set_signature_text_left(signing_data_, "");

    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    EXPECT_STREQ(signing_data_->signature_text_left, "");
}

TEST_F(PopplerSigningDataTest_2364, HandlesLargeStringInput_2364)
{
    ASSERT_NE(signing_data_, nullptr);

    std::string big(4096, 'A');
    poppler_signing_data_set_signature_text_left(signing_data_, big.c_str());

    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    EXPECT_EQ(std::strlen(signing_data_->signature_text_left), big.size());
    EXPECT_EQ(std::memcmp(signing_data_->signature_text_left, big.data(), big.size()), 0);
}

TEST_F(PopplerSigningDataTest_2364, NullSigningDataEmitsCriticalAndDoesNotCrash_2364)
{
    GlibCriticalCapture cap;

    poppler_signing_data_set_signature_text_left(nullptr, "X");

    EXPECT_GE(cap.critical_count(), 1);
}

TEST_F(PopplerSigningDataTest_2364, NullSignatureTextLeftEmitsCriticalAndDoesNotChangeValue_2364)
{
    ASSERT_NE(signing_data_, nullptr);
    signing_data_->signature_text_left = g_strdup("KeepMe");
    ASSERT_NE(signing_data_->signature_text_left, nullptr);
    char *old_ptr = signing_data_->signature_text_left;

    GlibCriticalCapture cap;
    poppler_signing_data_set_signature_text_left(signing_data_, nullptr);

    EXPECT_GE(cap.critical_count(), 1);

    // Observable behavior: since the call returns early, the existing value remains.
    EXPECT_EQ(signing_data_->signature_text_left, old_ptr);
    EXPECT_STREQ(signing_data_->signature_text_left, "KeepMe");
}