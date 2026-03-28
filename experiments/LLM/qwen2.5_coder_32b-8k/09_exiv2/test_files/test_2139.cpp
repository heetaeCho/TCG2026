#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XMPMeta.h"



using namespace std;

using ::testing::_;

using ::testing::InvokeWithoutArgs;

using ::testing::Return;



// Mocking the XMP_TextOutputProc function signature

class MockTextOutputProc {

public:

    MOCK_METHOD(void, OutProcNewlineMock, (), ());

    MOCK_METHOD(void, OutProcLiteralMock, (XMP_StringPtr), ());

    MOCK_METHOD(void, OutProcNCharsMock, (const char*, size_t), ());

    MOCK_METHOD(void, OutProcPaddingMock, (size_t), ());

    MOCK_METHOD(void, DumpClearStringMock, (XMP_StringPtr, XMP_TextOutputProc, void*), ());



    static void OutProcNewline() {

        instance()->OutProcNewlineMock();

    }



    static void OutProcLiteral(XMP_StringPtr str) {

        instance()->OutProcLiteralMock(str);

    }



    static void OutProcNChars(const char* chars, size_t count) {

        instance()->OutProcNCharsMock(chars, count);

    }



    static void OutProcPadding(size_t count) {

        instance()->OutProcPaddingMock(count);

    }



    static void DumpClearString(XMP_StringPtr str, XMP_TextOutputProc outProc, void* refCon) {

        instance()->DumpClearStringMock(str, outProc, refCon);

    }



private:

    MockTextOutputProc() = default;

    ~MockTextOutputProc() = default;



    static MockTextOutputProc* instance() {

        static MockTextOutputProc mockInstance;

        return &mockInstance;

    }

};



XMP_TextOutputProc OutProcNewline = MockTextOutputProc::OutProcNewline;

XMP_TextOutputProc OutProcLiteral = MockTextOutputProc::OutProcLiteral;

XMP_TextOutputProc OutProcNChars = MockTextOutputProc::OutProcNChars;

XMP_TextOutputProc OutProcPadding = MockTextOutputProc::OutProcPadding;

XMP_TextOutputProc DumpClearString = MockTextOutputProc::DumpClearString;



TEST(DumpStringMapTest_2139, EmptyMap_2139) {

    XMP_StringMap map;

    const char* label = "Label";

    void* refCon = nullptr;



    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNewlineMock()).Times(2);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcLiteralMock("Label"));

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(_, _)).Times(0);



    XMP_Status status = DumpStringMap(map, label, OutProcNewline, refCon);

}



TEST(DumpStringMapTest_2139, SingleEntry_2139) {

    XMP_StringMap map;

    map["key"] = "value";

    const char* label = "Label";

    void* refCon = nullptr;



    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNewlineMock()).Times(3);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcLiteralMock("Label"));

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("key", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(0));

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value", _, _)).Times(1);



    XMP_Status status = DumpStringMap(map, label, OutProcNewline, refCon);

}



TEST(DumpStringMapTest_2139, MultipleEntries_2139) {

    XMP_StringMap map;

    map["key1"] = "value1";

    map["longerKey"] = "value2";

    const char* label = "Label";

    void* refCon = nullptr;



    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNewlineMock()).Times(4);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcLiteralMock("Label"));

    

    // Key1

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("key1", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(6)); // Padding for "longerKey" - "key1"

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value1", _, _)).Times(1);



    // LongerKey

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("longerKey", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(0)); // No padding needed

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value2", _, _)).Times(1);



    XMP_Status status = DumpStringMap(map, label, OutProcNewline, refCon);

}



TEST(DumpStringMapTest_2139, LongestKeyAtEnd_2139) {

    XMP_StringMap map;

    map["key1"] = "value1";

    map["key2"] = "value2";

    map["longerKey"] = "value3";

    const char* label = "Label";

    void* refCon = nullptr;



    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNewlineMock()).Times(5);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcLiteralMock("Label"));



    // Key1

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("key1", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(6)); // Padding for "longerKey" - "key1"

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value1", _, _)).Times(1);



    // Key2

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("key2", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(6)); // Padding for "longerKey" - "key2"

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value2", _, _)).Times(1);



    // LongerKey

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock("  ", 2));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("longerKey", _, _)).Times(1);

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcPaddingMock(0)); // No padding needed

    EXPECT_CALL(*MockTextOutputProc::instance(), OutProcNCharsMock(" => ", 4));

    EXPECT_CALL(*MockTextOutputProc::instance(), DumpClearStringMock("value3", _, _)).Times(1);



    XMP_Status status = DumpStringMap(map, label, OutProcNewline, refCon);

}
