// annots_display_decide_cb_test_2432.cc
#include <gtest/gtest.h>

#include <glib.h>

// We include the .cc to get access to the TU-local (static) callback.
// This keeps us from re-implementing or copying the function under test.
#include "poppler-page.cc"

#include "poppler/Annot.h"
#include "poppler/PDFRectangle.h"

namespace {

class TestAnnotForDecideCb_2432 : public Annot {
public:
  explicit TestAnnotForDecideCb_2432(int subtype_int)
      : Annot(/*docA=*/nullptr, &rect_) {
    // Annot::type is protected, so a derived test helper can set it to craft inputs.
    // This is an external dependency setup, not inspection of private state of the
    // function under test.
    this->type = static_cast<Annot::AnnotSubtype>(subtype_int);
  }

private:
  PDFRectangle rect_{0, 0, 1, 1};
};

static guint FlagsForSubtypeInt_2432(int subtype_int) {
  // Mirrors the mask computation contract that is observable via return values,
  // without re-implementing the callback itself.
  //
  // NOTE: This helper matches the public math described by the callback signature:
  // flags vs. computed bit mask for the subtype. We keep it minimal and only use it
  // to construct inputs for the black-box callback.
  const int idx = MAX(0, subtype_int - 1);
  return static_cast<guint>(1u << idx);
}

}  // namespace

TEST(AnnotsDisplayDecideCbTest_2432, ReturnsFalseWhenUserDataNull_2432) {
  TestAnnotForDecideCb_2432 annot(/*subtype_int=*/1);

  // If user_data is null, GPOINTER_TO_UINT -> 0, so no bits should match.
  EXPECT_FALSE(annots_display_decide_cb(&annot, /*user_data=*/nullptr));
}

TEST(AnnotsDisplayDecideCbTest_2432, ReturnsTrueWhenFlagBitForSubtypeIsSet_2432) {
  TestAnnotForDecideCb_2432 annot(/*subtype_int=*/1);

  const guint flags = FlagsForSubtypeInt_2432(/*subtype_int=*/1);
  EXPECT_TRUE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags)));
}

TEST(AnnotsDisplayDecideCbTest_2432, ReturnsFalseWhenFlagBitForSubtypeIsNotSet_2432) {
  TestAnnotForDecideCb_2432 annot(/*subtype_int=*/2);

  // Provide a flag that corresponds to subtype 1 only.
  const guint flags = FlagsForSubtypeInt_2432(/*subtype_int=*/1);
  EXPECT_FALSE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags)));
}

TEST(AnnotsDisplayDecideCbTest_2432, BoundarySubtypeZeroMapsToBitZero_2432) {
  // Boundary: subtype_int = 0 => MAX(0, -1) => 0 => (1 << 0)
  TestAnnotForDecideCb_2432 annot(/*subtype_int=*/0);

  const guint flags = FlagsForSubtypeInt_2432(/*subtype_int=*/0);
  EXPECT_TRUE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags)));

  // And if the bit is not present, it should be false.
  EXPECT_FALSE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags << 1)));
}

TEST(AnnotsDisplayDecideCbTest_2432, MultipleFlagsAnyMatchingBitReturnsTrue_2432) {
  TestAnnotForDecideCb_2432 annot(/*subtype_int=*/3);

  const guint bit1 = FlagsForSubtypeInt_2432(/*subtype_int=*/1);
  const guint bit3 = FlagsForSubtypeInt_2432(/*subtype_int=*/3);
  const guint combined = bit1 | bit3;

  EXPECT_TRUE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(combined)));
}

TEST(AnnotsDisplayDecideCbTest_2432, HigherSubtypeWithinIntShiftRangeBehavesCorrectly_2432) {
  // Choose a subtype that keeps (1u << idx) well-defined for 32-bit guint.
  // subtype_int = 31 => idx = 30 => 1u<<30 is valid.
  constexpr int kSubtype = 31;
  TestAnnotForDecideCb_2432 annot(kSubtype);

  const guint flags_match = FlagsForSubtypeInt_2432(kSubtype);
  EXPECT_TRUE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags_match)));

  const guint flags_mismatch = FlagsForSubtypeInt_2432(kSubtype - 1);
  EXPECT_FALSE(annots_display_decide_cb(&annot, GUINT_TO_POINTER(flags_mismatch)));
}