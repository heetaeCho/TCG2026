#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "GooString.h"



using ::testing::Return;

using ::testing::_;



class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(std::unique_ptr<LinkDest>, findDest, (const GooString*), (override));

};



TEST_F(MockPopplerDocumentTest_2159, FindDest_ReturnsValidPointerForExistingLink_2159) {

    MockPopplerDocument mockDoc;

    const gchar* link_name = "existing_link";

    gsize len;

    guint8* data = poppler_named_dest_to_bytestring(link_name, &len);

    GooString g_link_name((const char*)data, (int)len);

    g_free(data);



    auto mockLinkDest = std::make_unique<LinkDest>();

    EXPECT_CALL(mockDoc, findDest(&g_link_name)).WillOnce(Return(std::move(mockLinkDest)));



    PopplerDest* dest = poppler_document_find_dest(&mockDoc, link_name);

    ASSERT_NE(dest, nullptr);

    _poppler_dest_free(dest);

}



TEST_F(MockPopplerDocumentTest_2159, FindDest_ReturnsNullForNonExistingLink_2159) {

    MockPopplerDocument mockDoc;

    const gchar* link_name = "non_existing_link";

    gsize len;

    guint8* data = poppler_named_dest_to_bytestring(link_name, &len);

    GooString g_link_name((const char*)data, (int)len);

    g_free(data);



    EXPECT_CALL(mockDoc, findDest(&g_link_name)).WillOnce(Return(nullptr));



    PopplerDest* dest = poppler_document_find_dest(&mockDoc, link_name);

    ASSERT_EQ(dest, nullptr);

}



TEST_F(MockPopplerDocumentTest_2159, FindDest_ReturnsNullForNullLinkName_2159) {

    MockPopplerDocument mockDoc;

    const gchar* link_name = nullptr;



    PopplerDest* dest = poppler_document_find_dest(&mockDoc, link_name);

    ASSERT_EQ(dest, nullptr);

}



TEST_F(MockPopplerDocumentTest_2159, FindDest_ReturnsNullForInvalidDocument_2159) {

    MockPopplerDocument* mockDoc = nullptr;

    const gchar* link_name = "existing_link";



    PopplerDest* dest = poppler_document_find_dest(mockDoc, link_name);

    ASSERT_EQ(dest, nullptr);

}



TEST_F(MockPopplerDocumentTest_2159, FindDest_HandlesEmptyLinkNameCorrectly_2159) {

    MockPopplerDocument mockDoc;

    const gchar* link_name = "";

    gsize len;

    guint8* data = poppler_named_dest_to_bytestring(link_name, &len);

    GooString g_link_name((const char*)data, (int)len);

    g_free(data);



    EXPECT_CALL(mockDoc, findDest(&g_link_name)).WillOnce(Return(nullptr));



    PopplerDest* dest = poppler_document_find_dest(&mockDoc, link_name);

    ASSERT_EQ(dest, nullptr);

}
