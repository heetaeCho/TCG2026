// SplashOutBlendColorDodge_tests_1582.cc
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <vector>

// Poppler / Splash headers
#include "splash/SplashTypes.h"

// Include the implementation file to access the internal-linkage (static) function.
// This is a common unit-testing technique for file-local helpers.
#include "poppler/SplashOutputDev.cc"

namespace {

static int NumComps(SplashColorMode cm) {
  // splashColorModeNComps is provided by Splash / Poppler.
  return splashColorModeNComps[cm];
}

static std::vector<Guchar> MakeColor(SplashColorMode cm, const std::vector<int> &vals) {
  const int n = NumComps(cm);
  std::vector<Guchar> c(n, 0);
  for (int i = 0; i < n && i < static_cast<int>(vals.size()); ++i) {
    int v = vals[i];
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    c[i] = static_cast<Guchar>(v);
  }
  return c;
}

static std::vector<Guchar> MakeFilled(SplashColorMode cm, int v) {
  const int n = NumComps(cm);
  v = std::clamp(v, 0, 255);
  return std::vector<Guchar>(n, static_cast<Guchar>(v));
}

static std::vector<Guchar> Invert255(const std::vector<Guchar> &c) {
  std::vector<Guchar> out = c;
  for (auto &x : out) {
    x = static_cast<Guchar>(255 - x);
  }
  return out;
}

static void Call(SplashColorMode cm,
                 std::vector<Guchar> &src,
                 std::vector<Guchar> &dest,
                 std::vector<Guchar> &blend) {
  ASSERT_EQ(src.size(), static_cast<size_t>(NumComps(cm)));
  ASSERT_EQ(dest.size(), static_cast<size_t>(NumComps(cm)));
  ASSERT_EQ(blend.size(), static_cast<size_t>(NumComps(cm)));
  splashOutBlendColorDodge(src.data(), dest.data(), blend.data(), cm);
}

static void ExpectAllInRange(const std::vector<Guchar> &c) {
  for (auto v : c) {
    EXPECT_LE(static_cast<int>(v), 255);
    EXPECT_GE(static_cast<int>(v), 0);
  }
}

} // namespace

class SplashOutBlendColorDodgeTest_1582 : public ::testing::Test {};

// ---------- Non-inverting modes (most common) ----------

TEST_F(SplashOutBlendColorDodgeTest_1582, Src255ForcesBlend255InRgb8_1582) {
  const SplashColorMode cm = splashModeRGB8;

  auto src = MakeFilled(cm, 255);
  auto dest = MakeColor(cm, {10, 20, 30});
  auto blend = MakeFilled(cm, 0);

  const auto src_before = src;
  const auto dest_before = dest;

  Call(cm, src, dest, blend);

  // Observable safety: inputs should not be modified.
  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);

  // Boundary observable behavior.
  for (auto v : blend) {
    EXPECT_EQ(static_cast<int>(v), 255);
  }
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Src0KeepsBlendEqualToDestInRgb8_1582) {
  const SplashColorMode cm = splashModeRGB8;

  auto src = MakeFilled(cm, 0);
  auto dest = MakeColor(cm, {1, 128, 254});
  auto blend = MakeFilled(cm, 0);

  const auto src_before = src;
  const auto dest_before = dest;

  Call(cm, src, dest, blend);

  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);
  EXPECT_EQ(blend, dest_before);
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Dest0ProducesZeroBlendWhenSrcNot255InRgb8_1582) {
  const SplashColorMode cm = splashModeRGB8;

  auto src = MakeColor(cm, {1, 2, 3});
  auto dest = MakeFilled(cm, 0);
  auto blend = MakeFilled(cm, 123);

  Call(cm, src, dest, blend);

  for (auto v : blend) {
    EXPECT_EQ(static_cast<int>(v), 0);
  }
}

TEST_F(SplashOutBlendColorDodgeTest_1582, OutputIsClampedTo255InRgb8_1582) {
  const SplashColorMode cm = splashModeRGB8;

  // Values near the extremes are good for verifying clamping behavior.
  auto src = MakeColor(cm, {254, 254, 254});
  auto dest = MakeColor(cm, {1, 200, 255});
  auto blend = MakeFilled(cm, 0);

  Call(cm, src, dest, blend);

  ExpectAllInRange(blend);
  // At least one channel should hit the top bound for this extreme input set.
  EXPECT_TRUE(std::any_of(blend.begin(), blend.end(),
                          [](Guchar v) { return static_cast<int>(v) == 255; }));
}

