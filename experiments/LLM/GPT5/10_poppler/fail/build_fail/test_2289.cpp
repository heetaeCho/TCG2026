// File: poppler-action-dest-new-goto-test.cc
// Targets: static PopplerDest *dest_new_goto(PopplerDocument *document, const LinkDest *link_dest)
// TEST_ID: 2289

#include <gtest/gtest.h>

#include <memory>
#include <utility>
#include <vector>

// Poppler core
#include "poppler/Link.h"
#include "poppler/Object.h"

// Poppler glib
#include "glib/poppler-action.h"

// Glib
#include <glib.h>

// Include the .cc to access the static function under test.
#include "glib/poppler-action.cc"

namespace {

struct LinkDestOwned {
  std::unique_ptr<Array> arr;
  std::unique_ptr<LinkDest> dest;
};

static Object MakeIntObj(int v) {
  Object o;
  o.initInt(v);
  return o;
}

static Object MakeRealObj(double v) {
  Object o;
  o.initReal(v);
  return o;
}

static Object MakeNullObj() {
  Object o;
  o.initNull();
  return o;
}

static Object MakeNameObj(const char *name) {
  Object o;
  o.initName(name);
  return o;
}

static Object MakeRefObj(int num, int gen) {
  Object o;
  o.initRef(num, gen);
  return o;
}

static void ArrayAdd(Array *a, Object &&o) {
  // Poppler Array API varies slightly across versions; this call style is the
  // most common in modern Poppler. If your version uses a different signature,
  // adjust here (tests are otherwise black-box for dest_new_goto).
  a->add(std::move(o));
}

static LinkDestOwned MakeLinkDest_PageNum(LinkDestKind kind,
                                         int page_num,
                                         bool use_null_for_optional = false) {
  auto arr = std::make_unique<Array>(/*xref*/ nullptr);

  // page (int)
  ArrayAdd(arr.get(), MakeIntObj(page_num));

  // kind name and parameters (PDF destination array shape)
  switch (kind) {
    case destXYZ: {
      ArrayAdd(arr.get(), MakeNameObj("XYZ"));
      // left, top, zoom (nulls allowed)
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(12.25));
      ArrayAdd(arr.get(), MakeRealObj(34.5)); // top
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(1.75));
    } break;
    case destFit: {
      ArrayAdd(arr.get(), MakeNameObj("Fit"));
    } break;
    case destFitH: {
      ArrayAdd(arr.get(), MakeNameObj("FitH"));
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(99.0)); // top
    } break;
    case destFitV: {
      ArrayAdd(arr.get(), MakeNameObj("FitV"));
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(88.0)); // left
    } break;
    case destFitR: {
      ArrayAdd(arr.get(), MakeNameObj("FitR"));
      ArrayAdd(arr.get(), MakeRealObj(1.0));   // left
      ArrayAdd(arr.get(), MakeRealObj(2.0));   // bottom
      ArrayAdd(arr.get(), MakeRealObj(300.0)); // right
      ArrayAdd(arr.get(), MakeRealObj(400.0)); // top
    } break;
    case destFitB: {
      ArrayAdd(arr.get(), MakeNameObj("FitB"));
    } break;
    case destFitBH: {
      ArrayAdd(arr.get(), MakeNameObj("FitBH"));
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(77.0)); // top
    } break;
    case destFitBV: {
      ArrayAdd(arr.get(), MakeNameObj("FitBV"));
      ArrayAdd(arr.get(), use_null_for_optional ? MakeNullObj() : MakeRealObj(66.0)); // left
    } break;
    default:
      // Should not happen with known enum values; leave minimal.
      ArrayAdd(arr.get(), MakeNameObj("Fit"));
      break;
  }

  auto dest = std::make_unique<LinkDest>(*arr);
  return {std::move(arr), std::move(dest)};
}

static LinkDestOwned MakeLinkDest_PageRef(LinkDestKind kind, int ref_num, int ref_gen) {
  auto arr = std::make_unique<Array>(/*xref*/ nullptr);

  // page (ref)
  ArrayAdd(arr.get(), MakeRefObj(ref_num, ref_gen));

  // Keep parameters minimal per kind.
  switch (kind) {
    case destXYZ:
      ArrayAdd(arr.get(), MakeNameObj("XYZ"));
      ArrayAdd(arr.get(), MakeRealObj(10.0));
      ArrayAdd(arr.get(), MakeRealObj(20.0));
      ArrayAdd(arr.get(), MakeRealObj(1.0));
      break;
    case destFit:
      ArrayAdd(arr.get(), MakeNameObj("Fit"));
      break;
    default:
      // Use a commonly-valid shape for non-XYZ
      ArrayAdd(arr.get(), MakeNameObj("Fit"));
      break;
  }

  auto dest = std::make_unique<LinkDest>(*arr);
  return {std::move(arr), std::move(dest)};
}

struct KindMapping {
  LinkDestKind kind;
  PopplerDestType expected;
};

class DestNewGotoKindMappingTest_2289 : public ::testing::TestWithParam<KindMapping> {};

