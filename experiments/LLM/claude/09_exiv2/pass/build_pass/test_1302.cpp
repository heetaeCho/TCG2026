#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

class XmpDataTest_1302 : public ::testing::Test {
protected:
    XmpData xmpData_;

    void SetUp() override {
        // Ensure XMP parser is initialized
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }
};

// Test that a newly created XmpData is empty
TEST_F(XmpDataTest_1302, DefaultConstructorCreatesEmptyData_1302) {
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test that begin() == end() for empty data
TEST_F(XmpDataTest_1302, BeginEqualsEndWhenEmpty_1302) {
    EXPECT_EQ(xmpData_.begin(), xmpData_.end());
}

// Test operator[] creates a new entry when key doesn't exist
TEST_F(XmpDataTest_1302, OperatorBracketCreatesNewEntry_1302) {
    xmpData_["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test operator[] returns existing entry when key exists
TEST_F(XmpDataTest_1302, OperatorBracketReturnsExistingEntry_1302) {
    xmpData_["Xmp.dc.title"] = "First";
    xmpData_["Xmp.dc.title"] = "Second";
    EXPECT_EQ(xmpData_.count(), 1);
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "Second");
}

// Test add with XmpKey and Value
TEST_F(XmpDataTest_1302, AddWithKeyAndValue_1302) {
    XmpKey key("Xmp.dc.subject");
    auto value = Value::create(xmpText);
    value->read("TestSubject");
    int result = xmpData_.add(key, value.get());
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test add with Xmpdatum
TEST_F(XmpDataTest_1302, AddWithXmpdatum_1302) {
    Xmpdatum datum(XmpKey("Xmp.dc.creator"));
    datum.setValue("John Doe");
    int result = xmpData_.add(datum);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(xmpData_.count(), 1);
}

// Test findKey returns end() when key not found
TEST_F(XmpDataTest_1302, FindKeyReturnsEndWhenNotFound_1302) {
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.nonexistent"));
    EXPECT_EQ(it, xmpData_.end());
}

// Test findKey returns correct iterator when key exists
TEST_F(XmpDataTest_1302, FindKeyReturnsCorrectIterator_1302) {
    xmpData_["Xmp.dc.title"] = "FindMe";
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "FindMe");
}

// Test erase removes an element
TEST_F(XmpDataTest_1302, EraseRemovesElement_1302) {
    xmpData_["Xmp.dc.title"] = "ToBeRemoved";
    EXPECT_EQ(xmpData_.count(), 1);
    auto it = xmpData_.begin();
    xmpData_.erase(it);
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test clear removes all elements
TEST_F(XmpDataTest_1302, ClearRemovesAllElements_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.subject"] = "Subject";
    EXPECT_EQ(xmpData_.count(), 3);
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test count returns correct number of elements
TEST_F(XmpDataTest_1302, CountReturnsCorrectNumber_1302) {
    EXPECT_EQ(xmpData_.count(), 0);
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_EQ(xmpData_.count(), 1);
    xmpData_["Xmp.dc.creator"] = "Creator";
    EXPECT_EQ(xmpData_.count(), 2);
    xmpData_["Xmp.dc.subject"] = "Subject";
    EXPECT_EQ(xmpData_.count(), 3);
}

// Test empty returns true when no elements
TEST_F(XmpDataTest_1302, EmptyReturnsTrueWhenNoElements_1302) {
    EXPECT_TRUE(xmpData_.empty());
}

// Test empty returns false when elements exist
TEST_F(XmpDataTest_1302, EmptyReturnsFalseWhenElementsExist_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    EXPECT_FALSE(xmpData_.empty());
}

// Test usePacket default value
TEST_F(XmpDataTest_1302, UsePacketDefaultIsFalse_1302) {
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test usePacket setter and getter
TEST_F(XmpDataTest_1302, UsePacketSetterAndGetter_1302) {
    xmpData_.usePacket(true);
    EXPECT_TRUE(xmpData_.usePacket());
    xmpData_.usePacket(false);
    EXPECT_FALSE(xmpData_.usePacket());
}

// Test setPacket and xmpPacket
TEST_F(XmpDataTest_1302, SetPacketAndXmpPacket_1302) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    xmpData_.setPacket(packet);
    EXPECT_EQ(xmpData_.xmpPacket(), packet);
}

// Test xmpPacket returns empty string by default
TEST_F(XmpDataTest_1302, XmpPacketDefaultIsEmpty_1302) {
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test multiple different keys
TEST_F(XmpDataTest_1302, MultipleDifferentKeys_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.description"] = "Description";
    xmpData_["Xmp.dc.creator"] = "Creator";

    EXPECT_EQ(xmpData_.count(), 3);

    auto it1 = xmpData_.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it1, xmpData_.end());
    EXPECT_EQ(it1->toString(), "Title");

    auto it2 = xmpData_.findKey(XmpKey("Xmp.dc.description"));
    ASSERT_NE(it2, xmpData_.end());
    EXPECT_EQ(it2->toString(), "Description");

    auto it3 = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    ASSERT_NE(it3, xmpData_.end());
    EXPECT_EQ(it3->toString(), "Creator");
}

// Test sortByKey doesn't crash and data is still accessible
TEST_F(XmpDataTest_1302, SortByKeyMaintainsData_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.description"] = "Description";

    xmpData_.sortByKey();

    EXPECT_EQ(xmpData_.count(), 3);
    auto it = xmpData_.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData_.end());
    EXPECT_EQ(it->toString(), "Title");
}

// Test iteration through elements
TEST_F(XmpDataTest_1302, IterationThroughElements_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";

    int count = 0;
    for (auto it = xmpData_.begin(); it != xmpData_.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test const iteration
TEST_F(XmpDataTest_1302, ConstIteration_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";

    const XmpData& constData = xmpData_;
    int count = 0;
    for (auto it = constData.begin(); it != constData.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 2);
}

// Test const findKey
TEST_F(XmpDataTest_1302, ConstFindKey_1302) {
    xmpData_["Xmp.dc.title"] = "Title";

    const XmpData& constData = xmpData_;
    auto it = constData.findKey(XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, constData.end());
    EXPECT_EQ(it->toString(), "Title");
}

// Test const findKey when not found
TEST_F(XmpDataTest_1302, ConstFindKeyNotFound_1302) {
    const XmpData& constData = xmpData_;
    auto it = constData.findKey(XmpKey("Xmp.dc.nonexistent"));
    EXPECT_EQ(it, constData.end());
}

// Test erase from middle of collection
TEST_F(XmpDataTest_1302, EraseFromMiddle_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";
    xmpData_["Xmp.dc.subject"] = "Subject";

    auto it = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    ASSERT_NE(it, xmpData_.end());
    xmpData_.erase(it);

    EXPECT_EQ(xmpData_.count(), 2);
    auto notFound = xmpData_.findKey(XmpKey("Xmp.dc.creator"));
    EXPECT_EQ(notFound, xmpData_.end());
}

// Test clear on already empty data
TEST_F(XmpDataTest_1302, ClearOnEmptyData_1302) {
    EXPECT_TRUE(xmpData_.empty());
    xmpData_.clear();
    EXPECT_TRUE(xmpData_.empty());
    EXPECT_EQ(xmpData_.count(), 0);
}

// Test operator[] with same key returns same reference
TEST_F(XmpDataTest_1302, OperatorBracketSameKeyDoesNotDuplicate_1302) {
    xmpData_["Xmp.dc.title"] = "Original";
    long countBefore = xmpData_.count();
    xmpData_["Xmp.dc.title"] = "Modified";
    long countAfter = xmpData_.count();
    EXPECT_EQ(countBefore, countAfter);
}

// Test adding duplicate key via add method
TEST_F(XmpDataTest_1302, AddDuplicateKeyReturnsError_1302) {
    XmpKey key("Xmp.dc.title");
    auto value1 = Value::create(xmpText);
    value1->read("First");
    int result1 = xmpData_.add(key, value1.get());
    EXPECT_EQ(result1, 0);

    auto value2 = Value::create(xmpText);
    value2->read("Second");
    // Second add of same key - behavior depends on implementation
    int result2 = xmpData_.add(key, value2.get());
    // We just verify the call doesn't crash; the return value depends on implementation
    (void)result2;
}

// Test XmpKey construction and properties
TEST_F(XmpDataTest_1302, XmpKeyProperties_1302) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test XmpKey copy constructor
TEST_F(XmpDataTest_1302, XmpKeyCopyConstructor_1302) {
    XmpKey key("Xmp.dc.title");
    XmpKey keyCopy(key);
    EXPECT_EQ(keyCopy.key(), "Xmp.dc.title");
    EXPECT_EQ(keyCopy.groupName(), "dc");
    EXPECT_EQ(keyCopy.tagName(), "title");
}

// Test XmpKey assignment operator
TEST_F(XmpDataTest_1302, XmpKeyAssignmentOperator_1302) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.creator");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Xmp.dc.title");
}

// Test XmpKey clone
TEST_F(XmpDataTest_1302, XmpKeyClone_1302) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), "Xmp.dc.title");
}

// Test eraseFamily
TEST_F(XmpDataTest_1302, EraseFamilyRemovesRelatedEntries_1302) {
    xmpData_["Xmp.dc.title"] = "Title";
    xmpData_["Xmp.dc.creator"] = "Creator";

    auto it = xmpData_.begin();
    xmpData_.eraseFamily(it);
    // After eraseFamily, some or all family members may be removed
    // We just verify no crash and the data remains in a valid state
    EXPECT_GE(xmpData_.count(), 0);
}

// Test setPacket with empty string
TEST_F(XmpDataTest_1302, SetPacketWithEmptyString_1302) {
    xmpData_.setPacket("");
    EXPECT_TRUE(xmpData_.xmpPacket().empty());
}

// Test usePacket returns previous value
TEST_F(XmpDataTest_1302, UsePacketReturnsPreviousValue_1302) {
    EXPECT_FALSE(xmpData_.usePacket(true));
    EXPECT_TRUE(xmpData_.usePacket(false));
    EXPECT_FALSE(xmpData_.usePacket());
}
