#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "re2/regexp.h"



using namespace re2;



class NamedCapturesWalkerTest : public ::testing::Test {

protected:

    NamedCapturesWalker walker;

};



TEST_F(NamedCapturesWalkerTest_359, PreVisit_CaptureWithNonNullName_AddsToMap_359) {

    std::string name = "test_capture";

    Regexp* regexp = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    regexp->name_ = &name;



    bool stop = false;

    walker.PreVisit(regexp, 0, &stop);



    std::map<std::string, int>* map = walker.TakeMap();

    ASSERT_NE(map, nullptr);

    EXPECT_EQ((*map)["test_capture"], 1);

}



TEST_F(NamedCapturesWalkerTest_359, PreVisit_CaptureWithNullName_DoesNotAddToMap_359) {

    Regexp* regexp = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 2);

    regexp->name_ = nullptr;



    bool stop = false;

    walker.PreVisit(regexp, 0, &stop);



    std::map<std::string, int>* map = walker.TakeMap();

    ASSERT_NE(map, nullptr);

    EXPECT_TRUE(map->empty());

}



TEST_F(NamedCapturesWalkerTest_359, PreVisit_NonCaptureOperation_DoesNotAddToMap_359) {

    Regexp* regexp = Regexp::NewLiteral('a', 0);



    bool stop = false;

    walker.PreVisit(regexp, 0, &stop);



    std::map<std::string, int>* map = walker.TakeMap();

    ASSERT_NE(map, nullptr);

    EXPECT_TRUE(map->empty());

}



TEST_F(NamedCapturesWalkerTest_359, PreVisit_MultipleCaptures_AddsAllToMap_359) {

    std::string name1 = "capture1";

    std::string name2 = "capture2";



    Regexp* regexp1 = Regexp::Capture(Regexp::NewLiteral('a', 0), 0, 1);

    regexp1->name_ = &name1;



    Regexp* regexp2 = Regexp::Capture(Regexp::NewLiteral('b', 0), 0, 2);

    regexp2->name_ = &name2;



    bool stop = false;

    walker.PreVisit(regexp1, 0, &stop);

    walker.PreVisit(regexp2, 0, &stop);



    std::map<std::string, int>* map = walker.TakeMap();

    ASSERT_NE(map, nullptr);

    EXPECT_EQ((*map)["capture1"], 1);

    EXPECT_EQ((*map)["capture2"], 2);

}



TEST_F(NamedCapturesWalkerTest_359, TakeMap_ReturnsNonNullPointer_359) {

    std::map<std::string, int>* map = walker.TakeMap();

    ASSERT_NE(map, nullptr);

}



TEST_F(NamedCapturesWalkerTest_359, TakeMap_ReturnsEmptyMapInitially_359) {

    std::map<std::string, int>* map = walker.TakeMap();

    EXPECT_TRUE(map->empty());

}
