// TEST_ID: 68
#include <gtest/gtest.h>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

tinyxml2::XMLUnknown* FindFirstUnknown(tinyxml2::XMLNode* start) {
    for (tinyxml2::XMLNode* n = start; n != nullptr; n = n->NextSibling()) {
        if (auto* u = n->ToUnknown()) {
            return u;
        }
    }
    return nullptr;
}

class XMLUnknownTest_68 : public ::testing::Test {
protected:
    // Use an XML that is expected to produce an XMLUnknown node (e.g., DOCTYPE).
    static tinyxml2::XMLUnknown* ParseAndGetUnknown(tinyxml2::XMLDocument& doc) {
        // Note: We intentionally do not assume internal parsing behavior beyond the public
        // observation that an XMLUnknown node can exist in a document.
        const char* xml = "<!DOCTYPE root [ <!ELEMENT root ANY> ]>\n<root/>";

        const tinyxml2::XMLError err = doc.Parse(xml);
        EXPECT_EQ(err, tinyxml2::XML_SUCCESS);

        // Search from the document's first child across siblings for an unknown node.
        tinyxml2::XMLUnknown* unknown = FindFirstUnknown(doc.FirstChild());
        return unknown;
    }
};

}  // namespace

TEST_F(XMLUnknownTest_68, ToUnknown_ReturnsThisPointer_68) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLUnknown* unknown = ParseAndGetUnknown(doc);

    ASSERT_NE(unknown, nullptr);
    EXPECT_EQ(unknown->ToUnknown(), unknown);
}

TEST_F(XMLUnknownTest_68, ToUnknown_ViaBasePointerStillReturnsSameObject_68) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLUnknown* unknown = ParseAndGetUnknown(doc);

    ASSERT_NE(unknown, nullptr);

    tinyxml2::XMLNode* asNode = unknown;  // Upcast to verify virtual dispatch.
    tinyxml2::XMLUnknown* result = asNode->ToUnknown();

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, unknown);
}

TEST_F(XMLUnknownTest_68, ToUnknown_MultipleCallsAreStable_68) {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLUnknown* unknown = ParseAndGetUnknown(doc);

    ASSERT_NE(unknown, nullptr);

    tinyxml2::XMLUnknown* r1 = unknown->ToUnknown();
    tinyxml2::XMLUnknown* r2 = unknown->ToUnknown();
    tinyxml2::XMLUnknown* r3 = unknown->ToUnknown();

    EXPECT_EQ(r1, unknown);
    EXPECT_EQ(r2, unknown);
    EXPECT_EQ(r3, unknown);
}
