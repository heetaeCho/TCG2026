// FormFieldChoice_isSelected_916_test.cc
#include <gtest/gtest.h>

#include "poppler/Form.h"

namespace {

// NOTE:
// These tests treat FormFieldChoice as a black box *for behavior assertions*.
// However, the provided interface snippet only exposes `isSelected(int)`,
// and constructing a real FormFieldChoice instance requires heavy Poppler
// objects (PDFDoc/Object/Ref parsing). To keep the tests focused on the
// observable behavior of `isSelected(int)` without re-implementing logic,
// we use a minimal test-only "layout access" helper that writes the protected
// `choices` pointer and `numChoices` count into raw storage, then calls
// the real `isSelected(int)` implementation.
//
// The assertions remain purely on the public API: `isSelected(int)`.

struct ChoiceFieldLayoutAccess_916 final : public FormFieldChoice {
  // Expose protected fields for *test-only setup*.
  using FormFieldChoice::choices;
  using FormFieldChoice::numChoices;

  // Also initialize other known protected fields defensively (when present).
  using FormFieldChoice::combo;
  using FormFieldChoice::edit;
  using FormFieldChoice::multiselect;
  using FormFieldChoice::doCommitOnSelChange;
  using FormFieldChoice::defaultChoices;
  using FormFieldChoice::topIdx;
};

// Owns an unconstructed FormFieldChoice-like storage plus a choices array.
class ChoiceFieldRawHarness_916 {
public:
  using ChoiceOpt = ChoiceFieldLayoutAccess_916::ChoiceOpt;

  explicit ChoiceFieldRawHarness_916(int n) : n_(n), opts_(new ChoiceOpt[n]()) {
    // Point raw storage at a "layout access" view.
    auto *p = ptr_();

    // Defensive initialization of known fields.
    p->choices = opts_;
    p->numChoices = n_;

    // Initialize other known flags/pointers to safe defaults (if present).
    p->combo = false;
    p->edit = false;
    p->multiselect = false;
    p->doCommitOnSelChange = false;
    p->defaultChoices = nullptr;
    p->topIdx = 0;
  }

  ChoiceFieldRawHarness_916(const ChoiceFieldRawHarness_916 &) = delete;
  ChoiceFieldRawHarness_916 &operator=(const ChoiceFieldRawHarness_916 &) = delete;

  ~ChoiceFieldRawHarness_916() { delete[] opts_; }

  FormFieldChoice *field() { return reinterpret_cast<FormFieldChoice *>(&storage_); }
  const FormFieldChoice *field() const {
    return reinterpret_cast<const FormFieldChoice *>(&storage_);
  }

  void setSelected(int i, bool v) {
    ASSERT_GE(i, 0);
    ASSERT_LT(i, n_);
    opts_[i].selected = v;
  }

  int size() const { return n_; }

private:
  ChoiceFieldLayoutAccess_916 *ptr_() {
    return reinterpret_cast<ChoiceFieldLayoutAccess_916 *>(&storage_);
  }
  const ChoiceFieldLayoutAccess_916 *ptr_() const {
    return reinterpret_cast<const ChoiceFieldLayoutAccess_916 *>(&storage_);
  }

  int n_;
  ChoiceOpt *opts_;
  std::aligned_storage_t<sizeof(ChoiceFieldLayoutAccess_916),
                         alignof(ChoiceFieldLayoutAccess_916)>
      storage_{};
};

}  // namespace

TEST(FormFieldChoiceTest_916, IsSelectedReturnsTrueWhenOptionSelected_916) {
  ChoiceFieldRawHarness_916 h(3);
  h.setSelected(0, true);
  h.setSelected(1, false);
  h.setSelected(2, false);

  EXPECT_TRUE(h.field()->isSelected(0));
  EXPECT_FALSE(h.field()->isSelected(1));
  EXPECT_FALSE(h.field()->isSelected(2));
}

TEST(FormFieldChoiceTest_916, IsSelectedReturnsFalseWhenOptionNotSelected_916) {
  ChoiceFieldRawHarness_916 h(2);
  h.setSelected(0, false);
  h.setSelected(1, false);

  EXPECT_FALSE(h.field()->isSelected(0));
  EXPECT_FALSE(h.field()->isSelected(1));
}

TEST(FormFieldChoiceTest_916, IsSelectedReflectsChangesAcrossMultipleIndices_916) {
  ChoiceFieldRawHarness_916 h(4);

  // Initial state: all false (value-initialized).
  for (int i = 0; i < h.size(); ++i) {
    EXPECT_FALSE(h.field()->isSelected(i));
  }

  // Flip a couple of indices.
  h.setSelected(1, true);
  h.setSelected(3, true);

  EXPECT_FALSE(h.field()->isSelected(0));
  EXPECT_TRUE(h.field()->isSelected(1));
  EXPECT_FALSE(h.field()->isSelected(2));
  EXPECT_TRUE(h.field()->isSelected(3));

  // Flip back one.
  h.setSelected(1, false);
  EXPECT_FALSE(h.field()->isSelected(1));
  EXPECT_TRUE(h.field()->isSelected(3));
}

TEST(FormFieldChoiceTest_916, IsSelectedWorksAtLastValidIndex_916) {
  ChoiceFieldRawHarness_916 h(5);
  h.setSelected(4, true);

  EXPECT_TRUE(h.field()->isSelected(4));
  EXPECT_FALSE(h.field()->isSelected(0));
}