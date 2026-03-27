// HtmlOutputDev_isOk_test_2705.cc
#include <gtest/gtest.h>

#include "HtmlOutputDev.h"

// NOTE:
// - We treat HtmlOutputDev as a black box.
// - We do NOT access private/internal state.
// - We only test observable behavior via the public interface (isOk()) and virtual dispatch.

namespace {

class HtmlOutputDevTest_2705 : public ::testing::Test {
protected:
  // Helper that exercises construction paths using boundary-ish inputs, without
  // asserting internal semantics. We only assert that isOk() is callable and
  // returns a stable boolean value across repeated calls.
  static void ExpectIsOkStableAcrossCalls(HtmlOutputDev &dev) {
    const bool v1 = dev.isOk();
    const bool v2 = dev.isOk();
    const bool v3 = dev.isOk();
    EXPECT_EQ(v1, v2);
    EXPECT_EQ(v2, v3);
  }
};

// A derived type used only to verify observable polymorphic behavior.
// This does not simulate internal behavior of HtmlOutputDev; it only verifies
// that isOk() is virtual and that overriding works as expected.
class OverridingHtmlOutputDev_2705 : public HtmlOutputDev {
public:
  using HtmlOutputDev::HtmlOutputDev;

  bool isOk() override { return override_value_; }
  void set_override_value(bool v) { override_value_ = v; }

private:
  bool override_value_ = false;
};

} // namespace

TEST_F(HtmlOutputDevTest_2705, IsOk_ReturnsConsistentValue_AcrossRepeatedCalls_2705) {
  // Boundary/error-flavored construction: null catalog and null metadata strings.
  // We do NOT assume whether this is considered "ok"; we only assert isOk() is
  // callable and stable across multiple calls.
  OverridingHtmlOutputDev_2705 dev(
      /*catalogA=*/nullptr,
      /*fileName=*/"htmloutdev_test_2705.html",
      /*title=*/nullptr,
      /*author=*/nullptr,
      /*keywords=*/nullptr,
      /*subject=*/nullptr,
      /*date=*/nullptr,
      /*rawOrder=*/false,
      /*firstPage=*/1,
      /*outline=*/false);

  // Call the *base* implementation explicitly (qualified) to exercise the
  // provided HtmlOutputDev::isOk() implementation, regardless of our override.
  const bool v1 = dev.HtmlOutputDev::isOk();
  const bool v2 = dev.HtmlOutputDev::isOk();
  EXPECT_EQ(v1, v2);
}

TEST_F(HtmlOutputDevTest_2705, IsOk_BaseImplementation_Stable_ForBoundaryFirstPageValues_2705) {
  // firstPage boundary-ish values. We only check stability and that it returns a bool.
  {
    OverridingHtmlOutputDev_2705 dev(
        nullptr, "htmloutdev_test_2705_fp0.html", nullptr, nullptr, nullptr, nullptr, nullptr,
        /*rawOrder=*/false, /*firstPage=*/0, /*outline=*/false);
    ExpectIsOkStableAcrossCalls(dev);
    const bool base_v = dev.HtmlOutputDev::isOk();
    const bool base_v2 = dev.HtmlOutputDev::isOk();
    EXPECT_EQ(base_v, base_v2);
  }
  {
    OverridingHtmlOutputDev_2705 dev(
        nullptr, "htmloutdev_test_2705_fpneg.html", nullptr, nullptr, nullptr, nullptr, nullptr,
        /*rawOrder=*/false, /*firstPage=*/-1, /*outline=*/false);
    ExpectIsOkStableAcrossCalls(dev);
    const bool base_v = dev.HtmlOutputDev::isOk();
    const bool base_v2 = dev.HtmlOutputDev::isOk();
    EXPECT_EQ(base_v, base_v2);
  }
  {
    OverridingHtmlOutputDev_2705 dev(
        nullptr, "htmloutdev_test_2705_fpmax.html", nullptr, nullptr, nullptr, nullptr, nullptr,
        /*rawOrder=*/false, /*firstPage=*/INT32_MAX, /*outline=*/false);
    ExpectIsOkStableAcrossCalls(dev);
    const bool base_v = dev.HtmlOutputDev::isOk();
    const bool base_v2 = dev.HtmlOutputDev::isOk();
    EXPECT_EQ(base_v, base_v2);
  }
}

TEST_F(HtmlOutputDevTest_2705, IsOk_VirtualDispatch_CallsOverride_2705) {
  // This verifies an observable interaction: isOk() is virtual.
  // We do not inspect any internal state; we only confirm that calling isOk()
  // through a base pointer hits the override.
  OverridingHtmlOutputDev_2705 dev(
      nullptr, "htmloutdev_test_2705_vdispatch.html", nullptr, nullptr, nullptr, nullptr, nullptr,
      /*rawOrder=*/false, /*firstPage=*/1, /*outline=*/false);

  HtmlOutputDev *base_ptr = &dev;

  dev.set_override_value(false);
  EXPECT_FALSE(base_ptr->isOk());

  dev.set_override_value(true);
  EXPECT_TRUE(base_ptr->isOk());

  // Also confirm we can still directly invoke the base implementation explicitly.
  // We don't assert its value, only that it is callable and returns a stable bool.
  const bool base_v1 = dev.HtmlOutputDev::isOk();
  const bool base_v2 = dev.HtmlOutputDev::isOk();
  EXPECT_EQ(base_v1, base_v2);
}

TEST_F(HtmlOutputDevTest_2705, IsOk_DoesNotMutateObservedResult_WhenCalledRepeatedly_2705) {
  // Another normal-operation style check: repeated calls should not toggle.
  // (We do not assume "ok" true/false, only that the return is consistent.)
  OverridingHtmlOutputDev_2705 dev(
      nullptr, "htmloutdev_test_2705_repeat.html",
      /*title=*/"", /*author=*/"", /*keywords=*/"", /*subject=*/"", /*date=*/"",
      /*rawOrder=*/true,
      /*firstPage=*/1,
      /*outline=*/true);

  // Exercise the provided base implementation specifically.
  const bool b1 = dev.HtmlOutputDev::isOk();
  const bool b2 = dev.HtmlOutputDev::isOk();
  const bool b3 = dev.HtmlOutputDev::isOk();
  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b2, b3);
}