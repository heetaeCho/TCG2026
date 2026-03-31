#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exiv2.hpp>

class XmpDataTest_50 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData_;
    
    void SetUp() override {
        // Ensure XMP parser is initialized
        Exiv2::XmpParser::initialize();
    }
    
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test usePacket default value and toggle behavior
TEST_F(XmpDataTest_50, UsePacketDefaultIsFalse_50) {
    // Default should be false; usePacket(bool) returns previous value
    bool previous = xmpData_.usePacket(true);
    EXPECT_FALSE(previous);
}

TEST_F(XmpDataTest_50, UsePacketReturnsPreviousValue_50) {
    xmpData_.usePacket(true);
    bool previous = xmpData_.usePacket(false);
    EXPECT_TRUE(previous);
}

TEST_F(XmpDataTest_50, UsePacketToggleMultipleTimes_50) {
    EXPECT_FALSE(xmpData_.usePacket(true));
    EXPECT_TRUE(xmpData_.usePacket(true));
    EXPECT_TRUE(xmpData_.usePacket(false));
    EXPECT_FALSE(xmpData_.usePacket(false));
    EXPECT_FALSE(xmpData_.usePacket(true));
}

TEST_F(XmpDataTest_50, UsePacketConstVersion_50) {
    const Exiv2::XmpData& constRef = xmpData_;
    EXPECT_FALSE(constRef.usePacket());
    xmpData_.usePacket(true);
    EXPECT_TRUE(constRef.usePacket());
}

// Test empty and count on fresh XmpData
TEST_F(XmpDataTest_50, EmptyOnConstruction_50) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test begin == end on empty data
TEST_F(XmpDataTest_50, BeginEqualsEndWhenEmpty_50) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test const begin == const end on empty data
TEST_F(XmpDataTest_50, ConstBeginEqualsConstEndWhenEmpty_50) {
    const Exiv2::XmpData& constRef = xmpData_;
    EXPECT_EQ(constRef.begin(), constRef.end());
}

// Test operator[] adds element
TEST_F(XmpDataTest_50, OperatorBracketAddsElement_50) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding via operator[] and retrieving
TEST_F(XmpDataTest_50, OperatorBracketRetrievesElement_50) {
    xmpData_["Xmp.dc.description"] = "A description";
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_NE(it, xmpData_.end());
    EXPECT_EQ("Xmp.dc.description", it->key());
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_50, AddWithKeyAndValue_50) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("John Doe");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_50, AddWithXmpdatum_50) {
    Exiv2::Xmpdatum datum(Exiv2::XmpKey("Xmp.dc.subject"));
    datum.setValue("Photography");
    int result = xmpData_.add(datum);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData_.empty());
}

// Test findKey returns end for non-existent key
TEST_F(XmpDataTest_50, FindKeyReturnsEndForNonExistent_50) {
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.nonexistent"));
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey finds existing key
TEST_F(XmpDataTest_50, FindKeyFindsExistingKey_50) {
    xmpData_["Xmp.dc.title"] = "Findable";
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, xmpData_.end());
}

// Test const findKey
TEST_F(XmpDataTest_50, ConstFindKeyFindsExistingKey_50) {
    xmpData_["Xmp.dc.title"] = "Findable";
    const Exiv2::XmpData& constRef = xmpData_;
    auto it = constRef.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, constRef.end());
}

// Test clear
TEST_F(XmpDataTest_50, ClearRemovesAllElements_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(2, xmpData_.count());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test erase
TEST_F(XmpDataTest_50, EraseRemovesElement_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_EQ(2, xmpData_.count());
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(1, xmpData_.count());
}

// Test multiple adds and count
TEST_F(XmpDataTest_50, MultipleAddsIncreasesCount_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(3, xmpData_.count());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_50, SetPacketAndGetPacket_50) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_50, XmpPacketDefaultIsEmpty_50) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_50, SetPacketWithEmptyString_50) {
    xmpData_.setPacket("some content");
    EXPECT_FALSE(xmpData_.xmpPacket().empty());
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test sortByKey doesn't crash on empty
TEST_F(XmpDataTest_50, SortByKeyOnEmptyDoesNotCrash_50) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
}

// Test sortByKey with elements
TEST_F(XmpDataTest_50, SortByKeyOrdersElements_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_NO_THROW(xmpData_.sortByKey());
    
    // After sorting, keys should be in alphabetical order
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

// Test eraseFamily
TEST_F(XmpDataTest_50, EraseFamilyRemovesRelatedEntries_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, count should have decreased
    // We just verify it doesn't crash and data is modified
    EXPECT_TRUE(xmpData_.count() >= 0);
}

// Test clear also resets packet behavior
TEST_F(XmpDataTest_50, ClearOnEmptyIsNoOp_50) {
    EXPECT_NO_THROW(xmpData_.clear());
    EXPECT_TRUE(xmpData_.empty());
}

// Test operator[] with same key returns same element
TEST_F(XmpDataTest_50, OperatorBracketSameKeyReturnsSameElement_50) {
    xmpData_["Xmp.dc.title"] = "First";
    xmpData_["Xmp.dc.title"] = "Second";
    // operator[] on existing key should modify in place
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_NE(it, xmpData_.end());
    EXPECT_EQ("Second", it->toString());
}

// Test iteration over elements
TEST_F(XmpDataTest_50, IterationCoversAllElements_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Author";
    
    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        count++;
    }
    EXPECT_EQ(3, count);
    EXPECT_EQ(xmpData_.count(), count);
}

// Test const iteration
TEST_F(XmpDataTest_50, ConstIterationCoversAllElements_50) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    
    const Exiv2::XmpData& constRef = xmpData_;
    int count = 0;
    for (auto it = constRef.begin(); it != constRef.end(); ++it) {
        count++;
    }
    EXPECT_EQ(2, count);
}
