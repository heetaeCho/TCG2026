#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <memory>

using namespace Exiv2;

class XmpdatumImplTest_1277 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Xmpdatum can be constructed with a valid XmpKey
TEST_F(XmpdatumImplTest_1277, ConstructWithValidKey_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test that Xmpdatum copy constructor works correctly
TEST_F(XmpdatumImplTest_1277, CopyConstructor_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum1(key);
    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test that Xmpdatum assignment operator works correctly
TEST_F(XmpdatumImplTest_1277, AssignmentOperator_1277) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum1(key1);
    Xmpdatum datum2(key2);
    datum2 = datum1;
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test self-assignment doesn't corrupt state
TEST_F(XmpdatumImplTest_1277, SelfAssignment_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    datum = datum;
    EXPECT_EQ(datum.key(), "Xmp.dc.title");
}

// Test that Xmpdatum can be constructed with a value
TEST_F(XmpdatumImplTest_1277, ConstructWithValue_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    datum.setValue("Test Value");
    EXPECT_EQ(datum.toString(), "Test Value");
}

// Test that after assignment, value is deep copied
TEST_F(XmpdatumImplTest_1277, AssignmentDeepCopiesValue_1277) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1);
    datum1.setValue("Value1");

    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2);
    datum2.setValue("Value2");

    datum2 = datum1;
    EXPECT_EQ(datum2.toString(), "Value1");
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
}

// Test that copy constructor deep copies value
TEST_F(XmpdatumImplTest_1277, CopyConstructorDeepCopiesValue_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum1(key);
    datum1.setValue("DeepCopyTest");

    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.toString(), "DeepCopyTest");

    // Modify datum1 and check datum2 is independent
    datum1.setValue("Modified");
    EXPECT_EQ(datum2.toString(), "DeepCopyTest");
    EXPECT_EQ(datum1.toString(), "Modified");
}

// Test that Xmpdatum with no value set
TEST_F(XmpdatumImplTest_1277, NoValueSet_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ(datum.count(), 0u);
}

// Test family name through Xmpdatum
TEST_F(XmpdatumImplTest_1277, FamilyName_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_STREQ(datum.familyName(), "Xmp");
}

// Test group name through Xmpdatum
TEST_F(XmpdatumImplTest_1277, GroupName_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ(datum.groupName(), "dc");
}

// Test tag name through Xmpdatum
TEST_F(XmpdatumImplTest_1277, TagName_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum(key);
    EXPECT_EQ(datum.tagName(), "title");
}

// Test assignment with datum that has no value
TEST_F(XmpdatumImplTest_1277, AssignmentFromNoValue_1277) {
    XmpKey key1("Xmp.dc.title");
    Xmpdatum datum1(key1);
    datum1.setValue("HasValue");

    XmpKey key2("Xmp.dc.description");
    Xmpdatum datum2(key2);
    // datum2 has no value

    datum1 = datum2;
    EXPECT_EQ(datum1.key(), "Xmp.dc.description");
    EXPECT_EQ(datum1.count(), 0u);
}

// Test copy constructor with datum that has no value
TEST_F(XmpdatumImplTest_1277, CopyConstructorFromNoValue_1277) {
    XmpKey key("Xmp.dc.title");
    Xmpdatum datum1(key);
    // datum1 has no value set

    Xmpdatum datum2(datum1);
    EXPECT_EQ(datum2.key(), "Xmp.dc.title");
    EXPECT_EQ(datum2.count(), 0u);
}

// Test XmpKey construction and basic properties
TEST_F(XmpdatumImplTest_1277, XmpKeyBasicProperties_1277) {
    XmpKey key("Xmp.dc.title");
    EXPECT_EQ(key.key(), "Xmp.dc.title");
    EXPECT_STREQ(key.familyName(), "Xmp");
    EXPECT_EQ(key.groupName(), "dc");
    EXPECT_EQ(key.tagName(), "title");
}

// Test XmpKey copy constructor
TEST_F(XmpdatumImplTest_1277, XmpKeyCopyConstructor_1277) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2(key1);
    EXPECT_EQ(key2.key(), "Xmp.dc.title");
}

// Test XmpKey assignment operator
TEST_F(XmpdatumImplTest_1277, XmpKeyAssignment_1277) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    key2 = key1;
    EXPECT_EQ(key2.key(), "Xmp.dc.title");
}

// Test XmpKey clone
TEST_F(XmpdatumImplTest_1277, XmpKeyClone_1277) {
    XmpKey key("Xmp.dc.title");
    auto cloned = key.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->key(), "Xmp.dc.title");
}

// Test multiple assignments in sequence
TEST_F(XmpdatumImplTest_1277, MultipleAssignments_1277) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");
    XmpKey key3("Xmp.dc.creator");

    Xmpdatum datum1(key1);
    datum1.setValue("Title");

    Xmpdatum datum2(key2);
    datum2.setValue("Description");

    Xmpdatum datum3(key3);
    datum3.setValue("Creator");

    datum1 = datum2;
    EXPECT_EQ(datum1.key(), "Xmp.dc.description");
    EXPECT_EQ(datum1.toString(), "Description");

    datum1 = datum3;
    EXPECT_EQ(datum1.key(), "Xmp.dc.creator");
    EXPECT_EQ(datum1.toString(), "Creator");
}

// Test that after assignment, modifying original doesn't affect copy (deep copy verification)
TEST_F(XmpdatumImplTest_1277, AssignmentIndependence_1277) {
    XmpKey key1("Xmp.dc.title");
    XmpKey key2("Xmp.dc.description");

    Xmpdatum datum1(key1);
    datum1.setValue("Original");

    Xmpdatum datum2(key2);
    datum2 = datum1;

    datum1.setValue("Modified");
    EXPECT_EQ(datum2.toString(), "Original");
    EXPECT_EQ(datum1.toString(), "Modified");
}
