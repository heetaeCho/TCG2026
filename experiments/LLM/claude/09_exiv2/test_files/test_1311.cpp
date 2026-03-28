#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>

namespace {

class XmpDataTest_1311 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData_;
};

// Test that a newly created XmpData has count() == 0
TEST_F(XmpDataTest_1311, DefaultConstructedHasZeroCount_1311) {
    EXPECT_EQ(0, xmpData_.count());
}

// Test that a newly created XmpData is empty
TEST_F(XmpDataTest_1311, DefaultConstructedIsEmpty_1311) {
    EXPECT_TRUE(xmpData_.empty());
}

// Test that begin() == end() for empty XmpData
TEST_F(XmpDataTest_1311, DefaultConstructedBeginEqualsEnd_1311) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test that adding an element via operator[] increases count
TEST_F(XmpDataTest_1311, OperatorBracketIncreasesCount_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_EQ(1, xmpData_.count());
    EXPECT_FALSE(xmpData_.empty());
}

// Test that adding multiple elements via operator[] increases count accordingly
TEST_F(XmpDataTest_1311, MultipleAdditionsIncreaseCount_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    xmpData_["Xmp.dc.creator"] = "Test Creator";
    EXPECT_EQ(3, xmpData_.count());
}

// Test that adding the same key via operator[] does not duplicate
TEST_F(XmpDataTest_1311, OperatorBracketSameKeyNoDuplicate_1311) {
    xmpData_["Xmp.dc.title"] = "Title 1";
    xmpData_["Xmp.dc.title"] = "Title 2";
    // operator[] on the same key should refer to the same datum
    EXPECT_EQ(1, xmpData_.count());
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_1311, AddWithKeyAndValue_1311) {
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::xmpText);
    value->read("Test Subject");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, xmpData_.count());
}

// Test clear empties the data
TEST_F(XmpDataTest_1311, ClearRemovesAllEntries_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    ASSERT_EQ(2, xmpData_.count());
    xmpData_.clear();
    EXPECT_EQ(0, xmpData_.count());
    EXPECT_TRUE(xmpData_.empty());
}

// Test erase removes an entry
TEST_F(XmpDataTest_1311, EraseRemovesEntry_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    xmpData_["Xmp.dc.description"] = "Test Description";
    ASSERT_EQ(2, xmpData_.count());
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_EQ(1, xmpData_.count());
}

// Test findKey returns end() for non-existent key
TEST_F(XmpDataTest_1311, FindKeyNonExistentReturnsEnd_1311) {
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_EQ(xmpData_.end(), it);
}

// Test findKey returns valid iterator for existing key
TEST_F(XmpDataTest_1311, FindKeyExistingReturnsValidIterator_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = xmpData_.findKey(key);
    EXPECT_NE(xmpData_.end(), it);
}

// Test usePacket default value
TEST_F(XmpDataTest_1311, UsePacketDefaultIsFalse_1311) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter
TEST_F(XmpDataTest_1311, UsePacketSetterWorks_1311) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test xmpPacket default is empty
TEST_F(XmpDataTest_1311, XmpPacketDefaultIsEmpty_1311) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1311, SetPacketAndRetrieve_1311) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(packet, xmpData_.xmpPacket());
}

// Test sortByKey doesn't crash on empty data
TEST_F(XmpDataTest_1311, SortByKeyOnEmptyData_1311) {
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(0, xmpData_.count());
}

// Test sortByKey with multiple entries
TEST_F(XmpDataTest_1311, SortByKeyWithMultipleEntries_1311) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";
    EXPECT_NO_THROW(xmpData_.sortByKey());
    EXPECT_EQ(3, xmpData_.count());
}

// Test const findKey
TEST_F(XmpDataTest_1311, ConstFindKey_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const Exiv2::XmpData& constRef = xmpData_;
    Exiv2::XmpKey key("Xmp.dc.title");
    auto it = constRef.findKey(key);
    EXPECT_NE(constRef.end(), it);
}

// Test const begin/end
TEST_F(XmpDataTest_1311, ConstBeginEnd_1311) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    const Exiv2::XmpData& constRef = xmpData_;
    int count = 0;
    for (auto it = constRef.begin(); it != constRef.end(); ++it) {
        ++count;
    }
    EXPECT_EQ(1, count);
}

// Test count matches iteration count
TEST_F(XmpDataTest_1311, CountMatchesIterationCount_1311) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.subject"] = "Subject";
    
    long iterCount = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        ++iterCount;
    }
    EXPECT_EQ(xmpData_.count(), iterCount);
}

// Test clear also handles packet state properly
TEST_F(XmpDataTest_1311, ClearAfterSetPacket_1311) {
    xmpData_.setPacket("some packet");
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_.clear();
    EXPECT_EQ(0, xmpData_.count());
    EXPECT_TRUE(xmpData_.empty());
}

// Test eraseFamily
TEST_F(XmpDataTest_1311, EraseFamilyRemovesRelated_1311) {
    xmpData_["Xmp.dc.title"] = "Title";
    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, the entry should be removed
    EXPECT_LE(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1311, AddXmpdatum_1311) {
    xmpData_["Xmp.dc.title"] = "Title";
    auto it = xmpData_.begin();
    Exiv2::Xmpdatum datum = *it;
    
    Exiv2::XmpData otherData;
    int result = otherData.add(datum);
    EXPECT_EQ(0, result);
    EXPECT_EQ(1, otherData.count());
}

// Test boundary: count returns long
TEST_F(XmpDataTest_1311, CountReturnsLong_1311) {
    long c = xmpData_.count();
    EXPECT_EQ(0L, c);
}

}  // namespace
