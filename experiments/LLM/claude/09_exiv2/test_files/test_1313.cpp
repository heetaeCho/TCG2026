#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <string>
#include <vector>

namespace {

class XmpDataEraseFamilyTest_1313 : public ::testing::Test {
protected:
    Exiv2::XmpData xmpData_;

    void SetUp() override {
        // Enable XMP support if needed
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    void addEntry(const std::string& key, const std::string& value) {
        xmpData_[key] = value;
    }
};

// Test eraseFamily on an empty XmpData
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilyOnEmptyData_1313) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test eraseFamily removes a single entry when there's only one matching key
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilySingleEntry_1313) {
    addEntry("Xmp.dc.title", "Test Title");
    EXPECT_EQ(xmpData_.count(), 1);

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());

    xmpData_.eraseFamily(it);
    EXPECT_EQ(xmpData_.count(), 0);
    EXPECT_TRUE(xmpData_.empty());
}

// Test eraseFamily removes entries that share the same key prefix
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilyRemovesRelatedEntries_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.dc.description", "Desc");
    addEntry("Xmp.xmp.Rating", "5");

    EXPECT_EQ(xmpData_.count(), 3);

    // Sort by key to ensure predictable ordering
    xmpData_.sortByKey();

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    ASSERT_NE(it, xmpData_.end());

    xmpData_.eraseFamily(it);

    // description should be erased, but title and rating might remain
    auto descIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_EQ(descIt, xmpData_.end());

    // Rating should still exist
    auto ratingIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.Rating"));
    EXPECT_NE(ratingIt, xmpData_.end());
}

// Test eraseFamily does not remove unrelated entries
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilyKeepsUnrelatedEntries_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.xmp.Rating", "5");
    addEntry("Xmp.xmp.CreateDate", "2023-01-01");

    long initialCount = xmpData_.count();
    EXPECT_EQ(initialCount, 3);

    xmpData_.sortByKey();

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());

    xmpData_.eraseFamily(it);

    // dc.title should be gone
    auto titleIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_EQ(titleIt, xmpData_.end());

    // xmp entries should remain
    auto ratingIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.Rating"));
    EXPECT_NE(ratingIt, xmpData_.end());

    auto createDateIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.CreateDate"));
    EXPECT_NE(createDateIt, xmpData_.end());
}

// Test eraseFamily when the iterator is at the last element
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilyAtLastElement_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.xmp.Rating", "5");

    xmpData_.sortByKey();

    // Find the last element in sorted order
    auto it = xmpData_.begin();
    auto lastIt = it;
    while (it != xmpData_.end()) {
        lastIt = it;
        ++it;
    }

    std::string lastKey = lastIt->key();
    xmpData_.eraseFamily(lastIt);

    auto findIt = xmpData_.findKey(Exiv2::XmpKey(lastKey));
    EXPECT_EQ(findIt, xmpData_.end());
}

// Test basic XmpData operations that eraseFamily depends on
TEST_F(XmpDataEraseFamilyTest_1313, BasicXmpDataOperations_1313) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);

    addEntry("Xmp.dc.title", "Test");
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);

    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test eraseFamily with multiple entries in the same group
TEST_F(XmpDataEraseFamilyTest_1313, EraseFamilyMultipleEntriesSameGroup_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.dc.creator", "Creator");
    addEntry("Xmp.dc.subject", "Subject");
    addEntry("Xmp.xmp.Rating", "5");

    EXPECT_EQ(xmpData_.count(), 4);

    xmpData_.sortByKey();

    // Erase dc.creator - should only erase that one entry (not others in dc group)
    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    ASSERT_NE(it, xmpData_.end());

    xmpData_.eraseFamily(it);

    auto creatorIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_EQ(creatorIt, xmpData_.end());

    // Other dc entries may or may not be erased depending on sorted adjacency
    // Rating should definitely remain since it's in a different namespace
    auto ratingIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.Rating"));
    EXPECT_NE(ratingIt, xmpData_.end());
}

// Test erasing all entries via repeated eraseFamily calls
TEST_F(XmpDataEraseFamilyTest_1313, EraseAllViaEraseFamily_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.xmp.Rating", "5");

    while (!xmpData_.empty()) {
        auto it = xmpData_.begin();
        xmpData_.eraseFamily(it);
    }

    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that findKey returns end() for non-existent key
TEST_F(XmpDataEraseFamilyTest_1313, FindKeyNonExistent_1313) {
    addEntry("Xmp.dc.title", "Title");

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.nonexistent"));
    EXPECT_EQ(it, xmpData_.end());
}

// Test erase (single element erase) works correctly
TEST_F(XmpDataEraseFamilyTest_1313, SingleErase_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.dc.creator", "Creator");

    EXPECT_EQ(xmpData_.count(), 2);

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());

    xmpData_.erase(it);
    EXPECT_EQ(xmpData_.count(), 1);

    auto titleIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    EXPECT_EQ(titleIt, xmpData_.end());

    auto creatorIt = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    EXPECT_NE(creatorIt, xmpData_.end());
}

// Test sortByKey actually orders entries
TEST_F(XmpDataEraseFamilyTest_1313, SortByKey_1313) {
    addEntry("Xmp.xmp.Rating", "5");
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.dc.creator", "Creator");

    xmpData_.sortByKey();

    std::string prevKey;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        if (!prevKey.empty()) {
            EXPECT_LE(prevKey, it->key());
        }
        prevKey = it->key();
    }
}

// Test add via XmpKey and Value
TEST_F(XmpDataEraseFamilyTest_1313, AddViaXmpKey_1313) {
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::Value::UniquePtr val = Exiv2::Value::create(Exiv2::xmpText);
    val->read("Test Title");

    int rc = xmpData_.add(key, val.get());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(xmpData_.count(), 1);

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "Test Title");
}

// Test operator[] creates entry if not present
TEST_F(XmpDataEraseFamilyTest_1313, OperatorBracketCreatesEntry_1313) {
    EXPECT_TRUE(xmpData_.empty());

    xmpData_["Xmp.dc.title"] = "New Title";

    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);

    auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->key(), "Xmp.dc.title");
}

// Test usePacket getter and setter
TEST_F(XmpDataEraseFamilyTest_1313, UsePacket_1313) {
    // Default should be false (based on usePacket_= {})
    EXPECT_FALSE(xmpData_.usePacket());

    bool oldVal = xmpData_.usePacket(true);
    EXPECT_FALSE(oldVal);
    EXPECT_TRUE(xmpData_.usePacket());

    oldVal = xmpData_.usePacket(false);
    EXPECT_TRUE(oldVal);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataEraseFamilyTest_1313, SetAndGetPacket_1313) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());

    std::string packet = "<xmp>test packet</xmp>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test clear resets everything
TEST_F(XmpDataEraseFamilyTest_1313, ClearResetsData_1313) {
    addEntry("Xmp.dc.title", "Title");
    addEntry("Xmp.dc.creator", "Creator");
    addEntry("Xmp.xmp.Rating", "5");

    EXPECT_EQ(xmpData_.count(), 3);

    xmpData_.clear();

    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

}  // namespace
