// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_gfxcolorspace_getmapping_400.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <vector>

#include "GfxState.h"

namespace {

TEST(GfxColorSpaceTest_400, ReturnTypeIsConstVectorRef_400) {
  // Compile-time verification of the public interface contract:
  // getMapping() returns: const std::vector<int>&
  static_assert(std::is_same_v<decltype(std::declval<const GfxColorSpace&>().getMapping()),
                               const std::vector<int>&>,
                "GfxColorSpace::getMapping() must return const std::vector<int>&");

  // Also ensure it's a reference type (not a value).
  static_assert(std::is_reference_v<decltype(std::declval<const GfxColorSpace&>().getMapping())>,
                "GfxColorSpace::getMapping() must return a reference");
}

TEST(GfxColorSpaceTest_400, ReferenceIsStableAcrossCalls_400) {
  GfxColorSpace cs;

  const std::vector<int>* p1 = &cs.getMapping();
  const std::vector<int>* p2 = &cs.getMapping();

  // Observable behavior: multiple calls should reference the same object.
  EXPECT_EQ(p1, p2);
}

TEST(GfxColorSpaceTest_400, ReferenceIsSameThroughConstView_400) {
  GfxColorSpace cs;
  const GfxColorSpace& ccs = cs;

  const std::vector<int>* p_nonconst_obj = &cs.getMapping();
  const std::vector<int>* p_const_obj = &ccs.getMapping();

  EXPECT_EQ(p_nonconst_obj, p_const_obj);
}

TEST(GfxColorSpaceTest_400, ReturnedReferenceIsUsableForReadOnlyQueries_400) {
  GfxColorSpace cs;

  // We do not assume anything about contents. We only verify the returned
  // reference can be used for read-only operations without crashing.
  const auto& m = cs.getMapping();
  (void)m.size();
  (void)m.empty();

  SUCCEED();
}

}  // namespace