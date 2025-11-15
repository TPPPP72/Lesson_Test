#pragma once

namespace lesson_test
{
enum class test_type
{
    practice,
    examination
};

class base_question
{
  public:
    base_question() = default;
    virtual ~base_question() = default;

  private:
    virtual void test() const = 0;
    friend class interact_tester;

  protected:
    test_type type{test_type::practice};
    mutable double score_percent{0};
};
} // namespace lesson_test
