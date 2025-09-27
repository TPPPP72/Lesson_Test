#pragma once

#include <functional>
#include <string>
#include <vector>

namespace Lesson_Test
{
// 读入 1 行输入 自动去除末尾 \t \n (space)
std::string read();

// MCQ = Mutiple Choices Question 选择题
class MCQ
{
  public:
    MCQ() = default;
    ~MCQ() = default;
    void set_question(std::string_view text);                       // 设置问题
    void add_option(std::string_view text, bool is_answer = false); // 添加选项
    void set_hint(std::string_view text);                           // 设置提示
    void set_solution(std::string_view text);                       // 设置解析

  private:
    void test();                      // 用于测试的函数
    std::string question;             // 问题
    std::vector<std::string> options; // 选项
    std::string hint;                 // 提示
    std::string solution;             // 解析
    char answer;                      // 答案
    int index = 0;                    // 选项偏移值
    friend class InteractTester;
};

// CRP = Code Reading Problem 阅读代码题
class CRP
{
  public:
    CRP() = default;
    ~CRP() = default;
    void set_origin_code(std::string_view text);                 // 设置展示给测试者的代码
    void set_input(std::string_view text);                       // 设置输入
    void set_real_output(const std::function<void()> &function); // 设置真实的输出
    void set_real_output(std::string_view text);                 // 设置真实的输出（重载）
    void set_hint(std::string_view text);                        // 设置提示
    void set_solution(std::string_view text);                    // 设置解析

  private:
    void test();                                // 用于测试的函数
    void run_and_capture();                     // 运行 f ，并捕获真实输出
    std::vector<std::string> get_real_output(); // 获取实际输出的每一行
    std::string origin_code;                    // 展示给测试者的代码
    std::string input;                          // 模拟程序输入
    std::string answer;                         // 答案
    std::string hint;                           // 提示
    std::string solution;                       // 解析
    std::function<void()> f;                    // 程序内部的代码（请使用 cout 输出）
    friend class InteractTester;
};

// 交互测试类
class InteractTester
{
  public:
    InteractTester();                       // 重写 InteractTester 构造函数
    InteractTester(std::string_view title); // 设置测试标题的构造函数
    ~InteractTester() = default;
    void add(MCQ &mcq); // 添加选择题
    void add(CRP &crp); // 添加阅读代码题
    void test();        // 运行测试

  private:
    enum class question_type
    {
        MCQ,
        CRP
    };
    std::string title;                      // 测试标题
    void set_console_utf8();                // 设置控制台编码为 UTF-8
    question_type query(int id);            // 通过题目编号查询题目类型
    std::vector<MCQ> mcq;                   // 存储mcq
    std::vector<CRP> crp;                   // 存储crp
    std::vector<question_type> type_vector; // 存储每个编号的题目类型
    int question_number;                    // 存储题目总数
    int mcq_index = 0;                      // mcq题目的下标
    int crp_index = 0;                      // crp题目的下标
};
}; // namespace Lesson_Test