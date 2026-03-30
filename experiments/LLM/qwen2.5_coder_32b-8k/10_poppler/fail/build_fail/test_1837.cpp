#include <gtest/gtest.h>

#include "JBIG2Stream.h"

#include <gmock/gmock.h>



using namespace testing;



class JBIG2CodeTableTest_1837 : public ::testing::Test {

protected:

    void SetUp() override {

        mockHuffTable = new NiceMock<MockJBig2HuffmanTable>();

        jbig2CodeTable = new JBIG2CodeTable(0, mockHuffTable);

    }



    void TearDown() override {

        delete jbig2CodeTable;

        delete mockHuffTable;

    }



    MockJBig2HuffmanTable* mockHuffTable;

    JBIG2CodeTable* jbig2CodeTable;



    class MockJBig2HuffmanTable : public JBIG2HuffmanTable {

    public:

        MOCK_METHOD(void, someMockMethod, (), (override));

    };

};



TEST_F(JBIG2CodeTableTest_1837, GetHuffTable_ReturnsCorrectPointer_1837) {

    EXPECT_EQ(jbig2CodeTable->getHuffTable(), mockHuffTable);

}



TEST_F(JBIG2CodeTableTest_1837, GetHuffTable_DoesNotModifyTable_1837) {

    JBIG2HuffmanTable* originalTable = jbig2CodeTable->getHuffTable();

    EXPECT_EQ(jbig2CodeTable->getHuffTable(), originalTable);

}

```


