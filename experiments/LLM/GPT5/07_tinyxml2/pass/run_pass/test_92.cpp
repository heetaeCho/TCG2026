// TEST_ID 92
#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class QueryAttributeUint64Test_92 : public ::testing::Test {
protected:
    void SetUp() override {
        elem = doc.NewElement("root");
        ASSERT_NE(elem, nullptr);
        doc.InsertEndChild(elem);
    }

    // Calls both APIs and verifies they behave identically (return code + output value).
    void ExpectSameAsQueryUnsigned64(const char* name,
                                    uint64_t* out_queryAttribute,
                                    uint64_t* out_queryUnsigned64,
                                    XMLError* out_err_queryAttribute,
                                    XMLError* out_err_queryUnsigned64) const {
        ASSERT_NE(out_queryAttribute, nullptr);
        ASSERT_NE(out_queryUnsigned64, nullptr);
        ASSERT_NE(out_err_queryAttribute, nullptr);
        ASSERT_NE(out_err_queryUnsigned64, nullptr);

        *out_err_queryAttribute = elem->QueryAttribute(name, out_queryAttribute);
        *out_err_queryUnsigned64 = elem->QueryUnsigned64Attribute(name, out_queryUnsigned64);

        EXPECT_EQ(*out_err_queryAttribute, *out_err_queryUnsigned64);
        EXPECT_EQ(*out_queryAttribute, *out_queryUnsigned64);
    }

    XMLDocument doc;
    XMLElement* elem = nullptr;
};

TEST_F(QueryAttributeUint64Test_92, ValidAttributeValue_MatchesQueryUnsigned64Attribute_92) {
    const char* kName = "u64";
    const uint64_t kValue = 1234567890123456789ULL;

    elem->SetAttribute(kName, kValue);

    uint64_t v1 = 0, v2 = 0;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kName, &v1, &v2, &e1, &e2);
    EXPECT_EQ(v1, kValue);
}

TEST_F(QueryAttributeUint64Test_92, ZeroValue_MatchesQueryUnsigned64Attribute_92) {
    const char* kName = "zero";
    elem->SetAttribute(kName, static_cast<uint64_t>(0));

    uint64_t v1 = 999, v2 = 111;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kName, &v1, &v2, &e1, &e2);
    EXPECT_EQ(v1, 0u);
}

TEST_F(QueryAttributeUint64Test_92, MaxUint64Value_MatchesQueryUnsigned64Attribute_92) {
    const char* kName = "max";
    const uint64_t kMax = (std::numeric_limits<uint64_t>::max)();
    elem->SetAttribute(kName, kMax);

    uint64_t v1 = 0, v2 = 0;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kName, &v1, &v2, &e1, &e2);
    EXPECT_EQ(v1, kMax);
}

TEST_F(QueryAttributeUint64Test_92, MissingAttribute_ReturnsSameErrorAndSameOutput_92) {
    const char* kMissing = "does_not_exist";

    // Seed different initial values so we can still compare equality after the calls
    // without assuming whether outputs are modified on error.
    uint64_t v1 = 0x1111111111111111ULL;
    uint64_t v2 = 0x2222222222222222ULL;

    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kMissing, &v1, &v2, &e1, &e2);
}

TEST_F(QueryAttributeUint64Test_92, EmptyName_ReturnsSameBehaviorAsQueryUnsigned64Attribute_92) {
    // Boundary-ish input: empty attribute name.
    const char* kEmpty = "";

    uint64_t v1 = 7, v2 = 9;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kEmpty, &v1, &v2, &e1, &e2);
}

TEST_F(QueryAttributeUint64Test_92, NonNumericAttributeText_ReturnsSameErrorAndSameOutput_92) {
    const char* kName = "bad";
    elem->SetAttribute(kName, "not_a_number");

    uint64_t v1 = 42, v2 = 84;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kName, &v1, &v2, &e1, &e2);
}

TEST_F(QueryAttributeUint64Test_92, OverflowingNumericText_ReturnsSameErrorAndSameOutput_92) {
    const char* kName = "overflow";
    // One more than UINT64_MAX as text.
    elem->SetAttribute(kName, "18446744073709551616");

    uint64_t v1 = 123, v2 = 456;
    XMLError e1 = XML_ERROR_FILE_READ_ERROR, e2 = XML_ERROR_FILE_READ_ERROR;
    ExpectSameAsQueryUnsigned64(kName, &v1, &v2, &e1, &e2);
}

}  // namespace
