// poppler_structure_element_get_table_padding_test_2575.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <array>
#include <string>
#include <vector>

namespace {

class ScopedGLogCriticalCapture_2575 {
public:
  ScopedGLogCriticalCapture_2575()
  {
    // Ensure CRITICAL logs are not treated as fatal during this scope.
    old_always_fatal_ = g_log_set_always_fatal((GLogLevelFlags)0);
    g_log_set_always_fatal((GLogLevelFlags)(old_always_fatal_ & ~G_LOG_LEVEL_CRITICAL));

    // Capture CRITICAL from common domains (Poppler often sets G_LOG_DOMAIN).
    handler_ids_.push_back(g_log_set_handler(nullptr, (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, this));
    handler_domains_.push_back(nullptr);

    handler_ids_.push_back(g_log_set_handler("Poppler", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, this));
    handler_domains_.push_back("Poppler");

    handler_ids_.push_back(g_log_set_handler("GLib", (GLogLevelFlags)G_LOG_LEVEL_CRITICAL, &Handler, this));
    handler_domains_.push_back("GLib");
  }

  ~ScopedGLogCriticalCapture_2575()
  {
    for (size_t i = 0; i < handler_ids_.size(); ++i) {
      g_log_remove_handler(handler_domains_[i], handler_ids_[i]);
    }
    g_log_set_always_fatal(old_always_fatal_);
  }

  int critical_count() const { return critical_count_; }

  const std::vector<std::string> &messages() const { return messages_; }

private:
  static void Handler(const gchar *log_domain,
                      GLogLevelFlags /*log_level*/,
                      const gchar *message,
                      gpointer user_data)
  {
    auto *self = static_cast<ScopedGLogCriticalCapture_2575 *>(user_data);
    self->critical_count_++;
    std::string dom = (log_domain != nullptr) ? log_domain : "";
    std::string msg = (message != nullptr) ? message : "";
    self->messages_.push_back(dom + ": " + msg);
  }

  GLogLevelFlags old_always_fatal_{0};
  std::vector<guint> handler_ids_;
  std::vector<const char *> handler_domains_;
  int critical_count_{0};
  std::vector<std::string> messages_;
};

class PopplerStructureElementTablePaddingTest_2575 : public ::testing::Test {
protected:
  void SetUp() override
  {
    // No global setup required; tests exercise observable behavior (guard clauses/logging).
  }
};

} // namespace

TEST_F(PopplerStructureElementTablePaddingTest_2575,
       NullElementDoesNotModifyPaddingsAndEmitsCritical_2575)
{
  ScopedGLogCriticalCapture_2575 logs;

  std::array<gdouble, 4> paddings = {1.0, 2.0, 3.0, 4.0};
  const auto before = paddings;

  // poppler_structure_element_get_table_padding() requires a "block" element.
  // Passing nullptr should fail the precondition and return without writing.
  poppler_structure_element_get_table_padding(nullptr, paddings.data());

  EXPECT_GE(logs.critical_count(), 1) << "Expected at least one CRITICAL log from g_return_if_fail";
  EXPECT_EQ(paddings, before) << "On precondition failure, paddings should remain unchanged";
}

TEST_F(PopplerStructureElementTablePaddingTest_2575,
       NullElementAndNullPaddingsEmitsCriticalAndDoesNotCrash_2575)
{
  ScopedGLogCriticalCapture_2575 logs;

  // Both arguments invalid: should short-circuit on the first g_return_if_fail and not crash.
  poppler_structure_element_get_table_padding(nullptr, nullptr);

  EXPECT_GE(logs.critical_count(), 1) << "Expected at least one CRITICAL log from g_return_if_fail";
}