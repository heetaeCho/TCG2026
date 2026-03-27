#include <gtest/gtest.h>

#include <exiv2/properties.hpp>



namespace Exiv2 {

    struct XmpKey {

        struct Impl {

            std::string property_;

            Impl() = default;

            Impl(const std::string & prefix, const std::string & property);

            void decomposeKey(const std::string & key);

        };

        XmpKey(const std::string & key);

        XmpKey(const std::string & prefix, const std::string & property);

        XmpKey(const XmpKey & rhs);

        ~XmpKey() override;

        XmpKey & operator= (const XmpKey & rhs);

        const std::string key () const override;

        const char * familyName () const override;

        const std::string groupName () const override;

        const std::string tagName () const override;

        const std::string tagLabel () const override;

        const std::string tagDesc () const override;

        const uint16_t tag () const override;

        const std::string ns () const;

    };

}



using namespace Exiv2;



// Test Fixture

class XmpKeyTest_1261 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if any

    }



    void TearDown() override {

        // Teardown code, if any

    }

};



// Test normal operation with a valid key

TEST_F(XmpKeyTest_1261, ValidKeyConstruction_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.key(), "Iptc.prefix.property");

}



// Test normal operation with a valid full key string

TEST_F(XmpKeyTest_1261, FullKeyStringConstruction_1261) {

    XmpKey xmpKey("Iptc.prefix.property");

    EXPECT_EQ(xmpKey.key(), "Iptc.prefix.property");

}



// Test boundary condition with empty prefix and property

TEST_F(XmpKeyTest_1261, EmptyPrefixAndProperty_1261) {

    XmpKey xmpKey("", "");

    EXPECT_EQ(xmpKey.key(), "Iptc..");

}



// Test boundary condition with empty prefix only

TEST_F(XmpKeyTest_1261, EmptyPrefixOnly_1261) {

    XmpKey xmpKey("", "property");

    EXPECT_EQ(xmpKey.key(), "Iptc..property");

}



// Test boundary condition with empty property only

TEST_F(XmpKeyTest_1261, EmptyPropertyOnly_1261) {

    XmpKey xmpKey("prefix", "");

    EXPECT_EQ(xmpKey.key(), "Iptc.prefix.");

}



// Test copy constructor

TEST_F(XmpKeyTest_1261, CopyConstructor_1261) {

    XmpKey originalXmpKey("prefix", "property");

    XmpKey copiedXmpKey(originalXmpKey);

    EXPECT_EQ(copiedXmpKey.key(), "Iptc.prefix.property");

}



// Test assignment operator

TEST_F(XmpKeyTest_1261, AssignmentOperator_1261) {

    XmpKey originalXmpKey("prefix", "property");

    XmpKey assignedXmpKey = originalXmpKey;

    EXPECT_EQ(assignedXmpKey.key(), "Iptc.prefix.property");

}



// Test familyName method

TEST_F(XmpKeyTest_1261, FamilyNameMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_STREQ(xmpKey.familyName(), "Iptc");

}



// Test groupName method (assuming it returns an empty string as not specified in the provided code)

TEST_F(XmpKeyTest_1261, GroupNameMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.groupName(), "");

}



// Test tagName method (assuming it returns an empty string as not specified in the provided code)

TEST_F(XmpKeyTest_1261, TagNameMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.tagName(), "");

}



// Test tagLabel method (assuming it returns an empty string as not specified in the provided code)

TEST_F(XmpKeyTest_1261, TagLabelMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.tagLabel(), "");

}



// Test tagDesc method (assuming it returns an empty string as not specified in the provided code)

TEST_F(XmpKeyTest_1261, TagDescMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.tagDesc(), "");

}



// Test tag method (assuming it returns 0 as not specified in the provided code)

TEST_F(XmpKeyTest_1261, TagMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.tag(), 0);

}



// Test ns method (assuming it returns an empty string as not specified in the provided code)

TEST_F(XmpKeyTest_1261, NsMethod_1261) {

    XmpKey xmpKey("prefix", "property");

    EXPECT_EQ(xmpKey.ns(), "");

}
