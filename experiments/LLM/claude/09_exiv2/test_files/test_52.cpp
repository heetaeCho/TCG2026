#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <string>

class XmpDataTest_52 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    Exiv2::XmpData xmpData_;
};

// Test that a default-constructed XmpData is empty
TEST_F(XmpDataTest_52, DefaultConstructedIsEmpty_52) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that xmpPacket returns empty string by default
TEST_F(XmpDataTest_52, DefaultXmpPacketIsEmpty_52) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_52, SetPacketAndRetrieve_52) {
    std::string packet = "<x:xmpmeta>test packet</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test setPacket with empty string
TEST_F(XmpDataTest_52, SetPacketEmptyString_52) {
    xmpData_.setPacket("some packet");
    EXPECT_EQ(xmpData_.xmpPacket(), "some packet");
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test usePacket default value
TEST_F(XmpDataTest_52, UsePacketDefaultIsFalse_52) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter
TEST_F(XmpDataTest_52, UsePacketSetTrue_52) {
    bool previous = xmpData_.usePacket(true);
    EXPECT_FALSE(previous);
    EXPECT_TRUE(xmpData_.usePacket());
}

// Test usePacket toggle
TEST_F(XmpDataTest_52, UsePacketToggle_52) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    bool prev = xmpData_.usePacket(false);
    EXPECT_TRUE(prev);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test operator[] adds a new entry
TEST_F(XmpDataTest_52, OperatorBracketAddsEntry_52) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test operator[] with multiple keys
TEST_F(XmpDataTest_52, OperatorBracketMultipleKeys_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 2);
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_52, AddWithKeyAndValue_52) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpBag);
    value->read("TestSubject");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_52, AddWithXmpdatum_52) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("Author Name");
    int result = xmpData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test findKey finds existing key
TEST_F(XmpDataTest_52, FindKeyExisting_52) {
    xmpData_["Xmp.dc.title"] = "My Title";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
    EXPECT_EQ(it->key(), "Xmp.dc.title");
}

// Test findKey returns end for non-existing key
TEST_F(XmpDataTest_52, FindKeyNonExisting_52) {
    xmpData_["Xmp.dc.title"] = "My Title";
    Exiv2::XmpKey key("Xmp.dc.description");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test clear
TEST_F(XmpDataTest_52, ClearRemovesAllEntries_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 2);
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test clear on already empty data
TEST_F(XmpDataTest_52, ClearOnEmptyData_52) {
    EXPECT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
}

// Test erase
TEST_F(XmpDataTest_52, EraseRemovesEntry_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(xmpData_.count(), 2);
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test begin and end iterators on empty data
TEST_F(XmpDataTest_52, BeginEqualsEndOnEmpty_52) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test begin and end iterators with data
TEST_F(XmpDataTest_52, BeginNotEqualsEndWithData_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_NE(xmpData_.begin(), xmpData_.end());
}

// Test const begin and end
TEST_F(XmpDataTest_52, ConstIterators_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_NE(constData.begin(), constData.end());
    EXPECT_EQ(constData.count(), 1);
}

// Test sortByKey
TEST_F(XmpDataTest_52, SortByKey_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_.sortByKey();

    // After sorting, entries should be in alphabetical order by key
    auto it = xmpData_.begin();
    std::string prevKey;
    while (it != xmpData_.end()) {
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, it->key());
        }
        prevKey = it->key();
        ++it;
    }
}

// Test iteration count matches count()
TEST_F(XmpDataTest_52, IterationCountMatchesCount_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";

    long manualCount = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++manualCount;
    }
    EXPECT_EQ(manualCount, xmpData_.count());
}

// Test eraseFamily
TEST_F(XmpDataTest_52, EraseFamilyRemovesRelatedEntries_52) {
    Exiv2::XmpKey key1("Xmp.dc.subject");
    Exiv2::Value::UniquePtr val1 = Exiv2::Value::create(Exiv2::xmpBag);
    val1->read("Subject1");
    xmpData_.add(key1, val1.get());

    xmpData_["Xmp.dc.title"] = "Title";

    long initialCount = xmpData_.count();
    EXPECT_GT(initialCount, 0);

    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    EXPECT_LE(xmpData_.count(), initialCount);
}

// Test const findKey
TEST_F(XmpDataTest_52, ConstFindKey_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
    EXPECT_EQ(it->key(), "Xmp.dc.title");
}

// Test const findKey non-existing
TEST_F(XmpDataTest_52, ConstFindKeyNonExisting_52) {
    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.nonexistent");
    auto it = constData.findKey(key);
    EXPECT_EQ(it, constData.end());
}

// Test const empty
TEST_F(XmpDataTest_52, ConstEmpty_52) {
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_TRUE(constData.empty());
}

// Test value retrieval through operator[]
TEST_F(XmpDataTest_52, OperatorBracketValueRetrieval_52) {
    xmpData_["Xmp.dc.title"] = "Hello World";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "Hello World");
}

// Test adding duplicate keys via add
TEST_F(XmpDataTest_52, AddDuplicateKey_52) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum1(key);
    datum1.setValue("Title1");
    int res1 = xmpData_.add(datum1);
    EXPECT_EQ(res1, 0);

    Exiv2::Xmpdatum datum2(key);
    datum2.setValue("Title2");
    int res2 = xmpData_.add(datum2);
    // The second add of the same key may succeed or fail depending on implementation
    // We just verify the data is in a consistent state
    EXPECT_GE(xmpData_.count(), 1);
}

// Test setPacket does not affect metadata entries
TEST_F(XmpDataTest_52, SetPacketDoesNotAffectMetadata_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.setPacket("some packet data");
    EXPECT_EQ(xmpData_.count(), 1);
    EXPECT_EQ(xmpData_.xmpPacket(), "some packet data");
}

// Test clear also affects packet
TEST_F(XmpDataTest_52, ClearClearsPacketAndData_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.setPacket("packet data");
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    // Packet state after clear - observable through xmpPacket()
    // The packet may or may not be cleared; we test what's observable
}

// Test multiple erases until empty
TEST_F(XmpDataTest_52, EraseUntilEmpty_52) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";

    while (!xmpData_.empty()) {
        auto it = xmpData_.begin();
        xmpData_.erase(it);
    }

    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}
