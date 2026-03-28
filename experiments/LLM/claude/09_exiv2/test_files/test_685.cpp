#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/error.hpp>
#include <exiv2/value.hpp>
#include <sstream>

using namespace Exiv2;

class IptcdatumTest_685 : public ::testing::Test {
protected:
  void SetUp() override {
  }
};

// Test that constructing an Iptcdatum with a valid key works
TEST_F(IptcdatumTest_685, ConstructWithValidKey_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ("Iptc.Application2.Caption", datum.key());
}

// Test that value() throws when no value is set
TEST_F(IptcdatumTest_685, ValueThrowsWhenNotSet_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_THROW(datum.value(), Error);
}

// Test that value() throws with ErrorCode::kerValueNotSet when no value is set
TEST_F(IptcdatumTest_685, ValueThrowsKerValueNotSet_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  try {
    datum.value();
    FAIL() << "Expected Error to be thrown";
  } catch (const Error& e) {
    EXPECT_EQ(ErrorCode::kerValueNotSet, e.code());
  }
}

// Test that getValue returns nullptr when no value is set
TEST_F(IptcdatumTest_685, GetValueReturnsNullWhenNotSet_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  auto val = datum.getValue();
  EXPECT_EQ(nullptr, val);
}

// Test that setValue with a string works and value can be retrieved
TEST_F(IptcdatumTest_685, SetValueString_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Hello World");
  EXPECT_NO_THROW(datum.value());
  EXPECT_EQ("Hello World", datum.toString());
}

// Test operator= with string
TEST_F(IptcdatumTest_685, AssignString_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum = std::string("Test Caption");
  EXPECT_NO_THROW(datum.value());
  EXPECT_EQ("Test Caption", datum.toString());
}

// Test operator= with uint16_t
TEST_F(IptcdatumTest_685, AssignUint16_685) {
  IptcKey key("Iptc.Application2.Urgency");
  Iptcdatum datum(key, nullptr);
  uint16_t val = 42;
  datum = val;
  EXPECT_NO_THROW(datum.value());
}

// Test copy constructor
TEST_F(IptcdatumTest_685, CopyConstructor_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Copy Test");
  Iptcdatum copy(datum);
  EXPECT_EQ(datum.key(), copy.key());
  EXPECT_EQ(datum.toString(), copy.toString());
}

// Test copy assignment operator
TEST_F(IptcdatumTest_685, CopyAssignment_685) {
  IptcKey key1("Iptc.Application2.Caption");
  IptcKey key2("Iptc.Application2.Headline");
  Iptcdatum datum1(key1, nullptr);
  datum1.setValue("Original");
  Iptcdatum datum2(key2, nullptr);
  datum2 = datum1;
  EXPECT_EQ(datum1.key(), datum2.key());
  EXPECT_EQ("Original", datum2.toString());
}

// Test familyName returns "Iptc"
TEST_F(IptcdatumTest_685, FamilyNameIsIptc_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_STREQ("Iptc", datum.familyName());
}

// Test groupName
TEST_F(IptcdatumTest_685, GroupName_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ("Application2", datum.groupName());
}

// Test recordName
TEST_F(IptcdatumTest_685, RecordName_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ("Application2", datum.recordName());
}

// Test tagName
TEST_F(IptcdatumTest_685, TagName_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ("Caption", datum.tagName());
}

// Test tag returns the expected tag number
TEST_F(IptcdatumTest_685, TagNumber_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  // Caption tag is 120 in IPTC Application2
  EXPECT_EQ(120, datum.tag());
}

// Test record returns expected record number
TEST_F(IptcdatumTest_685, RecordNumber_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  // Application2 record is 2
  EXPECT_EQ(2, datum.record());
}

// Test size when no value is set
TEST_F(IptcdatumTest_685, SizeWhenNoValue_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ(0u, datum.size());
}

// Test count when no value is set
TEST_F(IptcdatumTest_685, CountWhenNoValue_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ(0u, datum.count());
}

