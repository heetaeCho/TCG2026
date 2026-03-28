// poppler_signature_info_get_local_signing_time_test_2331.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string>
#include <vector>

extern "C" {

// Minimal forward decls to match the exposed interface used by poppler-form-field.cc.
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;
typedef int PopplerCertificateStatus;

// NOTE: The prompt’s “Known dependencies” shows `int * local_signing_time`, but the
// function returns `GDateTime*` and returns `siginfo->local_signing_time`.
// In Poppler GLib, this field is effectively a `GDateTime*`. We declare it that way
// to match the interface under test.
typedef struct _PopplerSignatureInfo {
    int sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    GDateTime *local_signing_time;
    PopplerCertificateInfo *certificate_info;
} PopplerSignatureInfo;

// Function under test (implemented in the real codebase)
GDateTime *poppler_signature_info_get_local_signing_time(const PopplerSignatureInfo *siginfo);

} // extern "C"

namespace {

class DefaultLogCatcher {
public:
    DefaultLogCatcher()
        : old_handler_(g_log_set_default_handler(&DefaultLogCatcher::Handler, this)),
          old_data_(nullptr) {
        // g_log_set_default_handler returns previous handler but not its data.
        // There is no API to retrieve old user_data; we restore handler only.
        // This is acceptable for test-only capture.
    }

    ~DefaultLogCatcher() { g_log_set_default_handler(old_handler_, old_data_); }

    int critical_count() const { return critical_count_; }
    const std::vector<std::string> &messages() const { return messages_; }

private:
    static void Handler(const gchar *log_domain,
                        GLogLevelFlags log_level,
                        const gchar *message,
                        gpointer user_data) {
        auto *self = static_cast<DefaultLogCatcher *>(user_data);
        // Record all CRITICAL logs; do not forward to avoid noisy test output.
        if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
            self->critical_count_++;
            if (message)
                self->messages_.emplace_back(message);
            else
                self->messages_.emplace_back("");
        }
        (void)log_domain;
    }

    GLogFunc old_handler_;
    gpointer old_data_;
    int critical_count_ = 0;
    std::vector<std::string> messages_;
};

struct GDateTimeDeleter {
    void operator()(GDateTime *dt) const {
        if (dt)
            g_date_time_unref(dt);
    }
};

using UniqueGDateTime = std::unique_ptr<GDateTime, GDateTimeDeleter>;

class PopplerSignatureInfoTest_2331 : public ::testing::Test {};

} // namespace

TEST_F(PopplerSignatureInfoTest_2331, NullSiginfoReturnsNull_2331) {
    DefaultLogCatcher logs;

    GDateTime *result = poppler_signature_info_get_local_signing_time(nullptr);

    EXPECT_EQ(result, nullptr);

    // Observable error case: g_return_val_if_fail should emit a CRITICAL log.
    // We don’t over-specify the exact message/domain to keep the test robust.
    EXPECT_GE(logs.critical_count(), 1);
}

TEST_F(PopplerSignatureInfoTest_2331, ReturnsSamePointerWhenPresent_2331) {
    PopplerSignatureInfo info{};
    UniqueGDateTime now(g_date_time_new_now_local());
    ASSERT_NE(now.get(), nullptr);

    info.local_signing_time = now.get();

    GDateTime *result = poppler_signature_info_get_local_signing_time(&info);

    // Function is a simple accessor; observable behavior is returning the same pointer.
    EXPECT_EQ(result, now.get());
}

TEST_F(PopplerSignatureInfoTest_2331, ReturnsNullWhenFieldIsNull_2331) {
    PopplerSignatureInfo info{};
    info.local_signing_time = nullptr;

    DefaultLogCatcher logs;
    GDateTime *result = poppler_signature_info_get_local_signing_time(&info);

    EXPECT_EQ(result, nullptr);

    // No precondition violation here (siginfo is non-null), so no required CRITICAL.
    // We keep this loose: it should *not* need to log.
    EXPECT_EQ(logs.critical_count(), 0);
}

TEST_F(PopplerSignatureInfoTest_2331, ConstInputDoesNotRequireMutableAccess_2331) {
    // Boundary-ish: pass as const pointer; ensure call works and returns expected value.
    PopplerSignatureInfo info{};
    UniqueGDateTime now(g_date_time_new_now_local());
    ASSERT_NE(now.get(), nullptr);
    info.local_signing_time = now.get();

    const PopplerSignatureInfo *const_ptr = &info;
    GDateTime *result = poppler_signature_info_get_local_signing_time(const_ptr);

    EXPECT_EQ(result, now.get());
}