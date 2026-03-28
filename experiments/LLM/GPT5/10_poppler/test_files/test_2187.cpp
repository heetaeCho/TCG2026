// poppler_document_set_creation_date_time_test_2187.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

// Minimal PDF generator for creating a valid PopplerDocument without relying on external files.
static std::string MakeMinimalPdfBytes()
{
    // Objects:
    // 1: Catalog
    // 2: Pages
    // 3: Page (empty contents)
    // 4: Empty content stream
    std::string pdf;
    pdf.reserve(1024);

    auto append = [&](const std::string &s) { pdf += s; };

    append("%PDF-1.4\n");

    std::vector<size_t> offsets(5, 0); // index by obj number; 0 is special

    offsets[1] = pdf.size();
    append("1 0 obj\n");
    append("<< /Type /Catalog /Pages 2 0 R >>\n");
    append("endobj\n");

    offsets[2] = pdf.size();
    append("2 0 obj\n");
    append("<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");
    append("endobj\n");

    offsets[3] = pdf.size();
    append("3 0 obj\n");
    append("<< /Type /Page /Parent 2 0 R /MediaBox [0 0 10 10]\n");
    append("   /Resources << >>\n");
    append("   /Contents 4 0 R >>\n");
    append("endobj\n");

    offsets[4] = pdf.size();
    append("4 0 obj\n");
    append("<< /Length 0 >>\n");
    append("stream\n");
    append("endstream\n");
    append("endobj\n");

    const size_t xref_pos = pdf.size();
    append("xref\n");
    append("0 5\n");
    append("0000000000 65535 f \n");

    auto fmt_offset = [](size_t off) {
        std::ostringstream oss;
        oss << std::setw(10) << std::setfill('0') << off;
        return oss.str();
    };

    for (int i = 1; i <= 4; ++i) {
        append(fmt_offset(offsets[i]));
        append(" 00000 n \n");
    }

    append("trailer\n");
    append("<< /Size 5 /Root 1 0 R >>\n");
    append("startxref\n");
    append(std::to_string(xref_pos));
    append("\n%%EOF\n");

    return pdf;
}

static PopplerDocument *NewDocumentFromMinimalPdf(GError **error)
{
    const std::string bytes = MakeMinimalPdfBytes();
    // poppler_document_new_from_data copies the data internally (per Poppler GLib API behavior).
    return poppler_document_new_from_data(bytes.c_str(),
                                         static_cast<int>(bytes.size()),
                                         /*password=*/nullptr,
                                         error);
}

class LogCatcher {
public:
    LogCatcher(const char *domain, GLogLevelFlags levels)
        : domain_(domain ? domain : ""), levels_(levels), handler_id_(0), count_(0)
    {
        handler_id_ = g_log_set_handler(domain, levels, &LogCatcher::HandlerThunk, this);
    }

    ~LogCatcher()
    {
        if (handler_id_ != 0) {
            g_log_remove_handler(domain_.c_str(), handler_id_);
        }
    }

    int count() const { return count_; }
    const std::string &last_message() const { return last_message_; }

private:
    static void HandlerThunk(const gchar *log_domain,
                             GLogLevelFlags log_level,
                             const gchar *message,
                             gpointer user_data)
    {
        (void)log_domain;
        (void)log_level;
        auto *self = static_cast<LogCatcher *>(user_data);
        self->count_++;
        self->last_message_ = message ? message : "";
    }

    std::string domain_;
    GLogLevelFlags levels_;
    guint handler_id_;
    int count_;
    std::string last_message_;
};

