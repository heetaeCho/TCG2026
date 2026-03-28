// TEST_ID: 539
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/exceptions.h"  // for YAML::ErrorMsg::INVALID_ANCHOR

namespace {

class EmitterWriteAnchorTest_539 : public ::testing::Test {
 protected:
  std::ostringstream out_;
  YAML::Emitter emitter_{out_};

  std::string Output() const { return out_.str(); }
};

TEST_F(EmitterWriteAnchorTest_539, ReturnsSelfReference_539) {
  YAML::_Anchor a("a");
  YAML::Emitter* before = &emitter_;

  YAML::Emitter& ret = emitter_.Write(a);

  EXPECT_EQ(&ret, before);
}

TEST_F(EmitterWriteAnchorTest_539, WritesAnchorContentToOutput_539) {
  const std::string content = "myAnchor";
  YAML::_Anchor a(content);

  ASSERT_TRUE(emitter_.good());
  const std::string before = Output();

  emitter_.Write(a);

  EXPECT_TRUE(emitter_.good());
  const std::string after = Output();
  EXPECT_GE(after.size(), before.size());
  // Black-box check: output should reflect the anchor content somehow.
  EXPECT_NE(after.find(content), std::string::npos);
}

TEST_F(EmitterWriteAnchorTest_539, SecondAnchorWriteSetsInvalidAnchorError_539) {
  YAML::_Anchor a1("first");
  YAML::_Anchor a2("second");

  emitter_.Write(a1);
  ASSERT_TRUE(emitter_.good());

  const std::string before_second = Output();
  emitter_.Write(a2);

  EXPECT_FALSE(emitter_.good());
  EXPECT_EQ(emitter_.GetLastError(), std::string(YAML::ErrorMsg::INVALID_ANCHOR));

  // After the error, output should not change for this failing call.
  EXPECT_EQ(Output(), before_second);
}

TEST_F(EmitterWriteAnchorTest_539, AfterErrorFurtherWritesAreNoOps_539) {
  YAML::_Anchor a1("first");
  YAML::_Anchor a2("second");
  YAML::_Anchor a3("third");

  emitter_.Write(a1);
  emitter_.Write(a2);  // triggers INVALID_ANCHOR error (second anchor)
  ASSERT_FALSE(emitter_.good());
  ASSERT_EQ(emitter_.GetLastError(), std::string(YAML::ErrorMsg::INVALID_ANCHOR));

  const std::string after_error = Output();
  const std::string err_after_error = emitter_.GetLastError();

  emitter_.Write(a3);

  EXPECT_EQ(Output(), after_error);
  EXPECT_FALSE(emitter_.good());
  EXPECT_EQ(emitter_.GetLastError(), err_after_error);
}

TEST_F(EmitterWriteAnchorTest_539, LargeAnchorContentDoesNotCrashAndIsObservableInOutput_539) {
  std::string big(1024, 'A');
  YAML::_Anchor a(big);

  emitter_.Write(a);

  EXPECT_TRUE(emitter_.good());
  EXPECT_NE(Output().find(big), std::string::npos);
}

}  // namespace