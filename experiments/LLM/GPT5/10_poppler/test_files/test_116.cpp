// Dict_getValNF_116_test.cpp
#include <gtest/gtest.h>

#include "Dict.h"
#include "Object.h"

namespace {

// Try to use the common Poppler/Xpdf-style Object init* APIs.
static Object MakeIntObject(int v) {
  Object o;
  o.initInt(v);
  return o;
}

static Object MakeBoolObject(bool v) {
  Object o;
  o.initBool(v);
  return o;
}

static void ExpectObjectEqualByObservableAPI(const Object& a, const Object& b) {
  // Compare using only public/observable Object behavior.
  // We intentionally keep this narrow to avoid relying on internal representation.
  EXPECT_EQ(a.getType(), b.getType());

  if (a.isInt()) {
    EXPECT_EQ(a.getInt(), b.getInt());
  } else if (a.isBool()) {
    EXPECT_EQ(a.getBool(), b.getBool());
  } else if (a.isNull()) {
    // Nothing else to compare.
  } else {
    // For other types, type equality is the only portable expectation here without
    // depending on extra APIs (string/name/array/stream/etc.) that may vary.
  }
}

}  // namespace

class DictGetValNFTest_116 : public ::testing::Test {
 protected:
  DictGetValNFTest_116() : dict_(nullptr) {}

  Dict dict_;
};

TEST_F(DictGetValNFTest_116, ReturnsReferenceConsistentWithGetValAtSameIndex_116) {
  dict_.add("A", MakeIntObject(123));
  dict_.add("B", MakeBoolObject(true));

  const int len = dict_.getLength();
  ASSERT_GE(len, 2);

  // For each valid index, getValNF(i) should represent the same observable value as getVal(i).
  for (int i = 0; i < len; ++i) {
    const Object byValue = dict_.getVal(i);
    const Object& byRef = dict_.getValNF(i);
    ExpectObjectEqualByObservableAPI(byValue, byRef);
  }
}

TEST_F(DictGetValNFTest_116, WorksForFirstAndLastValidIndex_116) {
  dict_.add("First", MakeIntObject(-7));
  dict_.add("Middle", MakeBoolObject(false));
  dict_.add("Last", MakeIntObject(999));

  const int len = dict_.getLength();
  ASSERT_GE(len, 3);

  {
    const Object v0 = dict_.getVal(0);
    const Object& r0 = dict_.getValNF(0);
    ExpectObjectEqualByObservableAPI(v0, r0);
  }

  {
    const Object vlast = dict_.getVal(len - 1);
    const Object& rlast = dict_.getValNF(len - 1);
    ExpectObjectEqualByObservableAPI(vlast, rlast);
  }
}

TEST_F(DictGetValNFTest_116, ReturnedReferenceIsStableAcrossRepeatedCalls_116) {
  dict_.add("K", MakeIntObject(42));

  ASSERT_GE(dict_.getLength(), 1);

  const Object* p1 = &dict_.getValNF(0);
  const Object* p2 = &dict_.getValNF(0);

  // Observable behavior from the interface: it returns a const reference, so the address
  // should remain the same across repeated calls as long as the Dict is not modified.
  EXPECT_EQ(p1, p2);

  // Also ensure the value matches getVal(0).
  ExpectObjectEqualByObservableAPI(dict_.getVal(0), *p1);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(DictGetValNFTest_116, DeathOnOutOfRangeIndexWhenNonEmpty_116) {
  // Out-of-range behavior is not specified by the interface; however, the provided
  // implementation directly indexes, which often results in a crash/assert.
  // We verify this as an observable error case via a death test.
  dict_.add("Only", MakeIntObject(1));

  ASSERT_GE(dict_.getLength(), 1);

  ASSERT_DEATH_IF_SUPPORTED(
      (void)dict_.getValNF(dict_.getLength()), ".*");
}

TEST_F(DictGetValNFTest_116, DeathOnNegativeIndexWhenNonEmpty_116) {
  dict_.add("Only", MakeIntObject(1));

  ASSERT_GE(dict_.getLength(), 1);

  ASSERT_DEATH_IF_SUPPORTED(
      (void)dict_.getValNF(-1), ".*");
}
#endif