// File: datasets_test_652.cpp
// TEST_ID: 652
//
// Unit tests for Exiv2::operator<<(std::ostream&, const Exiv2::DataSet&)
// covering observable formatting/escaping behaviors only (black-box).

#include <gtest/gtest.h>

#include <cstdint>
#include <iomanip>
#include <limits>
#include <regex>
#include <sstream>
#include <string>

#include "exiv2/datasets.hpp"

namespace {

std::string Hex4Lower(uint16_t v) {
  std::ostringstream os;
  os << "0x" << std::hex << std::nouppercase << std::setw(4) << std::setfill('0')
     << static_cast<unsigned>(v);
  return os.str();
}

std::string StreamDataSet(const Exiv2::DataSet& ds) {
  std::ostringstream os;
  os << ds;
  return os.str();
}

}  // namespace

class DataSetOstreamTest_652 : public ::testing::Test {};

TEST_F(DataSetOstreamTest_652, StreamsKnownDataSetFromList_NonEmptyAndHasHex_652) {
  // Use a real dataset from the library (no assumptions about internal logic).
  const Exiv2::DataSet* list = Exiv2::IptcDataSets::application2RecordList();
  ASSERT_NE(list, nullptr);

  // The list is expected to contain at least one entry in normal builds.
  const Exiv2::DataSet& ds = list[0];

  const std::string out = StreamDataSet(ds);
  EXPECT_FALSE(out.empty());

  // Observable formatting: contains 0x???? hex for dataset number (width 4).
  EXPECT_NE(out.find(Hex4Lower(ds.number_)), std::string::npos);

  // Observable: includes record name string for the recordId (whatever it is).
  const std::string recName = Exiv2::IptcDataSets::recordName(ds.recordId_);
  EXPECT_NE(out.find(recName), std::string::npos);
}

TEST_F(DataSetOstreamTest_652, EscapesQuotesInDescriptionByDoubling_652) {
  Exiv2::DataSet ds{};
  ds.number_ = 5;
  ds.recordId_ = 2;
  ds.name_ = "TestName";
  ds.title_ = "TestTitle";
  ds.mandatory_ = true;
  ds.repeatable_ = false;
  ds.minbytes_ = 0;
  ds.maxbytes_ = 10;
  ds.type_ = Exiv2::IptcDataSets::dataSetType(ds.number_, ds.recordId_);

  // Description containing quotes should have each " doubled in the streamed output.
  ds.desc_ = R"(He said "hello" and then "bye".)";
  ds.photoshop_ = "PsName";

  const std::string out = StreamDataSet(ds);

  // The operator wraps description in quotes and doubles internal quotes.
  // We check for the doubled-quote sequence "" (two quote characters) in the output.
  EXPECT_NE(out.find(R"("")"), std::string::npos);

  // Also ensure the raw (single) quoted fragment does not appear as-is.
  // (If it does, quotes weren't doubled.)
  EXPECT_EQ(out.find(R"("hello")"), std::string::npos);
}

TEST_F(DataSetOstreamTest_652, EmptyDescriptionIsStillQuoted_652) {
  Exiv2::DataSet ds{};
  ds.number_ = 1;
  ds.recordId_ = 1;
  ds.name_ = "N";
  ds.title_ = "T";
  ds.mandatory_ = false;
  ds.repeatable_ = false;
  ds.minbytes_ = 0;
  ds.maxbytes_ = 0;
  ds.type_ = Exiv2::IptcDataSets::dataSetType(ds.number_, ds.recordId_);
  ds.desc_ = "";
  ds.photoshop_ = "";

  const std::string out = StreamDataSet(ds);

  // Look for a quoted empty string: "" somewhere in the output.
  EXPECT_NE(out.find(R"("")"), std::string::npos);
}

TEST_F(DataSetOstreamTest_652, BooleanFieldsRenderAsTrueFalseStrings_652) {
  Exiv2::DataSet ds{};
  ds.number_ = 10;
  ds.recordId_ = 2;
  ds.name_ = "BoolTest";
  ds.title_ = "BoolTitle";
  ds.mandatory_ = true;
  ds.repeatable_ = false;
  ds.minbytes_ = 1;
  ds.maxbytes_ = 2;
  ds.type_ = Exiv2::IptcDataSets::dataSetType(ds.number_, ds.recordId_);
  ds.desc_ = "Desc";
  ds.photoshop_ = "Ps";

  const std::string out = StreamDataSet(ds);

  EXPECT_NE(out.find("true"), std::string::npos);
  EXPECT_NE(out.find("false"), std::string::npos);
}

TEST_F(DataSetOstreamTest_652, HexFormattingIsWidth4AtBoundaryValues_652) {
  {
    Exiv2::DataSet ds{};
    ds.number_ = 0;
    ds.recordId_ = 1;
    ds.name_ = "Zero";
    ds.title_ = "ZeroTitle";
    ds.mandatory_ = false;
    ds.repeatable_ = false;
    ds.minbytes_ = 0;
    ds.maxbytes_ = 0;
    ds.type_ = Exiv2::IptcDataSets::dataSetType(ds.number_, ds.recordId_);
    ds.desc_ = "D";
    ds.photoshop_ = "P";

    const std::string out = StreamDataSet(ds);
    EXPECT_NE(out.find("0x0000"), std::string::npos);
  }

  {
    Exiv2::DataSet ds{};
    ds.number_ = std::numeric_limits<uint16_t>::max();  // 0xFFFF
    ds.recordId_ = 1;
    ds.name_ = "Max";
    ds.title_ = "MaxTitle";
    ds.mandatory_ = false;
    ds.repeatable_ = false;
    ds.minbytes_ = 0;
    ds.maxbytes_ = 0;
    ds.type_ = Exiv2::IptcDataSets::dataSetType(ds.number_, ds.recordId_);
    ds.desc_ = "D";
    ds.photoshop_ = "P";

    const std::string out = StreamDataSet(ds);
    EXPECT_NE(out.find("0xffff"), std::string::npos);
  }
}