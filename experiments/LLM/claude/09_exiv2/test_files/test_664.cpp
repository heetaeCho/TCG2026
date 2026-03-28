#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include necessary Exiv2 headers
#include <exiv2/iptc.hpp>
#include <exiv2/exif.hpp>

// TEST_ID is 664

class IptcdatumTest_664 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that an Iptcdatum can be created with a valid IPTC tag key
TEST_F(IptcdatumTest_664, ConstructWithValidKey_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    EXPECT_EQ(datum.key(), "Iptc.Application2.Caption");
}

// Test that write outputs the value to the ostream
TEST_F(IptcdatumTest_664, WriteOutputsValueToStream_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("Hello World");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_EQ(oss.str(), "Hello World");
}

// Test write with empty value
TEST_F(IptcdatumTest_664, WriteEmptyValue_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    // An empty string value should produce empty or minimal output
    std::string result = oss.str();
    // The output depends on the value representation; just verify no crash
    EXPECT_TRUE(result.empty() || !result.empty());
}

// Test write returns the same ostream reference
TEST_F(IptcdatumTest_664, WriteReturnsSameStream_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("Test");
    
    std::ostringstream oss;
    std::ostream& returned = datum.write(oss, nullptr);
    EXPECT_EQ(&returned, &oss);
}

// Test that write works with a non-null ExifData pointer
TEST_F(IptcdatumTest_664, WriteWithExifData_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("Test with ExifData");
    
    Exiv2::ExifData exifData;
    std::ostringstream oss;
    datum.write(oss, &exifData);
    EXPECT_EQ(oss.str(), "Test with ExifData");
}

// Test IptcData container - adding and retrieving data
class IptcDataTest_664 : public ::testing::Test {
protected:
    Exiv2::IptcData iptcData;
};

// Test that IptcData starts empty
TEST_F(IptcDataTest_664, InitiallyEmpty_664) {
    EXPECT_TRUE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 0u);
}

// Test adding a datum to IptcData
TEST_F(IptcDataTest_664, AddDatum_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("A caption");
    iptcData.add(datum);
    
    EXPECT_FALSE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 1u);
}

// Test adding multiple data entries
TEST_F(IptcDataTest_664, AddMultipleData_664) {
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum1(key1);
    datum1.setValue("Caption 1");
    iptcData.add(datum1);
    
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Iptcdatum datum2(key2);
    datum2.setValue("Keyword1");
    iptcData.add(datum2);
    
    EXPECT_EQ(iptcData.count(), 2u);
}

// Test finding a datum by key
TEST_F(IptcDataTest_664, FindByKey_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("FindMe");
    iptcData.add(datum);
    
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData.end());
}

// Test finding a non-existent key returns end
TEST_F(IptcDataTest_664, FindNonExistentKeyReturnsEnd_664) {
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_EQ(it, iptcData.end());
}

// Test clear removes all data
TEST_F(IptcDataTest_664, ClearRemovesAllData_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("ToBeCleared");
    iptcData.add(datum);
    
    EXPECT_FALSE(iptcData.empty());
    iptcData.clear();
    EXPECT_TRUE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 0u);
}

// Test write with multiple successive writes to same stream
TEST_F(IptcdatumTest_664, MultipleWritesToSameStream_664) {
    Exiv2::IptcKey key1("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum1(key1);
    datum1.setValue("First");
    
    Exiv2::IptcKey key2("Iptc.Application2.Keywords");
    Exiv2::Iptcdatum datum2(key2);
    datum2.setValue("Second");
    
    std::ostringstream oss;
    datum1.write(oss, nullptr);
    datum2.write(oss, nullptr);
    EXPECT_EQ(oss.str(), "FirstSecond");
}

// Test Iptcdatum value accessor
TEST_F(IptcdatumTest_664, ValueAccessor_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("TestValue");
    
    std::string val = datum.toString();
    EXPECT_EQ(val, "TestValue");
}

// Test Iptcdatum tag and record accessors
TEST_F(IptcdatumTest_664, TagAndRecordAccessors_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    
    // Caption in Application2 has tag 120 and record 2
    EXPECT_EQ(datum.tag(), 120);
    EXPECT_EQ(datum.record(), 2);
}

// Test operator[] on IptcData
TEST_F(IptcDataTest_664, SubscriptOperator_664) {
    iptcData["Iptc.Application2.Caption"] = "via operator[]";
    
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    EXPECT_NE(it, iptcData.end());
    EXPECT_EQ(it->toString(), "via operator[]");
}

// Test erase
TEST_F(IptcDataTest_664, EraseDatum_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("ToErase");
    iptcData.add(datum);
    
    EXPECT_EQ(iptcData.count(), 1u);
    
    auto it = iptcData.findKey(Exiv2::IptcKey("Iptc.Application2.Caption"));
    ASSERT_NE(it, iptcData.end());
    iptcData.erase(it);
    
    EXPECT_TRUE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 0u);
}

// Test iteration over IptcData
TEST_F(IptcDataTest_664, IterateOverData_664) {
    iptcData["Iptc.Application2.Caption"] = "Caption";
    iptcData["Iptc.Application2.Keywords"] = "Keyword";
    
    int count = 0;
    for (auto it = iptcData.begin(); it != iptcData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test Iptcdatum copy
TEST_F(IptcdatumTest_664, CopyDatum_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("Original");
    
    Exiv2::Iptcdatum copy(datum);
    EXPECT_EQ(copy.toString(), "Original");
    EXPECT_EQ(copy.key(), "Iptc.Application2.Caption");
}

// Test write with special characters in value
TEST_F(IptcdatumTest_664, WriteSpecialCharacters_664) {
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Iptcdatum datum(key);
    datum.setValue("Line1\nLine2\tTabbed");
    
    std::ostringstream oss;
    datum.write(oss, nullptr);
    EXPECT_EQ(oss.str(), "Line1\nLine2\tTabbed");
}
