#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_source_line_info.hpp"



namespace Catch {

    bool SourceLineInfo::operator == ( SourceLineInfo const& other ) const noexcept {

        return line == other.line && std::strcmp(file, other.file) == 0;

    }



    bool SourceLineInfo::operator < ( SourceLineInfo const& other ) const noexcept {

        return line < other.line || (line == other.line && std::strcmp(file, other.file) < 0);

    }

}



using namespace Catch;



class SourceLineInfoTest_488 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    SourceLineInfo createSourceLineInfo(const char* file, std::size_t line) const {

        return SourceLineInfo(file, line);

    }

};



TEST_F(SourceLineInfoTest_488, CompareDifferentLines_488) {

    SourceLineInfo info1("file1.cpp", 10);

    SourceLineInfo info2("file1.cpp", 20);

    EXPECT_TRUE(info1 < info2);

}



TEST_F(SourceLineInfoTest_488, CompareSameLinesDifferentFiles_488) {

    SourceLineInfo info1("file1.cpp", 10);

    SourceLineInfo info2("file2.cpp", 10);

    EXPECT_TRUE(info1 < info2);

}



TEST_F(SourceLineInfoTest_488, CompareSameFileAndLine_488) {

    SourceLineInfo info1("file1.cpp", 10);

    SourceLineInfo info2("file1.cpp", 10);

    EXPECT_FALSE(info1 < info2);

}



TEST_F(SourceLineInfoTest_488, CompareDifferentFilesAndLines_488) {

    SourceLineInfo info1("file1.cpp", 5);

    SourceLineInfo info2("file2.cpp", 10);

    EXPECT_TRUE(info1 < info2);

}



TEST_F(SourceLineInfoTest_488, CompareEqualObjects_488) {

    SourceLineInfo info1("file1.cpp", 10);

    SourceLineInfo info2("file1.cpp", 10);

    EXPECT_TRUE(info1 == info2);

}



TEST_F(SourceLineInfoTest_488, CompareDifferentFileAndSameLine_488) {

    SourceLineInfo info1("file1.cpp", 10);

    SourceLineInfo info2("file2.cpp", 10);

    EXPECT_FALSE(info1 == info2);

}



TEST_F(SourceLineInfoTest_488, CompareSameFileDifferentLines_488) {

    SourceLineInfo info1("file1.cpp", 5);

    SourceLineInfo info2("file1.cpp", 10);

    EXPECT_FALSE(info1 == info2);

}
