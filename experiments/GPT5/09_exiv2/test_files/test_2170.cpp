// TEST_ID 2170
// File: test_langaltvalue_2170.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::LangAltValue;
using Exiv2::byte;
using Exiv2::ByteOrder;

class LangAltValueTest_2170 : public ::testing::Test {
protected:
  static void ExpectEquivalent(const LangAltValue& a, const LangAltValue& b) {
    // Compare only observable behavior via public interface.
    EXPECT_EQ(a.count(), b.count());

    // toString(size_t) ignores index in signature comments, but we still call it consistently.
    EXPECT_EQ(a.toString(0), b.toString(0));

    // Qualifier-based access: compare for a few representative qualifiers.
    EXPECT_EQ(a.toString(std::string()), b.toString(std::string()));
    EXPECT_EQ(a.toString("xml:lang"), b.toString("xml:lang"));
    EXPECT_EQ(a.toString("x-default"), b.toString("x-default"));

    // Numeric conversions: compare; do not assert any particular numeric value.
    EXPECT_EQ(a.toInt64(0), b.toInt64(0));
    EXPECT_EQ(a.toUint32(0), b.toUint32(0));
    EXPECT_FLOAT_EQ(a.toFloat(0), b.toFloat(0));
    EXPECT_EQ(a.toRational(0), b.toRational(0));

    // Stream serialization: compare output text.
    std::ostringstream osa;
    std::ostringstream osb;
    a.write(osa);
    b.write(osb);
    EXPECT_EQ(osa.str(), osb.str());

    // Base-class observable state: size/copy should match for equivalent content.
    const size_t sa = a.size();
    const size_t sb = b.size();
    EXPECT_EQ(sa, sb);

    if (sa == 0) {
      std::vector<byte> bufA;
      std::vector<byte> bufB;
      EXPECT_EQ(a.copy(nullptr, ByteOrder::invalidByteOrder), b.copy(nullptr, ByteOrder::invalidByteOrder));
    } else {
      std::vector<byte> bufA(sa);
      std::vector<byte> bufB(sb);

      const size_t ca = a.copy(bufA.data(), ByteOrder::invalidByteOrder);
      const size_t cb = b.copy(bufB.data(), ByteOrder::invalidByteOrder);
      EXPECT_EQ(ca, cb);
      EXPECT_EQ(bufA, bufB);
    }

    // XMP meta accessors (if these are available per header): must match too.
    EXPECT_EQ(a.xmpArrayType(), b.xmpArrayType());
    EXPECT_EQ(a.xmpStruct(), b.xmpStruct());
  }

  static LangAltValue MakeViaCtor(const std::string& buf) {
    return LangAltValue(buf);
  }

  static LangAltValue MakeViaDefaultThenRead(const std::string& buf, int* readRc = nullptr) {
    LangAltValue v;
    const int rc = v.read(buf);
    if (readRc) *readRc = rc;
    return v;
  }
};

TEST_F(LangAltValueTest_2170, DefaultCtor_IsUsableAndCloneRoundTrips_2170) {
  LangAltValue v;

  // Clone should be non-null and behaviorally equivalent to the original.
  LangAltValue::UniquePtr c = v.clone();
  ASSERT_TRUE(c.get() != nullptr);

  // Compare observable behavior.
  ExpectEquivalent(v, *c);
}

TEST_F(LangAltValueTest_2170, StringCtor_MatchesDefaultThenRead_ForEmptyString_2170) {
  const std::string input;

  LangAltValue viaCtor = MakeViaCtor(input);
  int rcRead = 0;
  LangAltValue viaRead = MakeViaDefaultThenRead(input, &rcRead);

  // Ensure both construction paths yield the same observable behavior.
  ExpectEquivalent(viaCtor, viaRead);
}

TEST_F(LangAltValueTest_2170, StringCtor_MatchesDefaultThenRead_ForSimpleAscii_2170) {
  const std::string input = "hello world";

  LangAltValue viaCtor = MakeViaCtor(input);
  LangAltValue viaRead = MakeViaDefaultThenRead(input);

  ExpectEquivalent(viaCtor, viaRead);
}

TEST_F(LangAltValueTest_2170, StringCtor_MatchesDefaultThenRead_ForUtf8Text_2170) {
  const std::string input = u8"한국어 테스트 — café — 🚀";

  LangAltValue viaCtor = MakeViaCtor(input);
  LangAltValue viaRead = MakeViaDefaultThenRead(input);

  ExpectEquivalent(viaCtor, viaRead);
}

TEST_F(LangAltValueTest_2170, StringCtor_MatchesDefaultThenRead_ForXmlLikePayload_2170) {
  // This resembles typical XMP text forms, but we do not assume parsing rules.
  const std::string input =
      "<rdf:Alt>"
      "<rdf:li xml:lang=\"x-default\">Title</rdf:li>"
      "<rdf:li xml:lang=\"en-US\">Title EN</rdf:li>"
      "</rdf:Alt>";

  LangAltValue viaCtor = MakeViaCtor(input);
  int rcRead = 0;
  LangAltValue viaRead = MakeViaDefaultThenRead(input, &rcRead);

  ExpectEquivalent(viaCtor, viaRead);
}

TEST_F(LangAltValueTest_2170, Read_CanBeCalledMultipleTimes_AndMatchesCtorAfterSecondRead_2170) {
  const std::string first = "first";
  const std::string second = "second";

  LangAltValue v;
  const int rc1 = v.read(first);
  (void)rc1;  // only observable via subsequent public behavior, which we check below
  const int rc2 = v.read(second);
  (void)rc2;

  LangAltValue viaCtorSecond(second);

  // After reading "second", object should match an object constructed from "second".
  ExpectEquivalent(v, viaCtorSecond);
}

TEST_F(LangAltValueTest_2170, Clone_PreservesBehavior_AfterRead_2170) {
  const std::string input =
      "<rdf:Alt><rdf:li xml:lang=\"x-default\">X</rdf:li></rdf:Alt>";

  LangAltValue v(input);

  LangAltValue::UniquePtr c = v.clone();
  ASSERT_TRUE(c.get() != nullptr);

  ExpectEquivalent(v, *c);
}

TEST_F(LangAltValueTest_2170, Boundary_LargeInput_MatchesCtorVsRead_2170) {
  // Large but reasonable for a unit test: repeated pattern.
  std::string input;
  input.reserve(64 * 1024);
  for (int i = 0; i < 8192; ++i) {
    input += "abcd";
  }

  LangAltValue viaCtor(input);
  LangAltValue viaRead = MakeViaDefaultThenRead(input);

  ExpectEquivalent(viaCtor, viaRead);
}

TEST_F(LangAltValueTest_2170, ErrorHandling_ReadReturnCode_ConsistentBetweenPaths_2170) {
  // Provide a "likely malformed" payload. We don't assume it's invalid, only that
  // whatever the library decides, ctor-vs-read should be consistent in resulting behavior.
  const std::string input = "<rdf:Alt><rdf:li xml:lang=\"x-default\">missing close";

  int rcRead = 0;
  LangAltValue viaRead = MakeViaDefaultThenRead(input, &rcRead);
  LangAltValue viaCtor(input);

  // We can observe rcRead directly (ctor return code isn't exposed), but we can still
  // require behavioral equivalence.
  (void)rcRead;
  ExpectEquivalent(viaCtor, viaRead);
}

}  // namespace