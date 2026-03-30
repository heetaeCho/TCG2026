// poppler_structure_element_is_grouping_test_2527.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler.h"

// Access to internal fields (elem) for boundary/error-path validation.
#include "poppler-private.h"

namespace {

class ScopedDefaultGLogCapture {
public:
    ScopedDefaultGLogCapture()
        : oldHandler(g_log_set_default_handler(&ScopedDefaultGLogCapture::Handler, this))
    {
    }

    ~ScopedDefaultGLogCapture()
    {
        g_log_set_default_handler(oldHandler, nullptr);
    }

    int criticalCount() const { return criticals; }
    int warningCount() const { return warnings; }

private:
    static void Handler(const gchar * /*log_domain*/, GLogLevelFlags log_level, const gchar * /*message*/, gpointer user_data)
    {
        auto *self = static_cast<ScopedDefaultGLogCapture *>(user_data);
        if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
            self->criticals++;
        }
        if ((log_level & G_LOG_LEVEL_WARNING) != 0) {
            self->warnings++;
        }
        // Swallow the log to keep test output clean.
    }

    GLogFunc oldHandler = nullptr;
    int criticals = 0;
    int warnings = 0;
};

class PopplerStructureElementIsGroupingTest_2527 : public ::testing::Test {
protected:
    void SetUp() override
    {
        // Ensure criticals from g_return_val_if_fail do not abort the test process.
        oldFatalMask = g_log_set_fatal_mask(nullptr, static_cast<GLogLevelFlags>(G_LOG_FATAL_MASK & ~G_LOG_LEVEL_CRITICAL));
    }

    void TearDown() override { g_log_set_fatal_mask(nullptr, oldFatalMask); }

private:
    GLogLevelFlags oldFatalMask = static_cast<GLogLevelFlags>(0);
};

} // namespace

TEST_F(PopplerStructureElementIsGroupingTest_2527, NullPointerReturnsFalse_2527)
{
    ScopedDefaultGLogCapture capture;

    EXPECT_FALSE(poppler_structure_element_is_grouping(nullptr));

    // Observable behavior: g_return_val_if_fail should emit at least one critical log.
    EXPECT_GE(capture.criticalCount(), 1);
}

TEST_F(PopplerStructureElementIsGroupingTest_2527, WrongGObjectTypeReturnsFalse_2527)
{
    ScopedDefaultGLogCapture capture;

    // Create a valid GObject instance of the wrong type and cast it.
    GObject *obj = static_cast<GObject *>(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(obj, nullptr);

    EXPECT_FALSE(poppler_structure_element_is_grouping(reinterpret_cast<PopplerStructureElement *>(obj)));

    g_object_unref(obj);

    // Observable behavior: type check failure should log a critical.
    EXPECT_GE(capture.criticalCount(), 1);
}

TEST_F(PopplerStructureElementIsGroupingTest_2527, NullElemFieldReturnsFalse_2527)
{
    ScopedDefaultGLogCapture capture;

    PopplerStructureElement *se =
        reinterpret_cast<PopplerStructureElement *>(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    ASSERT_NE(se, nullptr);

    // Boundary condition: elem is required; make it explicitly null to hit the guard.
    // poppler-private.h exposes the internal instance struct for tests.
    auto *priv = reinterpret_cast<_PopplerStructureElement *>(se);
    priv->elem = nullptr;

    EXPECT_FALSE(poppler_structure_element_is_grouping(se));

    g_object_unref(se);

    // Observable behavior: elem null guard should log a critical.
    EXPECT_GE(capture.criticalCount(), 1);
}