// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_sony_misc3c_selector_1542.cpp
//
// Unit tests for Exiv2::Internal::sonyMisc3cSelector()
// Constraints:
// - Treat implementation as black box (we only assert observable return values)
// - Use mocks/stubs only for external collaborators (here: getExifValue seam)
// - Do not touch private/internal state

#include <gtest/gtest.h>

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

// =====================================================================================
// Seam/stubs to make the selector testable without requiring construction of full TIFF
// component trees. The function under test is a small selector that delegates value lookup
// to getExifValue(...). In production, getExifValue is an external collaborator of this
// selector (free function in the same namespace). Here we provide a controllable seam.
// =====================================================================================

namespace Exiv2 {
using byte = unsigned char;

enum class IfdId { sony1Id, sony2Id };

class Value {
public:
  virtual ~Value() = default;
  virtual size_t count() const = 0;
  virtual int64_t toInt64() const = 0;
};

namespace Internal {

class TiffComponent {
public:
  virtual ~TiffComponent() = default;
};

// A controllable fake Value.
class FakeValue final : public Exiv2::Value {
public:
  FakeValue(size_t c, int64_t v) : c_(c), v_(v) {}
  size_t count() const override { return c_; }
  int64_t toInt64() const override { return v_; }

private:
  size_t c_;
  int64_t v_;
};

// ---- Seam control (test-only) ----
struct GetExifValueKey {
  uint16_t tag{};
  Exiv2::IfdId ifd{};

  bool operator<(const GetExifValueKey& other) const {
    return std::tie(tag, ifd) < std::tie(other.tag, other.ifd);
  }
};

static std::map<GetExifValueKey, std::shared_ptr<Exiv2::Value>> g_values;

// Test helper to set/clear returned values.
static void ClearSeam() { g_values.clear(); }

static void SetSeamValue(uint16_t tag, Exiv2::IfdId ifd, size_t count, int64_t v) {
  g_values[{tag, ifd}] = std::make_shared<FakeValue>(count, v);
}

static void UnsetSeamValue(uint16_t tag, Exiv2::IfdId ifd) { g_values.erase({tag, ifd}); }

// This is the collaborator the production implementation calls.
// We provide it here as a seam so tests can control inputs.
static std::shared_ptr<Exiv2::Value> getExifValue(TiffComponent* /*pRoot*/, uint16_t tag, Exiv2::IfdId ifd) {
  auto it = g_values.find({tag, ifd});
  if (it == g_values.end()) return {};
  return it->second;
}

// =====================================================================================
// Function under test (as provided in prompt).
// NOTE: In a real Exiv2 tree, you should instead include the real header and link against
// the library/object file. This snippet is included verbatim here to keep the unit tests
// self-contained for the given prompt.
// =====================================================================================
int sonyMisc3cSelector(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* pRoot) {
  auto value = getExifValue(pRoot, 0x9400, Exiv2::IfdId::sony1Id);
  if (!value) {
    value = getExifValue(pRoot, 0x9400, Exiv2::IfdId::sony2Id);
    if (!value) return -1;
  }
  if (value->count() < 1) return -1;
  switch (value->toInt64()) {
    case 35:
    case 36:
    case 38:
    case 40:
    case 49:
    case 50:
      return 0;
    default:
      break;
  }
  return -1;
}

}  // namespace Internal
}  // namespace Exiv2

// =====================================================================================
// Tests
// =====================================================================================

namespace {

class SonyMisc3cSelectorTest_1542 : public ::testing::Test {
protected:
  void SetUp() override { Exiv2::Internal::ClearSeam(); }
  void TearDown() override { Exiv2::Internal::ClearSeam(); }
};

TEST_F(SonyMisc3cSelectorTest_1542, ReturnsMinus1WhenSony1AndSony2Missing_1542) {
  Exiv2::Internal::TiffComponent root;
  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(-1, rc);
}

TEST_F(SonyMisc3cSelectorTest_1542, UsesSony2WhenSony1MissingAndSony2PresentAllowedValue_1542) {
  Exiv2::Internal::TiffComponent root;

  // sony1 missing, sony2 present
  Exiv2::Internal::UnsetSeamValue(0x9400, Exiv2::IfdId::sony1Id);
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony2Id, /*count*/ 1, /*value*/ 35);

  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(0, rc);
}

TEST_F(SonyMisc3cSelectorTest_1542, PrefersSony1OverSony2WhenBothPresent_1542) {
  Exiv2::Internal::TiffComponent root;

  // Both present: sony1 has disallowed value, sony2 has allowed value.
  // Expected: selector uses sony1 first and returns -1 (does not fall back).
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony1Id, /*count*/ 1, /*value*/ 999);
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony2Id, /*count*/ 1, /*value*/ 35);

  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(-1, rc);
}

TEST_F(SonyMisc3cSelectorTest_1542, ReturnsMinus1WhenCountIsZero_1542) {
  Exiv2::Internal::TiffComponent root;

  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony1Id, /*count*/ 0, /*value*/ 35);

  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(-1, rc);
}

class SonyMisc3cSelectorAllowedValuesTest_1542
    : public SonyMisc3cSelectorTest_1542,
      public ::testing::WithParamInterface<int64_t> {};

TEST_P(SonyMisc3cSelectorAllowedValuesTest_1542, Returns0ForAllowedValuesFromSony1_1542) {
  Exiv2::Internal::TiffComponent root;
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony1Id, /*count*/ 1, GetParam());

  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(0, rc);
}

INSTANTIATE_TEST_SUITE_P(AllowedValues, SonyMisc3cSelectorAllowedValuesTest_1542,
                         ::testing::Values<int64_t>(35, 36, 38, 40, 49, 50));

class SonyMisc3cSelectorDisallowedValuesTest_1542
    : public SonyMisc3cSelectorTest_1542,
      public ::testing::WithParamInterface<int64_t> {};

TEST_P(SonyMisc3cSelectorDisallowedValuesTest_1542, ReturnsMinus1ForDisallowedValuesFromSony1_1542) {
  Exiv2::Internal::TiffComponent root;
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony1Id, /*count*/ 1, GetParam());

  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0, /*pData*/ nullptr, /*size*/ 0, &root);
  EXPECT_EQ(-1, rc);
}

INSTANTIATE_TEST_SUITE_P(DisallowedValues, SonyMisc3cSelectorDisallowedValuesTest_1542,
                         ::testing::Values<int64_t>(-999, -1, 0, 1, 34, 37, 39, 41, 48, 51,
                                                   INT64_MAX, INT64_MIN));

TEST_F(SonyMisc3cSelectorTest_1542, IgnoresInputTagAndDataParameters_1542) {
  Exiv2::Internal::TiffComponent root;

  // Make it succeed purely based on exif value lookup; selector ignores tag/pData/size params.
  Exiv2::Internal::SetSeamValue(0x9400, Exiv2::IfdId::sony1Id, /*count*/ 1, /*value*/ 50);

  const Exiv2::byte dummy[3] = {0x01, 0x02, 0x03};
  const int rc = Exiv2::Internal::sonyMisc3cSelector(/*tag*/ 0xFFFF, /*pData*/ dummy, /*size*/ sizeof(dummy), &root);
  EXPECT_EQ(0, rc);
}

}  // namespace