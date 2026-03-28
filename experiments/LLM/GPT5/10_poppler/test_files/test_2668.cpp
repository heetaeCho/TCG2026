// pdfinfo_printAttribute_test_2668.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

#include "poppler/GooString.h"
#include "poppler/Object.h"
#include "poppler/StructElement.h"

// pdfinfo.cc is a utility with a main(). We rename it so we can include the .cc
// and still build/run gtest without symbol conflicts, while keeping access to
// internal static helpers in this translation unit.
#define main pdfinfo_main_2668
#include "utils/pdfinfo.cc"
#undef main

using ::testing::HasSubstr;
using ::testing::Not;

namespace {

class PrintAttributeTest_2668 : public ::testing::Test {
protected:
  static std::string CapturePrintAttribute(const Attribute *attr, unsigned indent) {
    testing::internal::CaptureStdout();
    printAttribute(attr, indent);
    return testing::internal::GetCapturedStdout();
  }
};

TEST_F(PrintAttributeTest_2668, StandardAttributePrintsTypeAndValue_2668) {
  // Use a known standard attribute type from Attribute::Type.
  auto *value = new Object(42);
  Attribute attr(Attribute::Placement, value);

  const std::string out = CapturePrintAttribute(&attr, 0);

  // Basic markers: leading " /<TypeName> " and the printed value.
  EXPECT_THAT(out, HasSubstr(" /"));
  EXPECT_THAT(out, HasSubstr("/Placement"));
  EXPECT_THAT(out, HasSubstr("42"));

  // Not a user property, so no "(name)" segment should be printed.
  EXPECT_THAT(out, Not(HasSubstr("(")));
  EXPECT_THAT(out, Not(HasSubstr(")")));
}

TEST_F(PrintAttributeTest_2668, UserPropertyPrintsTypeNameAndCustomName_2668) {
  auto *value = new Object(7);
  Attribute attr(GooString("CustomProp"), value); // UserProperty attribute

  const std::string out = CapturePrintAttribute(&attr, 0);

  EXPECT_THAT(out, HasSubstr("/UserProperty"));
  EXPECT_THAT(out, HasSubstr("(CustomProp)"));
  EXPECT_THAT(out, HasSubstr("7"));
}

TEST_F(PrintAttributeTest_2668, FormattedValueIsPrintedInQuotesWhenPresent_2668) {
  auto *value = new Object(123);
  Attribute attr(Attribute::Width, value);
  attr.setFormattedValue("formatted-123");

  const std::string out = CapturePrintAttribute(&attr, 0);

  EXPECT_THAT(out, HasSubstr("/Width"));
  EXPECT_THAT(out, HasSubstr("123"));
  EXPECT_THAT(out, HasSubstr(" \"formatted-123\""));
}

TEST_F(PrintAttributeTest_2668, HiddenFlagAppendsHiddenMarker_2668) {
  auto *value = new Object(1);
  Attribute attr(Attribute::Height, value);
  attr.setHidden(true);

  const std::string out = CapturePrintAttribute(&attr, 0);

  EXPECT_THAT(out, HasSubstr("/Height"));
  EXPECT_THAT(out, HasSubstr("1"));
  EXPECT_THAT(out, HasSubstr(" [hidden]"));
}

TEST_F(PrintAttributeTest_2668, NoFormattedValueDoesNotPrintQuotes_2668) {
  auto *value = new Object(55);
  Attribute attr(Attribute::TextIndent, value);

  const std::string out = CapturePrintAttribute(&attr, 0);

  EXPECT_THAT(out, HasSubstr("/TextIndent"));
  EXPECT_THAT(out, HasSubstr("55"));
  EXPECT_THAT(out, Not(HasSubstr(" \""))); // no opening quote segment expected
}

TEST_F(PrintAttributeTest_2668, IndentDoesNotAffectCoreContent_2668) {
  auto *value = new Object(9);
  Attribute attr(Attribute::SpaceBefore, value);

  const std::string out0 = CapturePrintAttribute(&attr, 0);
  const std::string out4 = CapturePrintAttribute(&attr, 4);

  // We don't assert exact indentation (printIndent is outside this snippet),
  // but core content should always be present.
  EXPECT_THAT(out0, HasSubstr("/SpaceBefore"));
  EXPECT_THAT(out0, HasSubstr("9"));

  EXPECT_THAT(out4, HasSubstr("/SpaceBefore"));
  EXPECT_THAT(out4, HasSubstr("9"));
}

TEST_F(PrintAttributeTest_2668, UnknownTypeDoesNotCrashAndPrintsSomething_2668) {
  auto *value = new Object(0);
  Attribute attr(Attribute::Unknown, value);

  const std::string out = CapturePrintAttribute(&attr, 0);

  // Observable behavior: should emit at least the " /" prefix and a value print.
  EXPECT_THAT(out, HasSubstr(" /"));
  EXPECT_THAT(out, HasSubstr("0"));
}

} // namespace