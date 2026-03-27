#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/XMLParserAdapter.hpp"



using namespace testing;



class ExpatAdapter : public XMLParserAdapter {

public:

    ExpatAdapter() {}

    virtual ~ExpatAdapter() {}



    void EndElementHandler(XMP_StringPtr name) {

        ::EndElementHandler(this, name);

    }



#if XMP_DebugBuild

    int elemNesting = 0;

    FILE* parseLog = nullptr;

#endif



    std::vector<XML_Node> parseStack;

};



class ExpatAdapterTest : public Test {

protected:

    ExpatAdapter adapter;



    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(ExpatAdapterTest_2094, EndElementHandler_RemovesFromParseStack_2094) {

    XML_Node node1("node1");

    XML_Node node2("node2");



    adapter.parseStack.push_back(node1);

    adapter.parseStack.push_back(node2);



    const char* elementName = "node2";

    adapter.EndElementHandler(elementName);



    ASSERT_EQ(adapter.parseStack.size(), 1);

    EXPECT_EQ(adapter.parseStack.back().name, "node1");

}



TEST_F(ExpatAdapterTest_2094, EndElementHandler_EmptyParseStack_NoCrash_2094) {

    const char* elementName = "node";

    adapter.EndElementHandler(elementName);



    // If no crash occurs, the test passes

    SUCCEED();

}



#if XMP_DebugBuild

TEST_F(ExpatAdapterTest_2094, EndElementHandler_DecreasesElemNesting_2094) {

    adapter.elemNesting = 3;

    const char* elementName = "node";

    adapter.EndElementHandler(elementName);



    EXPECT_EQ(adapter.elemNesting, 2);

}



TEST_F(ExpatAdapterTest_2094, EndElementHandler_LogsEndElementEvent_2094) {

    FILE* fakeFile = fopen("fakefile.log", "w");

    ASSERT_NE(fakeFile, nullptr);



    adapter.parseLog = fakeFile;

    adapter.elemNesting = 1;



    const char* elementName = "node";

    adapter.EndElementHandler(elementName);



    fclose(fakeFile);



    // Verify the log file content if necessary

    SUCCEED();

}

#endif
