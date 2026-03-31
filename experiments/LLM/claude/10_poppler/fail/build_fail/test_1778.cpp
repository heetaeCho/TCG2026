#include <gtest/gtest.h>
#include "poppler/StructElement.h"

class AttributeOwnerTest_1778 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Attribute objects can be created with valid Owner values
TEST_F(AttributeOwnerTest_1778, OwnerXML100_1778) {
    // Verify that XML_1_00 owner is a valid owner enum value
    Attribute::Owner owner = Attribute::XML_1_00;
    EXPECT_EQ(owner, Attribute::XML_1_00);
}

TEST_F(AttributeOwnerTest_1778, OwnerHTML320_1778) {
    Attribute::Owner owner = Attribute::HTML_3_20;
    EXPECT_EQ(owner, Attribute::HTML_3_20);
}

TEST_F(AttributeOwnerTest_1778, OwnerHTML401_1778) {
    Attribute::Owner owner = Attribute::HTML_4_01;
    EXPECT_EQ(owner, Attribute::HTML_4_01);
}

TEST_F(AttributeOwnerTest_1778, OwnerOEB100_1778) {
    Attribute::Owner owner = Attribute::OEB_1_00;
    EXPECT_EQ(owner, Attribute::OEB_1_00);
}

TEST_F(AttributeOwnerTest_1778, OwnerRTF105_1778) {
    Attribute::Owner owner = Attribute::RTF_1_05;
    EXPECT_EQ(owner, Attribute::RTF_1_05);
}

TEST_F(AttributeOwnerTest_1778, OwnerCSS100_1778) {
    Attribute::Owner owner = Attribute::CSS_1_00;
    EXPECT_EQ(owner, Attribute::CSS_1_00);
}

TEST_F(AttributeOwnerTest_1778, OwnerCSS200_1778) {
    Attribute::Owner owner = Attribute::CSS_2_00;
    EXPECT_EQ(owner, Attribute::CSS_2_00);
}

TEST_F(AttributeOwnerTest_1778, OwnerLayout_1778) {
    Attribute::Owner owner = Attribute::Layout;
    EXPECT_EQ(owner, Attribute::Layout);
}

TEST_F(AttributeOwnerTest_1778, OwnerPrintField_1778) {
    Attribute::Owner owner = Attribute::PrintField;
    EXPECT_EQ(owner, Attribute::PrintField);
}

TEST_F(AttributeOwnerTest_1778, OwnerTable_1778) {
    Attribute::Owner owner = Attribute::Table;
    EXPECT_EQ(owner, Attribute::Table);
}

TEST_F(AttributeOwnerTest_1778, OwnerList_1778) {
    Attribute::Owner owner = Attribute::List;
    EXPECT_EQ(owner, Attribute::List);
}

TEST_F(AttributeOwnerTest_1778, OwnerUserProperties_1778) {
    Attribute::Owner owner = Attribute::UserProperties;
    EXPECT_EQ(owner, Attribute::UserProperties);
}

// Test that all known Owner enum values are distinct
TEST_F(AttributeOwnerTest_1778, AllOwnersDistinct_1778) {
    std::vector<Attribute::Owner> owners = {
        Attribute::XML_1_00, Attribute::HTML_3_20, Attribute::HTML_4_01,
        Attribute::OEB_1_00, Attribute::RTF_1_05, Attribute::CSS_1_00,
        Attribute::CSS_2_00, Attribute::Layout, Attribute::PrintField,
        Attribute::Table, Attribute::List, Attribute::UserProperties
    };

    for (size_t i = 0; i < owners.size(); ++i) {
        for (size_t j = i + 1; j < owners.size(); ++j) {
            EXPECT_NE(owners[i], owners[j])
                << "Owner at index " << i << " should differ from owner at index " << j;
        }
    }
}

// Test Attribute::getOwnerName for known owners
TEST_F(AttributeOwnerTest_1778, GetOwnerNameLayout_1778) {
    const char *name = Attribute::getOwnerName(Attribute::Layout);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Layout");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameTable_1778) {
    const char *name = Attribute::getOwnerName(Attribute::Table);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "Table");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameList_1778) {
    const char *name = Attribute::getOwnerName(Attribute::List);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "List");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameUserProperties_1778) {
    const char *name = Attribute::getOwnerName(Attribute::UserProperties);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "UserProperties");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNamePrintField_1778) {
    const char *name = Attribute::getOwnerName(Attribute::PrintField);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PrintField");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameXML100_1778) {
    const char *name = Attribute::getOwnerName(Attribute::XML_1_00);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "XML-1.00");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameHTML320_1778) {
    const char *name = Attribute::getOwnerName(Attribute::HTML_3_20);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "HTML-3.20");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameHTML401_1778) {
    const char *name = Attribute::getOwnerName(Attribute::HTML_4_01);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "HTML-4.01");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameCSS100_1778) {
    const char *name = Attribute::getOwnerName(Attribute::CSS_1_00);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "CSS-1.00");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameCSS200_1778) {
    const char *name = Attribute::getOwnerName(Attribute::CSS_2_00);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "CSS-2.00");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameOEB100_1778) {
    const char *name = Attribute::getOwnerName(Attribute::OEB_1_00);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "OEB-1.00");
}

TEST_F(AttributeOwnerTest_1778, GetOwnerNameRTF105_1778) {
    const char *name = Attribute::getOwnerName(Attribute::RTF_1_05);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "RTF-1.05");
}

// Boundary: test with an invalid/unknown owner value
TEST_F(AttributeOwnerTest_1778, GetOwnerNameUnknownReturnsNull_1778) {
    const char *name = Attribute::getOwnerName(static_cast<Attribute::Owner>(9999));
    EXPECT_EQ(name, nullptr);
}
