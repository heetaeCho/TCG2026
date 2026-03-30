// printTextString_test_2662.cc
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>

#include "goo/GooString.h"
#include "poppler/UnicodeMap.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::StrictMock;

// --- Hooking printStdTextString ------------------------------------------------
// We don't know where/if the real printStdTextString is defined in the build.
// To make the test independent (and verifiable), we remap the symbol used by
// pdfinfo.cc to our hook via a preprocessor define before including pdfinfo.cc.
class PrintStdTextStringMock_2662 {
public:
  MOCK_METHOD(void, Call, (const std::string &s, const UnicodeMap *uMap));
};

static PrintStdTextStringMock_2662 *g_printStdTextStringMock_2662 = nullptr;

static void printStdTextString_TestHook_2662(const std::string &s, const UnicodeMap *uMap)
{
  // If no mock is installed, just return (keeps non-mock scenarios from crashing).
  if (g_printStdTextStringMock_2662) {
    g_printStdTextStringMock_2662->Call(s, uMap);
  }
}

#define printStdTextString printStdTextString_TestHook_2662
// Include the implementation so the TU can see the static helper.
#include "utils/pdfinfo.cc"
#undef printStdTextString

// --- Tests --------------------------------------------------------------------
class PrintTextStringTest_2662 : public ::testing::Test {
protected:
  void SetUp() override { g_printStdTextStringMock_2662 = &mock_; }
  void TearDown() override { g_printStdTextStringMock_2662 = nullptr; }

  StrictMock<PrintStdTextStringMock_2662> mock_;
};

TEST_F(PrintTextStringTest_2662, ForwardsStringAndMapPointer_2662)
{
  const GooString s("Hello, Poppler!");
  const UnicodeMap *uMap = nullptr;

  EXPECT_CALL(mock_, Call(Eq(std::string("Hello, Poppler!")), Eq(uMap))).Times(1);

  // Calls the static helper from pdfinfo.cc (visible because we included it).
  printTextString(&s, uMap);
}

TEST_F(PrintTextStringTest_2662, HandlesEmptyString_2662)
{
  const GooString s("");
  const UnicodeMap *uMap = nullptr;

  EXPECT_CALL(mock_, Call(Eq(std::string("")), Eq(uMap))).Times(1);

  printTextString(&s, uMap);
}

TEST_F(PrintTextStringTest_2662, PreservesEmbeddedNullBytes_2662)
{
  const char raw[] = {'A', 'B', '\0', 'C', 'D'};
  const GooString s(raw, sizeof(raw));
  const UnicodeMap *uMap = nullptr;

  const std::string expected(raw, sizeof(raw));
  EXPECT_CALL(mock_, Call(Eq(expected), Eq(uMap))).Times(1);

  printTextString(&s, uMap);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PrintTextStringTest_2662, DeathOnNullGooStringPointer_2662)
{
  // Observable error case: passing nullptr will dereference s->toStr().
  // We don't assert a specific message; just that it terminates.
  EXPECT_DEATH({ printTextString(nullptr, nullptr); }, "");
}
#endif