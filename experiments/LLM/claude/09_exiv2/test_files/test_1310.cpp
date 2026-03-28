#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/exiv2.hpp>

class XmpDataTest_1310 : public ::testing::Test {
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
TEST_F(XmpDataTest_1310, DefaultConstructedIsEmpty_1310) {
    EXPECT_TRUE(xmpData_.empty());
}

// Test that count is zero for a newly constructed XmpData
TEST_F(XmpDataTest_1310, DefaultConstructedCountIsZero_1310) {
    EXPECT_EQ(0, xmpData_.count());
}

// Test that begin equals end for empty XmpData
TEST_F(XmpDataTest_1310, BeginEqualsEndWhenEmpty_1310) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test adding an element via operator[] makes it non-empty
TEST_F(XmpDataTest_1310, OperatorBracketAddsElement_1310) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_GT(xmpData_.count(), 0);
}

// Test adding an element with add(XmpKey, Value*)
TEST_F(XmpDataTest_1310, AddWithKeyAndValue_1310) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("John Doe");
    EXPECT_EQ(0, xmpData_.add(key, value.get()));
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding an Xmpdatum
TEST_F(XmpDataTest_1310, AddXmpdatum_1310) {
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("A description");
    xmpData_.add(key, value.get());

    // Get the datum and add it again to a fresh XmpData
    Exiv2::XmpData xmpData2;
    auto it = xmpData_.begin();
    ASSERT_NE(it, xmpData_.end());
    xmpData2.add(*it);
    EXPECT_FALSE(xmpData2.empty());
    EXPECT_EQ(1, xmpData2.count());
}

// Test clear removes all elements
TEST_F(XmpDataTest_1310, ClearRemovesAllElements_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_FALSE(xmpData_.empty());

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test erase removes a single element
TEST_F(XmpDataTest_1310, EraseRemovesElement_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    long countBefore = xmpData_.count();

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(countBefore - 1, xmpData_.count());
}

// Test findKey returns end() when key not found
TEST_F(XmpDataTest_1310, FindKeyReturnsEndWhenNotFound_1310) {
    Exiv2::XmpKey key("Xmp.dc.nonexistent");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey finds an existing key
TEST_F(XmpDataTest_1310, FindKeyFindsExistingKey_1310) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(it, xmpData_.end());
}

// Test const findKey on a const XmpData
TEST_F(XmpDataTest_1310, ConstFindKeyFindsExistingKey_1310) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const Exiv2::XmpData& constData = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constData.findKey(key);
    EXPECT_NE(it, constData.end());
}

// Test const begin/end
TEST_F(XmpDataTest_1310, ConstBeginEnd_1310) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_NE(constData.begin(), constData.end());
}

// Test usePacket default value
TEST_F(XmpDataTest_1310, UsePacketDefaultIsFalse_1310) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter
TEST_F(XmpDataTest_1310, UsePacketSetterGetter_1310) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());

    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1310, XmpPacketDefaultIsEmpty_1310) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1310, SetPacketAndGetPacket_1310) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test sortByKey does not crash on empty data
TEST_F(XmpDataTest_1310, SortByKeyOnEmptyData_1310) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_TRUE(xmpData_.empty());
}

// Test sortByKey with data
TEST_F(XmpDataTest_1310, SortByKeyWithData_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Desc";

    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(3, xmpData_.count());
}

// Test multiple additions with operator[]
TEST_F(XmpDataTest_1310, MultipleAdditionsWithOperatorBracket_1310) {
    xmpData_["Xmp.dc.title"] = "Title1";
    xmpData_["Xmp.dc.creator"] = "Creator1";
    xmpData_["Xmp.dc.subject"] = "Subject1";

    EXPECT_EQ(3, xmpData_.count());
    EXPECT_FALSE(xmpData_.empty());
}

// Test operator[] updates existing value
TEST_F(XmpDataTest_1310, OperatorBracketUpdatesExistingValue_1310) {
    xmpData_["Xmp.dc.title"] = "Original";
    long countAfterFirst = xmpData_.count();

    xmpData_["Xmp.dc.title"] = "Updated";
    // Should still have the same count (overwrite, not duplicate)
    EXPECT_EQ(countAfterFirst, xmpData_.count());
}

// Test eraseFamily
TEST_F(XmpDataTest_1310, EraseFamilyRemovesRelatedEntries_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";

    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // At least one element should have been removed
    EXPECT_LE(xmpData_.count(), 1);
}

// Test clear then add again
TEST_F(XmpDataTest_1310, ClearThenAddAgain_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());

    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(1, xmpData_.count());
}

// Test empty after erase last element
TEST_F(XmpDataTest_1310, EmptyAfterEraseLastElement_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_EQ(1, xmpData_.count());

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1310, SetPacketWithEmptyString_1310) {
    xmpData_.setPacket("some packet");
    EXPECT_FALSE(xmpData_.xmpPacket().empty());

    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test const empty on non-empty data
TEST_F(XmpDataTest_1310, ConstEmptyOnNonEmptyData_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_FALSE(constData.empty());
}

// Test const count
TEST_F(XmpDataTest_1310, ConstCount_1310) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    const Exiv2::XmpData& constData = xmpData_;
    EXPECT_EQ(2, constData.count());
}
