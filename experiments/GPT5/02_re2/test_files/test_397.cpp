// File: prog_dump_test_397.cc
#include <gtest/gtest.h>
#include <regex>
#include <string>
#include "re2/prog.h"

using re2::Prog;
using std::string;

static void ExpectRegex(const std::string& s, const std::string& pattern) {
  std::regex re(pattern);
  ASSERT_TRUE(std::regex_match(s, re)) << "actual: [" << s << "] regex: [" << pattern << "]";
}

TEST(ProgInstDump_397, DumpAltFormatsBothBranches_397) {
  Prog::Inst inst;
  inst.InitAlt(/*out=*/12, /*out1=*/34);
  string s = inst.Dump();
  EXPECT_EQ(s, "alt -> 12 | 34");
}

TEST(ProgInstDump_397, DumpCaptureShowsCapAndOut_397) {
  Prog::Inst inst;
  inst.InitCapture(/*cap=*/7, /*out=*/99);
  string s = inst.Dump();
  EXPECT_EQ(s, "capture 7 -> 99");
}

TEST(ProgInstDump_397, DumpMatchShowsId_397) {
  Prog::Inst inst;
  inst.InitMatch(/*id=*/1234);
  string s = inst.Dump();
  EXPECT_EQ(s, "match! 1234");
}

TEST(ProgInstDump_397, DumpNopShowsOut_397) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/5);
  string s = inst.Dump();
  EXPECT_EQ(s, "nop -> 5");
}

TEST(ProgInstDump_397, DumpFailShowsFail_397) {
  Prog::Inst inst;
  inst.InitFail();
  string s = inst.Dump();
  EXPECT_EQ(s, "fail");
}

TEST(ProgInstDump_397, DumpEmptyWidthHexAndOut_397) {
  Prog::Inst inst;
  // Use a non-zero mask to verify %#x formatting shows hex with 0x prefix.
  // We don't rely on specific EmptyOp constants; we just pass a value.
  auto mask = static_cast<EmptyOp>(0x13); // arbitrary test value
  inst.InitEmptyWidth(mask, /*out=*/7);
  string s = inst.Dump();
  EXPECT_EQ(s, "emptywidth 0x13 -> 7");
}

TEST(ProgInstDump_397, DumpByteRangeNoFoldcase_397) {
  Prog::Inst inst;
  // 'A'-'Z' range. We do not assume any particular 'hint()' value, so we match it with a regex.
  inst.InitByteRange(/*lo=*/0x41, /*hi=*/0x5a, /*foldcase=*/0, /*out=*/3);
  string s = inst.Dump();
  // Expected format: "byte [41-5a] <hint> -> 3"
  // Verify exact hex casing and layout; allow any decimal hint.
  ExpectRegex(s, R"(byte \[41-5a\] \d+ -> 3)");
}

TEST(ProgInstDump_397, DumpByteRangeWithFoldcase_397) {
  Prog::Inst inst;
  // Full byte range boundary check with foldcase flag.
  inst.InitByteRange(/*lo=*/0x00, /*hi=*/0xff, /*foldcase=*/1, /*out=*/255);
  string s = inst.Dump();
  // Expected format: "byte/i [00-ff] <hint> -> 255"
  ExpectRegex(s, R"(byte/i \[00-ff\] \d+ -> 255)");
}
