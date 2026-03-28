#include <gtest/gtest.h>

#include "XMPIterator.hpp"



class XMPIteratorTest_1910 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize XMPIterator if needed

        XMPIterator::Initialize();

    }



    void TearDown() override {

        // Terminate XMPIterator if needed

        XMPIterator::Terminate();

    }

};



TEST_F(XMPIteratorTest_1910, DecrementRefCount_ValidPointer_1910) {

    XMPMeta xmpObj;

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "exampleProperty";

    XMPIteratorRef iterRef = new XMPIterator(xmpObj, schemaNS, propName, 0);



    WXMPIterator_DecrementRefCount_1(iterRef);



    // Assuming the object is deleted when ref count reaches 0

    EXPECT_EQ(iterRef, nullptr);

}



TEST_F(XMPIteratorTest_1910, DecrementRefCount_MultipleCalls_1910) {

    XMPMeta xmpObj;

    const char* schemaNS = "http://example.com/schema";

    const char* propName = "exampleProperty";

    XMPIteratorRef iterRef = new XMPIterator(xmpObj, schemaNS, propName, 0);



    WXMPIterator_DecrementRefCount_1(iterRef);

    EXPECT_NE(iterRef, nullptr); // Should not be deleted yet



    WXMPIterator_DecrementRefCount_1(iterRef);

    EXPECT_EQ(iterRef, nullptr); // Should be deleted now

}



TEST_F(XMPIteratorTest_1910, DecrementRefCount_ZeroRefs_1910) {

    XMPIteratorRef iterRef = new XMPIterator("http://example.com/schema", "exampleProperty", 0);

    WXMPIterator_DecrementRefCount_1(iterRef); // Ref count should be 0 now



    EXPECT_THROW(WXMPIterator_DecrementRefCount_1(iterRef), std::exception); // Should throw or handle invalid state

}



TEST_F(XMPIteratorTest_1910, DecrementRefCount_NullPointer_1910) {

    XMPIteratorRef iterRef = nullptr;

    EXPECT_NO_THROW(WXMPIterator_DecrementRefCount_1(iterRef)); // Should not crash with null pointer

}
