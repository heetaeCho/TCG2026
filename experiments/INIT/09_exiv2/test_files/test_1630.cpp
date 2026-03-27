// File: test_tiff_finder_1630.cpp
#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace {

using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffComponent;

// NOTE: There is a namespace named Exiv2::Internal::TiffVisitor that contains GoEvent,
// and a class Exiv2::Internal::TiffVisitor. We alias the *namespace* here.
namespace Tv = Exiv2::Internal::TiffVisitor;

class TiffFinderTest_1630 : public ::testing::Test {
 protected:
  static Tv::GoEvent Traverse() { return Tv::geTraverse; }
  static Tv::GoEvent KnownMakernote() { return Tv::geKnownMakernote; }

  static IfdId Ifd(int v) { return static_cast<IfdId>(v); }
};

TEST_F(TiffFinderTest_1630, ResultIsNullBeforeAnyMatch_1630) {
  TiffFinder finder(/*tag*/ 0x1234, /*group*/ Ifd(1));

  // No traversal yet; no object checked.
  EXPECT_EQ(finder.result(), nullptr);

  // Default go-flags should be true (observable via public go()).
  EXPECT_TRUE(finder.go(Traverse()));
  EXPECT_TRUE(finder.go(KnownMakernote()));
}

TEST_F(TiffFinderTest_1630, FindObjectDoesNotSetResultOnTagMismatch_1630) {
  const uint16_t wantTag = 0x1234;
  const IfdId wantGroup = Ifd(1);

  TiffFinder finder(wantTag, wantGroup);
  TiffComponent nonMatching(/*tag*/ static_cast<uint16_t>(wantTag + 1), /*group*/ wantGroup);

  finder.findObject(&nonMatching);

  EXPECT_EQ(finder.result(), nullptr);

  // No match => traversal should not have been stopped by findObject().
  EXPECT_TRUE(finder.go(Traverse()));
}

TEST_F(TiffFinderTest_1630, FindObjectDoesNotSetResultOnGroupMismatch_1630) {
  const uint16_t wantTag = 0x1234;
  const IfdId wantGroup = Ifd(1);

  TiffFinder finder(wantTag, wantGroup);
  TiffComponent nonMatching(/*tag*/ wantTag, /*group*/ Ifd(2));

  finder.findObject(&nonMatching);

  EXPECT_EQ(finder.result(), nullptr);
  EXPECT_TRUE(finder.go(Traverse()));
}

TEST_F(TiffFinderTest_1630, FindObjectSetsResultAndStopsTraverseOnExactMatch_1630) {
  const uint16_t wantTag = 0x1234;
  const IfdId wantGroup = Ifd(1);

  TiffFinder finder(wantTag, wantGroup);
  TiffComponent matching(/*tag*/ wantTag, /*group*/ wantGroup);

  ASSERT_TRUE(finder.go(Traverse()));  // precondition observable from interface
  finder.findObject(&matching);

  EXPECT_EQ(finder.result(), &matching);

  // On match, findObject() should stop traversal (observable via go()).
  EXPECT_FALSE(finder.go(Traverse()));

  // Only traverse flag is expected to change here; the other flag should remain untouched.
  EXPECT_TRUE(finder.go(KnownMakernote()));
}

TEST_F(TiffFinderTest_1630, OnceMatchedLaterMismatchesDoNotOverrideResult_1630) {
  const uint16_t wantTag = 0x1234;
  const IfdId wantGroup = Ifd(1);

  TiffFinder finder(wantTag, wantGroup);

  TiffComponent firstMatch(/*tag*/ wantTag, /*group*/ wantGroup);
  TiffComponent laterNonMatch(/*tag*/ wantTag, /*group*/ Ifd(2));

  finder.findObject(&firstMatch);
  ASSERT_EQ(finder.result(), &firstMatch);

  finder.findObject(&laterNonMatch);

  // Observable expectation: mismatch should not change the previously found result.
  EXPECT_EQ(finder.result(), &firstMatch);
}

TEST_F(TiffFinderTest_1630, BoundaryValuesForTagCanMatch_1630) {
  // Boundary tags: 0x0000 and 0xFFFF.
  const IfdId group = Ifd(0);

  {
    TiffFinder finder(/*tag*/ 0x0000, group);
    TiffComponent matching(/*tag*/ 0x0000, group);
    finder.findObject(&matching);
    EXPECT_EQ(finder.result(), &matching);
    EXPECT_FALSE(finder.go(Traverse()));
  }

  {
    TiffFinder finder(/*tag*/ 0xFFFF, group);
    TiffComponent matching(/*tag*/ 0xFFFF, group);
    finder.findObject(&matching);
    EXPECT_EQ(finder.result(), &matching);
    EXPECT_FALSE(finder.go(Traverse()));
  }
}

TEST_F(TiffFinderTest_1630, InitChangesSearchCriteriaAndClearsPreviousResult_1630) {
  // This test covers observable effects of init(): after re-init, a new match should be found.
  // If init() also clears any previous result, result() should reflect that (observable).
  TiffFinder finder(/*tag*/ 0x1111, /*group*/ Ifd(1));

  TiffComponent firstMatch(/*tag*/ 0x1111, /*group*/ Ifd(1));
  finder.findObject(&firstMatch);
  ASSERT_EQ(finder.result(), &firstMatch);

  // Re-initialize to a different (tag, group) and try matching a different object.
  finder.init(/*tag*/ 0x2222, /*group*/ Ifd(2));

  // After init(), traversal should be allowed again (observable) so a new match can stop it.
  EXPECT_TRUE(finder.go(Traverse()));

  TiffComponent secondMatch(/*tag*/ 0x2222, /*group*/ Ifd(2));
  finder.findObject(&secondMatch);

  EXPECT_EQ(finder.result(), &secondMatch);
  EXPECT_FALSE(finder.go(Traverse()));
}

}  // namespace