// ============================================================================
// Unit tests for DumpStringMap (TEST_ID: 2139)
// File: test_DumpStringMap_2139.cpp
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <map>
#include <string>
#include <vector>
#include <cstring>

// Pull in the real implementation (DumpStringMap has internal linkage in the .cpp).
// This is a common technique for unit-testing file-scope static functions without
// re-implementing them.
#include "TestProjects/exiv2/xmpsdk/src/XMPMeta.cpp"

namespace {

using ::testing::AtLeast;

// A capture sink for XMP_TextOutputProc.
struct OutputCapture {
  std::string out;
};

// A trampoline that matches XMP_TextOutputProc as defined by the XMP SDK headers
// brought in via XMPMeta.cpp includes.
static void CaptureTextOutput(void* refCon, XMP_StringPtr buffer, XMP_StringLen len) {
  auto* cap = static_cast<OutputCapture*>(refCon);
  if (cap == nullptr) return;
  if (buffer == nullptr) return;
  cap->out.append(buffer, static_cast<size_t>(len));
}

// Helper: find the first occurrence of a line containing `needle`.
static bool AnyLineContains(const std::string& haystack, const std::string& needle) {
  size_t start = 0;
  while (start <= haystack.size()) {
    size_t end = haystack.find('\n', start);
    if (end == std::string::npos) end = haystack.size();
    const std::string line = haystack.substr(start, end - start);
    if (line.find(needle) != std::string::npos) return true;
    if (end == haystack.size()) break;
    start = end + 1;
  }
  return false;
}

class DumpStringMapTest_2139 : public ::testing::Test {};

TEST_F(DumpStringMapTest_2139, EmptyMapEmitsLabelAndNoKeyValueArrowLines_2139) {
  XMP_StringMap map;  // typically std::map<std::string, std::string>
  OutputCapture cap;

  const XMP_StringPtr label = "MyLabel";
  const XMP_Status st = DumpStringMap(map, label, &CaptureTextOutput, &cap);

  // Observable behavior:
  // - Should at least emit the label somewhere in the output.
  EXPECT_NE(cap.out.find("MyLabel"), std::string::npos);

  // - With an empty map, there should be no " => " key/value lines.
  EXPECT_EQ(cap.out.find(" => "), std::string::npos);

  // - Should be "successful" (observable via return value).
  //   (In the real codebase, DumpStringMap returns an XMP_Status where 0 means OK.)
  EXPECT_EQ(st, static_cast<XMP_Status>(0));
}

TEST_F(DumpStringMapTest_2139, SingleEntryEmitsKeyArrowValueLine_2139) {
  XMP_StringMap map;
  map["Key"] = "Value";

  OutputCapture cap;
  const XMP_Status st = DumpStringMap(map, "One", &CaptureTextOutput, &cap);

  EXPECT_EQ(st, static_cast<XMP_Status>(0));

  // Expect a line that contains the key and value with the arrow marker.
  EXPECT_TRUE(AnyLineContains(cap.out, "Key"))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, " => "))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, "Value"))
      << "Output was:\n"
      << cap.out;

  // The implementation shows it emits two leading spaces before the key on each entry line.
  // Verify the presence of the expected prefix pattern somewhere.
  EXPECT_NE(cap.out.find("  Key"), std::string::npos)
      << "Output was:\n"
      << cap.out;
}

TEST_F(DumpStringMapTest_2139, MultipleEntriesIncludeAllPairs_2139) {
  XMP_StringMap map;
  map["A"] = "1";
  map["BB"] = "22";
  map["CCC"] = "333";

  OutputCapture cap;
  const XMP_Status st = DumpStringMap(map, "Multi", &CaptureTextOutput, &cap);

  EXPECT_EQ(st, static_cast<XMP_Status>(0));

  // Verify each pair appears in output (order is map-defined; we don't assume it).
  EXPECT_TRUE(AnyLineContains(cap.out, "A"))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, "BB"))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, "CCC"))
      << "Output was:\n"
      << cap.out;

  EXPECT_TRUE(AnyLineContains(cap.out, "1"))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, "22"))
      << "Output was:\n"
      << cap.out;
  EXPECT_TRUE(AnyLineContains(cap.out, "333"))
      << "Output was:\n"
      << cap.out;

  // Arrow marker should appear for each entry (at least 3 times).
  size_t pos = 0;
  int arrowCount = 0;
  while (true) {
    pos = cap.out.find(" => ", pos);
    if (pos == std::string::npos) break;
    ++arrowCount;
    pos += 4;
  }
  EXPECT_GE(arrowCount, 3) << "Output was:\n" << cap.out;
}

struct MockOutProcSink {
  MOCK_METHOD(void, OnChunk, (XMP_StringPtr buf, XMP_StringLen len));
};

static void MockTextOutput(void* refCon, XMP_StringPtr buffer, XMP_StringLen len) {
  auto* sink = static_cast<MockOutProcSink*>(refCon);
  if (sink == nullptr) return;
  sink->OnChunk(buffer, len);
}

TEST_F(DumpStringMapTest_2139, InvokesOutputProcForLabelAndEntries_2139) {
  XMP_StringMap map;
  map["K"] = "V";

  MockOutProcSink sink;

  // We don't assume chunk boundaries; just verify it calls the proc at least once.
  EXPECT_CALL(sink, OnChunk(::testing::NotNull(), ::testing::_)).Times(AtLeast(1));

  const XMP_Status st = DumpStringMap(map, "Lbl", &MockTextOutput, &sink);
  EXPECT_EQ(st, static_cast<XMP_Status>(0));
}

}  // namespace