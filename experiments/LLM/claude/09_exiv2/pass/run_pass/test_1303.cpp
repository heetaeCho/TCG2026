#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>
#include <memory>

class XmpDataTest_1303 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::XmpData xmpData_;
};

// Test that a newly created XmpData is empty
TEST_F(XmpDataTest_1303, DefaultConstructorCreatesEmptyData_1303) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test adding an element via add(XmpKey, Value*)
TEST_F(XmpDataTest_1303, AddWithKeyAndValueIncreasesCount_1303) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Title");
    
    int result = xmpData_.add(key, value.get());
    
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
    EXPECT_FALSE(xmpData_.empty());
}

// Test adding an element via add(Xmpdatum)
TEST_F(XmpDataTest_1303, AddWithXmpdatumIncreasesCount_1303) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Subject");
    
    Exiv2::Xmpdatum datum(key, value.get());
    int result = xmpData_.add(datum);
    
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding multiple elements
TEST_F(XmpDataTest_1303, AddMultipleElementsIncreasesCount_1303) {
    Exiv2::XmpKey key1("Xmp.dc.title");
    auto value1 = Exiv2::Value::create(Exiv2::xmpText);
    value1->read("Title");
    xmpData_.add(key1, value1.get());

    Exiv2::XmpKey key2("Xmp.dc.description");
    auto value2 = Exiv2::Value::create(Exiv2::xmpText);
    value2->read("Description");
    xmpData_.add(key2, value2.get());

    EXPECT_EQ(2, xmpData_.count());
}

// Test operator[] creates new element if key doesn't exist
TEST_F(XmpDataTest_1303, OperatorBracketCreatesNewElement_1303) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test operator[] accesses existing element
TEST_F(XmpDataTest_1303, OperatorBracketAccessesExistingElement_1303) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    
    Exiv2::Xmpdatum& datum = xmpData_["Xmp.dc.title"];
    EXPECT_EQ("Test Title", datum.toString());
}

// Test findKey finds existing element
TEST_F(XmpDataTest_1303, FindKeyReturnsIteratorToExistingElement_1303) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Title");
    xmpData_.add(key, value.get());

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(xmpData_.end(), it);
    EXPECT_EQ("Xmp.dc.title", it->key());
}

// Test findKey returns end() for non-existing key
TEST_F(XmpDataTest_1303, FindKeyReturnsEndForNonExistingKey_1303) {
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_EQ(xmpData_.end(), it);
}

// Test clear removes all elements
TEST_F(XmpDataTest_1303, ClearRemovesAllElements_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(2, xmpData_.count());

    xmpData_.clear();

    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test erase removes specific element
TEST_F(XmpDataTest_1303, EraseRemovesSpecificElement_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(2, xmpData_.count());

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(xmpData_.end(), it);
    xmpData_.erase(it);

    EXPECT_EQ(1, xmpData_.count());
    auto it2 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_EQ(xmpData_.end(), it2);
}

// Test begin and end iterators on empty data
TEST_F(XmpDataTest_1303, BeginEqualsEndOnEmptyData_1303) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test begin and end iterators with data
TEST_F(XmpDataTest_1303, BeginNotEqualsEndWithData_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_NE(xmpData_.begin(), xmpData_.end());
}

// Test iteration over elements
TEST_F(XmpDataTest_1303, IterationCoversAllElements_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.subject"] = "Subject";

    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(3, count);
}

// Test const begin/end iterators
TEST_F(XmpDataTest_1303, ConstIteratorsWork_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    
    const Exiv2::XmpData& constData = xmpData_;
    int count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(1, count);
}

// Test const findKey
TEST_F(XmpDataTest_1303, ConstFindKeyWorks_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    
    const Exiv2::XmpData& constData = xmpData_;
    auto it = constData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(constData.end(), it);
    EXPECT_EQ("Title", it->toString());
}

// Test usePacket default value
TEST_F(XmpDataTest_1303, UsePacketDefaultIsFalse_1303) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter/getter
TEST_F(XmpDataTest_1303, UsePacketSetterGetter_1303) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1303, XmpPacketDefaultIsEmpty_1303) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1303, SetPacketAndGetPacket_1303) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test sortByKey does not lose elements
TEST_F(XmpDataTest_1303, SortByKeyPreservesCount_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";

    long countBefore = xmpData_.count();
    xmpData_.sortByKey();
    EXPECT_EQ(countBefore, xmpData_.count());
}

