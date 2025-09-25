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
    using option = std::pair<char, std::string>;        // 设置选项别名
    void set_question(std::string_view s);              // 设置问题
    void add_option(const option &op);                  // 添加选项
    void add_option(char op, std::string_view context); // 添加选项（重载）
    void set_ans(char c);                               // 设置答案
    void test();                                        // 用于测试的函数

  private:
    std::string question;        // 问题
    std::vector<option> options; // 选项
    char ans;                    // 答案
};

// CRP = Code Reading Problem 阅读代码题
class CRP
{
  public:
    CRP() = default;
    ~CRP() = default;
    void set_origin_code(std::string_view s);             // 设置展示给测试者的代码
    void set_input(std::string_view s);                   // 设置输入
    void set_real_output(const std::function<void()> &f); // 程序内部的输出函数
    void test();                                          // 用于测试的函数

  private:
    void run_and_capture();                     // 运行 f ，并捕获真实输出
    std::vector<std::string> get_real_output(); // 获取实际输出的每一行
    std::string origin_code;                    // 展示给测试者的代码
    std::string input;                          // 模拟程序输入
    std::string ans;                            // 答案
    std::function<void()> f;                    // 程序内部的代码（请使用 cout 输出）
};

// 交互测试类
class InteractTester
{
  public:
    InteractTester();
    void set_title(std::string_view s);
    void add_question(const MCQ &mcq); // 添加选择题
    void add_question(const CRP &crp); // 添加阅读代码题
    void test();                       // 运行测试

  private:
    enum class question_type
    {
        MCQ,
        CRP
    };
    std::string title;
    void set_console_utf8();             // 设置控制台编码为 UTF-8
    question_type query(int id);         // 通过题目编号查询题目类型
    std::vector<MCQ> mcq;                // 存储mcq
    std::vector<CRP> crp;                // 存储crp
    std::vector<question_type> type_vec; // 存储每个编号的题目类型
    int question_num;                    // 存储题目总数
    int mcq_index = 0;                   // mcq题目的下标
    int crp_index = 0;                   // crp题目的下标
};
}; // namespace Lesson_Test