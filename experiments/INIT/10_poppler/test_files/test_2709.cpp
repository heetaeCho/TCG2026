// HtmlOutputDev_needNonText_test_2709.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Include the real header under test.
#include "HtmlOutputDev.h"

// Some builds may require these forward declarations/types to be visible via the header;
// we don't introduce or depend on their definitions here.

namespace {

class HtmlOutputDevTest_2709 : public ::testing::Test {
protected:
  // Helper: construct HtmlOutputDev in a way that compiles in both of these situations:
  //  1) HtmlOutputDev is default-constructible (as in the "Partial Code" snippet).
  //  2) HtmlOutputDev requires a complex ctor (as listed in the optional dependency block).
  //
  // We do NOT assert anything about ctor behavior besides being able to obtain an object
  // instance when possible. We only test observable behavior of needNonText().
  template <typename T>
  static T *makeDeviceOrNull() {
    if constexpr (std::is_default_constructible_v<T>) {
      return new T();
    } else if constexpr (std::is_constructible_v<T,
                                                 /*Catalog*/ void *,
                                                 const char *,
                                                 const char *,
                                                 const char *,
                                                 const char *,
                                                 const char *,
                                                 const char *,
                                                 bool,
                                                 int,
                                                 bool>) {
      // We intentionally pass benign placeholder values.
      // This is only to obtain an instance so we can exercise needNonText().
      // If the real implementation cannot tolerate these, the test will fail
      // (observable behavior), but we do not infer internals.
      return new T(reinterpret_cast<void *>(nullptr),
                   "dummy.html",
                   "title",
                   "author",
                   "keywords",
                   "subject",
                   "date",
                   /*rawOrder=*/false,
                   /*firstPage=*/1,
                   /*outline=*/false);
    } else {
      // Unknown constructor shape: cannot safely instantiate.
      return nullptr;
    }
  }
};

TEST_F(HtmlOutputDevTest_2709, NeedNonTextReturnsTrue_2709) {
  HtmlOutputDev *dev = makeDeviceOrNull<HtmlOutputDev>();
  ASSERT_NE(dev, nullptr) << "HtmlOutputDev could not be instantiated with the available constructors.";

  EXPECT_TRUE(dev->needNonText());

  delete dev;
}

TEST_F(HtmlOutputDevTest_2709, NeedNonTextIsStableAcrossMultipleCalls_2709) {
  HtmlOutputDev *dev = makeDeviceOrNull<HtmlOutputDev>();
  ASSERT_NE(dev, nullptr) << "HtmlOutputDev could not be instantiated with the available constructors.";

  // Boundary-ish behavior: repeated calls should be consistent/side-effect free
  // from the public observer's point of view.
  EXPECT_TRUE(dev->needNonText());
  EXPECT_TRUE(dev->needNonText());
  EXPECT_TRUE(dev->needNonText());

  delete dev;
}

TEST_F(HtmlOutputDevTest_2709, NeedNonTextVirtualDispatchThroughBasePointer_2709) {
  HtmlOutputDev *dev = makeDeviceOrNull<HtmlOutputDev>();
  ASSERT_NE(dev, nullptr) << "HtmlOutputDev could not be instantiated with the available constructors.";

  // Verify observable behavior through polymorphic interface (if OutputDev is a base).
  // This is an external interaction verification in the sense of public virtual dispatch.
  OutputDev *base = dev;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->needNonText());

  delete dev;
}

} // namespace