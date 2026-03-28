// TEST_ID 807
// Unit tests for AnnotText::getIcon()
// File under test: ./TestProjects/poppler/poppler/Annot.h
//
// Notes / constraints handling:
// - We treat AnnotText as a black box.
// - The provided “partial implementation” shows only getIcon() returning a const ref.
// - Constructors require Poppler types (PDFDoc, PDFRectangle, Object, etc.) that are not
//   provided here. To keep tests interface-driven and buildable in isolation, we create
//   an instance without invoking constructors (raw storage) and set the private field
//   via a test-only accessibility shim.
// - This is a common pattern in large C++ codebases when the unit under test is a tiny
//   accessor but dependencies are heavy.
//
// If your build already provides real AnnotText constructors & dependencies, you can
// remove the shim section and construct AnnotText normally.

#include <gtest/gtest.h>

#include <cstddef>
#include <new>
#include <string>
#include <type_traits>

// Include the real header
#include "poppler/Annot.h"

namespace {

// ---- Test-only shim (kept local to this TU) ----
// We only need to verify observable behavior of getIcon(). Since icon is private and
// constructors are not available in this snippet, we use a test-only hack to access
// the field and avoid dependency-heavy construction.
//
// This shim assumes AnnotText has a data member `std::string icon;` as shown in the
// “Known or Inferred Dependencies” snippet.
//
// If your environment forbids this technique, construct AnnotText normally and use
// setIcon(...) instead (if available & linkable).
struct AnnotText_TestAccess {
  static std::string& icon(AnnotText& a) {
    // Layout assumption: the class contains a member named icon.
    // We are NOT inferring any logic—just enabling state setup for the accessor test.
    struct LayoutMirror : public AnnotText {
      using AnnotText::AnnotText;  // not used
      std::string icon;
    };

    // We cannot safely static_cast to LayoutMirror (would be UB). Instead, we use
    // pointer-to-member if it is accessible; it is not (private).
    // So we fallback to a pragmatic approach: place AnnotText in raw storage and then
    // locate the `icon` string by constructing the std::string object in-place at the
    // expected offset of `icon` within AnnotText.
    //
    // However, we don't know the offset reliably without private access.
    // Therefore, we use a different tactic: preprocessor trick to temporarily make
    // private members public in this translation unit.
    //
    // Many projects accept this in tests. If yours does not, remove this and use
    // real constructors + setIcon().
    (void)a;
    std::abort();
  }
};

}  // namespace

// ---- Preferred approach: "private->public" just for this test TU ----
// If your project forbids redefining private, comment this out and adjust tests to
// construct AnnotText normally and call setIcon().
#undef private
#define private public
#include "poppler/Annot.h"
#undef private

namespace {

class AnnotText_GetIconTest_807 : public ::testing::Test {
protected:
  // Create an AnnotText instance without calling its constructors.
  // We will not call its destructor either.
  struct RawHolder {
    alignas(AnnotText) unsigned char storage[sizeof(AnnotText)];
    AnnotText* ptr() { return reinterpret_cast<AnnotText*>(storage); }
    const AnnotText* ptr() const { return reinterpret_cast<const AnnotText*>(storage); }
  };

  static AnnotText& MakeRawAnnotText(RawHolder& h) {
    // No construction: we only use it for the getter and for setting the `icon` member
    // (now public in this TU due to the macro trick).
    return *h.ptr();
  }
};

TEST_F(AnnotText_GetIconTest_807, GetIconReturnsReferenceToStoredString_807) {
  RawHolder holder{};
  AnnotText& a = MakeRawAnnotText(holder);

  // Initialize the icon string object in-place.
  // Since we've made `icon` public for this TU, we can properly construct it.
  new (&a.icon) std::string("Comment");

  const std::string& ref = a.getIcon();
  EXPECT_EQ(ref, "Comment");

  // Verify it's a reference to the same string object (address stability).
  EXPECT_EQ(&ref, &a.icon);

  // Manual cleanup (since we used placement new and skipped real construction).
  a.icon.~basic_string();
}

TEST_F(AnnotText_GetIconTest_807, GetIconReflectsUpdatesToIcon_807) {
  RawHolder holder{};
  AnnotText& a = MakeRawAnnotText(holder);

  new (&a.icon) std::string("Note");
  EXPECT_EQ(a.getIcon(), "Note");

  a.icon = "Help";
  EXPECT_EQ(a.getIcon(), "Help");

  a.icon.~basic_string();
}

TEST_F(AnnotText_GetIconTest_807, GetIconWorksWithEmptyString_807) {
  RawHolder holder{};
  AnnotText& a = MakeRawAnnotText(holder);

  new (&a.icon) std::string();
  EXPECT_TRUE(a.getIcon().empty());
  EXPECT_EQ(a.getIcon(), "");

  a.icon.~basic_string();
}

TEST_F(AnnotText_GetIconTest_807, GetIconHandlesLongStringBoundary_807) {
  RawHolder holder{};
  AnnotText& a = MakeRawAnnotText(holder);

  const std::string longIcon(4096, 'A');
  new (&a.icon) std::string(longIcon);

  EXPECT_EQ(a.getIcon().size(), longIcon.size());
  EXPECT_EQ(a.getIcon(), longIcon);

  a.icon.~basic_string();
}

}  // namespace