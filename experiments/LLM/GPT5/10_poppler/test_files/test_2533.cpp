// Test file for poppler_structure_element_get_actual_text()
// Covers TEST_ID 2533
//
// We treat Poppler as a black box: tests only validate observable behavior
// (return values + externally-visible GLib critical logs from g_return_val_if_fail).

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

// We include the private header ONLY to access the public struct layout/types.
// We do NOT read or assert on any internal/private state values.
// (We only construct a valid PopplerStructureElement via public GObject APIs.)
#include "poppler-private.h"

namespace {

class ScopedDefaultLogCapture {
public:
    ScopedDefaultLogCapture()
    {
        prevHandler_ = g_log_set_default_handler(&ScopedDefaultLogCapture::Handler, this);
    }

    ~ScopedDefaultLogCapture()
    {
        g_log_set_default_handler(prevHandler_, nullptr);
    }

    void reset()
    {
        messages_.clear();
    }

    size_t count_critical() const
    {
        size_t n = 0;
        for (const auto &m : messages_) {
            if (m.level & G_LOG_LEVEL_CRITICAL) {
                ++n;
            }
        }
        return n;
    }

    bool any_message_contains(const char *needle) const
    {
        if (!needle) {
            return false;
        }
        for (const auto &m : messages_) {
            if (m.message.find(needle) != std::string::npos) {
                return true;
            }
        }
        return false;
    }

private:
    struct Entry {
        GLogLevelFlags level;
        std::string domain;
        std::string message;
    };

    static void Handler(const gchar *log_domain,
                        GLogLevelFlags log_level,
                        const gchar *message,
                        gpointer user_data)
    {
        auto *self = static_cast<ScopedDefaultLogCapture *>(user_data);
        Entry e;
        e.level = log_level;
        e.domain = log_domain ? log_domain : "";
        e.message = message ? message : "";
        self->messages_.push_back(std::move(e));
        // Swallow logs to keep test output clean.
    }

    GLogFunc prevHandler_ = nullptr;
    std::vector<Entry> messages_;
};

class PopplerStructureElementGetActualTextTest_2533 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Make sure GType system is ready (usually already initialized).
        // Calling g_type_init() is deprecated; avoid it.
    }

    ScopedDefaultLogCapture logCapture_;
};

TEST_F(PopplerStructureElementGetActualTextTest_2533, NullPtr_ReturnsNullAndLogsCritical_2533)
{
    logCapture_.reset();

    gchar *out = poppler_structure_element_get_actual_text(nullptr);

    EXPECT_EQ(out, nullptr);
    EXPECT_GE(logCapture_.count_critical(), 1u);
    // The exact message text is GLib-version dependent; check a stable substring.
    EXPECT_TRUE(logCapture_.any_message_contains("POPPLER_IS_STRUCTURE_ELEMENT") ||
                logCapture_.any_message_contains("assertion") ||
                logCapture_.any_message_contains("failed"));
}

TEST_F(PopplerStructureElementGetActualTextTest_2533, WrongType_ReturnsNullAndLogsCritical_2533)
{
    logCapture_.reset();

    GObject *obj = g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(obj, nullptr);

    // Intentionally pass a non-PopplerStructureElement instance.
    gchar *out = poppler_structure_element_get_actual_text(reinterpret_cast<PopplerStructureElement *>(obj));

    EXPECT_EQ(out, nullptr);
    EXPECT_GE(logCapture_.count_critical(), 1u);
    EXPECT_TRUE(logCapture_.any_message_contains("POPPLER_IS_STRUCTURE_ELEMENT") ||
                logCapture_.any_message_contains("assertion") ||
                logCapture_.any_message_contains("failed"));

    g_object_unref(obj);
}

TEST_F(PopplerStructureElementGetActualTextTest_2533, ValidObjectWithNullElem_ReturnsNullAndLogsCritical_2533)
{
    logCapture_.reset();

    // Construct a valid instance via the public GObject type.
    // This does not assume any internal behavior besides being constructible.
    PopplerStructureElement *se =
        POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(se, nullptr);

    // We do NOT set or read internal state; we only observe behavior.
    // If the object is not backed by an underlying StructElement (elem == nullptr),
    // the function is expected to return NULL and emit a g_return critical.
    gchar *out = poppler_structure_element_get_actual_text(se);

    EXPECT_EQ(out, nullptr);
    EXPECT_GE(logCapture_.count_critical(), 1u);
    EXPECT_TRUE(logCapture_.any_message_contains("elem") ||
                logCapture_.any_message_contains("assertion") ||
                logCapture_.any_message_contains("failed"));

    g_object_unref(se);
}

TEST_F(PopplerStructureElementGetActualTextTest_2533, RepeatedCallsWithInvalidInput_AreStable_2533)
{
    logCapture_.reset();

    // Boundary-style check: repeated calls with the same invalid input should be safe.
    for (int i = 0; i < 3; ++i) {
        gchar *out = poppler_structure_element_get_actual_text(nullptr);
        EXPECT_EQ(out, nullptr);
    }

    // Expect at least one critical across calls (implementation logs per call).
    EXPECT_GE(logCapture_.count_critical(), 1u);
}

} // namespace