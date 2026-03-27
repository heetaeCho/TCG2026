// poppler_ps_file_new_test_2256.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include <poppler.h>

// NOTE:
// We treat poppler_ps_file_new() as a black box.
// We only assert observable behavior through the public interface:
// - return value (NULL/non-NULL)
// - returned instance type (GObject type check)
// We avoid reading any private/internal struct fields.

namespace {

class PopplerPSFileNewTest_2256 : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Ensure GType system is initialized (usually automatic on modern GLib,
    // but harmless and keeps older environments happy).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  // Best-effort creation of a PopplerDocument instance for argument validation.
  // If the PopplerDocument type is abstract or not constructible in this build,
  // we skip tests that require a valid document.
  static PopplerDocument* CreateDocumentOrSkip() {
    GType doc_type = POPPLER_TYPE_DOCUMENT;

    // If it's abstract, we can't construct it directly.
    if (g_type_test_flags(doc_type, G_TYPE_FLAG_ABSTRACT)) {
      return nullptr;
    }

    PopplerDocument* doc = POPPLER_DOCUMENT(g_object_new(doc_type, nullptr));
    return doc;
  }
};

TEST_F(PopplerPSFileNewTest_2256, NullDocumentReturnsNull_2256) {
  PopplerPSFile* ps = poppler_ps_file_new(nullptr, "out.ps", /*first_page=*/0, /*n_pages=*/1);
  EXPECT_EQ(ps, nullptr);
}

TEST_F(PopplerPSFileNewTest_2256, NullFilenameReturnsNull_2256) {
  PopplerDocument* doc = CreateDocumentOrSkip();
  if (!doc) {
    GTEST_SKIP() << "PopplerDocument is not constructible in this build; skipping filename validation test.";
  }

  PopplerPSFile* ps = poppler_ps_file_new(doc, nullptr, /*first_page=*/0, /*n_pages=*/1);
  EXPECT_EQ(ps, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerPSFileNewTest_2256, NonPositivePagesReturnsNull_2256) {
  PopplerDocument* doc = CreateDocumentOrSkip();
  if (!doc) {
    GTEST_SKIP() << "PopplerDocument is not constructible in this build; skipping n_pages validation test.";
  }

  // Boundary: n_pages == 0
  PopplerPSFile* ps0 = poppler_ps_file_new(doc, "out.ps", /*first_page=*/0, /*n_pages=*/0);
  EXPECT_EQ(ps0, nullptr);

  // Boundary: n_pages < 0
  PopplerPSFile* psneg = poppler_ps_file_new(doc, "out.ps", /*first_page=*/0, /*n_pages=*/-1);
  EXPECT_EQ(psneg, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerPSFileNewTest_2256, ValidArgsReturnPSFileInstance_2256) {
  PopplerDocument* doc = CreateDocumentOrSkip();
  if (!doc) {
    GTEST_SKIP() << "PopplerDocument is not constructible in this build; skipping success-path test.";
  }

  PopplerPSFile* ps = poppler_ps_file_new(doc, "out.ps", /*first_page=*/0, /*n_pages=*/1);
  ASSERT_NE(ps, nullptr);

  // Observable external behavior: it should be a PopplerPSFile GObject instance.
  EXPECT_TRUE(POPPLER_IS_PS_FILE(ps));

  // Cleanup should be safe.
  g_object_unref(ps);
  g_object_unref(doc);
}

TEST_F(PopplerPSFileNewTest_2256, EmptyFilenameIsAcceptedOrRejectedButMustNotCrash_2256) {
  PopplerDocument* doc = CreateDocumentOrSkip();
  if (!doc) {
    GTEST_SKIP() << "PopplerDocument is not constructible in this build; skipping empty filename test.";
  }

  // Boundary: filename is non-null but empty string.
  PopplerPSFile* ps = poppler_ps_file_new(doc, "", /*first_page=*/0, /*n_pages=*/1);

  // The interface contract only rejects nullptr; empty string behavior is unspecified here.
  // We assert the call is safe and, if it succeeds, the result is a valid PSFile instance.
  if (ps) {
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps));
    g_object_unref(ps);
  } else {
    EXPECT_EQ(ps, nullptr);
  }

  g_object_unref(doc);
}

}  // namespace