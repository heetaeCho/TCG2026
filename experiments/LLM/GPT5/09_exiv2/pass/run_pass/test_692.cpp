// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdata_operator_brackets_692.cpp
//
// Unit tests for Exiv2::IptcData::operator[](const std::string&)
// based strictly on the public interface / observable behavior.

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/datasets.hpp>

#include <string>

namespace {

class IptcDataOperatorBracketsTest_692 : public ::testing::Test {
 protected:
  Exiv2::IptcData data_;
};

TEST_F(IptcDataOperatorBracketsTest_692, EmptyInitially_692) {
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);
  EXPECT_EQ(data_.size(), 0u);
}

TEST_F(IptcDataOperatorBracketsTest_692, InsertsNewKeyAndIncreasesCount_692) {
  const std::string key = "Iptc.Application2.Caption";

  auto before = data_.count();
  Exiv2::Iptcdatum& d = data_[key];
  (void)d;

  EXPECT_EQ(data_.count(), before + 1u);
  EXPECT_FALSE(data_.empty());
  EXPECT_EQ(data_.size(), data_.count());
}

TEST_F(IptcDataOperatorBracketsTest_692, ReAccessSameKeyDoesNotIncreaseCountAndReturnsSameDatum_692) {
  const std::string key = "Iptc.Application2.Caption";

  Exiv2::Iptcdatum& first = data_[key];
  auto after_first = data_.count();

  Exiv2::Iptcdatum& second = data_[key];
  auto after_second = data_.count();

  EXPECT_EQ(after_second, after_first) << "Re-accessing an existing key should not add another entry.";
  EXPECT_EQ(&second, &first) << "Operator[] should return a reference to the existing datum for the same key.";
}

TEST_F(IptcDataOperatorBracketsTest_692, DifferentKeysCreateDistinctEntries_692) {
  const std::string key1 = "Iptc.Application2.Caption";
  const std::string key2 = "Iptc.Application2.ObjectName";

  Exiv2::Iptcdatum& d1 = data_[key1];
  Exiv2::Iptcdatum& d2 = data_[key2];

  EXPECT_EQ(data_.count(), 2u);
  EXPECT_NE(&d1, &d2);
}

TEST_F(IptcDataOperatorBracketsTest_692, ReturnedReferenceRemainsValidAcrossFurtherInsertions_692) {
  // Observable contract we can check: the reference we got can still be used
  // after more operator[] calls. (We do not inspect private state.)
  const std::string key0 = "Iptc.Application2.Caption";
  Exiv2::Iptcdatum& first = data_[key0];

  // Trigger several insertions (potentially causing internal container growth).
  for (int i = 0; i < 50; ++i) {
    data_["Iptc.Application2.ObjectName" + std::to_string(i)];
  }

  // If reference were invalidated, this access could crash/UB; in practice
  // this test validates the observable safety of returning a reference.
  Exiv2::Iptcdatum& again = data_[key0];
  EXPECT_EQ(&again, &first);
}

TEST_F(IptcDataOperatorBracketsTest_692, WorksWithEmptyStringKey_Boundary_692) {
  // Boundary: empty key string. Behavior should be safe/defined at interface level:
  // - should not throw
  // - should create/find an entry and keep container consistent
  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& d = data_[std::string()];
    (void)d;
  });

  EXPECT_EQ(data_.count(), 1u);
  EXPECT_FALSE(data_.empty());

  // Re-access should not add again.
  Exiv2::Iptcdatum& d1 = data_[std::string()];
  Exiv2::Iptcdatum& d2 = data_[std::string()];
  EXPECT_EQ(&d1, &d2);
  EXPECT_EQ(data_.count(), 1u);
}

TEST_F(IptcDataOperatorBracketsTest_692, WorksWithLongKeyString_Boundary_692) {
  // Boundary: very long key. We only assert it behaves consistently.
  std::string longKey(4096, 'A');
  // Make it look like a dotted key but still very long.
  longKey.replace(0, 5, "Iptc.");
  longKey.replace(10, 1, ".");

  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& d = data_[longKey];
    (void)d;
  });

  EXPECT_EQ(data_.count(), 1u);
  EXPECT_EQ(data_.size(), 1u);

  // Re-access should be stable.
  Exiv2::Iptcdatum& d1 = data_[longKey];
  Exiv2::Iptcdatum& d2 = data_[longKey];
  EXPECT_EQ(&d1, &d2);
  EXPECT_EQ(data_.count(), 1u);
}

TEST_F(IptcDataOperatorBracketsTest_692, KeyLookupObservableViaFindKey_WhenAvailable_692) {
  // Verify operator[] insertion is observable via public lookup API.
  const std::string keyStr = "Iptc.Application2.Caption";
  Exiv2::Iptcdatum& byIndex = data_[keyStr];

  const Exiv2::IptcKey key(keyStr);
  auto it = data_.findKey(key);
  ASSERT_NE(it, data_.end());

  // We can compare addresses: iterator deref yields Iptcdatum&, same object.
  EXPECT_EQ(&(*it), &byIndex);
}

TEST_F(IptcDataOperatorBracketsTest_692, AfterClearOperatorInsertsAgain_692) {
  data_["Iptc.Application2.Caption"];
  data_["Iptc.Application2.ObjectName"];
  ASSERT_EQ(data_.count(), 2u);

  data_.clear();
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0u);

  // Insert again after clear.
  Exiv2::Iptcdatum& d = data_["Iptc.Application2.Caption"];
  (void)d;
  EXPECT_EQ(data_.count(), 1u);
}

TEST_F(IptcDataOperatorBracketsTest_692, InsertManyUniqueKeysCountMatches_Boundary_692) {
  const int kN = 200;
  for (int i = 0; i < kN; ++i) {
    data_["Iptc.Application2.ObjectName" + std::to_string(i)];
  }
  EXPECT_EQ(data_.count(), static_cast<size_t>(kN));
  EXPECT_EQ(data_.size(), data_.count());
  EXPECT_FALSE(data_.empty());
}

}  // namespace