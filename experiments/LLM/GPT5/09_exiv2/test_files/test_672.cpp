// File: test_iptcdatum_tagdesc_672.cpp
// TEST_ID: 672

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>

#include <cstdint>
#include <string>

namespace {

// A test double for IptcKey that lets us verify Iptcdatum::tagDesc() forwards to the key,
// and that cloning preserves the dynamic type behavior.
//
// Note: Iptcdatum stores a clone of the provided key (key.clone()).
class TestIptcKey_672 : public Exiv2::IptcKey {
 public:
  explicit TestIptcKey_672(std::string custom_desc)
      : Exiv2::IptcKey(std::string("Iptc.Application2.ObjectName")), custom_desc_(std::move(custom_desc)) {}

  // Override tagDesc() so we can observe forwarding through Iptcdatum::tagDesc().
  std::string tagDesc() const override { return custom_desc_; }

 private:
  // IptcKey implements clone() via an internal virtual clone_(). We override clone_() to ensure
  // cloning keeps this derived type (so tagDesc() remains our overridden behavior).
  Exiv2::IptcKey* clone_() const override { return new TestIptcKey_672(*this); }

  std::string custom_desc_;
};

class IptcdatumTest_672 : public ::testing::Test {
 protected:
  // Most tests only need to create a datum; passing nullptr for Value is allowed by the interface.
  static Exiv2::Iptcdatum MakeDatum(const Exiv2::IptcKey& key) {
    return Exiv2::Iptcdatum(key, /*pValue=*/nullptr);
  }
};

}  // namespace

TEST_F(IptcdatumTest_672, TagDescMatchesKeyTagDesc_ForKeyStringCtor_672) {
  // Construct key using string-based constructor.
  Exiv2::IptcKey key(std::string("Iptc.Application2.ObjectName"));

  Exiv2::Iptcdatum datum = MakeDatum(key);

  // Observable behavior: Iptcdatum::tagDesc() should match the key's tagDesc().
  EXPECT_EQ(datum.tagDesc(), key.tagDesc());
}

TEST_F(IptcdatumTest_672, TagDescMatchesKeyTagDesc_ForTagRecordCtor_672) {
  // Construct key using (tag, record) constructor.
  // Values chosen are arbitrary but valid uint16_t domain values.
  const uint16_t tag = 5;
  const uint16_t record = 2;
  Exiv2::IptcKey key(tag, record);

  Exiv2::Iptcdatum datum = MakeDatum(key);

  EXPECT_EQ(datum.tagDesc(), key.tagDesc());
}

TEST_F(IptcdatumTest_672, TagDescPreservedAfterCopyConstruction_672) {
  Exiv2::IptcKey key(std::string("Iptc.Application2.ObjectName"));
  Exiv2::Iptcdatum original = MakeDatum(key);

  Exiv2::Iptcdatum copied(original);

  EXPECT_EQ(copied.tagDesc(), original.tagDesc());
  EXPECT_EQ(copied.tagDesc(), key.tagDesc());
}

TEST_F(IptcdatumTest_672, TagDescPreservedAfterCopyAssignment_672) {
  Exiv2::IptcKey keyA(std::string("Iptc.Application2.ObjectName"));
  Exiv2::IptcKey keyB(std::string("Iptc.Application2.Headline"));

  Exiv2::Iptcdatum a = MakeDatum(keyA);
  Exiv2::Iptcdatum b = MakeDatum(keyB);

  const std::string b_desc_before = b.tagDesc();
  ASSERT_EQ(b_desc_before, keyB.tagDesc());

  b = a;

  // After assignment, observable behavior should match the assigned-from object.
  EXPECT_EQ(b.tagDesc(), a.tagDesc());
  EXPECT_EQ(b.tagDesc(), keyA.tagDesc());
}

TEST_F(IptcdatumTest_672, TagDescReflectsDifferentKeys_672) {
  // Boundary-ish: use two different construction paths and simply ensure behavior tracks the key used.
  Exiv2::IptcKey key_from_string(std::string("Iptc.Application2.ObjectName"));
  Exiv2::IptcKey key_from_numbers(static_cast<uint16_t>(5), static_cast<uint16_t>(2));

  Exiv2::Iptcdatum d1 = MakeDatum(key_from_string);
  Exiv2::Iptcdatum d2 = MakeDatum(key_from_numbers);

  EXPECT_EQ(d1.tagDesc(), key_from_string.tagDesc());
  EXPECT_EQ(d2.tagDesc(), key_from_numbers.tagDesc());

  // If the underlying library defines different descriptions, these may differ.
  // We don't require inequality (dataset mappings could be identical or empty); we only require correctness
  // relative to each key.
}

TEST_F(IptcdatumTest_672, TagDescUsesClonedDynamicType_672) {
  // Verify "external interaction": Iptcdatum stores a clone of the passed key, and tagDesc()
  // should reflect the dynamic type's overridden behavior.
  TestIptcKey_672 test_key("my custom description");

  Exiv2::Iptcdatum datum = MakeDatum(test_key);

  EXPECT_EQ(datum.tagDesc(), "my custom description");
  // Also matches the key's own tagDesc(), confirming forwarding consistency.
  EXPECT_EQ(datum.tagDesc(), test_key.tagDesc());
}