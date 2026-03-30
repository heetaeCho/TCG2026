// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffvisitor_int_tifffinder_visitifdmakernote_1638.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

class TiffFinderTest_1638 : public ::testing::Test {
 protected:
  // Use casts to avoid depending on any particular IfdId enumerator name/value.
  TiffFinderTest_1638() : finder_(static_cast<uint16_t>(0), static_cast<IfdId>(0)) {}

  TiffFinder finder_;
};

TEST_F(TiffFinderTest_1638, VisitIfdMakernote_NullptrDoesNotChangeNullResult_1638) {
  // Baseline: for a freshly constructed finder, result should be a valid query point.
  // We only assert observable behavior: result() remains nullptr after a nullptr visit.
  EXPECT_EQ(nullptr, finder_.result());

  finder_.visitIfdMakernote(nullptr);

  EXPECT_EQ(nullptr, finder_.result());
}

TEST_F(TiffFinderTest_1638, VisitIfdMakernote_NullptrAfterInitKeepsResultNull_1638) {
  finder_.init(static_cast<uint16_t>(0), static_cast<IfdId>(0));
  EXPECT_EQ(nullptr, finder_.result());

  finder_.visitIfdMakernote(nullptr);

  EXPECT_EQ(nullptr, finder_.result());
}

TEST_F(TiffFinderTest_1638, VisitIfdMakernote_NullptrIsIdempotentAcrossMultipleCalls_1638) {
  EXPECT_EQ(nullptr, finder_.result());

  finder_.visitIfdMakernote(nullptr);
  EXPECT_EQ(nullptr, finder_.result());

  finder_.visitIfdMakernote(nullptr);
  EXPECT_EQ(nullptr, finder_.result());

  finder_.visitIfdMakernote(nullptr);
  EXPECT_EQ(nullptr, finder_.result());
}

}  // namespace Internal
}  // namespace Exiv2