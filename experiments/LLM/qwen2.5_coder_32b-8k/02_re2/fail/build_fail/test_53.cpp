#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "_re2.cc"

#include "re2/re2.h"



using namespace re2_python;

using namespace re2;



class RE2InitShimTest_53 : public ::testing::Test {

protected:

    py::buffer_info CreateBuffer(const std::string& data) {

        return py::bytes(data).request();

    }



    RE2::Options default_options;

};



TEST_F(RE2InitShimTest_53, ValidPattern_53) {

    auto buffer = CreateBuffer("valid_pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), default_options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, EmptyPattern_53) {

    auto buffer = CreateBuffer("");

    auto re2_instance = RE2InitShim(py::buffer(buffer), default_options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, InvalidPattern_53) {

    auto buffer = CreateBuffer("(*invalid_pattern*");

    auto re2_instance = RE2InitShim(py::buffer(buffer), default_options);

    EXPECT_EQ(re2_instance->ok(), false);

}



TEST_F(RE2InitShimTest_53, LargePattern_53) {

    std::string large_pattern(100000, 'a');

    auto buffer = CreateBuffer(large_pattern);

    auto re2_instance = RE2InitShim(py::buffer(buffer), default_options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetMaxMem_53) {

    RE2::Options options;

    options.set_max_mem(1024);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetEncodingUTF8_53) {

    RE2::Options options;

    options.set_encoding(EncodingUTF8);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetEncodingLatin1_53) {

    RE2::Options options;

    options.set_encoding(EncodingLatin1);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetPosixSyntax_53) {

    RE2::Options options;

    options.set_posix_syntax(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetLogErrorsFalse_53) {

    RE2::Options options;

    options.set_log_errors(false);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetLiteralTrue_53) {

    RE2::Options options;

    options.set_literal(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetNeverNLTrue_53) {

    RE2::Options options;

    options.set_never_nl(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetDotNLTrue_53) {

    RE2::Options options;

    options.set_dot_nl(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetNeverCaptureTrue_53) {

    RE2::Options options;

    options.set_never_capture(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetCaseSensitiveFalse_53) {

    RE2::Options options;

    options.set_case_sensitive(false);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetPerlClassesTrue_53) {

    RE2::Options options;

    options.set_perl_classes(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetWordBoundaryTrue_53) {

    RE2::Options options;

    options.set_word_boundary(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}



TEST_F(RE2InitShimTest_53, SetOneLineTrue_53) {

    RE2::Options options;

    options.set_one_line(true);

    auto buffer = CreateBuffer("pattern");

    auto re2_instance = RE2InitShim(py::buffer(buffer), options);

    ASSERT_NE(re2_instance, nullptr);

}
