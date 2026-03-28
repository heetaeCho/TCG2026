// TEST_ID: 322
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

#include <string>

namespace {

using namespace tinyxml2;

class XMLPrinterVisitUnknownTest_322 : public ::testing::Test {
protected:
  static XMLPrinter MakePrinter() {
    // The provided header shows a 4-arg constructor taking EscapeAposCharsInAttributes.
    // Use a safe default value via cast to avoid depending on specific enum constants.
    return XMLPrinter(nullptr, /*compact=*/false, /*depth=*/0,
                      static_cast<EscapeAposCharsInAttributes>(0));
  }

  // Parses a small document that should contain an unknown node (commonly produced by
  // processing instructions other than the XML declaration).
  static XMLUnknown* ParseAndGetUnknownOrFail(XMLDocument& doc) {
    // Processing instruction inside the document body is typically represented as XMLUnknown.
    const char* kXml = "<root><?pi target?></root>";
    EXPECT_EQ(doc.Parse(kXml), XML_SUCCESS);

    XMLNode* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);
    if (!root) return nullptr;

    for (XMLNode* n = root->FirstChild(); n; n = n->NextSibling()) {
      if (XMLUnknown* u = n->ToUnknown()) {
        return u;
      }
    }
    // If the library build doesn't treat processing instructions as XMLUnknown,
    // the test can't proceed meaningfully.
    ADD_FAILURE() << "Expected an XMLUnknown node under <root>, but none was found.";
    return nullptr;
  }
};

TEST_F(XMLPrinterVisitUnknownTest_322, VisitReturnsTrue_322) {
  XMLDocument doc;
  XMLUnknown* unknown = ParseAndGetUnknownOrFail(doc);
  ASSERT_NE(unknown, nullptr);

  XMLPrinter printer = MakePrinter();
  EXPECT_TRUE(printer.Visit(*unknown));
}

TEST_F(XMLPrinterVisitUnknownTest_322, VisitEmitsUnknownValueIntoOutput_322) {
  XMLDocument doc;
  XMLUnknown* unknown = ParseAndGetUnknownOrFail(doc);
  ASSERT_NE(unknown, nullptr);
  ASSERT_NE(unknown->Value(), nullptr);

  XMLPrinter printer = MakePrinter();

  const std::string before = printer.CStr() ? printer.CStr() : "";
  ASSERT_TRUE(printer.Visit(*unknown));

  const std::string after = printer.CStr() ? printer.CStr() : "";
  // Observable behavior: output should contain the unknown's Value() somewhere.
  EXPECT_NE(after.find(unknown->Value()), std::string::npos);

  // Also ensure Visit did not shrink output.
  EXPECT_GE(after.size(), before.size());
}

TEST_F(XMLPrinterVisitUnknownTest_322, AcceptInvokesVisitorAndReturnsTrue_322) {
  XMLDocument doc;
  XMLUnknown* unknown = ParseAndGetUnknownOrFail(doc);
  ASSERT_NE(unknown, nullptr);
  ASSERT_NE(unknown->Value(), nullptr);

  XMLPrinter printer = MakePrinter();

  // Exercise the visitor path through the XMLUnknown public interface.
  EXPECT_TRUE(unknown->Accept(&printer));

  const std::string out = printer.CStr() ? printer.CStr() : "";
  EXPECT_NE(out.find(unknown->Value()), std::string::npos);
}

TEST_F(XMLPrinterVisitUnknownTest_322, MultipleVisitsAppendOutput_322) {
  XMLDocument doc;
  XMLUnknown* unknown = ParseAndGetUnknownOrFail(doc);
  ASSERT_NE(unknown, nullptr);
  ASSERT_NE(unknown->Value(), nullptr);

  XMLPrinter printer = MakePrinter();

  ASSERT_TRUE(printer.Visit(*unknown));
  const std::string once = printer.CStr() ? printer.CStr() : "";

  ASSERT_TRUE(printer.Visit(*unknown));
  const std::string twice = printer.CStr() ? printer.CStr() : "";

  // Observable effect: after a second visit, output should not be shorter.
  EXPECT_GE(twice.size(), once.size());

  // And it should still contain the unknown value.
  EXPECT_NE(twice.find(unknown->Value()), std::string::npos);
}

}  // namespace
