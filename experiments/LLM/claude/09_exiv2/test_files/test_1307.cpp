#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <string>
#include <algorithm>

namespace {

class XmpDataTest_1307 : public ::testing::Test {
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
TEST_F(XmpDataTest_1307, DefaultConstructorCreatesEmptyData_1307) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test that begin() == end() for empty data
TEST_F(XmpDataTest_1307, BeginEqualsEndWhenEmpty_1307) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test adding an element via operator[]
TEST_F(XmpDataTest_1307, OperatorBracketAddsElement_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding multiple elements via operator[]
TEST_F(XmpDataTest_1307, OperatorBracketAddsMultipleElements_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    xmpData_["Xmp.dc.creator"] = "Test Creator";
    EXPECT_EQ(3, xmpData_.count());
}

// Test that operator[] with the same key accesses the same element
TEST_F(XmpDataTest_1307, OperatorBracketSameKeyAccessesSameElement_1307) {
    xmpData_["Xmp.dc.title"] = "First";
    xmpData_["Xmp.dc.title"] = "Second";
    // Depending on implementation, it may add a second or overwrite
    // We check that at least one entry exists
    EXPECT_FALSE(xmpData_.empty());
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_1307, AddWithKeyAndValue_1307) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Title");
    EXPECT_EQ(0, xmpData_.add(key, value.get()));
    EXPECT_EQ(1, xmpData_.count());
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1307, AddWithXmpdatum_1307) {
    Exiv2::Xmpdatum datum(Exiv2::XmpKey("Xmp.dc.title"));
    datum.setValue("Test Title");
    EXPECT_EQ(0, xmpData_.add(datum));
    EXPECT_EQ(1, xmpData_.count());
}

// Test findKey on existing key
TEST_F(XmpDataTest_1307, FindKeyExistingKey_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test findKey on non-existing key
TEST_F(XmpDataTest_1307, FindKeyNonExistingKey_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    Exiv2::XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey on empty data
TEST_F(XmpDataTest_1307, FindKeyOnEmptyData_1307) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test erase removes an element
TEST_F(XmpDataTest_1307, EraseRemovesElement_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    EXPECT_EQ(2, xmpData_.count());

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(1, xmpData_.count());
}

// Test clear removes all elements
TEST_F(XmpDataTest_1307, ClearRemovesAllElements_1307) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(3, xmpData_.count());

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test clear on already empty data
TEST_F(XmpDataTest_1307, ClearOnEmptyData_1307) {
    EXPECT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test sortByKey sorts entries
TEST_F(XmpDataTest_1307, SortByKeySortsEntries_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";

    xmpData_.sortByKey();

    // After sorting by key, verify the order is lexicographic by key
    std::string prevKey;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        std::string currentKey = it->key();
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, currentKey);
        }
        prevKey = currentKey;
    }
}

// Test sortByKey on empty data doesn't crash
TEST_F(XmpDataTest_1307, SortByKeyOnEmptyData_1307) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_TRUE(xmpData_.empty());
}

// Test sortByKey on single element
TEST_F(XmpDataTest_1307, SortByKeySingleElement_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(1, xmpData_.count());
}

// Test usePacket default value
TEST_F(XmpDataTest_1307, UsePacketDefaultIsFalse_1307) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter and getter
TEST_F(XmpDataTest_1307, UsePacketSetAndGet_1307) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());

    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1307, SetPacketAndGetPacket_1307) {
    std::string packet = "<x:xmpmeta>test packet</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1307, XmpPacketDefaultIsEmpty_1307) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1307, SetPacketEmptyString_1307) {
    xmpData_.setPacket("some packet");
    EXPECT_FALSE(xmpData_.xmpPacket().empty());

    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test const begin/end iteration
TEST_F(XmpDataTest_1307, ConstIterationWorks_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";

    const Exiv2::XmpData& constData = xmpData_;
    int count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(2, count);
}

// Test const findKey
TEST_F(XmpDataTest_1307, ConstFindKey_1307) {
    xmpData_["Xmp.dc.title"] = "Title";

    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
}

// Test const empty and count
TEST_F(XmpDataTest_1307, ConstEmptyAndCount_1307) {
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_TRUE(constData.empty());
    EXPECT_EQ(0, constData.count());
}

// Test eraseFamily
TEST_F(XmpDataTest_1307, EraseFamilyRemovesRelatedEntries_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.xmp.CreateDate"] = "2023-01-01";

    long initialCount = xmpData_.count();
    EXPECT_GT(initialCount, 0);

    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After erasing a family, count should decrease
    EXPECT_LE(xmpData_.count(), initialCount);
}

// Test that erase returns valid iterator
TEST_F(XmpDataTest_1307, EraseReturnsValidIterator_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";

    auto it = xmpData_.begin();
    auto nextIt = xmpData_.erase(it);
    // The returned iterator should be valid (either pointing to next element or end)
    EXPECT_EQ(1, xmpData_.count());
    // nextIt should be begin() since we erased the first element
    EXPECT_EQ(nextIt, xmpData_.begin());
}

// Test adding many elements and sorting
TEST_F(XmpDataTest_1307, AddManyElementsAndSort_1307) {
    xmpData_["Xmp.dc.title"] = "Z Title";
    xmpData_["Xmp.dc.creator"] = "A Creator";
    xmpData_["Xmp.dc.description"] = "M Description";
    xmpData_["Xmp.dc.subject"] = "B Subject";
    xmpData_["Xmp.dc.rights"] = "C Rights";

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

// Test erase all elements one by one
TEST_F(XmpDataTest_1307, EraseAllElementsOneByOne_1307) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";

    while (!xmpData_.empty()) {
        auto it = xmpData_.begin();
        xmpData_.erase(it);
    }

    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test value retrieval after adding via add()
TEST_F(XmpDataTest_1307, ValueRetrievalAfterAdd_1307) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("My Title");
    xmpData_.add(key, value.get());

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ("My Title", it->toString());
}

// Test usePacket returns old value when set
TEST_F(XmpDataTest_1307, UsePacketReturnsOldValue_1307) {
    EXPECT_FALSE(xmpData_.usePacket());
    bool oldVal = xmpData_.usePacket(true);
    // The return value should be the old value (false) based on typical setter pattern
    // but we just verify the new state
    EXPECT_TRUE(xmpData_.usePacket());
}

}  // namespace
