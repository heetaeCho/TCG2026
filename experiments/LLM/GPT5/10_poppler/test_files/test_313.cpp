// LinkRendition_getMedia_test_313.cpp

#include <gtest/gtest.h>

#if __has_include("poppler/Link.h")
#include "poppler/Link.h"
#else
#include "Link.h"
#endif

#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#elif __has_include("Object.h")
#include "Object.h"
#endif

namespace {

class LinkRenditionTest_313 : public ::testing::Test {
 protected:
  // Helper to create a minimal Object instance to feed into LinkRendition's ctor.
  // We intentionally do not assume anything about Object's internal state or type.
  static Object MakeDefaultObject() {
    // Most Poppler builds provide a default-constructible Object; this keeps the
    // test black-box and avoids relying on specific Object factories.
    return Object();
  }
};

TEST_F(LinkRenditionTest_313, GetMediaPointerIsStableAcrossCalls_313) {
  Object obj = MakeDefaultObject();
  LinkRendition action(&obj);

  const MediaRendition* p1 = action.getMedia();
  const MediaRendition* p2 = action.getMedia();

  // Purely observable invariant: repeated calls to a const getter should be stable.
  EXPECT_EQ(p1, p2);
}

TEST_F(LinkRenditionTest_313, GetMediaCallableOnConstInstance_313) {
  Object obj = MakeDefaultObject();
  LinkRendition action(&obj);

  const LinkRendition& constAction = action;

  const MediaRendition* p1 = action.getMedia();
  const MediaRendition* p2 = constAction.getMedia();

  EXPECT_EQ(p1, p2);
}

TEST_F(LinkRenditionTest_313, GetMediaUnaffectedByOtherConstQueries_313) {
  Object obj = MakeDefaultObject();
  LinkRendition action(&obj);

  const MediaRendition* before = action.getMedia();

  // Call other const methods (if available) to ensure getMedia is not affected.
  // We do not assert specific return values; only that calls are safe and do not
  // change the observable getMedia() pointer.
  (void)action.isOk();
  (void)action.getKind();
  (void)action.hasScreenAnnot();
  (void)action.getOperation();
  (void)action.getScript();

  const MediaRendition* after = action.getMedia();
  EXPECT_EQ(before, after);
}

TEST_F(LinkRenditionTest_313, GetMediaDoesNotThrow_313) {
  Object obj = MakeDefaultObject();
  LinkRendition action(&obj);

  EXPECT_NO_THROW({
    const MediaRendition* p = action.getMedia();
    (void)p;
  });
}

}  // namespace