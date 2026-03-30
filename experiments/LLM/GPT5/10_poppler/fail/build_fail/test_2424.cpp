// File: poppler-page-new-test.cc
#include <gtest/gtest.h>

#include <glib-object.h>

extern "C" {
#include "poppler.h"
#include "poppler-private.h"

// Private constructor under test (defined in glib/poppler-page.cc)
PopplerPage *_poppler_page_new(PopplerDocument *document, Page *page, int index);
}

// A small helper to silence GLib warnings/criticals in tests that intentionally
// trigger g_return_* checks.
class ScopedGLibLogSilencer {
public:
  ScopedGLibLogSilencer()
  {
    handler_ = g_log_set_handler(nullptr,
                                 static_cast<GLogLevelFlags>(G_LOG_LEVEL_WARNING |
                                                             G_LOG_LEVEL_CRITICAL |
                                                             G_LOG_LEVEL_MESSAGE),
                                 &ScopedGLibLogSilencer::OnLog,
                                 nullptr);
  }

  ~ScopedGLibLogSilencer()
  {
    if (handler_ != 0) {
      g_log_remove_handler(nullptr, handler_);
    }
  }

  ScopedGLibLogSilencer(const ScopedGLibLogSilencer &) = delete;
  ScopedGLibLogSilencer &operator=(const ScopedGLibLogSilencer &) = delete;

private:
  static void OnLog(const gchar * /*log_domain*/,
                    GLogLevelFlags /*log_level*/,
                    const gchar * /*message*/,
                    gpointer /*user_data*/)
  {
    // Intentionally ignore.
  }

  guint handler_ = 0;
};

static void WeakNotifyDestroyed(gpointer data, GObject * /*where_the_object_was*/)
{
  auto *flag = static_cast<bool *>(data);
  *flag = true;
}

class PopplerPageNewTest_2424 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // Ensure GTypes are registered (harmless if already done).
    g_type_ensure(POPPLER_TYPE_DOCUMENT);
    g_type_ensure(POPPLER_TYPE_PAGE);
  }
};

TEST_F(PopplerPageNewTest_2424, NullDocumentReturnsNull_2424)
{
  ScopedGLibLogSilencer silencer;

  PopplerPage *page = _poppler_page_new(nullptr, /*Page*/ nullptr, /*index*/ 0);
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerPageNewTest_2424, NonDocumentGObjectReturnsNull_2424)
{
  ScopedGLibLogSilencer silencer;

  // Create an object that is definitely NOT a PopplerDocument.
  GObject *not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));

  PopplerPage *page =
      _poppler_page_new(reinterpret_cast<PopplerDocument *>(not_a_doc), /*Page*/ nullptr, 0);
  EXPECT_EQ(page, nullptr);

  g_object_unref(not_a_doc);
}

TEST_F(PopplerPageNewTest_2424, ValidDocumentCreatesPage_2424)
{
  // Construct a PopplerDocument instance as a plain GObject.
  // (We do not assume any internal initialization beyond the type existing.)
  PopplerDocument *doc = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));
  ASSERT_NE(doc, nullptr);

  PopplerPage *page = _poppler_page_new(doc, /*Page*/ nullptr, /*index*/ 0);
  ASSERT_NE(page, nullptr);
  EXPECT_TRUE(POPPLER_IS_PAGE(page));

  g_object_unref(page);
  g_object_unref(doc);
}

TEST_F(PopplerPageNewTest_2424, IndexBoundaryValuesStillCreatePage_2424)
{
  PopplerDocument *doc = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));
  ASSERT_NE(doc, nullptr);

  PopplerPage *page_neg = _poppler_page_new(doc, /*Page*/ nullptr, /*index*/ -1);
  ASSERT_NE(page_neg, nullptr);
  EXPECT_TRUE(POPPLER_IS_PAGE(page_neg));

  PopplerPage *page_max = _poppler_page_new(doc, /*Page*/ nullptr, /*index*/ G_MAXINT);
  ASSERT_NE(page_max, nullptr);
  EXPECT_TRUE(POPPLER_IS_PAGE(page_max));

  g_object_unref(page_neg);
  g_object_unref(page_max);
  g_object_unref(doc);
}

TEST_F(PopplerPageNewTest_2424, ReturnedPageHoldsReferenceToDocument_2424)
{
  // This test verifies an *observable* external interaction:
  // the returned PopplerPage keeps the PopplerDocument alive (via ref)
  // after the caller releases their own reference.
  PopplerDocument *doc = POPPLER_DOCUMENT(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));
  ASSERT_NE(doc, nullptr);

  bool destroyed = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifyDestroyed, &destroyed);

  PopplerPage *page = _poppler_page_new(doc, /*Page*/ nullptr, /*index*/ 1);
  ASSERT_NE(page, nullptr);

  // Drop our reference; if PopplerPage took a ref, doc should still be alive.
  g_object_unref(doc);
  EXPECT_FALSE(destroyed);

  // Now drop the PopplerPage; document should become destroyable and weak notify should fire.
  g_object_unref(page);
  EXPECT_TRUE(destroyed);
}