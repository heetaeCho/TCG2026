// emitter_operator_tag_test.cpp
// Unit tests for: YAML::operator<<(Emitter&, const _Tag&)
// TEST_ID: 43

#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>
#include <utility>

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/emittermanip.h>

namespace {

class EmitterOperatorTagTest_43 : public ::testing::Test {
 protected:
  using TagType = std::decay_t<decltype(std::declval<YAML::_Tag>().type)>;

  static YAML::_Tag MakeTag(const std::string& prefix,
                            const std::string& content,
                            int type_value = 0) {
    return YAML::_Tag(prefix, content, static_cast<TagType>(type_value));
  }
};

TEST_F(EmitterOperatorTagTest_43, ReturnsSameEmitterReference_43) {
  YAML::Emitter emitter;
  YAML::_Tag tag = MakeTag("!", "foo");

  YAML::Emitter* original = &emitter;
  YAML::Emitter& ret = (emitter << tag);

  EXPECT_EQ(&ret, original);
}

TEST_F(EmitterOperatorTagTest_43, SupportsChaining_43) {
  YAML::Emitter emitter;
  YAML::_Tag tag1 = MakeTag("!", "foo");
  YAML::_Tag tag2 = MakeTag("!!", "bar", 1);

  YAML::Emitter& ret = (emitter << tag1 << tag2 << tag1);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(EmitterOperatorTagTest_43, OperatorOutputMatchesWriteOutput_43) {
  std::ostringstream out_op;
  std::ostringstream out_write;

  YAML::Emitter emitter_op(out_op);
  YAML::Emitter emitter_write(out_write);

  YAML::_Tag tag = MakeTag("!", "foo");

  emitter_op << tag;
  emitter_write.Write(tag);

  EXPECT_EQ(out_op.str(), out_write.str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());
}

TEST_F(EmitterOperatorTagTest_43, EmptyPrefixAndContentMatchesWrite_43) {
  std::ostringstream out_op;
  std::ostringstream out_write;

  YAML::Emitter emitter_op(out_op);
  YAML::Emitter emitter_write(out_write);

  YAML::_Tag empty = MakeTag("", "");

  emitter_op << empty;
  emitter_write.Write(empty);

  EXPECT_EQ(out_op.str(), out_write.str());
  EXPECT_EQ(emitter_op.size(), emitter_write.size());
  EXPECT_STREQ(emitter_op.c_str(), emitter_write.c_str());
  EXPECT_EQ(emitter_op.good(), emitter_write.good());
  EXPECT_EQ(emitter_op.GetLastError(), emitter_write.GetLastError());
}

TEST_F(EmitterOperatorTagTest_43, DoesNotThrowWhenOstreamIsInBadState_43) {
  std::ostringstream out;
  out.setstate(std::ios::badbit);

  YAML::Emitter emitter(out);
  YAML::_Tag tag = MakeTag("!", "foo");

  EXPECT_NO_THROW({
    YAML::Emitter& ret = (emitter << tag);
    (void)ret;
  });

  // Observable behavior can vary by implementation; we only assert the call is safe
  // and the returned reference is usable for chaining.
  EXPECT_EQ(&(emitter << tag), &emitter);
}

}  // namespace
