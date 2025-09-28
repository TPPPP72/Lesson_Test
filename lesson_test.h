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
    void set_hint(std::string_view text);
    void set_solution(std::string_view text);

  private:
    void run();
    std::string question;
    std::vector<std::string> options;
    std::string hint;
    std::string solution;
    char answer;
    int index = 0;
    friend class InteractTester;
};

// CRP = Code Reading Problem 阅读代码题
class CRP
{
  public:
    CRP() = delete;
    CRP(std::string_view source_code);
    ~CRP() = default;
    void add(std::string_view input, std::string_view answer, std::string_view hint, std::string_view solution);
    void add(std::string_view input, const std::function<void()> &answer, std::string_view hint,
             std::string_view solution);

  private:
    struct Info
    {
        std::string input;
        std::string hint;
        std::vector<std::string> answer;
        std::string solution;
    };
    void run();
    std::vector<std::string> split(std::string_view output);
    std::string source_code;
    std::vector<Info> infos;
    friend class InteractTester;
};

// 交互测试类
class InteractTester
{
  public:
    InteractTester();                       // 重写 InteractTester 构造函数
    InteractTester(std::string_view title); // 设置测试标题的构造函数
    ~InteractTester() = default;
    void add(MCQ &&mcq); // 添加选择题
    void add(CRP &&crp); // 添加阅读代码题
    void run();          // 运行测试

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