TEST_F(SplashOutBlendColorDodgeTest_1582, WorksAcrossSeveralNonInvertingModes_1582) {
  const SplashColorMode modes[] = {splashModeMono1, splashModeMono8, splashModeRGB8,
                                  splashModeBGR8, splashModeXBGR8};

  for (SplashColorMode cm : modes) {
    SCOPED_TRACE(static_cast<int>(cm));

    auto src = MakeFilled(cm, 0);
    auto dest = MakeFilled(cm, 77);
    auto blend = MakeFilled(cm, 0);

    const auto src_before = src;
    const auto dest_before = dest;

    Call(cm, src, dest, blend);

    EXPECT_EQ(src, src_before);
    EXPECT_EQ(dest, dest_before);
    EXPECT_EQ(blend, dest_before);

    // Also verify src==255 forces blend==255 for these modes.
    src = MakeFilled(cm, 255);
    dest = MakeFilled(cm, 33);
    blend = MakeFilled(cm, 0);

    Call(cm, src, dest, blend);

    for (auto v : blend) {
      EXPECT_EQ(static_cast<int>(v), 255);
    }
  }
}

// ---------- Inverting modes: CMYK8 / DeviceN8 ----------

TEST_F(SplashOutBlendColorDodgeTest_1582, InputsRemainUnchangedInCmyk8_1582) {
  const SplashColorMode cm = splashModeCMYK8;

  auto src = MakeColor(cm, {5, 100, 200, 250});
  auto dest = MakeColor(cm, {250, 200, 100, 5});
  auto blend = MakeFilled(cm, 0);

  const auto src_before = src;
  const auto dest_before = dest;

  Call(cm, src, dest, blend);

  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);
  ExpectAllInRange(blend);
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Src255YieldsBlendEqualToDestInCmyk8_1582) {
  const SplashColorMode cm = splashModeCMYK8;

  auto src = MakeFilled(cm, 255);
  auto dest = MakeColor(cm, {1, 2, 3, 4});
  auto blend = MakeFilled(cm, 0);

  const auto dest_before = dest;

  Call(cm, src, dest, blend);

  EXPECT_EQ(blend, dest_before);
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Src0YieldsZeroBlendInCmyk8_1582) {
  const SplashColorMode cm = splashModeCMYK8;

  auto src = MakeFilled(cm, 0);
  auto dest = MakeColor(cm, {1, 2, 3, 4});
  auto blend = MakeFilled(cm, 123);

  Call(cm, src, dest, blend);

  for (auto v : blend) {
    EXPECT_EQ(static_cast<int>(v), 0);
  }
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Src255YieldsBlendEqualToDestInDeviceN8_1582) {
  const SplashColorMode cm = splashModeDeviceN8;

  auto src = MakeFilled(cm, 255);

  // Use a pattern across all components (DeviceN component count is mode-dependent).
  std::vector<int> vals;
  vals.reserve(NumComps(cm));
  for (int i = 0; i < NumComps(cm); ++i) {
    vals.push_back((i * 37) % 256);
  }
  auto dest = MakeColor(cm, vals);
  auto blend = MakeFilled(cm, 0);

  const auto src_before = src;
  const auto dest_before = dest;

  Call(cm, src, dest, blend);

  EXPECT_EQ(src, src_before);
  EXPECT_EQ(dest, dest_before);
  EXPECT_EQ(blend, dest_before);
}

TEST_F(SplashOutBlendColorDodgeTest_1582, Src0YieldsZeroBlendInDeviceN8_1582) {
  const SplashColorMode cm = splashModeDeviceN8;

  auto src = MakeFilled(cm, 0);
  std::vector<int> vals;
  vals.reserve(NumComps(cm));
  for (int i = 0; i < NumComps(cm); ++i) {
    vals.push_back(255 - ((i * 53) % 256));
  }
  auto dest = MakeColor(cm, vals);
  auto blend = MakeFilled(cm, 200);

  Call(cm, src, dest, blend);

  for (auto v : blend) {
    EXPECT_EQ(static_cast<int>(v), 0);
  }
}