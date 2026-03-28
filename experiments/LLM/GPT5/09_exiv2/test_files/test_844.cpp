// TEST_ID: 844
// File: test_xmparrayvalue_clone_844.cpp

#include <gtest/gtest.h>

#include <string>

// Exiv2 public header (as provided in prompt)
#include "exiv2/value.hpp"

namespace {

class XmpArrayValueTest_844 : public ::testing::Test {
protected:
  static Exiv2::XmpArrayValue MakeValue() {
    // Use a commonly available Exiv2 TypeId. Treat as black-box: we only need
    // a constructible instance to exercise the public API.
    return Exiv2::XmpArrayValue(Exiv2::xmpText);
  }

  static void SnapshotPublicState(const Exiv2::XmpArrayValue& v, size_t& outCount, std::string& outFirst) {
    outCount = v.count();
    outFirst.clear();
    if (outCount > 0) {
      outFirst = v.toString(0);
    }
  }
};

TEST_F(XmpArrayValueTest_844, CloneOnDefaultConstructedIsNonNullAndSafe_844) {
  const auto v = MakeValue();

  // Observable behavior: clone() returns a smart pointer; it should be safe to call.
  ASSERT_NO_THROW({
    auto c = v.clone();
    EXPECT_NE(c.get(), nullptr);
  });
}

TEST_F(XmpArrayValueTest_844, ClonePreservesObservableStateAtCloneTime_844) {
  auto v = MakeValue();

  // Populate using only public API. We do not assume parsing rules; we only
  // compare clone vs original at the moment of cloning.
  (void)v.read("one");

  const auto clonePtr = v.clone();
  ASSERT_NE(clonePtr.get(), nullptr);

  // clone() returns an Exiv2::XmpArrayValue::UniquePtr; treat it as a polymorphic value.
  const auto* cloned = dynamic_cast<const Exiv2::XmpArrayValue*>(clonePtr.get());
  ASSERT_NE(cloned, nullptr) << "clone() should produce an object usable as XmpArrayValue via RTTI";

  size_t c1 = 0, c2 = 0;
  std::string s1, s2;
  SnapshotPublicState(v, c1, s1);
  SnapshotPublicState(*cloned, c2, s2);

  EXPECT_EQ(c2, c1);
  EXPECT_EQ(s2, s1);
}

TEST_F(XmpArrayValueTest_844, CloneIsIndependentFromSubsequentMutationsOfOriginal_844) {
  auto v = MakeValue();
  (void)v.read("first");

  size_t beforeCount = 0;
  std::string beforeFirst;
  SnapshotPublicState(v, beforeCount, beforeFirst);

  auto clonePtr = v.clone();
  ASSERT_NE(clonePtr.get(), nullptr);
  const auto* cloned = dynamic_cast<const Exiv2::XmpArrayValue*>(clonePtr.get());
  ASSERT_NE(cloned, nullptr);

  size_t cloneCountBefore = 0;
  std::string cloneFirstBefore;
  SnapshotPublicState(*cloned, cloneCountBefore, cloneFirstBefore);

  // If read("first") did not produce observable elements, we can still verify non-crash + stability.
  if (beforeCount == 0 && cloneCountBefore == 0) {
    // Mutate original and just assert clone remains callable and consistent with its own earlier snapshot.
    ASSERT_NO_THROW((void)v.read("second"));
    size_t cloneCountAfter = 0;
    std::string cloneFirstAfter;
    SnapshotPublicState(*cloned, cloneCountAfter, cloneFirstAfter);
    EXPECT_EQ(cloneCountAfter, cloneCountBefore);
    EXPECT_EQ(cloneFirstAfter, cloneFirstBefore);
    return;
  }

  // Mutate original after cloning (black-box: might replace or append; we only require clone stability).
  ASSERT_NO_THROW((void)v.read("second"));

  size_t cloneCountAfter = 0;
  std::string cloneFirstAfter;
  SnapshotPublicState(*cloned, cloneCountAfter, cloneFirstAfter);

  EXPECT_EQ(cloneCountAfter, cloneCountBefore);
  EXPECT_EQ(cloneFirstAfter, cloneFirstBefore);
}

TEST_F(XmpArrayValueTest_844, MultipleClonesAreDistinctObjects_844) {
  const auto v = MakeValue();

  auto c1 = v.clone();
  auto c2 = v.clone();

  ASSERT_NE(c1.get(), nullptr);
  ASSERT_NE(c2.get(), nullptr);

  EXPECT_NE(c1.get(), c2.get());
}

TEST_F(XmpArrayValueTest_844, CloneWorksAfterLargeInputRead_844) {
  auto v = MakeValue();

  std::string large(100000, 'A'); // boundary-ish size, but still reasonable for a unit test
  (void)v.read(large);

  ASSERT_NO_THROW({
    auto c = v.clone();
    EXPECT_NE(c.get(), nullptr);
  });
}

}  // namespace