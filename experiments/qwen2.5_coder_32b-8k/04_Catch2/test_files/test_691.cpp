#include <gtest/gtest.h>

#include "catch2/internal/catch_reporter_spec_parser.hpp"

#include "catch2/internal/catch_optional.hpp"



using namespace Catch;



TEST(parseReporterSpec_691, ValidSimpleInput_691) {

    StringRef reporterSpec("console");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_TRUE(result.some());

    EXPECT_EQ(result->name, "console");

    EXPECT_FALSE(result->outputFileName);

    EXPECT_FALSE(result->colourMode);

    EXPECT_TRUE(result->kvPairs.empty());

}



TEST(parseReporterSpec_691, ValidWithOutputFile_691) {

    StringRef reporterSpec("console,out=results.txt");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_TRUE(result.some());

    EXPECT_EQ(result->name, "console");

    EXPECT_EQ(*result->outputFileName, "results.txt");

    EXPECT_FALSE(result->colourMode);

    EXPECT_TRUE(result->kvPairs.empty());

}



TEST(parseReporterSpec_691, ValidWithColourMode_691) {

    StringRef reporterSpec("console,colour-mode=ansi");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_TRUE(result.some());

    EXPECT_EQ(result->name, "console");

    EXPECT_FALSE(result->outputFileName);

    EXPECT_TRUE(result->colourMode);

    EXPECT_EQ(*result->colourMode, ColourMode::Ansi);

    EXPECT_TRUE(result->kvPairs.empty());

}



TEST(parseReporterSpec_691, ValidWithKVPair_691) {

    StringRef reporterSpec("console,Xkey=value");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_TRUE(result.some());

    EXPECT_EQ(result->name, "console");

    EXPECT_FALSE(result->outputFileName);

    EXPECT_FALSE(result->colourMode);

    EXPECT_EQ(result->kvPairs.size(), 1);

    EXPECT_EQ(result->kvPairs["key"], "value");

}



TEST(parseReporterSpec_691, ValidWithMultipleKVPair_691) {

    StringRef reporterSpec("console,Xkey1=value1,Xkey2=value2");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_TRUE(result.some());

    EXPECT_EQ(result->name, "console");

    EXPECT_FALSE(result->outputFileName);

    EXPECT_FALSE(result->colourMode);

    EXPECT_EQ(result->kvPairs.size(), 2);

    EXPECT_EQ(result->kvPairs["key1"], "value1");

    EXPECT_EQ(result->kvPairs["key2"], "value2");

}



TEST(parseReporterSpec_691, InvalidEmptyInput_691) {

    StringRef reporterSpec("");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidMissingKey_691) {

    StringRef reporterSpec("console,");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidMissingValue_691) {

    StringRef reporterSpec("console,key=");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidDuplicateKey_691) {

    StringRef reporterSpec("console,Xkey=value,Xkey=value2");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidDuplicateOutputFile_691) {

    StringRef reporterSpec("console,out=results.txt,out=other.txt");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidDuplicateColourMode_691) {

    StringRef reporterSpec("console,colour-mode=ansi,colour-mode=nocolor");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}



TEST(parseReporterSpec_691, InvalidMalformedKVPair_691) {

    StringRef reporterSpec("console,key=value=");

    auto result = parseReporterSpec(reporterSpec);

    EXPECT_FALSE(result.some());

}