// Test count and size after setting a value
TEST_F(IptcdatumTest_685, CountAndSizeAfterSetValue_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Hello");
  EXPECT_GT(datum.size(), 0u);
  EXPECT_GT(datum.count(), 0u);
}

// Test setValue with Value pointer (nullptr resets value)
TEST_F(IptcdatumTest_685, SetValuePtrNull_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Some text");
  EXPECT_NO_THROW(datum.value());
  datum.setValue(static_cast<const Value*>(nullptr));
  EXPECT_THROW(datum.value(), Error);
}

// Test setValue with a Value object
TEST_F(IptcdatumTest_685, SetValueWithValueObject_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  StringValue sv("Test Value");
  datum = sv;
  EXPECT_EQ("Test Value", datum.toString());
}

// Test operator= with Value reference
TEST_F(IptcdatumTest_685, AssignValueRef_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  StringValue sv("Assigned Value");
  datum = static_cast<const Value&>(sv);
  EXPECT_EQ("Assigned Value", datum.toString());
}

// Test write to ostream
TEST_F(IptcdatumTest_685, WriteToStream_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Stream test");
  std::ostringstream oss;
  datum.write(oss, nullptr);
  EXPECT_FALSE(oss.str().empty());
}

// Test toString with index 0
TEST_F(IptcdatumTest_685, ToStringWithIndex_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("Indexed string");
  EXPECT_EQ("Indexed string", datum.toString(0));
}

// Test constructing with Envelope record
TEST_F(IptcdatumTest_685, EnvelopeRecord_685) {
  IptcKey key("Iptc.Envelope.CharacterSet");
  Iptcdatum datum(key, nullptr);
  EXPECT_EQ("Iptc.Envelope.CharacterSet", datum.key());
  EXPECT_EQ("Envelope", datum.groupName());
  EXPECT_EQ(1, datum.record());
}

// Test typeId when no value set
TEST_F(IptcdatumTest_685, TypeIdWhenNoValue_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  // When no value is set, typeId should return some default
  TypeId tid = datum.typeId();
  // Just verify it doesn't crash and returns a valid TypeId
  (void)tid;
}

// Test toInt64 after setting numeric value
TEST_F(IptcdatumTest_685, ToInt64_685) {
  IptcKey key("Iptc.Application2.Urgency");
  Iptcdatum datum(key, nullptr);
  datum.setValue("5");
  EXPECT_NO_THROW(datum.toInt64(0));
}

// Test toFloat after setting value
TEST_F(IptcdatumTest_685, ToFloat_685) {
  IptcKey key("Iptc.Application2.Urgency");
  Iptcdatum datum(key, nullptr);
  datum.setValue("5");
  EXPECT_NO_THROW(datum.toFloat(0));
}

// Test toRational after setting value
TEST_F(IptcdatumTest_685, ToRational_685) {
  IptcKey key("Iptc.Application2.Urgency");
  Iptcdatum datum(key, nullptr);
  datum.setValue("5");
  EXPECT_NO_THROW(datum.toRational(0));
}

// Test tagLabel returns a non-empty string for known tags
TEST_F(IptcdatumTest_685, TagLabel_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  std::string label = datum.tagLabel();
  // Known tag should have a label
  EXPECT_FALSE(label.empty());
}

// Test constructing datum with a Value pointer
TEST_F(IptcdatumTest_685, ConstructWithValuePtr_685) {
  IptcKey key("Iptc.Application2.Caption");
  StringValue sv("Initial Value");
  Iptcdatum datum(key, &sv);
  EXPECT_NO_THROW(datum.value());
  EXPECT_EQ("Initial Value", datum.toString());
}

// Test that empty string can be set
TEST_F(IptcdatumTest_685, SetEmptyString_685) {
  IptcKey key("Iptc.Application2.Caption");
  Iptcdatum datum(key, nullptr);
  datum.setValue("");
  EXPECT_NO_THROW(datum.value());
  EXPECT_EQ("", datum.toString());
}
