// poppler-structure-element-get-padding-test_2562.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

namespace {

class ScopedDefaultLogCapture {
public:
    ScopedDefaultLogCapture()
        : old_handler_(g_log_set_default_handler(&ScopedDefaultLogCapture::Handler, this))
    {
    }

    ~ScopedDefaultLogCapture()
    {
        g_log_set_default_handler(old_handler_, nullptr);
    }

    int critical_count() const { return critical_count_; }
    int warning_count() const { return warning_count_; }

private:
    static void Handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message, gpointer user_data)
    {
        auto *self = static_cast<ScopedDefaultLogCapture *>(user_data);
        (void)log_domain;
        (void)message;

        if (log_level & G_LOG_LEVEL_CRITICAL) {
            self->critical_count_++;
            return; // swallow
        }
        if (log_level & G_LOG_LEVEL_WARNING) {
            self->warning_count_++;
            return; // swallow
        }

        // Forward non-critical/warning logs to GLib's default handler so we don't hide unexpected info.
        g_log_default_handler(log_domain, log_level, message, nullptr);
    }

    GLogFunc old_handler_{nullptr};
    int critical_count_{0};
    int warning_count_{0};
};

class PopplerStructureElementPaddingTest_2562 : public ::testing::Test {};

TEST_F(PopplerStructureElementPaddingTest_2562, NullElementEmitsCriticalAndDoesNotWrite_2562)
{
    ScopedDefaultLogCapture logs;

    gdouble paddings[4] = {123.0, 456.0, 789.0, 101112.0};

    poppler_structure_element_get_padding(nullptr, paddings);

    EXPECT_GE(logs.critical_count(), 1);
    EXPECT_DOUBLE_EQ(paddings[0], 123.0);
    EXPECT_DOUBLE_EQ(paddings[1], 456.0);
    EXPECT_DOUBLE_EQ(paddings[2], 789.0);
    EXPECT_DOUBLE_EQ(paddings[3], 101112.0);
}

TEST_F(PopplerStructureElementPaddingTest_2562, NullPaddingsEmitsCritical_2562)
{
    ScopedDefaultLogCapture logs;

    // PopplerStructureElement is a public struct type in the GLib API (boxed-style wrapper).
    // For g_return_if_fail checks, a non-null pointer is enough to reach the paddings nullptr check.
    PopplerStructureElement element{};
    poppler_structure_element_get_padding(&element, nullptr);

    EXPECT_GE(logs.critical_count(), 1);
}

TEST_F(PopplerStructureElementPaddingTest_2562, SmokeNonNullArgsDoesNotEmitCritical_2562)
{
    ScopedDefaultLogCapture logs;

    PopplerStructureElement element{};
    gdouble paddings[4] = {NAN, NAN, NAN, NAN};

    // This is a smoke/boundary test: it verifies the function tolerates a valid pointer and a
    // 4-double output buffer without tripping g_return_if_fail guards.
    poppler_structure_element_get_padding(&element, paddings);

    EXPECT_EQ(logs.critical_count(), 0);

    // We don't assume specific values (black-box); we only check the function had an opportunity
    // to write something to the provided buffer.
    //
    // If the implementation leaves defaults, these may become 0.0; if it preserves NaNs,
    // this assertion will fail and reveal the observable behavior in your environment.
    EXPECT_FALSE(std::isnan(paddings[0]) && std::isnan(paddings[1]) && std::isnan(paddings[2]) && std::isnan(paddings[3]));
}

} // namespace