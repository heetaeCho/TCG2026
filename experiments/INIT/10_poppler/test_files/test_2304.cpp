// File: poppler-dest-new-goto-test_2304.cc
#include <gtest/gtest.h>

extern "C" {

// Forward declarations (avoid pulling heavy Poppler headers into the unit test).
typedef struct _PopplerDocument PopplerDocument;
typedef struct _PopplerDest PopplerDest;

} // extern "C"

// LinkDest is a C++ type (from Poppler core). We only need it as an opaque pointer here.
class LinkDest;

extern "C" {
// Function under test (from ./TestProjects/poppler/glib/poppler-action.cc)
PopplerDest* _poppler_dest_new_goto(PopplerDocument* document, LinkDest* link_dest);
} // extern "C"

namespace {

class PopplerDestNewGotoTest_2304 : public ::testing::Test {
 protected:
  // Create a trivially-initialized PopplerDocument-like object without depending on its real layout.
  // We only pass its pointer through the interface; we do not dereference it in the test.
  static PopplerDocument* MakeDummyDocument_2304() {
    // Allocate a small block; treat it as an opaque PopplerDocument.
    // This is intentionally minimal and avoids relying on internal struct fields.
    return reinterpret_cast<PopplerDocument*>(new unsigned char[64]());
  }

  static void FreeDummyDocument_2304(PopplerDocument* doc) {
    delete[] reinterpret_cast<unsigned char*>(doc);
  }
};

TEST_F(PopplerDestNewGotoTest_2304, CallWithNullsDoesNotCrash_2304) {
  // Boundary condition: both inputs nullptr.
  // Observable behavior requirement: at minimum, the call should be safe to make.
  ASSERT_NO_FATAL_FAILURE({
    PopplerDest* out = _poppler_dest_new_goto(nullptr, nullptr);
    (void)out;
  });
}

TEST_F(PopplerDestNewGotoTest_2304, CallWithNonNullDocumentNullDestDoesNotCrash_2304) {
  // Boundary condition: document provided, link_dest is nullptr.
  PopplerDocument* doc = MakeDummyDocument_2304();
  ASSERT_NE(doc, nullptr);

  ASSERT_NO_FATAL_FAILURE({
    PopplerDest* out = _poppler_dest_new_goto(doc, nullptr);
    (void)out;
  });

  FreeDummyDocument_2304(doc);
}

TEST_F(PopplerDestNewGotoTest_2304, CallWithNullDocumentNonNullDestPointerDoesNotDereferenceInTest_2304) {
  // Boundary-ish: link_dest pointer is non-null, but we intentionally do NOT construct a real LinkDest,
  // because doing so would require Poppler core types (Array, etc.) and would risk relying on internals.
  //
  // We only verify that the wrapper can be invoked with an arbitrary non-null pointer without the test
  // itself dereferencing it. If the implementation dereferences it and crashes, that's observable.
  LinkDest* opaque_link_dest = reinterpret_cast<LinkDest*>(0x1);  // intentionally invalid sentinel

  ASSERT_NO_FATAL_FAILURE({
    // Some implementations may crash if they dereference link_dest without checking;
    // this test captures that as an observable failure if it occurs.
    PopplerDest* out = _poppler_dest_new_goto(nullptr, opaque_link_dest);
    (void)out;
  });
}

TEST_F(PopplerDestNewGotoTest_2304, CallWithNonNullDocumentAndOpaqueDestPointerDoesNotDereferenceInTest_2304) {
  // Another boundary/error-style case: both pointers non-null, but link_dest is opaque/sentinel.
  // This helps cover "exceptional/error cases" through observable outcomes (e.g., crash vs no crash).
  PopplerDocument* doc = MakeDummyDocument_2304();
  ASSERT_NE(doc, nullptr);

  LinkDest* opaque_link_dest = reinterpret_cast<LinkDest*>(0x1);  // intentionally invalid sentinel

  ASSERT_NO_FATAL_FAILURE({
    PopplerDest* out = _poppler_dest_new_goto(doc, opaque_link_dest);
    (void)out;
  });

  FreeDummyDocument_2304(doc);
}

}  // namespace