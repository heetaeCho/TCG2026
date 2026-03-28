// TEST_ID 679
#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>

namespace {

class IptcdatumTest_679 : public ::testing::Test {
 protected:
  static Exiv2::IptcKey MakeKey() {
    // Use a well-known IPTC key string from Exiv2's public API surface.
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumTest_679, ToStringReturnsEmptyWhenConstructedWithNullValue_679) {
  const Exiv2::IptcKey key = MakeKey();

  // Observable behavior from provided implementation snippet:
  // toString() returns "" if no value is set.
  Exiv2::Iptcdatum d(key, /*pValue=*/nullptr);

  EXPECT_EQ(d.toString(), "");
}

TEST_F(IptcdatumTest_679, ToStringReturnsEmptyAfterCopyWhenSourceHasNullValue_679) {
  const Exiv2::IptcKey key = MakeKey();

  Exiv2::Iptcdatum src(key, /*pValue=*/nullptr);
  Exiv2::Iptcdatum copy(src);

  EXPECT_EQ(src.toString(), "");
  EXPECT_EQ(copy.toString(), "");
}

TEST_F(IptcdatumTest_679, ToStringReflectsStringAssignmentNonEmpty_679) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum d(key, /*pValue=*/nullptr);

  d = std::string("hello");

  // We only assert observable public behavior: after assigning a string,
  // toString() should reflect it.
  EXPECT_EQ(d.toString(), "hello");
}

TEST_F(IptcdatumTest_679, ToStringReflectsStringAssignmentEmptyBoundary_679) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum d(key, /*pValue=*/nullptr);

  d = std::string("");

  // Boundary: explicitly setting an empty string should yield an empty string.
  EXPECT_EQ(d.toString(), "");
}

TEST_F(IptcdatumTest_679, ToStringIsStableAcrossAssignmentOperatorFromOtherDatum_679) {
  const Exiv2::IptcKey key = MakeKey();

  Exiv2::Iptcdatum a(key, /*pValue=*/nullptr);
  Exiv2::Iptcdatum b(key, /*pValue=*/nullptr);

  a = std::string("alpha");
  b = a;  // copy-assignment

  EXPECT_EQ(a.toString(), "alpha");
  EXPECT_EQ(b.toString(), "alpha");
}

TEST_F(IptcdatumTest_679, ToStringAfterUint16AssignmentIsNonEmptyAndCallable_679) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum d(key, /*pValue=*/nullptr);

  d = static_cast<uint16_t>(0);

  // We avoid assuming formatting details; we only require that the public API
  // produces a usable string representation (and does not stay null-empty).
  EXPECT_FALSE(d.toString().empty());
}

}  // namespace