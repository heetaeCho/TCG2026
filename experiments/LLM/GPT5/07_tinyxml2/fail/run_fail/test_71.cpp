// TEST_ID: 71
#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLAttributeIntValueTest_71 : public ::testing::Test {
protected:
  // Parses: <root a="..."/>
  // Returns the attribute pointer for name "a" (must exist if parse succeeds).
  static const XMLAttribute* ParseAndGetAttrA(const std::string& attrValue) {
    XMLDocument doc;

    std::string xml = "<root a=\"";
    xml += attrValue;
    xml += "\"/>";

    const XMLError err = doc.Parse(xml.c_str());
    EXPECT_EQ(err, XML_SUCCESS) << "XML parse failed for input: " << xml;

    const XMLElement* root = doc.FirstChildElement("root");
    EXPECT_NE(root, nullptr);

    const XMLAttribute* attr = root->FindAttribute("a");
    EXPECT_NE(attr, nullptr);
    return attr;
  }

  // Converts an integer to string without locale surprises.
  template <typename T>
  static std::string ToString(T v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
  }
};

}  // namespace

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForPositiveNumber_71) {
  const XMLAttribute* attr = ParseAndGetAttrA("42");

  int queried = 12345;  // intentionally non-zero to observe any overwrite behavior
  (void)attr->QueryIntValue(&queried);

  EXPECT_EQ(attr->IntValue(), queried);
}

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForNegativeNumber_71) {
  const XMLAttribute* attr = ParseAndGetAttrA("-7");

  int queried = 12345;
  (void)attr->QueryIntValue(&queried);

  EXPECT_EQ(attr->IntValue(), queried);
}

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForIntMax_71) {
  const int kMax = (std::numeric_limits<int>::max)();
  const XMLAttribute* attr = ParseAndGetAttrA(ToString(kMax));

  int queried = 0;
  (void)attr->QueryIntValue(&queried);

  EXPECT_EQ(attr->IntValue(), queried);
}

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForIntMin_71) {
  const int kMin = (std::numeric_limits<int>::min)();
  const XMLAttribute* attr = ParseAndGetAttrA(ToString(kMin));

  int queried = 0;
  (void)attr->QueryIntValue(&queried);

  EXPECT_EQ(attr->IntValue(), queried);
}

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForNonNumericString_71) {
  const XMLAttribute* attr = ParseAndGetAttrA("abc");

  int queried = 999;
  (void)attr->QueryIntValue(&queried);

  // IntValue is defined in terms of QueryIntValue(&i) and returning i.
  EXPECT_EQ(attr->IntValue(), queried);
}

TEST_F(XMLAttributeIntValueTest_71, MatchesQueryIntValueForMixedNumericString_71) {
  const XMLAttribute* attr = ParseAndGetAttrA("12abc");

  int queried = 999;
  (void)attr->QueryIntValue(&queried);

  EXPECT_EQ(attr->IntValue(), queried);
}
