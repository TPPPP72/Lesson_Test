#include "lesson_test.h"
#include <iostream>
#include <sstream>
#if _WIN32
#include <windows.h>
#endif

namespace Lesson_Test
{

std::string read()
{
    std::string str;
    std::getline(std::cin, str);
    while (!str.empty())
    {
        auto back = str.back();
        if (back == '\n' || back == '\t' || back == ' ')
        {
            str.pop_back();
            continue;
        }
        break;
    }
    return str;
}

void MCQ::set_question(std::string_view s)
{
    this->question = s;
}

void MCQ::set_hint(std::string_view s)
{
    this->hint = s;
}

void MCQ::set_solution(std::string_view s)
{
    this->solution = s;
}

void MCQ::add_option(const option &op)
{
    this->options.emplace_back(op);
}

void MCQ::add_option(char op, std::string_view context)
{
    this->add_option((option){op, context});
}

void MCQ::set_ans(char c)
{
    this->ans = c;
}

void MCQ::test()
{
    if (this->ans == 0)
    {
        std::cout << "严重错误：未设定答案选项" << std::endl;
        return;
    }
    std::cout << this->question << std::endl << std::endl;
    std::cout << "选项：" << std::endl;
    for (const auto &[option, context] : this->options)
    {
        std::cout << option << '.' << context << std::endl;
    }
    std::cout << std::endl;
    if (!this->hint.empty())
    {
        std::cout << "提示：" << hint << std::endl << std::endl;
    }
    bool is_correct = false;
    while (true)
    {
        std::cout << "输入你的答案：";
        auto user_input = read();
        if (user_input.length() >= 1)
        {
            char user_ans = user_input[0];
            if (std::toupper(user_ans) == this->ans)
            {
                is_correct = true;
                std::cout << "✅ 正确" << std::endl << std::endl;
            }
            else
            {
                std::cout << "❌ 错误" << std::endl << std::endl;
            }
        }
        else
        {
            std::cout << "你没有输入任何字符" << std::endl << std::endl;
        }
        if (is_correct)
        {
            break;
        }
    }
    if (!this->solution.empty())
    {
        std::cout << "解析：" << this->solution << std::endl << std::endl;
    }
}

void CRP::set_origin_code(std::string_view s)
{
    this->origin_code = s;
}

void CRP::set_input(std::string_view s)
{
    this->input = s;
}

void CRP::set_solution(std::string_view s)
{
    this->solution = s;
}

void CRP::set_hint(std::string_view s)
{
    this->hint = s;
}

void CRP::set_real_output(const std::function<void()> &f)
{
    this->f = f;
    this->run_and_capture();
}

void CRP::set_real_output(std::string_view s)
{
    this->ans = s;
}

void CRP::run_and_capture()
{
    std::ostringstream oss;
    std::streambuf *oldBuf = std::cout.rdbuf(oss.rdbuf());
    this->f();
    std::cout.rdbuf(oldBuf);
    this->ans = oss.str();
}

std::vector<std::string> CRP::get_real_output()
{
    std::istringstream iss(ans);
    std::vector<std::string> realLines;
    std::string line;
    while (std::getline(iss, line))
    {
        realLines.push_back(line);
    }
    return realLines;
}

void CRP::test()
{
    auto real = get_real_output();

    int attempt = 1;
    while (true)
    {
        std::cout << "源代码：" << std::endl;
        std::cout << this->origin_code << std::endl << std::endl;

        if (!this->input.empty())
        {
            std::cout << "输入：" << std::endl;
            std::cout << input << std::endl << std::endl;
        }

        if (!this->hint.empty())
        {
            std::cout << "提示：" << hint << std::endl << std::endl;
        }

        std::cout << "程序应该输出：" << std::endl;

        bool allCorrect = true;
        for (size_t i = 0; i < real.size(); ++i)
        {
            std::cout << "第 " << (i + 1) << " 行: ";
            auto user_ans = read();
            if (user_ans == real[i])
            {
                std::cout << "✅ 正确" << std::endl << std::endl;
            }
            else
            {
                std::cout << "❌ 错误" << std::endl << std::endl;
                allCorrect = false;
                break;
            }
        }

        if (allCorrect)
        {
            std::cout << "全部正确！共 " << real.size() << " 行，尝试次数：" << attempt << std::endl << std::endl;
            break;
        }
        ++attempt;
    }
    if (!this->solution.empty())
    {
        std::cout << "解析：" << this->solution << std::endl << std::endl;
    }
}

void InteractTester::set_console_utf8()
{
#if _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

InteractTester::question_type InteractTester::query(int id)
{
    return type_vec[id - 1];
}

InteractTester::InteractTester()
{
#if _WIN32
    this->set_console_utf8();
#endif
    this->question_num = 0;
}

void InteractTester::set_title(std::string_view s)
{
    this->title = s;
}

void InteractTester::add_question(const MCQ &mcq)
{
    this->mcq.emplace_back(mcq);
    type_vec.emplace_back(question_type::MCQ);
    ++this->question_num;
}

void InteractTester::add_question(const CRP &crp)
{
    this->crp.emplace_back(crp);
    type_vec.emplace_back(question_type::CRP);
    ++this->question_num;
}

void InteractTester::test()
{
    if (!this->title.empty())
    {
        std::cout << "😀 欢迎来到 " << title << " 测试程序!" << std::endl;
    }
    std::cout << "本次测试共有 " << question_num << " 道题目" << std::endl << std::endl;
    int id = 1;
    while (id <= this->question_num)
    {
        std::cout << "第 " << id << " 题：" << std::endl << std::endl;
        auto type = this->query(id);
        if (type == question_type::MCQ)
        {
            this->mcq[mcq_index].test();
            ++mcq_index;
        }
        else
        {
            this->crp[crp_index].test();
            ++crp_index;
        }
        std::cout << "第 " << id << " 题正确！" << std::endl << std::endl;
        ++id;
    }
    std::cout << "🎉 恭喜通过所有测试！ 按回车键退出程序" << std::endl;
    std::cin.get();
}

} // namespace Lesson_Test
