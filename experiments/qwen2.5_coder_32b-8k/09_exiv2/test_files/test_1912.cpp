#include <gtest/gtest.h>

#include "XMPIterator.hpp"

#include "WXMP_Common.hpp"



// Mock class for XMPMeta to be used as a dependency if needed.

class MockXMPMeta {

public:

    MOCK_METHOD0(GetIterator, XMPIterator*(const XMP_StringPtr, const XMP_StringPtr, XMP_OptionBits));

};



TEST_F(WXMPIteratorTest_1912, Next_ReturnsTrueForValidIteration_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propPath, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, &propValue, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_ReturnsFalseForEndOfIteration_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propPath, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    // Assume first call returns true

    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, &propValue, &valueSize, &propOptions, &wResult);

    

    // Second call should return false indicating end of iteration

    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, &propValue, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, false);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesNullSchemaNSPointer_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr propPath, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    WXMPIterator_Next_1(iterRef, nullptr, &nsSize, &propPath, &pathSize, &propValue, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesNullPropPathPointer_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, nullptr, &pathSize, &propValue, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesNullPropValuePointer_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propPath;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, nullptr, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesNullPropOptionsPointer_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propPath, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;



    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, &propValue, &valueSize, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesNullAllPointers_1912) {

    XMPMeta xmpObj;

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    WXMPIterator_Next_1(iterRef, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &wResult);



    EXPECT_EQ(wResult.int32Result, true);

}



TEST_F(WXMPIteratorTest_1912, Next_HandlesEmptyXMPObject_1912) {

    XMPMeta xmpObj;  // Assuming this is an empty XMP object

    XMPIteratorRef iterRef = xmpObj.GetIterator("", "", 0);

    WXMP_Result wResult;



    XMP_StringPtr schemaNS, propPath, propValue;

    XMP_StringLen nsSize, pathSize, valueSize;

    XMP_OptionBits propOptions;



    WXMPIterator_Next_1(iterRef, &schemaNS, &nsSize, &propPath, &pathSize, &propValue, &valueSize, &propOptions, &wResult);



    EXPECT_EQ(wResult.int32Result, false);

}
