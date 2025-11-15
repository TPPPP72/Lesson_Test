#pragma once

#include "base_question.hpp"
#include <functional>
#include <string>
#include <vector>

namespace lesson_test
{
// 读入 1 行输入 自动去除末尾 \t \n (space)
std::string read();

// MCQ = Mutiple Choices Question 选择题
class MCQ : public base_question
{
  public:
    MCQ(std::string_view question, std::vector<std::pair<std::string_view, bool>> &&options, std::string_view hint,
        std::string_view solution);
    ~MCQ() = default;
    MCQ(const MCQ &) = delete;
    MCQ(MCQ &&) = delete;
    operator base_question *()
    {
        return this;
    }

  private:
    struct test_info
    {
        std::string question;
        std::vector<std::string> options;
        std::string answer;
        std::string hint;
        std::string solution;
    };
    test_info info;
    void test() const override;
};

// CRP = Code Reading Problem 阅读代码题
class CRP : public base_question
{
  public:
    CRP() = delete;
    CRP(std::string_view source_code);
    ~CRP() = default;
    CRP(const CRP &) = delete;
    CRP(CRP &&) = delete;
    void add(std::string_view input, std::string_view answer, std::string_view hint = "",
             std::string_view solution = "");
    void add(std::string_view input, const std::function<void()> &answer, std::string_view hint = "",
             std::string_view solution = "");
    operator base_question *()
    {
        return this;
    }

  private:
    struct test_info
    {
        std::string input;
        std::string hint;
        std::vector<std::string> answer;
        std::string solution;
    };
    std::vector<std::string> split(std::string_view output);
    std::string source_code;
    std::vector<test_info> infos;
    void test() const override;
};

// 交互测试类
class interact_tester
{
  public:
    interact_tester();                       // 重写 interact_tester 构造函数
    interact_tester(std::string_view title); // 设置测试标题的构造函数
    ~interact_tester() = default;
    void add(base_question *question);              // 添加题目
    void run(test_type type = test_type::practice); // 运行测试

  private:
    std::string title;                          // 测试标题
    std::vector<base_question *> question_list; // 题目列表
    void set_console_utf8();                    // 设置控制台编码为 UTF-8
};
}; // namespace lesson_test