// File: poppler-index-iter-is-open-test_2216.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <vector>

#include <glib.h>

// -----------------------------------------------------------------------------
// NOTE:
// These tests treat the implementation as a black box and validate only
// observable behavior (return value / process death on invalid inputs).
//
// To keep the unit under test isolated and constructible, we compile the
// production function directly by including the .cc file (common in unit tests
// for small C functions).
// -----------------------------------------------------------------------------

// Minimal collaborator stub (external to the function under test).
// We do NOT infer Poppler internal behavior; we only provide the dependency
// needed to observe the function's output deterministically.
class OutlineItem {
 public:
  explicit OutlineItem(bool open) : open_(open) {}
  bool isOpen() const { return open_; }

 private:
  bool open_;
};

// Match the structure shape used by the function under test:
//   item = (*iter->items)[iter->index];
struct _PopplerIndexIter {
  std::vector<OutlineItem*>* items;
  std::size_t index;
};
using PopplerIndexIter = _PopplerIndexIter;

// Compile the production implementation into this test TU.
#include "TestProjects/poppler/glib/poppler-document.cc"

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

class PopplerIndexIterIsOpenTest_2216 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Own the items so pointers remain valid for the duration of each test.
    owned_.clear();
    raw_.clear();
  }

  OutlineItem* AddItem(bool open) {
    owned_.push_back(std::make_unique<OutlineItem>(open));
    raw_.push_back(owned_.back().get());
    return raw_.back();
  }

  PopplerIndexIter MakeIter(std::size_t idx) {
    PopplerIndexIter it{};
    it.items = &raw_;
    it.index = idx;
    return it;
  }

  std::vector<std::unique_ptr<OutlineItem>> owned_;
  std::vector<OutlineItem*> raw_;
};

TEST_F(PopplerIndexIterIsOpenTest_2216, ReturnsTrueWhenCurrentItemIsOpen_2216) {
  AddItem(true);
  AddItem(false);

  PopplerIndexIter it = MakeIter(0);
  EXPECT_EQ(poppler_index_iter_is_open(&it), TRUE);
}

TEST_F(PopplerIndexIterIsOpenTest_2216, ReturnsFalseWhenCurrentItemIsClosed_2216) {
  AddItem(true);
  AddItem(false);

  PopplerIndexIter it = MakeIter(1);
  EXPECT_EQ(poppler_index_iter_is_open(&it), FALSE);
}

TEST_F(PopplerIndexIterIsOpenTest_2216, Boundary_FirstElement_2216) {
  AddItem(false);
  AddItem(true);

  PopplerIndexIter it = MakeIter(0);
  EXPECT_EQ(poppler_index_iter_is_open(&it), FALSE);
}

TEST_F(PopplerIndexIterIsOpenTest_2216, Boundary_LastElement_2216) {
  AddItem(false);
  AddItem(true);
  AddItem(true);

  PopplerIndexIter it = MakeIter(raw_.size() - 1);
  EXPECT_EQ(poppler_index_iter_is_open(&it), TRUE);
}

TEST_F(PopplerIndexIterIsOpenTest_2216, RepeatedCallsAreConsistent_2216) {
  AddItem(true);

  PopplerIndexIter it = MakeIter(0);
  const gboolean first = poppler_index_iter_is_open(&it);
  const gboolean second = poppler_index_iter_is_open(&it);
  EXPECT_EQ(first, second);
}

TEST_F(PopplerIndexIterIsOpenTest_2216, Death_NullIterPointer_2216) {
  // The implementation dereferences `iter` unconditionally; this is an
  // observable error case as process termination.
  EXPECT_DEATH({ (void)poppler_index_iter_is_open(nullptr); }, ".*");
}

TEST_F(PopplerIndexIterIsOpenTest_2216, Death_IndexOutOfRange_2216) {
  AddItem(true);

  PopplerIndexIter it = MakeIter(999);  // clearly out of range
  EXPECT_DEATH({ (void)poppler_index_iter_is_open(&it); }, ".*");
}

TEST_F(PopplerIndexIterIsOpenTest_2216, Death_EmptyItemsVector_2216) {
  PopplerIndexIter it = MakeIter(0);
  EXPECT_DEATH({ (void)poppler_index_iter_is_open(&it); }, ".*");
}