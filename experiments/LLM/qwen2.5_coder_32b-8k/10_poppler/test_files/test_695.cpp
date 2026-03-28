#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Page.h"

#include "poppler/Object.h"



using ::testing::Return;

using ::testing::IsNull;



class PageAttrsTest : public ::testing::Test {

protected:

    Dict mockDict;

    PageAttrs pageAttrs{nullptr, &mockDict};

};



TEST_F(PageAttrsTest, GetMetadata_ReturnsNull_695) {

    EXPECT_CALL(mockDict, lookupNF("Metadata")).WillOnce(Return(Object::null()));

    Stream* metadata = pageAttrs.getMetadata();

    EXPECT_THAT(metadata, IsNull());

}



TEST_F(PageAttrsTest, GetMetadata_ReturnsStream_695) {

    auto mockStream = std::make_unique<Stream>();

    Object mockObject(std::move(mockStream));

    EXPECT_CALL(mockDict, lookupNF("Metadata")).WillOnce(ReturnRef(mockObject));



    Stream* metadata = pageAttrs.getMetadata();

    EXPECT_THAT(metadata, Not(IsNull()));

}



TEST_F(PageAttrsTest, GetMetadata_ReturnsNonStream_695) {

    Object mockObject("some_non_stream");

    EXPECT_CALL(mockDict, lookupNF("Metadata")).WillOnce(ReturnRef(mockObject));



    Stream* metadata = pageAttrs.getMetadata();

    EXPECT_THAT(metadata, IsNull());

}
