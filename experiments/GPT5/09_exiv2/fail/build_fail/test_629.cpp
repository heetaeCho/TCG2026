// File: test_IptcDataSets_dataSetType_629.cpp
#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>

#include <cstdint>
#include <string>
#include <vector>

namespace {

using Exiv2::DataSet;
using Exiv2::IptcDataSets;
using Exiv2::TypeId;

// Try to find a plausible recordId for which this dataset entry belongs by
// matching the public API title against the DataSet list entry's title_.
// We do NOT assume what recordId means; we only search for a match using
// observable behavior.
uint16_t FindRecordIdByTitleMatch(uint16_t dataSetNumber, const char* expectedTitle,
                                 uint16_t maxRecordIdToTry = 64) {
  if (expectedTitle == nullptr) return 0;

  const std::string expected(expectedTitle);
  for (uint16_t rid = 0; rid <= maxRecordIdToTry; ++rid) {
    const char* title = IptcDataSets::dataSetTitle(dataSetNumber, rid);
    if (title != nullptr && expected == title) {
      return rid;
    }
  }
  return 0;
}

// A conservative iterator over a DataSet list that stops on common sentinel
// patterns (nullptr title/desc/psname), or a bounded count to avoid overruns.
std::vector<const DataSet*> CollectFirstEntries(const DataSet* list, size_t maxCount = 256) {
  std::vector<const DataSet*> out;
  if (!list) return out;

  for (size_t i = 0; i < maxCount; ++i) {
    const DataSet* ds = &list[i];

    // Common sentinel patterns in Exiv2 tables: nullptr pointers and/or 0 number.
    // We don't *assume* the exact sentinel; we stop on the first clearly-invalid entry.
    if (ds->title_ == nullptr) break;

    // number_==0 is often used as end marker; treat it as an end marker if title is empty-ish.
    if (ds->number_ == 0) break;

    out.push_back(ds);
  }
  return out;
}

const DataSet* FindFirstPlausibleDataSet(const DataSet* list) {
  auto entries = CollectFirstEntries(list);
  for (const DataSet* ds : entries) {
    if (ds && ds->number_ != 0 && ds->title_ != nullptr) {
      return ds;
    }
  }
  return nullptr;
}

}  // namespace

class IptcDataSetsTest_629 : public ::testing::Test {};

TEST_F(IptcDataSetsTest_629, UnknownNumberAndRecordId_ReturnsUnknownType_629) {
  // For unknown (number, recordId), implementation indicates it returns unknownDataSet.type_.
  // We only assert the observable outcome via the public TypeId value.
  const TypeId t = IptcDataSets::dataSetType(/*number*/ 0xFFFFu, /*recordId*/ 0xFFFFu);
  EXPECT_EQ(t, Exiv2::string);
}

TEST_F(IptcDataSetsTest_629, KnownDataSetFromEnvelopeList_MatchesListedType_WhenRecordIdFound_629) {
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);

  const DataSet* first = FindFirstPlausibleDataSet(list);
  ASSERT_NE(first, nullptr);
  ASSERT_NE(first->title_, nullptr);

  const uint16_t rid = FindRecordIdByTitleMatch(first->number_, first->title_);
  ASSERT_NE(rid, 0u) << "Could not find a recordId where dataSetTitle matches the table title for "
                     << "dataset number=" << first->number_;

  const TypeId observed = IptcDataSets::dataSetType(first->number_, rid);
  EXPECT_EQ(observed, first->type_);
}

TEST_F(IptcDataSetsTest_629, KnownDataSetFromApplication2List_MatchesListedType_WhenRecordIdFound_629) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const DataSet* first = FindFirstPlausibleDataSet(list);
  ASSERT_NE(first, nullptr);
  ASSERT_NE(first->title_, nullptr);

  const uint16_t rid = FindRecordIdByTitleMatch(first->number_, first->title_);
  ASSERT_NE(rid, 0u) << "Could not find a recordId where dataSetTitle matches the table title for "
                     << "dataset number=" << first->number_;

  const TypeId observed = IptcDataSets::dataSetType(first->number_, rid);
  EXPECT_EQ(observed, first->type_);
}

TEST_F(IptcDataSetsTest_629, KnownNumberWithClearlyInvalidRecordId_ReturnsUnknownType_629) {
  const DataSet* list = IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const DataSet* first = FindFirstPlausibleDataSet(list);
  ASSERT_NE(first, nullptr);

  // Boundary/error: valid-looking dataset number paired with an out-of-range recordId.
  const TypeId observed = IptcDataSets::dataSetType(first->number_, /*recordId*/ 0xFFFFu);
  EXPECT_EQ(observed, Exiv2::string);
}

TEST_F(IptcDataSetsTest_629, ZeroNumber_ReturnsUnknownType_ForCommonRecordIds_629) {
  // Boundary: dataset number 0 should not normally exist (table sentinel), and should be treated as unknown.
  // We test multiple recordIds without assuming which are valid.
  for (uint16_t rid : {0u, 1u, 2u, 3u, 10u, 50u, 0xFFFFu}) {
    const TypeId observed = IptcDataSets::dataSetType(/*number*/ 0u, /*recordId*/ rid);
    EXPECT_EQ(observed, Exiv2::string) << "recordId=" << rid;
  }
}

TEST_F(IptcDataSetsTest_629, SeveralEntriesFromAList_MatchTheirListedTypes_WhenRecordIdFound_629) {
  // Broader coverage without relying on private/internal state:
  // For the first few entries, find a recordId by title match and verify type round-trips.
  const DataSet* list = IptcDataSets::envelopeRecordList();
  ASSERT_NE(list, nullptr);

  auto entries = CollectFirstEntries(list);
  ASSERT_FALSE(entries.empty());

  size_t verified = 0;
  for (const DataSet* ds : entries) {
    if (!ds || ds->number_ == 0 || ds->title_ == nullptr) continue;

    const uint16_t rid = FindRecordIdByTitleMatch(ds->number_, ds->title_);
    if (rid == 0u) continue;  // Some entries may not be findable by title match; skip without failing.

    EXPECT_EQ(IptcDataSets::dataSetType(ds->number_, rid), ds->type_)
        << "dataset number=" << ds->number_ << " recordId=" << rid << " title=" << ds->title_;
    ++verified;

    if (verified >= 10) break;  // keep test runtime reasonable and avoid depending on full table size
  }

  ASSERT_GE(verified, 1u) << "Expected to verify at least one dataset entry via public API matching.";
}