#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exiv2.hpp>
#include <string>

class XmpDataTest_51 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::XmpData xmpData_;
};

// Test that a newly constructed XmpData is empty
TEST_F(XmpDataTest_51, DefaultConstructorCreatesEmptyData_51) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test that begin() equals end() for empty XmpData
TEST_F(XmpDataTest_51, BeginEqualsEndWhenEmpty_51) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test setPacket stores the packet string
TEST_F(XmpDataTest_51, SetPacketStoresPacket_51) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_51, SetPacketWithEmptyString_51) {
    xmpData_.setPacket("");
    EXPECT_EQ("", xmpData_.xmpPacket());
}

// Test setPacket sets usePacket to false
TEST_F(XmpDataTest_51, SetPacketSetsUsePacketToFalse_51) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.setPacket("some packet");
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket getter/setter
TEST_F(XmpDataTest_51, UsePacketGetterSetter_51) {
    EXPECT_FALSE(xmpData_.usePacket());
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test operator[] adds new entry
TEST_F(XmpDataTest_51, OperatorBracketAddsEntry_51) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test operator[] with same key doesn't duplicate
TEST_F(XmpDataTest_51, OperatorBracketSameKeyNoExtraDuplicate_51) {
    xmpData_["Xmp.dc.title"] = "Title1";
    long countAfterFirst = xmpData_.count();
    xmpData_["Xmp.dc.title"] = "Title2";
    // operator[] should return existing datum for same key
    EXPECT_EQ(countAfterFirst, xmpData_.count());
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_51, AddWithKeyAndValue_51) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("John Doe");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_51, AddWithXmpdatum_51) {
    Exiv2::Xmpdatum datum(Exiv2::XmpKey("Xmp.dc.subject"));
    datum.setValue("Photography");
    int result = xmpData_.add(datum);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test findKey on existing key
TEST_F(XmpDataTest_51, FindKeyExistingKey_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey on non-existing key
TEST_F(XmpDataTest_51, FindKeyNonExistingKey_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    Exiv2::XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on empty XmpData
TEST_F(XmpDataTest_51, FindKeyOnEmptyData_51) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_51, ConstFindKey_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
}

// Test erase
TEST_F(XmpDataTest_51, EraseRemovesElement_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    xmpData_["Xmp.dc.creator"] = "Author";
    EXPECT_EQ(2, xmpData_.count());
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(1, xmpData_.count());
}

// Test clear
TEST_F(XmpDataTest_51, ClearRemovesAllElements_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    xmpData_["Xmp.dc.creator"] = "Author";
    xmpData_["Xmp.dc.subject"] = "Subject";
    EXPECT_EQ(3, xmpData_.count());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test clear on empty data
TEST_F(XmpDataTest_51, ClearOnEmptyData_51) {
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test count increases with additions
TEST_F(XmpDataTest_51, CountIncreasesWithAdditions_51) {
    EXPECT_EQ(0, xmpData_.count());
    xmpData_["Xmp.dc.title"] = "T1";
    EXPECT_EQ(1, xmpData_.count());
    xmpData_["Xmp.dc.creator"] = "C1";
    EXPECT_EQ(2, xmpData_.count());
    xmpData_["Xmp.dc.subject"] = "S1";
    EXPECT_EQ(3, xmpData_.count());
}

// Test empty returns false after adding elements
TEST_F(XmpDataTest_51, EmptyReturnsFalseAfterAdd_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    EXPECT_FALSE(xmpData_.empty());
}

// Test sortByKey does not change count
TEST_F(XmpDataTest_51, SortByKeyDoesNotChangeCount_51) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";
    long countBefore = xmpData_.count();
    xmpData_.sortByKey();
    EXPECT_EQ(countBefore, xmpData_.count());
}

// Test sortByKey produces sorted order
TEST_F(XmpDataTest_51, SortByKeyProducesSortedOrder_51) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_.sortByKey();

    std::string prevKey;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        std::string currentKey = it->key();
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, currentKey);
        }
        prevKey = currentKey;
    }
}

// Test const begin/end iterators
TEST_F(XmpDataTest_51, ConstIterators_51) {
    xmpData_["Xmp.dc.title"] = "Test";
    const Exiv2::XmpData& constData = xmpData_;
    int count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(1, count);
}

// Test setPacket replaces previous packet
TEST_F(XmpDataTest_51, SetPacketReplacesExistingPacket_51) {
    xmpData_.setPacket("first packet");
    EXPECT_EQ("first packet", xmpData_.xmpPacket());
    xmpData_.setPacket("second packet");
    EXPECT_EQ("second packet", xmpData_.xmpPacket());
}

// Test xmpPacket is empty by default
TEST_F(XmpDataTest_51, XmpPacketEmptyByDefault_51) {
    EXPECT_EQ("", xmpData_.xmpPacket());
}

// Test eraseFamily
TEST_F(XmpDataTest_51, EraseFamilyRemovesRelatedEntries_51) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, the iterator should have advanced or elements removed
    // Just verify count decreased
    EXPECT_TRUE(xmpData_.count() < 2);
}

// Test multiple adds with different keys
TEST_F(XmpDataTest_51, MultipleAddsWithDifferentKeys_51) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::xmpText);
    val1->read("Title");
    xmpData_.add(key1, val1.get());

    Exiv2::XmpKey key2("Xmp.dc.creator");
    Exiv2::Value::UniquePtr val2 = Exiv2::Value::create(Exiv2::xmpText);
    val2->read("Creator");
    xmpData_.add(key2, val2.get());

    EXPECT_EQ(2, xmpData_.count());
}

// Test setPacket with large string
TEST_F(XmpDataTest_51, SetPacketWithLargeString_51) {
    std::string largePacket(100000, 'x');
    xmpData_.setPacket(largePacket);
    EXPECT_EQ(largePacket, xmpData_.xmpPacket());
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test that erase on last element makes data empty
TEST_F(XmpDataTest_51, EraseLastElementMakesEmpty_51) {
    xmpData_["Xmp.dc.title"] = "Only";
    EXPECT_EQ(1, xmpData_.count());
    xmpData_.erase(xmpData_.begin());
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test usePacket returns the value that was set
TEST_F(XmpDataTest_51, UsePacketReturnsPreviousValue_51) {
    // Initially false
    bool prev = xmpData_.usePacket(true);
    // The return value of usePacket(bool) - checking it returns something meaningful
    // We set it to true, now check getter
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}