TEST_F(DestNewGotoKindMappingTest_2289, NullLinkDestReturnsUnknown_2289) {
  PopplerDest *d = dest_new_goto(/*document*/ nullptr, /*link_dest*/ nullptr);
  ASSERT_NE(d, nullptr);
  EXPECT_EQ(d->type, POPPLER_DEST_UNKNOWN);
  EXPECT_EQ(d->page_num, 0);
  // Prefer the public free function if available.
  poppler_dest_free(d);
}

INSTANTIATE_TEST_SUITE_P(
    KindToType,
    DestNewGotoKindMappingTest_2289,
    ::testing::Values(
        KindMapping{destXYZ, POPPLER_DEST_XYZ},
        KindMapping{destFit, POPPLER_DEST_FIT},
        KindMapping{destFitH, POPPLER_DEST_FITH},
        KindMapping{destFitV, POPPLER_DEST_FITV},
        KindMapping{destFitR, POPPLER_DEST_FITR},
        KindMapping{destFitB, POPPLER_DEST_FITB},
        KindMapping{destFitBH, POPPLER_DEST_FITBH},
        KindMapping{destFitBV, POPPLER_DEST_FITBV}));

TEST_P(DestNewGotoKindMappingTest_2289, MapsKindAndCopiesFields_PageNum_2289) {
  const KindMapping km = GetParam();

  LinkDestOwned owned = MakeLinkDest_PageNum(km.kind, /*page_num*/ 5, /*use_null_for_optional*/ false);
  ASSERT_TRUE(owned.dest);
  ASSERT_TRUE(owned.dest->isOk());

  const LinkDest *ld = owned.dest.get();
  PopplerDest *d = dest_new_goto(/*document*/ nullptr, ld);
  ASSERT_NE(d, nullptr);

  EXPECT_EQ(d->type, km.expected);
  EXPECT_EQ(d->page_num, ld->getPageNum());

  // Copy-through checks (black-box: compare to the observable LinkDest getters).
  EXPECT_DOUBLE_EQ(d->left, ld->getLeft());
  EXPECT_DOUBLE_EQ(d->bottom, ld->getBottom());
  EXPECT_DOUBLE_EQ(d->right, ld->getRight());
  EXPECT_DOUBLE_EQ(d->top, ld->getTop());
  EXPECT_DOUBLE_EQ(d->zoom, ld->getZoom());

  EXPECT_EQ(d->change_left, ld->getChangeLeft());
  EXPECT_EQ(d->change_top, ld->getChangeTop());
  EXPECT_EQ(d->change_zoom, ld->getChangeZoom());

  poppler_dest_free(d);
}

TEST_P(DestNewGotoKindMappingTest_2289, CopiesChangeFlagsWhenOptionalsAreNull_2289) {
  const KindMapping km = GetParam();

  // Only some kinds allow optional numeric entries (XYZ/FitH/FitV/FitBH/FitBV),
  // but this test stays black-box by comparing to LinkDest's own reported flags.
  LinkDestOwned owned = MakeLinkDest_PageNum(km.kind, /*page_num*/ 1, /*use_null_for_optional*/ true);
  ASSERT_TRUE(owned.dest);
  ASSERT_TRUE(owned.dest->isOk());

  const LinkDest *ld = owned.dest.get();
  PopplerDest *d = dest_new_goto(/*document*/ nullptr, ld);
  ASSERT_NE(d, nullptr);

  EXPECT_EQ(d->type, km.expected);
  EXPECT_EQ(d->page_num, ld->getPageNum());

  EXPECT_EQ(d->change_left, ld->getChangeLeft());
  EXPECT_EQ(d->change_top, ld->getChangeTop());
  EXPECT_EQ(d->change_zoom, ld->getChangeZoom());

  poppler_dest_free(d);
}

TEST_F(DestNewGotoKindMappingTest_2289, PageRefWithNullDocumentForcesPageNumZero_2289) {
  // When LinkDest uses a page Ref, dest_new_goto() has an observable fallback:
  // if document is null, it sets page_num = 0.
  LinkDestOwned owned = MakeLinkDest_PageRef(destXYZ, /*ref_num*/ 12, /*ref_gen*/ 0);
  ASSERT_TRUE(owned.dest);
  ASSERT_TRUE(owned.dest->isOk());
  ASSERT_TRUE(owned.dest->isPageRef());

  PopplerDest *d = dest_new_goto(/*document*/ nullptr, owned.dest.get());
  ASSERT_NE(d, nullptr);

  EXPECT_EQ(d->type, POPPLER_DEST_XYZ);
  EXPECT_EQ(d->page_num, 0);

  poppler_dest_free(d);
}

TEST_F(DestNewGotoKindMappingTest_2289, Boundary_PageNumZeroPassesThroughWhenNotRef_2289) {
  LinkDestOwned owned = MakeLinkDest_PageNum(destFit, /*page_num*/ 0);
  ASSERT_TRUE(owned.dest);
  ASSERT_TRUE(owned.dest->isOk());
  ASSERT_FALSE(owned.dest->isPageRef());

  PopplerDest *d = dest_new_goto(/*document*/ nullptr, owned.dest.get());
  ASSERT_NE(d, nullptr);

  EXPECT_EQ(d->type, POPPLER_DEST_FIT);
  EXPECT_EQ(d->page_num, 0);

  poppler_dest_free(d);
}

} // namespace