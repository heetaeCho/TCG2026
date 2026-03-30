// TEST_ID: 91
#include <cstdint>
#include <limits>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class QueryAttributeInt64Test_91 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem = nullptr;

    void SetUp() override {
        // Create a simple document with a root element.
        ASSERT_EQ(XML_SUCCESS, doc.Parse("<root/>"));
        elem = doc.FirstChildElement("root");
        ASSERT_NE(nullptr, elem);
    }
};

TEST_F(QueryAttributeInt64Test_91, ReturnsSameResultAsQueryInt64AttributeOnSuccess_91) {
    const char* kName = "a";
    const int64_t kExpected = 1234567890123LL;
    elem->SetAttribute(kName, kExpected);

    int64_t v1 = 0;
    int64_t v2 = 0;

    const XMLError e1 = elem->QueryAttribute(kName, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(kName, &v2);

    EXPECT_EQ(e2, e1);
    if (e1 == XML_SUCCESS) {
        EXPECT_EQ(kExpected, v1);
        EXPECT_EQ(kExpected, v2);
    }
}

TEST_F(QueryAttributeInt64Test_91, ReturnsSameResultAsQueryInt64AttributeWhenMissingAttribute_91) {
    const char* kMissing = "does_not_exist";

    int64_t v1 = 111;
    int64_t v2 = 222;

    const XMLError e1 = elem->QueryAttribute(kMissing, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(kMissing, &v2);

    EXPECT_EQ(e2, e1);
}

TEST_F(QueryAttributeInt64Test_91, HandlesInt64MaxConsistently_91) {
    const char* kName = "maxv";
    const int64_t kExpected = (std::numeric_limits<int64_t>::max)();
    elem->SetAttribute(kName, kExpected);

    int64_t v1 = 0;
    int64_t v2 = 0;

    const XMLError e1 = elem->QueryAttribute(kName, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(kName, &v2);

    EXPECT_EQ(e2, e1);
    if (e1 == XML_SUCCESS) {
        EXPECT_EQ(kExpected, v1);
        EXPECT_EQ(kExpected, v2);
    }
}

TEST_F(QueryAttributeInt64Test_91, HandlesInt64MinConsistently_91) {
    const char* kName = "minv";
    const int64_t kExpected = (std::numeric_limits<int64_t>::min)();
    elem->SetAttribute(kName, kExpected);

    int64_t v1 = 0;
    int64_t v2 = 0;

    const XMLError e1 = elem->QueryAttribute(kName, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(kName, &v2);

    EXPECT_EQ(e2, e1);
    if (e1 == XML_SUCCESS) {
        EXPECT_EQ(kExpected, v1);
        EXPECT_EQ(kExpected, v2);
    }
}

TEST_F(QueryAttributeInt64Test_91, ReturnsSameErrorAsQueryInt64AttributeForNullName_91) {
    int64_t v1 = 0;
    int64_t v2 = 0;

    const XMLError e1 = elem->QueryAttribute(nullptr, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(nullptr, &v2);

    EXPECT_EQ(e2, e1);
}

TEST_F(QueryAttributeInt64Test_91, ReturnsSameErrorAsQueryInt64AttributeForNullValuePointer_91) {
    const char* kName = "a";
    elem->SetAttribute(kName, static_cast<int64_t>(7));

    const XMLError e1 = elem->QueryAttribute(kName, static_cast<int64_t*>(nullptr));
    const XMLError e2 = elem->QueryInt64Attribute(kName, static_cast<int64_t*>(nullptr));

    EXPECT_EQ(e2, e1);
}

TEST_F(QueryAttributeInt64Test_91, ReturnsSameResultAsQueryInt64AttributeAfterAttributeUpdate_91) {
    const char* kName = "a";
    elem->SetAttribute(kName, static_cast<int64_t>(1));
    elem->SetAttribute(kName, static_cast<int64_t>(42));

    int64_t v1 = 0;
    int64_t v2 = 0;

    const XMLError e1 = elem->QueryAttribute(kName, &v1);
    const XMLError e2 = elem->QueryInt64Attribute(kName, &v2);

    EXPECT_EQ(e2, e1);
    if (e1 == XML_SUCCESS) {
        EXPECT_EQ(42, v1);
        EXPECT_EQ(42, v2);
    }
}
