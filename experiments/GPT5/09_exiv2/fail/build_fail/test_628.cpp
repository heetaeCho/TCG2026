// TEST_ID 628
#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#include "exiv2/datasets.hpp"

namespace {

constexpr uint16_t kTerminatorNumber = 65535;

// Walk a DataSet list until the terminator is found, with a hard cap to avoid runaway loops.
// This relies only on observable/public DataSet fields and the documented terminator number.
std::size_t CountUntilTerminator(const Exiv2::DataSet* list, std::size_t hard_cap = 1024) {
  if (!list) return 0;
  for (std::size_t i = 0; i < hard_cap; ++i) {
    if (list[i].number_ == kTerminatorNumber) return i + 1; // include terminator element
  }
  return 0; // not found within cap
}

}  // namespace

TEST(IptcDataSetsTest_628, Application2RecordListReturnsNonNull_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);
}

TEST(IptcDataSetsTest_628, Application2RecordListIsStableAcrossCalls_628) {
  const Exiv2::DataSet* list1 = Exiv2::IptcDataSets::application2RecordList();
  const Exiv2::DataSet* list2 = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list1, nullptr);
  EXPECT_EQ(list1, list2);
}

TEST(IptcDataSetsTest_628, Application2RecordListContainsTerminatorWithinReasonableBound_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const std::size_t count = CountUntilTerminator(list);
  EXPECT_GT(count, 0u) << "Terminator (number==65535) not found within hard cap";
}

TEST(IptcDataSetsTest_628, Application2RecordListHasAtLeastOneNonTerminatorEntry_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const std::size_t count = CountUntilTerminator(list);
  ASSERT_GT(count, 0u);
  ASSERT_GE(count, 2u) << "Expected at least one real entry plus a terminator";

  // First entry should not be the terminator.
  EXPECT_NE(list[0].number_, kTerminatorNumber);
}

TEST(IptcDataSetsTest_628, Application2RecordListTerminatorIsPresentAndCorrectlyMarked_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const std::size_t count = CountUntilTerminator(list);
  ASSERT_GT(count, 0u);

  const Exiv2::DataSet& last = list[count - 1];
  EXPECT_EQ(last.number_, kTerminatorNumber);
}

TEST(IptcDataSetsTest_628, Application2RecordListAllEntriesHaveApplication2RecordId_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const std::size_t count = CountUntilTerminator(list);
  ASSERT_GT(count, 0u);

  // Verify every element up to and including terminator reports application2 as recordId.
  for (std::size_t i = 0; i < count; ++i) {
    EXPECT_EQ(list[i].recordId_, Exiv2::IptcDataSets::application2) << "index=" << i;
  }
}

TEST(IptcDataSetsTest_628, Application2RecordListEntriesAreReadableWithoutCrashing_628) {
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  const std::size_t count = CountUntilTerminator(list);
  ASSERT_GT(count, 0u);

  // Boundary-style sanity checks on a few representative fields for all entries.
  // (No assumptions about exact strings or counts beyond terminator presence.)
  for (std::size_t i = 0; i < count; ++i) {
    // Pointers/strings in the struct should be non-null for core textual fields in a valid list.
    // If the implementation uses empty strings, they should still be non-null C strings.
    EXPECT_NE(list[i].name_, nullptr) << "index=" << i;
    EXPECT_NE(list[i].title_, nullptr) << "index=" << i;
    EXPECT_NE(list[i].desc_, nullptr) << "index=" << i;

    // Min/max sizes should not be inverted (boundary/consistency).
    EXPECT_LE(list[i].minSize_, list[i].maxSize_) << "index=" << i;
  }
}