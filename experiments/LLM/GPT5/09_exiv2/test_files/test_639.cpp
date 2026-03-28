// ============================================================================
// TEST_ID: 639
// Unit tests for Exiv2::IptcDataSets::dataSetList(std::ostream&)
// File: test_datasets_639.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include <exiv2/datasets.hpp>

namespace {

using Exiv2::DataSet;
using Exiv2::IptcDataSets;

// Collect the exact lines that dataSetList() would print for a single record list,
// by using the same public streaming operator that production code uses.
static std::vector<std::string> CollectPrintedLines(const DataSet* list) {
  std::vector<std::string> lines;
  if (!list) return lines;

  for (int i = 0; list[i].number_ != 0xffff; ++i) {
    std::ostringstream os;
    os << list[i] << "\n";
    lines.push_back(os.str());
  }
  return lines;
}

static std::string Join(const std::vector<std::string>& lines) {
  std::string out;
  for (const auto& l : lines) out += l;
  return out;
}

class IptcDataSetsTest_639 : public ::testing::Test {};

}  // namespace

TEST_F(IptcDataSetsTest_639, DataSetListProducesNonEmptyOutput_639) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
}

TEST_F(IptcDataSetsTest_639, DataSetListIsDeterministicAcrossCalls_639) {
  std::ostringstream os1;
  std::ostringstream os2;

  IptcDataSets::dataSetList(os1);
  IptcDataSets::dataSetList(os2);

  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(IptcDataSetsTest_639, DataSetListEndsLinesWithNewline_639) {
  std::ostringstream os;
  IptcDataSets::dataSetList(os);

  const std::string out = os.str();
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '\n');
}

TEST_F(IptcDataSetsTest_639, DataSetListContainsEnvelopeAndApplication2Entries_639) {
  // Build expected text for known public record lists.
  const auto env_lines = CollectPrintedLines(IptcDataSets::envelopeRecordList());
  const auto app2_lines = CollectPrintedLines(IptcDataSets::application2RecordList());

  // Sanity: at least one of these should have entries in a normal build.
  ASSERT_TRUE(!env_lines.empty() || !app2_lines.empty());

  std::ostringstream os;
  IptcDataSets::dataSetList(os);
  const std::string out = os.str();

  // Verify that printed output includes entries from those public record lists.
  // (We avoid assuming ordering across records; we only require inclusion.)
  for (const auto& l : env_lines) {
    EXPECT_NE(out.find(l), std::string::npos) << "Missing envelope entry line: " << l;
  }
  for (const auto& l : app2_lines) {
    EXPECT_NE(out.find(l), std::string::npos) << "Missing application2 entry line: " << l;
  }
}

TEST_F(IptcDataSetsTest_639, DataSetListDoesNotClearFailStateOfStream_639) {
  std::ostringstream os;
  os.setstate(std::ios::failbit);
  const auto before_state = os.rdstate();

  IptcDataSets::dataSetList(os);

  // If the caller passes a stream already in fail state, the function should not
  // "fix" it (observable behavior) and output should remain empty.
  EXPECT_EQ(os.rdstate(), before_state);
  EXPECT_TRUE(os.str().empty());
}