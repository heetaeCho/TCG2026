#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_section.hpp"



using namespace Catch;

using namespace testing;



class SectionTest_582 : public Test {

protected:

    SourceLineInfo lineInfo = {"test_file.cpp", 10};

    StringRef name = "TestSection";

};



TEST_F(SectionTest_582, ConstructorWithSectionInfo_582) {

    SectionInfo info(lineInfo, name);

    Section section(std::move(info));

}



TEST_F(SectionTest_582, ConstructorWithSourceLineInfoAndName_582) {

    const char* description = nullptr;

    Section section(lineInfo, name, description);

}



TEST_F(SectionTest_582, OperatorBoolReturnsTrueWhenIncluded_582) {

    SectionInfo info(lineInfo, name);

    Section section(std::move(info));

    EXPECT_TRUE(static_cast<bool>(section));

}



TEST_F(SectionTest_582, OperatorBoolReturnsFalseWhenNotIncluded_582) {

    SourceLineInfo lineInfo = {"test_file.cpp", 10};

    StringRef name = "ExcludedSection";

    const char* description = nullptr;

    Section section(lineInfo, name, description);

    EXPECT_FALSE(static_cast<bool>(section));

}



TEST_F(SectionTest_582, DestructorCalledProperly_582) {

    SourceLineInfo lineInfo = {"test_file.cpp", 10};

    StringRef name = "DestructorTest";

    const char* description = nullptr;

    Section* section = new Section(lineInfo, name, description);

    delete section;

}
