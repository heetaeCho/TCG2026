// TEST_ID 484
// Unit tests for GfxDeviceNColorSpace::getColorantName(int)
//
// Constraints respected:
// - Treat implementation as black box (no internal logic assumptions).
// - Use only public interface and observable behavior.
// - No access to private state.

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

// Poppler header under test
#include "poppler/GfxState.h"

namespace {

class GfxDeviceNColorSpaceTest_484 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxDeviceNColorSpace> MakeCS(std::vector<std::string> names) {
    const int nComps = static_cast<int>(names.size());

    // Provide minimal/empty collaborators; tests only exercise getColorantName().
    std::unique_ptr<GfxColorSpace> alt;  // null
    std::unique_ptr<Function> func;      // null
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> sepsCS;  // empty

    return std::make_unique<GfxDeviceNColorSpace>(nComps, std::move(names), std::move(alt), std::move(func),
                                                  std::move(sepsCS));
  }
};

TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_ReturnsExpectedForFirstIndex_484) {
  auto cs = MakeCS({"Cyan", "Magenta", "Yellow"});
  const std::string &name0 = cs->getColorantName(0);
  EXPECT_EQ(name0, "Cyan");
}

TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_ReturnsExpectedForLastIndex_484) {
  auto cs = MakeCS({"Cyan", "Magenta", "Yellow", "Black"});
  const std::string &nameLast = cs->getColorantName(cs->getNComps() - 1);
  EXPECT_EQ(nameLast, "Black");
}

TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_ReturnsReferenceStableForSameIndex_484) {
  auto cs = MakeCS({"SpotA", "SpotB"});

  const std::string &a1 = cs->getColorantName(1);
  const std::string &a2 = cs->getColorantName(1);

  EXPECT_EQ(a1, "SpotB");
  EXPECT_EQ(a2, "SpotB");
  // Observable behavior: function returns a const reference; repeated calls for same index
  // should reasonably refer to the same underlying string object.
  EXPECT_EQ(&a1, &a2);
}

TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_DifferentIndicesCanReturnDifferentNames_484) {
  auto cs = MakeCS({"Red", "Green", "Blue"});

  const std::string &n0 = cs->getColorantName(0);
  const std::string &n1 = cs->getColorantName(1);
  const std::string &n2 = cs->getColorantName(2);

  EXPECT_EQ(n0, "Red");
  EXPECT_EQ(n1, "Green");
  EXPECT_EQ(n2, "Blue");
  EXPECT_NE(n0, n1);
  EXPECT_NE(n1, n2);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(GfxDeviceNColorSpaceTest_484, GetColorantName_OutOfRangeIndexMayDie_484) {
  auto cs = MakeCS({"OnlyOne"});

  // Behavior for out-of-range is not specified by the interface here; if the implementation
  // asserts/aborts, this test verifies that observable error behavior.
  // If it does not die in your build, adjust by disabling this test or updating expectations.
  EXPECT_DEATH({ (void)cs->getColorantName(1); }, ".*");
}
#endif

}  // namespace