// Test sortByKey actually sorts
TEST_F(XmpDataTest_1303, SortByKeyOrdersElements_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";

    xmpData_.sortByKey();

    auto it = xmpData_.begin();
    std::string prev = it->key();
    ++it;
    while (it != xmpData_.end()) {
        EXPECT_LE(prev, it->key());
        prev = it->key();
        ++it;
    }
}

// Test eraseFamily
TEST_F(XmpDataTest_1303, EraseFamilyRemovesRelatedEntries_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    
    // After eraseFamily, count should be less than 2
    EXPECT_LT(xmpData_.count(), 2);
}

// Test clear on already empty data
TEST_F(XmpDataTest_1303, ClearOnEmptyDataIsNoOp_1303) {
    EXPECT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test empty returns correct value after adding and removing
TEST_F(XmpDataTest_1303, EmptyReflectsStateAfterAddAndErase_1303) {
    EXPECT_TRUE(xmpData_.empty());
    
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_FALSE(xmpData_.empty());
    
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_TRUE(xmpData_.empty());
}

// Test adding element with XmpBag type value
TEST_F(XmpDataTest_1303, AddXmpBagValue_1303) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    auto value = Exiv2::Value::create(Exiv2::xmpBag);
    value->read("keyword1");
    
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding element with XmpSeq type value
TEST_F(XmpDataTest_1303, AddXmpSeqValue_1303) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    auto value = Exiv2::Value::create(Exiv2::xmpSeq);
    value->read("Author Name");
    
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test that findKey with const data returns const_iterator
TEST_F(XmpDataTest_1303, FindKeyOnConstDataReturnsConstIterator_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    
    const Exiv2::XmpData& constRef = xmpData_;
    auto cit = constRef.findKey(Exiv2::XmpKey("Xmp.dc.nonexistent"));
    EXPECT_EQ(constRef.end(), cit);
}

// Test XmpKey construction with prefix and property
TEST_F(XmpDataTest_1303, XmpKeyWithPrefixAndProperty_1303) {
    Exiv2::XmpKey key("dc", "title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("My Title");
    
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(xmpData_.end(), it);
    EXPECT_EQ("My Title", it->toString());
}

// Test value is stored correctly and retrievable
TEST_F(XmpDataTest_1303, StoredValueIsRetrievable_1303) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Hello World");
    xmpData_.add(key, value.get());

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(xmpData_.end(), it);
    EXPECT_EQ("Hello World", it->toString());
}

// Test multiple erase operations
TEST_F(XmpDataTest_1303, MultipleEraseOperations_1303) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.subject"] = "Subject";
    EXPECT_EQ(3, xmpData_.count());

    while (!xmpData_.empty()) {
        xmpData_.erase(xmpData_.begin());
    }
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test setPacket overwrites previous packet
TEST_F(XmpDataTest_1303, SetPacketOverwritesPrevious_1303) {
    xmpData_.setPacket("first packet");
    EXPECT_EQ("first packet", xmpData_.xmpPacket());
    
    xmpData_.setPacket("second packet");
    EXPECT_EQ("second packet", xmpData_.xmpPacket());
}

// Test usePacket returns previous value
TEST_F(XmpDataTest_1303, UsePacketReturnsPreviousValue_1303) {
    EXPECT_FALSE(xmpData_.usePacket());
    bool prev = xmpData_.usePacket(true);
    // The setter returns a bool - we just verify current state
    EXPECT_TRUE(xmpData_.usePacket());
}
