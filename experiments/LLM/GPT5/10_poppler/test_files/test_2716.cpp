// File: getInfoString_test_2716.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "goo/GooString.h"

// pdftohtml.cc is a tool and may define its own main(). We rename it to avoid clashes.
#define main pdftohtml_tool_main_2716
#include "utils/pdftohtml.cc"
#undef main

namespace {

class GetInfoStringTest_2716 : public ::testing::Test {
protected:
  static std::unique_ptr<Dict> MakeDict_2716()
  {
    return std::make_unique<Dict>(nullptr);
  }

  static void AddString_2716(Dict *dict, const char *key, const std::string &bytes)
  {
    ASSERT_NE(dict, nullptr);
    ASSERT_NE(key, nullptr);
    auto gs = std::make_unique<GooString>(bytes.data(), bytes.size());
    dict->add(key, Object(std::move(gs)));
  }

  static void AddInt_2716(Dict *dict, const char *key, int v)
  {
    ASSERT_NE(dict, nullptr);
    ASSERT_NE(key, nullptr);
    dict->add(key, Object(v));
  }

  static std::string MakeUtf16BeWithBom_2716(const std::vector<uint16_t> &codeUnits)
  {
    // BOM (UTF-16BE): 0xFE 0xFF
    std::string s;
    s.push_back(static_cast<char>(0xFE));
    s.push_back(static_cast<char>(0xFF));
    for (uint16_t cu : codeUnits) {
      s.push_back(static_cast<char>((cu >> 8) & 0xFF));
      s.push_back(static_cast<char>(cu & 0xFF));
    }
    return s;
  }
};

TEST_F(GetInfoStringTest_2716, MissingKeyReturnsNull_2716)
{
  auto dict = MakeDict_2716();

  // Key doesn't exist -> lookup should not yield a string -> expect nullptr result.
  std::unique_ptr<GooString> out = getInfoString(dict.get(), "Title");
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetInfoStringTest_2716, NonStringValueReturnsNull_2716)
{
  auto dict = MakeDict_2716();
  AddInt_2716(dict.get(), "Title", 123);

  std::unique_ptr<GooString> out = getInfoString(dict.get(), "Title");
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetInfoStringTest_2716, AsciiStringReturnsNonNullAndIsDeterministic_2716)
{
  auto dict = MakeDict_2716();
  AddString_2716(dict.get(), "Title", "Hello, PDF!");

  std::unique_ptr<GooString> out1 = getInfoString(dict.get(), "Title");
  std::unique_ptr<GooString> out2 = getInfoString(dict.get(), "Title");

  ASSERT_NE(out1, nullptr);
  ASSERT_NE(out2, nullptr);

  // We don't assume exact transformation details (HTML escaping, etc.),
  // but repeated calls with the same inputs should be stable.
  EXPECT_EQ(out1->toStr(), out2->toStr());
}

TEST_F(GetInfoStringTest_2716, Utf16BeBomStringReturnsNonNullAndIsDeterministic_2716)
{
  auto dict = MakeDict_2716();

  // "AB" in UTF-16BE with BOM.
  const std::string bytes = MakeUtf16BeWithBom_2716({0x0041, 0x0042});
  AddString_2716(dict.get(), "Title", bytes);

  std::unique_ptr<GooString> out1 = getInfoString(dict.get(), "Title");
  std::unique_ptr<GooString> out2 = getInfoString(dict.get(), "Title");

  ASSERT_NE(out1, nullptr);
  ASSERT_NE(out2, nullptr);
  EXPECT_EQ(out1->toStr(), out2->toStr());
}

TEST_F(GetInfoStringTest_2716, HighBitBytesInPdfDocEncodingPathDoNotCrashAndReturnNonNull_2716)
{
  auto dict = MakeDict_2716();

  // Bytes with high bits set; exercises pdfDocEncoding lookup path.
  std::string bytes;
  bytes.push_back(static_cast<char>(0x80));
  bytes.push_back(static_cast<char>(0xFF));
  bytes.push_back(static_cast<char>(0xA5));
  bytes.push_back(static_cast<char>(0x00)); // include NUL as a raw byte as well
  bytes.push_back(static_cast<char>(0x7F));

  AddString_2716(dict.get(), "Title", bytes);

  std::unique_ptr<GooString> out = getInfoString(dict.get(), "Title");
  // Only observable guarantee we can assert from the interface here:
  // string input should produce some (possibly empty) filtered string object.
  EXPECT_NE(out, nullptr);
}

TEST_F(GetInfoStringTest_2716, LongStringReturnsNonNull_2716)
{
  auto dict = MakeDict_2716();

  std::string longBytes(4096, 'A');
  AddString_2716(dict.get(), "Title", longBytes);

  std::unique_ptr<GooString> out = getInfoString(dict.get(), "Title");
  EXPECT_NE(out, nullptr);
}

} // namespace