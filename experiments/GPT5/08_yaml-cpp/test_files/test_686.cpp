// TEST_ID: 686
//
// Unit tests for YAML::Node templated constructor (Node(const T& rhs)).
//
// Notes:
// - We treat YAML::Node as a black box and only validate observable behavior via the public API.
// - These tests focus on construction from common scalar types and observable conversion behavior.

#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "yaml-cpp/node/node.h"

namespace {

TEST(NodeCtorTemplateTest_686, ConstructsFromInt_IsDefinedAndConvertsBack_686) {
  const int value = 42;
  YAML::Node n(value);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(static_cast<bool>(n));
  EXPECT_FALSE(!n);

  EXPECT_TRUE(n.IsScalar()) << "Scalar construction should produce a scalar node (observable expectation).";
  EXPECT_EQ(n.as<int>(), value);
}

TEST(NodeCtorTemplateTest_686, ConstructsFromNegativeInt_ConvertsBack_686) {
  const int value = -123;
  YAML::Node n(value);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<int>(), value);
}

TEST(NodeCtorTemplateTest_686, ConstructsFromIntBoundary_MinMax_686) {
  {
    const int v = std::numeric_limits<int>::min();
    YAML::Node n(v);
    EXPECT_TRUE(n.IsDefined());
    EXPECT_TRUE(n.IsScalar());
    EXPECT_EQ(n.as<int>(), v);
  }
  {
    const int v = std::numeric_limits<int>::max();
    YAML::Node n(v);
    EXPECT_TRUE(n.IsDefined());
    EXPECT_TRUE(n.IsScalar());
    EXPECT_EQ(n.as<int>(), v);
  }
}

TEST(NodeCtorTemplateTest_686, ConstructsFromBool_ConvertsBack_686) {
  YAML::Node t(true);
  YAML::Node f(false);

  EXPECT_TRUE(t.IsDefined());
  EXPECT_TRUE(f.IsDefined());

  EXPECT_TRUE(t.IsScalar());
  EXPECT_TRUE(f.IsScalar());

  EXPECT_EQ(t.as<bool>(), true);
  EXPECT_EQ(f.as<bool>(), false);
}

TEST(NodeCtorTemplateTest_686, ConstructsFromDouble_ConvertsBack_686) {
  const double value = 3.141592653589793;
  YAML::Node n(value);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_DOUBLE_EQ(n.as<double>(), value);
}

TEST(NodeCtorTemplateTest_686, ConstructsFromStdString_EmptyAndNonEmpty_686) {
  {
    const std::string s;
    YAML::Node n(s);

    EXPECT_TRUE(n.IsDefined());
    EXPECT_TRUE(n.IsScalar());
    EXPECT_EQ(n.as<std::string>(), s);
    EXPECT_EQ(n.Scalar(), s);
  }
  {
    const std::string s = "hello";
    YAML::Node n(s);

    EXPECT_TRUE(n.IsDefined());
    EXPECT_TRUE(n.IsScalar());
    EXPECT_EQ(n.as<std::string>(), s);
    EXPECT_EQ(n.Scalar(), s);
  }
}

TEST(NodeCtorTemplateTest_686, ConstructsFromConstCharPtr_ConvertsToString_686) {
  const char* cstr = "world";
  YAML::Node n(cstr);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string("world"));
  EXPECT_EQ(n.Scalar(), std::string("world"));
}

TEST(NodeCtorTemplateTest_686, ConstructsFromCharArrayLiteral_ConvertsToString_686) {
  YAML::Node n("literal");

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), std::string("literal"));
}

TEST(NodeCtorTemplateTest_686, ConstructedNode_AllowsSettingTagAndStyle_686) {
  YAML::Node n(7);

  EXPECT_TRUE(n.IsDefined());

  // Tag/style setters are observable through corresponding getters.
  n.SetTag("!custom");
  EXPECT_EQ(n.Tag(), std::string("!custom"));

  // We don't assume a default style; only that SetStyle is reflected by Style().
  n.SetStyle(YAML::EmitterStyle::Flow);
  EXPECT_EQ(n.Style(), YAML::EmitterStyle::Flow);
}

TEST(NodeCtorTemplateTest_686, ConstructedNode_CanBeCopiedAndStillConvertible_686) {
  YAML::Node original(std::string("copy-me"));
  YAML::Node copy(original);

  EXPECT_TRUE(copy.IsDefined());
  EXPECT_TRUE(copy.IsScalar());
  EXPECT_EQ(copy.as<std::string>(), "copy-me");

  // is() is an observable API; we don't assume pointer identity semantics,
  // but we can at least verify it doesn't crash and is stable for self-compare.
  EXPECT_TRUE(original.is(original));
  EXPECT_TRUE(copy.is(copy));
}

TEST(NodeCtorTemplateTest_686, ConstructedNode_AssignmentFromScalarUpdatesObservableValue_686) {
  YAML::Node n(1);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_EQ(n.as<int>(), 1);

  n = 99;
  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<int>(), 99);

  n = std::string("now-string");
  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_EQ(n.as<std::string>(), "now-string");
}

TEST(NodeCtorTemplateTest_686, ConversionError_AsIntFromNonNumericScalarThrows_686) {
  YAML::Node n(std::string("not-a-number"));

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());

  // yaml-cpp exposes conversion failure via YAML::BadConversion.
  EXPECT_THROW((void)n.as<int>(), YAML::BadConversion);
}

TEST(NodeCtorTemplateTest_686, FallbackAs_ReturnsFallbackOnBadConversion_686) {
  YAML::Node n(std::string("NaN"));

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());

  // as<T>(fallback) is an observable alternative to exceptions.
  EXPECT_EQ(n.as<int>(12345), 12345);
  EXPECT_EQ(n.as<std::string>("fallback"), std::string("NaN"))  // should succeed, so no fallback used
      << "String conversion should succeed for scalar strings.";
}

TEST(NodeCtorTemplateTest_686, ConstructedNode_IsNotSequenceOrMapByDefaultForScalarInputs_686) {
  YAML::Node n(10);

  EXPECT_TRUE(n.IsDefined());
  EXPECT_TRUE(n.IsScalar());
  EXPECT_FALSE(n.IsSequence());
  EXPECT_FALSE(n.IsMap());

  // size() should be safe to call; we avoid asserting an exact value across node kinds,
  // but for a scalar node, size() is commonly 0. If the implementation differs, this
  // expectation may need adjustment in the codebase.
  EXPECT_EQ(n.size(), 0u);
}

}  // namespace