// File: poppler-document-finalize-test_2149.cc
#include <gtest/gtest.h>

#include <glib-object.h>

#include "poppler.h"

// We intentionally include the private header to (only) set up observable state
// through the public lifecycle (GObject finalize via g_object_unref).
#include "poppler-private.h"

// For CairoOutputDev (deleted by poppler_document_finalize).
#include "CairoOutputDev.h"

namespace {

class CountingCairoOutputDev : public CairoOutputDev {
public:
  explicit CountingCairoOutputDev(int *dtor_counter) : counter_(dtor_counter) {}
  ~CountingCairoOutputDev() override {
    if (counter_)
      ++(*counter_);
  }

private:
  int *counter_;
};

class PopplerDocumentFinalizeTest_2149 : public ::testing::Test {
protected:
  void SetUp() override {
    // No explicit init needed for GLib >= 2.36; keep test robust anyway.
  }

  static PopplerDocument *NewDocumentOrSkip() {
    if (!g_type_from_name("PopplerDocument")) {
      // If the type isn't registered for some reason, g_object_new will fail.
      // Avoid a hard crash in the test binary.
      return nullptr;
    }

    // Construct via the public GObject type system.
    auto *obj = g_object_new(POPPLER_TYPE_DOCUMENT, nullptr);
    return POPPLER_DOCUMENT(obj);
  }
};

TEST_F(PopplerDocumentFinalizeTest_2149, UnrefWithNullOutputDevDoesNotCrash_2149) {
  PopplerDocument *doc = NewDocumentOrSkip();
  if (!doc)
    GTEST_SKIP() << "PopplerDocument type not available/registered in this build.";

  // Boundary: output_dev is null (default / explicitly).
  doc->output_dev = nullptr;

  EXPECT_NO_FATAL_FAILURE(g_object_unref(G_OBJECT(doc)));
}

TEST_F(PopplerDocumentFinalizeTest_2149, FinalizeDeletesOutputDevExactlyOnce_2149) {
  PopplerDocument *doc = NewDocumentOrSkip();
  if (!doc)
    GTEST_SKIP() << "PopplerDocument type not available/registered in this build.";

  int dtor_calls = 0;
  doc->output_dev = new CountingCairoOutputDev(&dtor_calls);

  // Trigger finalize by dropping the last reference.
  g_object_unref(G_OBJECT(doc));

  EXPECT_EQ(dtor_calls, 1) << "output_dev should be deleted exactly once during finalize.";
}

TEST_F(PopplerDocumentFinalizeTest_2149, FinalizeHandlesNullObjectFieldsGracefully_2149) {
  PopplerDocument *doc = NewDocumentOrSkip();
  if (!doc)
    GTEST_SKIP() << "PopplerDocument type not available/registered in this build.";

  // Boundary/error-ish: leave all optional pointers null.
  doc->output_dev = nullptr;
  doc->layers_rbgroups = nullptr;

  EXPECT_NO_FATAL_FAILURE(g_object_unref(G_OBJECT(doc)));
}

}  // namespace