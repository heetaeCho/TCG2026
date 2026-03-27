#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Page.h"

#include "TestProjects/poppler/poppler/Stream.h"



using namespace testing;



class MockPageAttrs : public PageAttrs {

public:

    MOCK_METHOD(Stream*, getMetadata, (), (const, override));

};



class PageTest_717 : public Test {

protected:

    NiceMock<MockPageAttrs> mock_attrs;

    Page page{nullptr, 0, std::move(Object()), Ref{}, &mock_attrs};

};



TEST_F(PageTest_717, GetMetadata_ReturnsNonNullStream_717) {

    auto* expected_stream = new Stream();

    EXPECT_CALL(mock_attrs, getMetadata()).WillOnce(Return(expected_stream));

    

    Stream* actual_stream = page.getMetadata();



    EXPECT_EQ(actual_stream, expected_stream);

}



TEST_F(PageTest_717, GetMetadata_CallsGetMetadataOnAttrs_717) {

    EXPECT_CALL(mock_attrs, getMetadata());



    page.getMetadata();

}
