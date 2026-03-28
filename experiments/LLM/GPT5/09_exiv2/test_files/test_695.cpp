// File: test_iptcdata_add_695.cpp
#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <string>
#include <utility>

namespace {

// Finds a dataset number in [0, 255] for the given recordId whose repeatability matches desiredRepeatable.
// If none is found (unexpected / build-config dependent), tests should skip gracefully.
std::pair<bool, uint16_t> FindDatasetByRepeatable(uint16_t recordId, bool desiredRepeatable) {
  for (uint16_t ds = 0; ds <= 255; ++ds) {
    if (Exiv2::IptcDataSets::dataSetRepeatable(ds, recordId) == desiredRepeatable) {
      return {true, ds};
    }
  }
  return {false, 0};
}

Exiv2::Iptcdatum MakeIptcDatum(uint16_t dataset, uint16_t record, const std::string& valueStr) {
  // IptcKey constructor is part of Exiv2 public API.
  Exiv2::IptcKey key(dataset, record);

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::string);
  v->read(valueStr);

  // Iptcdatum takes a Value* (it is expected to clone / take a copy as part of its public contract).
  Exiv2::Iptcdatum datum(key, v.get());
  return datum;
}

}  // namespace

class IptcDataAddTest_695 : public ::testing::Test {
 protected:
  static constexpr uint16_t kRecordEnvelope = 1;
  static constexpr uint16_t kRecordApplication2 = 2;
};

TEST_F(IptcDataAddTest_695, AddFirstDatumReturnsZeroAndIncreasesSize_695) {
  Exiv2::IptcData data;
  ASSERT_EQ(0u, data.size());

  auto [found, ds] = FindDatasetByRepeatable(kRecordApplication2, /*desiredRepeatable=*/true);
  if (!found) GTEST_SKIP() << "Could not find a repeatable dataset in record 2 (Application2) within [0,255].";

  Exiv2::Iptcdatum d1 = MakeIptcDatum(ds, kRecordApplication2, "v1");

  const int rc = data.add(d1);
  EXPECT_EQ(0, rc);
  EXPECT_EQ(1u, data.size());

  // Observable via public findId/begin/end.
  EXPECT_NE(data.findId(d1.tag(), d1.record()), data.end());
}

TEST_F(IptcDataAddTest_695, AddDuplicateNonRepeatableReturns6AndDoesNotGrow_695) {
  Exiv2::IptcData data;

  auto [found, ds] = FindDatasetByRepeatable(kRecordApplication2, /*desiredRepeatable=*/false);
  if (!found) GTEST_SKIP() << "Could not find a non-repeatable dataset in record 2 (Application2) within [0,255].";

  Exiv2::Iptcdatum d1 = MakeIptcDatum(ds, kRecordApplication2, "first");
  Exiv2::Iptcdatum d2 = MakeIptcDatum(ds, kRecordApplication2, "second");  // same tag+record, different value

  ASSERT_EQ(0, data.add(d1));
  ASSERT_EQ(1u, data.size());

  const int rc2 = data.add(d2);
  EXPECT_EQ(6, rc2) << "Expected the documented duplicate error code for a non-repeatable dataset.";
  EXPECT_EQ(1u, data.size()) << "Size should not increase when duplicate non-repeatable datum is rejected.";

  // Still should be able to find the original id.
  EXPECT_NE(data.findId(d1.tag(), d1.record()), data.end());
}

TEST_F(IptcDataAddTest_695, AddDuplicateRepeatableReturnsZeroAndGrows_695) {
  Exiv2::IptcData data;

  auto [found, ds] = FindDatasetByRepeatable(kRecordApplication2, /*desiredRepeatable=*/true);
  if (!found) GTEST_SKIP() << "Could not find a repeatable dataset in record 2 (Application2) within [0,255].";

  Exiv2::Iptcdatum d1 = MakeIptcDatum(ds, kRecordApplication2, "a");
  Exiv2::Iptcdatum d2 = MakeIptcDatum(ds, kRecordApplication2, "b");  // same tag+record

  ASSERT_EQ(0, data.add(d1));
  ASSERT_EQ(1u, data.size());

  const int rc2 = data.add(d2);
  EXPECT_EQ(0, rc2);
  EXPECT_EQ(2u, data.size()) << "Repeatable datasets should allow multiple entries with same tag+record.";
}

TEST_F(IptcDataAddTest_695, NonRepeatableDuplicateCheckIsScopedToTagAndRecord_695) {
  Exiv2::IptcData data;

  auto [foundNonRep, ds] = FindDatasetByRepeatable(kRecordApplication2, /*desiredRepeatable=*/false);
  if (!foundNonRep) GTEST_SKIP() << "Could not find a non-repeatable dataset in record 2 (Application2) within [0,255].";

  // Same dataset number, different record id. Should be treated as a different ID for duplicate checking.
  Exiv2::Iptcdatum app2 = MakeIptcDatum(ds, kRecordApplication2, "x");
  Exiv2::Iptcdatum env1 = MakeIptcDatum(ds, kRecordEnvelope, "y");

  ASSERT_EQ(0, data.add(app2));
  ASSERT_EQ(1u, data.size());

  const int rc2 = data.add(env1);
  EXPECT_EQ(0, rc2);
  EXPECT_EQ(2u, data.size());

  EXPECT_NE(data.findId(app2.tag(), app2.record()), data.end());
  EXPECT_NE(data.findId(env1.tag(), env1.record()), data.end());
}

TEST_F(IptcDataAddTest_695, AddMultipleDistinctNonRepeatableDatasetsAllSucceed_695) {
  Exiv2::IptcData data;

  auto [foundNonRep1, ds1] = FindDatasetByRepeatable(kRecordApplication2, /*desiredRepeatable=*/false);
  if (!foundNonRep1) GTEST_SKIP() << "Could not find a non-repeatable dataset in record 2 within [0,255].";

  // Find a *different* non-repeatable dataset in record 2.
  bool foundNonRep2 = false;
  uint16_t ds2 = 0;
  for (uint16_t ds = 0; ds <= 255; ++ds) {
    if (ds == ds1) continue;
    if (Exiv2::IptcDataSets::dataSetRepeatable(ds, kRecordApplication2) == false) {
      foundNonRep2 = true;
      ds2 = ds;
      break;
    }
  }
  if (!foundNonRep2) GTEST_SKIP() << "Could not find two distinct non-repeatable datasets in record 2 within [0,255].";

  Exiv2::Iptcdatum d1 = MakeIptcDatum(ds1, kRecordApplication2, "v1");
  Exiv2::Iptcdatum d2 = MakeIptcDatum(ds2, kRecordApplication2, "v2");

  EXPECT_EQ(0, data.add(d1));
  EXPECT_EQ(0, data.add(d2));
  EXPECT_EQ(2u, data.size());

  EXPECT_NE(data.findId(d1.tag(), d1.record()), data.end());
  EXPECT_NE(data.findId(d2.tag(), d2.record()), data.end());
}