#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta.hpp"

#include "WXMP_Common.hpp"



using namespace testing;



// Mock function for XMP_TextOutputProc

class MockTextOutputProc {

public:

    MOCK_METHOD3(Call, void(void* refCon, const char* buffer, XMP_StringLen count));

};



void MockTextOutputProcCaller(void* refCon, const char* buffer, XMP_StringLen count) {

    static_cast<MockTextOutputProc*>(refCon)->Call(refCon, buffer, count);

}



class WXMPMetaTest : public Test {

protected:

    XMPMetaRef xmpRef;

    WXMP_Result wResult;



    void SetUp() override {

        // Assuming there's a way to create an XMPMetaRef, if not, this will need adjustment

        xmpRef = reinterpret_cast<XMPMetaRef>(new XMPMeta());

    }



    void TearDown() override {

        delete reinterpret_cast<XMPMeta*>(xmpRef);

    }

};



TEST_F(WXMPMetaTest_2035, DumpObjectWithValidOutputProc_2035) {

    MockTextOutputProc mockOutProc;

    EXPECT_CALL(mockOutProc, Call(_, _, _)).Times(AtLeast(1));



    WXMPMeta_DumpObject_1(xmpRef, &MockTextOutputProcCaller, &mockOutProc, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // Assuming success is represented by 0

}



TEST_F(WXMPMetaTest_2035, DumpObjectWithNullOutputProc_2035) {

    WXMPMeta_DumpObject_1(xmpRef, nullptr, nullptr, &wResult);

    EXPECT_EQ(wResult.int32Result, kXMPErr_BadParam);

}



TEST_F(WXMPMetaTest_2035, DumpObjectWithNonNullRefCon_2035) {

    MockTextOutputProc mockOutProc;

    void* refCon = reinterpret_cast<void*>(&mockOutProc);

    EXPECT_CALL(mockOutProc, Call(refCon, _, _)).Times(AtLeast(1));



    WXMPMeta_DumpObject_1(xmpRef, &MockTextOutputProcCaller, refCon, &wResult);

    EXPECT_EQ(wResult.int32Result, 0); // Assuming success is represented by 0

}
