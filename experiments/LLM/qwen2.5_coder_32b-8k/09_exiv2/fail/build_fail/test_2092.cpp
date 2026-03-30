#include <gtest/gtest.h>

#include "XMPMeta.hpp"



using namespace std;



class ExpatAdapterTest_2092 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources or state before each test.

    }



    void TearDown() override {

        // Clean up any resources or state after each test.

    }

};



TEST_F(ExpatAdapterTest_2092, NormalOperation_2092) {

    EXPECT_CALL(XMPMeta::RegisterNamespace, (StrEq("http://purl.org/dc/1.1/"), StrEq("_dflt_"))).Times(0);

    EXPECT_CALL(XMPMeta::RegisterNamespace, (StrEq("http://purl.org/dc/elements/1.1/"), StrEq("_dflt_"))).Times(1);



    StartNamespaceDeclHandler(nullptr, nullptr, "http://purl.org/dc/1.1/");

}



TEST_F(ExpatAdapterTest_2092, DefaultPrefix_2092) {

    EXPECT_CALL(XMPMeta::RegisterNamespace, (StrEq("http://example.com/namespace"), StrEq("_dflt_"))).Times(1);



    StartNamespaceDeclHandler(nullptr, nullptr, "http://example.com/namespace");

}



TEST_F(ExpatAdapterTest_2092, NonDefaultPrefix_2092) {

    EXPECT_CALL(XMPMeta::RegisterNamespace, (StrEq("http://example.com/namespace"), StrEq("prefix"))).Times(1);



    StartNamespaceDeclHandler(nullptr, "prefix", "http://example.com/namespace");

}



TEST_F(ExpatAdapterTest_2092, EmptyURI_2092) {

    EXPECT_CALL(XMPMeta::RegisterNamespace, (_, _)).Times(0);



    StartNamespaceDeclHandler(nullptr, nullptr, "");

}



TEST_F(ExpatAdapterTest_2092, NullURI_2092) {

    EXPECT_CALL(XMPMeta::RegisterNamespace, (_, _)).Times(0);



    StartNamespaceDeclHandler(nullptr, nullptr, nullptr);

}
