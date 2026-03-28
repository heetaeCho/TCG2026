// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptc_printstructure_701.cpp

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/error.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/slice.hpp>
#include <exiv2/types.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::byte;

class IptcDataPrintStructureTest_701 : public ::testing::Test {
 protected:
  static Exiv2::Slice<byte*> MakeSlice(std::vector<byte>& buf) {
    return Exiv2::Slice<byte*>(buf.data(), 0U, buf.size());
  }

  static std::string RunPrint(Exiv2::IptcData& iptc, std::vector<byte>& buf, size_t depth) {
    std::ostringstream os;
    iptc.printStructure(os, MakeSlice(buf), depth);
    return os.str();
  }

  static void AppendIptcBlock(std::vector<byte>& buf, uint8_t record, uint8_t dataset,
                             const std::vector<byte>& data) {
    // IPTC block format used by printStructure():
    // 0x1c, record, dataset, len_hi, len_lo, data...
    buf.push_back(static_cast<byte>(0x1c));
    buf.push_back(static_cast<byte>(record));
    buf.push_back(static_cast<byte>(dataset));
    const uint16_t len = static_cast<uint16_t>(data.size());
    buf.push_back(static_cast<byte>((len >> 8) & 0xff));
    buf.push_back(static_cast<byte>(len & 0xff));
    buf.insert(buf.end(), data.begin(), data.end());
  }
};

TEST_F(IptcDataPrintStructureTest_701, ReturnsEarlyWhenTooSmall_701) {
  Exiv2::IptcData iptc;

  std::vector<byte> buf0;
  EXPECT_TRUE(RunPrint(iptc, buf0, 0).empty());

  std::vector<byte> buf1 = {static_cast<byte>(0x1c)};
  EXPECT_TRUE(RunPrint(iptc, buf1, 0).empty());

  std::vector<byte> buf2 = {static_cast<byte>(0x00), static_cast<byte>(0x1c)};
  EXPECT_TRUE(RunPrint(iptc, buf2, 123).empty());
}

TEST_F(IptcDataPrintStructureTest_701, PrintsHeaderEvenIfNoMarkerFound_701) {
  Exiv2::IptcData iptc;

  // size == 3 is NOT an early-return; function prints the header then stops.
  std::vector<byte> buf3 = {static_cast<byte>(0x00), static_cast<byte>(0x00), static_cast<byte>(0x00)};
  const std::string out = RunPrint(iptc, buf3, 0);

  EXPECT_NE(out.find("Record | DataSet | Name | Length | Data"), std::string::npos);
}

TEST_F(IptcDataPrintStructureTest_701, SkipsLeadingBytesUntilMarkerAndPrintsEntry_701) {
  Exiv2::IptcData iptc;

  std::vector<byte> buf = {
      static_cast<byte>(0x00), static_cast<byte>(0xff), static_cast<byte>(0x7e), static_cast<byte>(0x01),
  };
  const uint8_t record = 2;
  const uint8_t dataset = 5;
  const std::vector<byte> data = {static_cast<byte>('A'), static_cast<byte>('B'), static_cast<byte>('C')};
  AppendIptcBlock(buf, record, dataset, data);

  const std::string out = RunPrint(iptc, buf, 0);

  EXPECT_NE(out.find("Record | DataSet | Name | Length | Data"), std::string::npos);

  // Validate that record/dataset and the dataset name (via public API) appear.
  const std::string expectedName = Exiv2::IptcDataSets::dataSetName(dataset, record);
  EXPECT_NE(out.find(expectedName), std::string::npos);

  // Also ensure numbers show up somewhere in the line (formatting is not asserted exactly).
  EXPECT_NE(out.find("2"), std::string::npos);
  EXPECT_NE(out.find("5"), std::string::npos);
}

TEST_F(IptcDataPrintStructureTest_701, StopsParsingIfByteAtCurrentIndexIsNotMarker_701) {
  Exiv2::IptcData iptc;

  // First a valid block, then an invalid byte instead of 0x1c -> loop breaks.
  std::vector<byte> buf;
  AppendIptcBlock(buf, /*record=*/1, /*dataset=*/1,
                  /*data=*/{static_cast<byte>('X')});

  buf.push_back(static_cast<byte>(0x00));  // not 0x1c
  // Even if more bytes follow, parsing should stop at this point.
  AppendIptcBlock(buf, /*record=*/2, /*dataset=*/2,
                  /*data=*/{static_cast<byte>('Y')});

  const std::string out = RunPrint(iptc, buf, 0);

  const std::string name1 = Exiv2::IptcDataSets::dataSetName(/*number=*/1, /*recordId=*/1);
  const std::string name2 = Exiv2::IptcDataSets::dataSetName(/*number=*/2, /*recordId=*/2);

  EXPECT_NE(out.find(name1), std::string::npos);
  EXPECT_EQ(out.find(name2), std::string::npos);  // second entry should not be printed
}

TEST_F(IptcDataPrintStructureTest_701, AppendsEllipsisWhenLengthExceeds40_701) {
  Exiv2::IptcData iptc;

  std::vector<byte> buf;
  std::vector<byte> data41(41, static_cast<byte>('Z'));
  AppendIptcBlock(buf, /*record=*/2, /*dataset=*/5, data41);

  const std::string out = RunPrint(iptc, buf, 0);

  // When len > 40, implementation appends "...\n".
  EXPECT_NE(out.find("..."), std::string::npos);
}

TEST_F(IptcDataPrintStructureTest_701, ThrowsOnTruncatedBlockHeaderOrData_701) {
  Exiv2::IptcData iptc;

  // Case A: marker present, but fewer than 5 bytes remaining -> corrupted.
  {
    std::vector<byte> buf = {
        static_cast<byte>(0x1c), static_cast<byte>(0x02), static_cast<byte>(0x05), static_cast<byte>(0x00),
        // missing length low byte (and data)
    };
    std::ostringstream os;
    EXPECT_THROW(iptc.printStructure(os, MakeSlice(buf), 0), Exiv2::Error);
  }

  // Case B: header says len=3 but only 2 bytes of data present -> corrupted.
  {
    std::vector<byte> buf = {
        static_cast<byte>(0x1c), static_cast<byte>(0x02), static_cast<byte>(0x05),
        static_cast<byte>(0x00), static_cast<byte>(0x03),  // len = 3
        static_cast<byte>('A'), static_cast<byte>('B')      // only 2 bytes data
    };
    std::ostringstream os;
    EXPECT_THROW(iptc.printStructure(os, MakeSlice(buf), 0), Exiv2::Error);
  }
}

}  // namespace