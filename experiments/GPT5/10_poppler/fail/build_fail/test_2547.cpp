// poppler_text_span_get_color_test_2547.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-page.h"              // PopplerColor
#include "poppler-structure-element.h" // PopplerTextSpan, poppler_text_span_get_color
}

#include <limits>
#include <string>
#include <vector>

namespace {

class ScopedGLogCapture {
public:
  ScopedGLogCapture()
  {
    // g_return_if_fail() typically logs at CRITICAL. Domain may vary depending on G_LOG_DOMAIN.
    handlers_.push_back({nullptr, g_log_set_handler(nullptr, G_LOG_LEVEL_CRITICAL, &ScopedGLogCapture::handler, this)});
    handlers_.push_back({"GLib", g_log_set_handler("GLib", G_LOG_LEVEL_CRITICAL, &ScopedGLogCapture::handler, this)});
    handlers_.push_back({"Poppler", g_log_set_handler("Poppler", G_LOG_LEVEL_CRITICAL, &ScopedGLogCapture::handler, this)});
  }

  ~ScopedGLogCapture()
  {
    for (const auto &h : handlers_) {
      g_log_remove_handler(h.domain, h.id);
    }
  }

  int critical_count() const { return critical_count_; }
  const std::vector<std::string> &messages() const { return messages_; }

private:
  struct Handler {
    const char *domain;
    guint id;
  };

  static void handler(const gchar * /*log_domain*/, GLogLevelFlags /*log_level*/, const gchar *message, gpointer user_data)
  {
    auto *self = static_cast<ScopedGLogCapture *>(user_data);
    self->critical_count_++;
    if (message) {
      self->messages_.push_back(message);
    }
  }

  std::vector<Handler> handlers_;
  int critical_count_ = 0;
  std::vector<std::string> messages_;
};

class PopplerTextSpanGetColorTest_2547 : public ::testing::Test {
protected:
  static PopplerColor MakeColor(int r, int g, int b)
  {
    PopplerColor c;
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
  }

  static void ExpectColorEq(const PopplerColor &actual, const PopplerColor &expected)
  {
    EXPECT_EQ(actual.red, expected.red);
    EXPECT_EQ(actual.green, expected.green);
    EXPECT_EQ(actual.blue, expected.blue);
  }
};

TEST_F(PopplerTextSpanGetColorTest_2547, CopiesColorToOutParam_2547)
{
  PopplerTextSpan span{};
  span.color = MakeColor(10, 20, 30);

  PopplerColor out = MakeColor(0, 0, 0);

  ScopedGLogCapture logs;
  poppler_text_span_get_color(&span, &out);

  EXPECT_EQ(logs.critical_count(), 0);
  ExpectColorEq(out, MakeColor(10, 20, 30));
}

TEST_F(PopplerTextSpanGetColorTest_2547, CopiesBoundaryValues_2547)
{
  PopplerTextSpan span{};
  span.color = MakeColor(0, std::numeric_limits<int>::max(), std::numeric_limits<int>::min());

  PopplerColor out = MakeColor(123, 456, 789);

  ScopedGLogCapture logs;
  poppler_text_span_get_color(&span, &out);

  EXPECT_EQ(logs.critical_count(), 0);
  ExpectColorEq(out, span.color);
}

TEST_F(PopplerTextSpanGetColorTest_2547, NullSpanEmitsCriticalAndDoesNotWriteOut_2547)
{
  PopplerColor out = MakeColor(1, 2, 3);
  PopplerColor before = out;

  ScopedGLogCapture logs;
  poppler_text_span_get_color(nullptr, &out);

  EXPECT_GE(logs.critical_count(), 1);
  ExpectColorEq(out, before);
}

TEST_F(PopplerTextSpanGetColorTest_2547, NullOutColorEmitsCritical_2547)
{
  PopplerTextSpan span{};
  span.color = MakeColor(9, 8, 7);

  ScopedGLogCapture logs;
  poppler_text_span_get_color(&span, nullptr);

  EXPECT_GE(logs.critical_count(), 1);
}

} // namespace