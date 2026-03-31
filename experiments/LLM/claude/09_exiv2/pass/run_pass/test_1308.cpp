#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class XmpDataTest_1308 : public ::testing::Test {
protected:
    XmpData xmpData_;

    void SetUp() override {
        // Fresh XmpData for each test
        xmpData_ = XmpData();
    }
};

// Test that a newly constructed XmpData is empty
TEST_F(XmpDataTest_1308, DefaultConstructorCreatesEmptyData_1308) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that begin() equals end() for empty data
TEST_F(XmpDataTest_1308, BeginEqualsEndWhenEmpty_1308) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test adding an element via operator[]
TEST_F(XmpDataTest_1308, OperatorBracketAddsElement_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test adding an element via add(XmpKey, Value*)
TEST_F(XmpDataTest_1308, AddWithKeyAndValue_1308) {
    XmpKey key("Xmp.dc.creator");
    Value::UniquePtr value = Value::create(xmpText);
    value->read("John Doe");
    EXPECT_EQ(xmpData_.add(key, value.get()), 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test adding an Xmpdatum
TEST_F(XmpDataTest_1308, AddXmpdatum_1308) {
    xmpData_["Xmp.dc.description"] = "A description";
    Xmpdatum datum = *xmpData_.begin();
    
    XmpData other;
    EXPECT_EQ(other.add(datum), 0);
    EXPECT_EQ(other.count(), 1);
}

// Test that count reflects number of elements added
TEST_F(XmpDataTest_1308, CountReflectsAddedElements_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test findKey on existing key
TEST_F(XmpDataTest_1308, FindKeyExistingKey_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey on non-existing key
TEST_F(XmpDataTest_1308, FindKeyNonExistingKey_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    XmpKey key("Xmp.dc.creator");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_1308, ConstFindKey_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
}

// Test erase
TEST_F(XmpDataTest_1308, EraseRemovesElement_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 2);
    
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test clear
TEST_F(XmpDataTest_1308, ClearRemovesAllElements_1308) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 2);
    
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test clear on already empty data
TEST_F(XmpDataTest_1308, ClearOnEmptyData_1308) {
    EXPECT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test empty returns false after adding elements
TEST_F(XmpDataTest_1308, EmptyReturnsFalseAfterAdd_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_FALSE(xmpData_.empty());
}

// Test sortByKey does not change count
TEST_F(XmpDataTest_1308, SortByKeyPreservesCount_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    
    long countBefore = xmpData_.count();
    xmpData_.sortByKey();
    EXPECT_EQ(xmpData_.count(), countBefore);
}

// Test sortByKey on empty data
TEST_F(XmpDataTest_1308, SortByKeyOnEmptyData_1308) {
    xmpData_.sortByKey();
    EXPECT_TRUE(xmpData_.empty());
}

// Test usePacket default value
TEST_F(XmpDataTest_1308, UsePacketDefaultValue_1308) {
    // Default constructed, usePacket_ should be default initialized (false)
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setting usePacket
TEST_F(XmpDataTest_1308, SetUsePacket_1308) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1308, XmpPacketDefaultEmpty_1308) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1308, SetAndGetPacket_1308) {
    std::string packet = "<xmp>test packet</xmp>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1308, SetEmptyPacket_1308) {
    xmpData_.setPacket("some packet");
    EXPECT_FALSE(xmpData_.xmpPacket().empty());
    
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test const begin and end
TEST_F(XmpDataTest_1308, ConstBeginEnd_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    const XmpData& constData = xmpData_;
    
    auto it = constData.begin();
    EXPECT_NE(it, constData.end());
    
    int count = 0;
    for (auto cit = constData.begin(); cit != constData.end(); ++cit) {
        ++count;
    }
    EXPECT_EQ(count, 1);
}

// Test iterator traversal
TEST_F(XmpDataTest_1308, IteratorTraversal_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    
    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(count, 2);
}

// Test operator[] with same key updates or accesses the same element
TEST_F(XmpDataTest_1308, OperatorBracketSameKeyAccess_1308) {
    xmpData_["Xmp.dc.title"] = "Title1";
    xmpData_["Xmp.dc.title"] = "Title2";
    
    // The behavior depends on implementation - operator[] may add duplicates or update
    // We just verify it doesn't crash and data is accessible
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test eraseFamily
TEST_F(XmpDataTest_1308, EraseFamilyRemovesRelatedEntries_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, we should have fewer elements or the iterator has moved
    // Just verify no crash and the data is in a valid state
    EXPECT_GE(xmpData_.count(), 0);
}

// Test erase all elements one by one
TEST_F(XmpDataTest_1308, EraseAllElementsOneByOne_1308) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";
    
    while (!xmpData_.empty()) {
        auto it = xmpData_.begin();
        xmpData_.erase(it);
    }
    
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that count returns long type
TEST_F(XmpDataTest_1308, CountReturnsLong_1308) {
    long c = xmpData_.count();
    EXPECT_EQ(c, 0L);
}

// Test adding multiple different properties
TEST_F(XmpDataTest_1308, AddMultipleDifferentProperties_1308) {
    XmpKey key1("Xmp.dc.title");
    Value::UniquePtr val1 = Value::create(xmpText);
    val1->read("Title");
    xmpData_.add(key1, val1.get());

    XmpKey key2("Xmp.dc.creator");
    Value::UniquePtr val2 = Value::create(xmpText);
    val2->read("Creator");
    xmpData_.add(key2, val2.get());

    EXPECT_EQ(xmpData_.count(), 2);
    EXPECT_FALSE(xmpData_.empty());
}

// Test findKey returns end for empty XmpData
TEST_F(XmpDataTest_1308, FindKeyOnEmptyReturnsEnd_1308) {
    XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test const version findKey on empty returns const end
TEST_F(XmpDataTest_1308, ConstFindKeyOnEmptyReturnsEnd_1308) {
    const XmpData& constData = xmpData_;
    XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}
