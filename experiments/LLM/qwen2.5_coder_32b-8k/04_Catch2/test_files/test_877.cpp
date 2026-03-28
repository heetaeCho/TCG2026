#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_json.hpp"

#include "catch2/internal/catch_list.hpp"



using namespace Catch;

using ::testing::Return;



class JsonReporterTest : public testing::Test {

protected:

    std::stringstream ss;

    ReporterConfig config = ReporterConfig(ss);

    JsonReporter reporter = JsonReporter(std::move(config));

};



TEST_F(JsonReporterTest_877, ListTags_EmptyList_NoOutput_877) {

    std::vector<TagInfo> tags;

    reporter.listTags(tags);

    EXPECT_EQ(ss.str(), "");

}



TEST_F(JsonReporterTest_877, ListTags_SingleTagWithNoAliases_OutputSingleEntry_877) {

    TagInfo tagInfo;

    tagInfo.count = 1;



    std::vector<TagInfo> tags{tagInfo};

    reporter.listTags(tags);



    EXPECT_EQ(ss.str(), "{\"tags\":[{\"aliases\":[],\"count\":1}]}");

}



TEST_F(JsonReporterTest_877, ListTags_SingleTagWithOneAlias_OutputSingleEntryWithAlias_877) {

    TagInfo tagInfo;

    tagInfo.add("alias1");

    tagInfo.count = 1;



    std::vector<TagInfo> tags{tagInfo};

    reporter.listTags(tags);



    EXPECT_EQ(ss.str(), "{\"tags\":[{\"aliases\":[\"alias1\"],\"count\":1}]}");

}



TEST_F(JsonReporterTest_877, ListTags_MultipleTagsWithAliases_OutputMultipleEntries_877) {

    TagInfo tagInfo1;

    tagInfo1.add("alias1a");

    tagInfo1.add("alias1b");

    tagInfo1.count = 2;



    TagInfo tagInfo2;

    tagInfo2.add("alias2a");

    tagInfo2.count = 3;



    std::vector<TagInfo> tags{tagInfo1, tagInfo2};

    reporter.listTags(tags);



    EXPECT_EQ(ss.str(), "{\"tags\":[{\"aliases\":[\"alias1a\",\"alias1b\"],\"count\":2},{\"aliases\":[\"alias2a\"],\"count\":3}]}");

}



TEST_F(JsonReporterTest_877, ListTags_StartListingCalledOnce_OutputContainsStartObject_877) {

    TagInfo tagInfo;

    std::vector<TagInfo> tags{tagInfo};

    reporter.listTags(tags);



    EXPECT_TRUE(ss.str().find("{\"tags\":") != std::string::npos);

}
