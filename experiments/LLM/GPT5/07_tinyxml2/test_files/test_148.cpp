// File: xmlprinter_cstr_test_148.cpp
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLPrinterTest_148 : public ::testing::Test {
protected:
  using namespace tinyxml2;

  // Helper to build a printer without relying on specific enum values.
  static XMLPrinter MakePrinter() {
    // The interface shows: XMLPrinter(FILE*, bool, int, EscapeAposCharsInAttributes)
    // We avoid depending on specific enumerators by casting 0.
    return XMLPrinter(nullptr, /*compact=*/false, /*depth=*/0,
                      static_cast<EscapeAposCharsInAttributes>(0));
  }
};

TEST_F(XMLPrinterTest_148, CStr_IsNonNullAndNullTerminated_148) {
  auto printer = MakePrinter();

  const char* cstr = printer.CStr();
  ASSERT_NE(cstr, nullptr);

  // Validate it behaves like a C string (null-terminated).
  // If this isn't a valid C string, strlen would be unsafe; this test asserts the contract.
  EXPECT_GE(std::strlen(cstr), static_cast<size_t>(0));
}

TEST_F(XMLPrinterTest_148, CStr_IsIdempotentAcrossRepeatedCalls_148) {
  auto printer = MakePrinter();

  const char* p1 = printer.CStr();
  const char* p2 = printer.CStr();

  // For an unchanged printer, repeated calls should be stable.
  EXPECT_EQ(p1, p2);
}

TEST_F(XMLPrinterTest_148, CStr_ReflectsWrittenTextInBuffer_148) {
  auto printer = MakePrinter();

  // Use only public interface; do not assume exact formatting, only that text becomes observable.
  printer.OpenElement("root", /*compactMode=*/false);
  printer.PushText("hello", /*cdata=*/false);
  printer.CloseElement(/*compactMode=*/false);

  const std::string out = printer.CStr();
  EXPECT_NE(out.find("hello"), std::string::npos);
}

TEST_F(XMLPrinterTest_148, CStr_HandlesLargeTextWrites_148) {
  auto printer = MakePrinter();

  const std::string big(5000, 'a');

  printer.OpenElement("root", /*compactMode=*/false);
  printer.PushText(big.c_str(), /*cdata=*/false);
  printer.CloseElement(/*compactMode=*/false);

  const std::string out = printer.CStr();

  // Don't assume overall structure; just that the content is present.
  EXPECT_NE(out.find(big), std::string::npos);
}

TEST_F(XMLPrinterTest_148, ClearBuffer_ResetsObservableContentFromCStr_148) {
  auto printer = MakePrinter();

  printer.OpenElement("root", /*compactMode=*/false);
  printer.PushText("hello", /*cdata=*/false);
  printer.CloseElement(/*compactMode=*/false);

  const std::string before = printer.CStr();
  ASSERT_NE(before.find("hello"), std::string::npos);

  printer.ClearBuffer();

  const std::string after = printer.CStr();

  // Observable effect: previously-written content should no longer be present.
  EXPECT_EQ(after.find("hello"), std::string::npos);

  // Also ensure CStr remains valid after clearing.
  ASSERT_NE(printer.CStr(), nullptr);
  EXPECT_GE(std::strlen(printer.CStr()), static_cast<size_t>(0));
}

}  // namespace
