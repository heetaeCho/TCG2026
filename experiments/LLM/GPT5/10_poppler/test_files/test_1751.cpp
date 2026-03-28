// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for CairoFontEngine.cc (_free_type3_font_info)
// TEST_ID: 1751

#include <gtest/gtest.h>

#include <memory>

// NOTE:
// _free_type3_font_info is a file-local (static) function inside CairoFontEngine.cc.
// To test it directly, we include the .cc here so the function is in this TU.
// This pattern assumes the test target does NOT also link a separately-compiled
// CairoFontEngine.cc object file (to avoid duplicate symbols).
#include "CairoFontEngine.cc"

namespace {

class FreeType3FontInfoTest_1751 : public ::testing::Test {};

TEST_F(FreeType3FontInfoTest_1751, NullClosureDies_1751)
{
  // Observable behavior: the function unconditionally dereferences closure.
  // Passing nullptr is an error case; verify it crashes (death test).
  ASSERT_DEATH(
      {
        _free_type3_font_info(nullptr);
      },
      ".*");
}

TEST_F(FreeType3FontInfoTest_1751, NullMembersDoNotCrash_1751)
{
  // Boundary case: deleting null pointers is valid in C++.
  // Construct type3_font_info_t with null collaborators, then free it.
  //
  // This test only asserts the observable behavior "does not crash".
  // It does not inspect or rely on any internal state.
  auto font = std::shared_ptr<GfxFont>(); // empty
  PDFDoc *doc = nullptr;
  CairoFontEngine *engine = nullptr;
  CairoOutputDev *outputDev = nullptr;
  Gfx *gfx = nullptr;

  auto *info = new type3_font_info_t(font, doc, engine, outputDev, gfx);
  ASSERT_NO_FATAL_FAILURE(_free_type3_font_info(info));
}

} // namespace