class PopplerDocumentSetCreationDateTimeTest_2187 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Ensure GType system is ready (usually already inited by Poppler/GLib, but safe).
        if (!g_type_check_instance_is_fundamentally_a(reinterpret_cast<GTypeInstance *>(g_object_new(G_TYPE_OBJECT, nullptr)),
                                                      G_TYPE_OBJECT)) {
            // no-op; just to touch GType in a safe way
        }
    }
};

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetNonNullThenGetMatches_2187)
{
    GError *error = nullptr;
    PopplerDocument *doc = NewDocumentFromMinimalPdf(&error);
    ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "Failed to create PopplerDocument");
    if (error) {
        g_error_free(error);
        error = nullptr;
    }

    GDateTime *dt = g_date_time_new_utc(2020, 1, 2, 3, 4, 5);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(doc, dt);

    GDateTime *got = poppler_document_get_creation_date_time(doc);
    ASSERT_NE(got, nullptr);

    // Compare using Unix time to avoid timezone formatting differences.
    const gint64 want_unix = g_date_time_to_unix(dt);
    const gint64 got_unix = g_date_time_to_unix(got);
    EXPECT_EQ(got_unix, want_unix);

    g_date_time_unref(got);
    g_date_time_unref(dt);
    g_object_unref(doc);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetNullClearsCreationDate_2187)
{
    GError *error = nullptr;
    PopplerDocument *doc = NewDocumentFromMinimalPdf(&error);
    ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "Failed to create PopplerDocument");
    if (error) {
        g_error_free(error);
        error = nullptr;
    }

    GDateTime *dt = g_date_time_new_utc(2021, 12, 31, 23, 59, 59);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(doc, dt);
    g_date_time_unref(dt);

    // Now clear it.
    poppler_document_set_creation_date_time(doc, nullptr);

    GDateTime *got = poppler_document_get_creation_date_time(doc);
    EXPECT_EQ(got, nullptr);
    if (got) {
        g_date_time_unref(got);
    }

    g_object_unref(doc);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, AcceptsNonUtcTimezoneAndPreservesInstant_2187)
{
    GError *error = nullptr;
    PopplerDocument *doc = NewDocumentFromMinimalPdf(&error);
    ASSERT_NE(doc, nullptr) << (error && error->message ? error->message : "Failed to create PopplerDocument");
    if (error) {
        g_error_free(error);
        error = nullptr;
    }

    // Create a datetime with a non-UTC timezone (Asia/Seoul).
    GTimeZone *tz = g_time_zone_new("Asia/Seoul");
    ASSERT_NE(tz, nullptr);

    GDateTime *dt_local = g_date_time_new(tz, 2022, 6, 1, 12, 0, 0);
    ASSERT_NE(dt_local, nullptr);

    const gint64 want_unix = g_date_time_to_unix(dt_local);

    poppler_document_set_creation_date_time(doc, dt_local);

    GDateTime *got = poppler_document_get_creation_date_time(doc);
    ASSERT_NE(got, nullptr);

    const gint64 got_unix = g_date_time_to_unix(got);
    EXPECT_EQ(got_unix, want_unix);

    g_date_time_unref(got);
    g_date_time_unref(dt_local);
    g_time_zone_unref(tz);
    g_object_unref(doc);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, NullDocumentEmitsCriticalAndReturns_2187)
{
    // g_return_if_fail typically logs a CRITICAL with the module's log domain.
    // In Poppler GLib, this is commonly "Poppler".
    LogCatcher catcher("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

    GDateTime *dt = g_date_time_new_utc(2000, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(nullptr, dt);

    EXPECT_GE(catcher.count(), 1);
    EXPECT_NE(catcher.last_message().find("POPPLER_IS_DOCUMENT"), std::string::npos);

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, NonDocumentInstanceEmitsCriticalAndReturns_2187)
{
    LogCatcher catcher("Poppler", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

    // Create an object of the wrong type and pass it as PopplerDocument*.
    GObject *not_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(not_doc, nullptr);

    GDateTime *dt = g_date_time_new_utc(2010, 5, 6, 7, 8, 9);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(reinterpret_cast<PopplerDocument *>(not_doc), dt);

    EXPECT_GE(catcher.count(), 1);
    EXPECT_NE(catcher.last_message().find("POPPLER_IS_DOCUMENT"), std::string::npos);

    g_date_time_unref(dt);
    g_object_unref(not_doc);
}

} // namespace