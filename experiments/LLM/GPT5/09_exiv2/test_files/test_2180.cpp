// -----------------------------------------------------------------------------
// Test file for: ./TestProjects/exiv2/src/xmp.cpp
// Focus: Exiv2::Xmpdatum::Impl copy behavior (deep-copy of key_ and value_)
// TEST_ID: 2180
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/xmp.hpp>

#include <memory>
#include <string>

namespace {

class XmpdatumImplCopyTest_2180 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr MakeTextValue(const std::string& s) {
    // Prefer XMP text value type if available in Exiv2 builds.
    // This relies only on public interfaces (Value::create + Value::read).
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::xmpText);
    // If read fails, the observable behavior would be reflected by toString/ok(),
    // but we keep the test simple and just populate the value.
    (void)v->read(s);
    return v;
  }

  static Exiv2::Xmpdatum MakeDatum(const std::string& xmpKey, const std::string& valueStr) {
    Exiv2::XmpKey key(xmpKey);
    auto v = MakeTextValue(valueStr);
    // Xmpdatum ctor takes a Value* (may clone internally). We treat it as a black box.
    return Exiv2::Xmpdatum(key, v.get());
  }
};

TEST_F(XmpdatumImplCopyTest_2180, CopyConstructorPreservesKeyAndValue_2180) {
  const std::string k = "Xmp.dc.title";
  Exiv2::Xmpdatum original = MakeDatum(k, "hello");

  Exiv2::Xmpdatum copy(original);

  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.toString(), original.toString());
}

TEST_F(XmpdatumImplCopyTest_2180, CopySurvivesAfterOriginalDestroyed_2180) {
  Exiv2::Xmpdatum copy = MakeDatum("Xmp.dc.title", "placeholder");

  {
    Exiv2::Xmpdatum original = MakeDatum("Xmp.dc.title", "keep me");
    copy = original;  // exercise operator= which uses Impl::operator=
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.toString(), original.toString());
  }  // original destroyed here

  // If Impl performed a shallow copy of key_/value_, accessing copy could crash or change.
  EXPECT_EQ(copy.key(), "Xmp.dc.title");
  EXPECT_EQ(copy.toString(), "keep me");
}

TEST_F(XmpdatumImplCopyTest_2180, CopyIsIndependentFromOriginalValueChanges_2180) {
  Exiv2::Xmpdatum original = MakeDatum("Xmp.dc.description", "first");
  Exiv2::Xmpdatum copy(original);

  // Mutate only the original through its public interface.
  // (We do not assume internal behavior; we only observe external effects.)
  ASSERT_NO_THROW(original.setValue("second"));

  EXPECT_EQ(original.toString(), "second");
  // Deep-copy behavior: the copy should retain its own cloned value.
  EXPECT_EQ(copy.toString(), "first");
}

TEST_F(XmpdatumImplCopyTest_2180, AssignmentOverwritesExistingAndDeepCopies_2180) {
  Exiv2::Xmpdatum a = MakeDatum("Xmp.dc.subject", "A");
  Exiv2::Xmpdatum b = MakeDatum("Xmp.dc.subject", "B");

  b = a;

  EXPECT_EQ(b.key(), a.key());
  EXPECT_EQ(b.toString(), a.toString());

  // Change a after assignment; b should remain unchanged if deep-copied.
  ASSERT_NO_THROW(a.setValue("A2"));
  EXPECT_EQ(a.toString(), "A2");
  EXPECT_EQ(b.toString(), "A");
}

TEST_F(XmpdatumImplCopyTest_2180, SelfAssignmentDoesNotBreakObservables_2180) {
  Exiv2::Xmpdatum d = MakeDatum("Xmp.dc.creator", "me");

  const std::string beforeKey = d.key();
  const std::string beforeVal = d.toString();

  d = d;  // self-assignment

  EXPECT_EQ(d.key(), beforeKey);
  EXPECT_EQ(d.toString(), beforeVal);
}

}  // namespace