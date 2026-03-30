// File: test_iptcdatum_operator_value_assign_689.cpp
// TEST_ID: 689

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

namespace {

using ::testing::Eq;

class IptcdatumAssignmentTest_689 : public ::testing::Test {
 protected:
  // Commonly-valid IPTC key used across Exiv2 examples/docs.
  static Exiv2::IptcKey MakeKey() { return Exiv2::IptcKey("Iptc.Application2.Caption"); }
};

// We mock only the external interaction: the virtual call to setValue(const Value*).
class MockIptcdatum_689 : public Exiv2::Iptcdatum {
 public:
  using Exiv2::Iptcdatum::Iptcdatum;
  MOCK_METHOD(void, setValue, (const Exiv2::Value* pValue), (override));
};

TEST_F(IptcdatumAssignmentTest_689, AssignValueCallsSetValueWithAddress_689) {
  const Exiv2::IptcKey key = MakeKey();

  // Provide any non-null initial value pointer to satisfy the constructor contract.
  auto init = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(init.get(), nullptr);

  MockIptcdatum_689 datum(key, init.get());

  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  (void)v->read(std::string("hello"));

  EXPECT_CALL(datum, setValue(Eq(v.get()))).Times(1);

  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& ret = (datum = *v);
    EXPECT_EQ(&ret, static_cast<Exiv2::Iptcdatum*>(&datum));
  });
}

TEST_F(IptcdatumAssignmentTest_689, AssignValueSupportsChainingAndInvokesSetValueTwice_689) {
  const Exiv2::IptcKey key = MakeKey();

  auto init = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(init.get(), nullptr);

  MockIptcdatum_689 datum(key, init.get());

  auto v1 = Exiv2::Value::create(Exiv2::asciiString);
  auto v2 = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v1.get(), nullptr);
  ASSERT_NE(v2.get(), nullptr);

  (void)v1->read(std::string("first"));
  (void)v2->read(std::string("second"));

  {
    ::testing::InSequence seq;
    EXPECT_CALL(datum, setValue(Eq(v1.get()))).Times(1);
    EXPECT_CALL(datum, setValue(Eq(v2.get()))).Times(1);
  }

  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& ret = ((datum = *v1) = *v2);
    EXPECT_EQ(&ret, static_cast<Exiv2::Iptcdatum*>(&datum));
  });
}

TEST_F(IptcdatumAssignmentTest_689, AssignValueWithEmptyStringValueStillCallsSetValue_689) {
  const Exiv2::IptcKey key = MakeKey();

  auto init = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(init.get(), nullptr);

  MockIptcdatum_689 datum(key, init.get());

  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(v.get(), nullptr);
  (void)v->read(std::string(""));  // Boundary-ish input (empty payload)

  EXPECT_CALL(datum, setValue(Eq(v.get()))).Times(1);

  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& ret = (datum = *v);
    EXPECT_EQ(&ret, static_cast<Exiv2::Iptcdatum*>(&datum));
  });
}

TEST_F(IptcdatumAssignmentTest_689, AssignValueWithDifferentTypeStillCallsSetValue_689) {
  const Exiv2::IptcKey key = MakeKey();

  auto init = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(init.get(), nullptr);

  MockIptcdatum_689 datum(key, init.get());

  // Boundary/variation: use a different Value type to ensure operator= forwards the address as-is.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_NE(v.get(), nullptr);

  // If read fails for any reason, that's fine: the operator= contract we can observe is the call to setValue(&value).
  // We avoid asserting on read() return to keep the test black-box.
  (void)v->read(std::string("1"));

  EXPECT_CALL(datum, setValue(Eq(v.get()))).Times(1);

  EXPECT_NO_THROW({
    Exiv2::Iptcdatum& ret = (datum = *v);
    EXPECT_EQ(&ret, static_cast<Exiv2::Iptcdatum*>(&datum));
  });
}

}  // namespace