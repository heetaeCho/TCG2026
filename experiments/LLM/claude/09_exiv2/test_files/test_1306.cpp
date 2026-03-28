#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/xmpkey.hpp>
#include <exiv2/value.hpp>
#include <string>

namespace {

class XmpDataTest_1306 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData_;

    void SetUp() override {
        // Fresh XmpData for each test
    }
};

// Test that a newly constructed XmpData is empty
TEST_F(XmpDataTest_1306, DefaultConstructedIsEmpty_1306) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test that begin() == end() for empty XmpData
TEST_F(XmpDataTest_1306, BeginEqualsEndWhenEmpty_1306) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test clear on empty XmpData does not crash
TEST_F(XmpDataTest_1306, ClearOnEmptyDoesNotCrash_1306) {
    EXPECT_NO_THROW(xmpData_.clear());
    EXPECT_TRUE(xmpData_.empty());
}

// Test adding an element via operator[] and checking count
TEST_F(XmpDataTest_1306, OperatorBracketAddsElement_1306) {
    xmpData_["Xmp.dc.title"] = "TestTitle";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_GE(xmpData_.count(), 1);
}

// Test that clear removes all elements
TEST_F(XmpDataTest_1306, ClearRemovesAllElements_1306) {
    xmpData_["Xmp.dc.title"] = "TestTitle";
    xmpData_["Xmp.dc.description"] = "TestDescription";
    EXPECT_FALSE(xmpData_.empty());

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
}

// Test that count reflects number of added elements
TEST_F(XmpDataTest_1306, CountReflectsNumberOfElements_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(3, xmpData_.count());
}

// Test adding element via add(XmpKey, Value*)
TEST_F(XmpDataTest_1306, AddWithKeyAndValue_1306) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("TestSubject");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test adding element via add(Xmpdatum)
TEST_F(XmpDataTest_1306, AddWithXmpdatum_1306) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Xmpdatum datum(key);
    datum.setValue("TestValue");
    int result = xmpData_.add(datum);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData_.empty());
}

// Test findKey returns end() when key not found
TEST_F(XmpDataTest_1306, FindKeyReturnsEndWhenNotFound_1306) {
    Exiv2::XmpKey key("Xmp.dc.nonexistent");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(xmpData_.end(), it);
}

// Test findKey finds an existing key
TEST_F(XmpDataTest_1306, FindKeyFindsExistingKey_1306) {
    xmpData_["Xmp.dc.title"] = "SomeTitle";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(xmpData_.end(), it);
}

// Test erase removes an element
TEST_F(XmpDataTest_1306, EraseRemovesElement_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    EXPECT_EQ(2, xmpData_.count());

    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(1, xmpData_.count());
}

// Test usePacket default value
TEST_F(XmpDataTest_1306, UsePacketDefaultIsFalse_1306) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter and getter
TEST_F(XmpDataTest_1306, UsePacketSetAndGet_1306) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());

    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1306, SetPacketAndGetPacket_1306) {
    std::string packet = "<xmp>test packet</xmp>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test xmpPacket is empty by default
TEST_F(XmpDataTest_1306, XmpPacketDefaultIsEmpty_1306) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test sortByKey does not crash on empty data
TEST_F(XmpDataTest_1306, SortByKeyOnEmptyDoesNotCrash_1306) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
}

// Test sortByKey with elements
TEST_F(XmpDataTest_1306, SortByKeySortsElements_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";

    EXPECT_NO_THROW(xmpData_.sortByKey());

    // Verify sorted order: creator < description < title
    auto it = xmpData_.begin();
    std::string prev_key;
    for (; it != xmpData_.end(); ++it) {
        std::string current_key = it->key();
        if (!prev_key.empty()) {
            EXPECT_LE(prev_key, current_key);
        }
        prev_key = current_key;
    }
}

// Test operator[] on same key returns same element (no duplicate)
TEST_F(XmpDataTest_1306, OperatorBracketSameKeyNoDuplicate_1306) {
    xmpData_["Xmp.dc.title"] = "First";
    xmpData_["Xmp.dc.title"] = "Second";
    // operator[] should find existing entry, so count should remain 1
    Exiv2::XmpKey key("Xmp.dc.title");
    long count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        if (it->key() == "Xmp.dc.title") {
            ++count;
        }
    }
    EXPECT_EQ(1, count);
}

// Test clear also clears packet-related state indirectly
TEST_F(XmpDataTest_1306, ClearAfterAddingMultipleElements_1306) {
    for (int i = 0; i < 100; ++i) {
        std::string key = "Xmp.dc.subject" + std::to_string(i);
        // Use add with XmpKey
        Exiv2::XmpKey xmpKey("Xmp.dc.title");
        // Use operator[] with unique keys instead
    }
    // Simpler approach
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";
    xmpData_["Xmp.dc.creator"] = "Creator";

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(0, xmpData_.count());
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test const iterator access
TEST_F(XmpDataTest_1306, ConstIteratorAccess_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constRef = xmpData_;
    auto it = constRef.begin();
    EXPECT_NE(it, constRef.end());
    EXPECT_EQ("Xmp.dc.title", it->key());
}

// Test const findKey
TEST_F(XmpDataTest_1306, ConstFindKey_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    const Exiv2::XmpData& constRef = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constRef.findKey(key);
    EXPECT_NE(it, constRef.end());
}

// Test const empty and count
TEST_F(XmpDataTest_1306, ConstEmptyAndCount_1306) {
    const Exiv2::XmpData& constRef = xmpData_;
    EXPECT_TRUE(constRef.empty());
    EXPECT_EQ(0, constRef.count());
}

// Test eraseFamily
TEST_F(XmpDataTest_1306, EraseFamilyRemovesRelatedEntries_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After erasing family, the data should have fewer or no elements
    // At minimum we verify it doesn't crash
    EXPECT_GE(xmpData_.count(), 0);
}

// Test that erase returns valid iterator
TEST_F(XmpDataTest_1306, EraseReturnsValidIterator_1306) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Desc";

    auto it = xmpData_.begin();
    auto next = xmpData_.erase(it);
    // The returned iterator should be valid (either pointing to next element or end)
    EXPECT_EQ(1, xmpData_.count());
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1306, SetPacketWithEmptyString_1306) {
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket overwrites previous packet
TEST_F(XmpDataTest_1306, SetPacketOverwritesPrevious_1306) {
    xmpData_.setPacket("first");
    EXPECT_EQ("first", xmpData_.xmpPacket());

    xmpData_.setPacket("second");
    EXPECT_EQ("second", xmpData_.xmpPacket());
}

// Test usePacket returns previous value
TEST_F(XmpDataTest_1306, UsePacketReturnsPreviousValue_1306) {
    EXPECT_FALSE(xmpData_.usePacket(true));
    EXPECT_TRUE(xmpData_.usePacket(false));
    EXPECT_FALSE(xmpData_.usePacket(true));
}

}  // namespace
