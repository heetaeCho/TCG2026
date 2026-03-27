// File: test_sony2FpSelector_1540.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>

namespace Exiv2 {
using byte = unsigned char;

namespace Internal {

// ---- Minimal seam types + collaborator stub (external dependency) ----
struct TiffComponent {};

// Test-controlled model string returned by getExifModel().
static thread_local std::string g_testExifModel;

std::string getExifModel(TiffComponent* /*pRoot*/) {
  return g_testExifModel;
}

// ---- SUT: provided implementation (verbatim) ----
int sony2FpSelector(uint16_t /*tag*/, const byte* /*pData*/, size_t /*size*/, TiffComponent* pRoot) {
  std::string model = getExifModel(pRoot);
  for (auto str : {"SLT-", "HV", "ILCA-"})
    if (model.starts_with(str)) return -1;
  return 0;
}

}  // namespace Internal
}  // namespace Exiv2

// -------------------- Tests --------------------

class Sony2FpSelectorTest_1540 : public ::testing::Test {
 protected:
  void SetModel(const std::string& model) { Exiv2::Internal::g_testExifModel = model; }
};

TEST_F(Sony2FpSelectorTest_1540, ReturnsMinusOneForSLTPrefix_1540) {
  SetModel("SLT-A99V");
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, ReturnsMinusOneForHVPrefix_1540) {
  SetModel("HV-123");
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, ReturnsMinusOneForILCAPrefix_1540) {
  SetModel("ILCA-77M2");
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, ReturnsZeroForNonMatchingModel_1540) {
  SetModel("DSC-RX100");
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(0, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, BoundaryEmptyModelReturnsZero_1540) {
  SetModel("");
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(0, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, BoundaryExactPrefixOnlyMatches_1540) {
  Exiv2::Internal::TiffComponent root;

  SetModel("SLT-");
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));

  SetModel("HV");
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));

  SetModel("ILCA-");
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, CaseSensitivityLowercaseDoesNotMatch_1540) {
  SetModel("slt-a99");  // different case
  Exiv2::Internal::TiffComponent root;
  EXPECT_EQ(0, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
}

TEST_F(Sony2FpSelectorTest_1540, TagDataSizeDoNotAffectResult_1540) {
  SetModel("ILCA-7M4");
  Exiv2::Internal::TiffComponent root;

  const Exiv2::byte dummy[3] = {0x01, 0x02, 0x03};

  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, &root));
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0xFFFFu, dummy, sizeof(dummy), &root));
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(123u, dummy, 1u, &root));
}

TEST_F(Sony2FpSelectorTest_1540, NullRootIsHandledAndUsesModel_1540) {
  // Observable behavior: return depends on the model string provided by the collaborator.
  SetModel("SLT-A58");
  EXPECT_EQ(-1, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, nullptr));

  SetModel("DSC-WX500");
  EXPECT_EQ(0, Exiv2::Internal::sony2FpSelector(0, nullptr, 0, nullptr));
}