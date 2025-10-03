#include "lesson_test.h"
#include <algorithm>
#include <iostream>
#include <sstream>

#if _WIN32
#include <windows.h>
#endif

namespace lesson_test
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

MCQ::MCQ(std::string_view question, std::vector<std::pair<std::string_view, bool>> &&options, std::string_view hint,
         std::string_view solution)
{
    this->info.question = std::string{question};
    std::size_t index = 0;
    for (const auto &[text, is_answer] : options)
    {
        this->info.options.emplace_back(std::string{text});
        if (is_answer)
        {
            this->info.answer += static_cast<char>('A' + index);
        }
        ++index;
    }
    this->info.hint = std::string{hint};
    this->info.solution = std::string{solution};
}

bool MCQ::run(TestMode mode)
{
    std::cout << this->info.question << std::endl << std::endl;
    std::cout << "选项：" << std::endl;
    std::size_t index = 0;
    for (const auto context : this->info.options)
    {
        std::cout << static_cast<char>('A' + index) << '.' << context << std::endl;
        ++index;
    }
    std::cout << std::endl;
    if (!this->info.hint.empty())
    {
        std::cout << "ℹ️ 提示：" << info.hint << std::endl << std::endl;
    }
    bool is_correct = false;
    bool has_input = false;
    while (true)
    {
        std::cout << "输入你的答案：";
        auto user_input = read();
        user_input.erase(std::remove_if(user_input.begin(), user_input.end(), [](auto ch) { return std::isspace(ch); }),
                         user_input.end());
        if (user_input.length() >= 1)
        {
            has_input = true;
            std::transform(user_input.begin(), user_input.end(), user_input.begin(),
                           [](auto ch) { return std::toupper(ch); });
            std::sort(user_input.begin(), user_input.end());
            if (user_input == this->info.answer)
            {
                is_correct = true;
                if (mode == TestMode::practice)
                {
                    std::cout << "✅ 正确" << std::endl << std::endl;
                }
            }
            else if (mode == TestMode::practice)
            {
                std::cout << "❌ 错误" << std::endl << std::endl;
            }
        }
        else
        {
            std::cout << "你没有输入任何字符" << std::endl << std::endl;
        }
        if (mode == TestMode::examination && has_input)
        {
            std::cout << std::endl;
            return is_correct;
        }
        if (is_correct)
        {
            break;
        }
    }
    if (!this->info.solution.empty())
    {
        std::cout << "📝 解析：" << this->info.solution << std::endl << std::endl;
    }
    return true;
}

CRP::CRP(std::string_view source_code)
{
    this->source_code = source_code;
}

void CRP::add(std::string_view input, std::string_view answer, std::string_view hint, std::string_view solution)
{
    Info info;
    info.input = std::string{input};
    info.answer = this->split(answer);
    info.hint = std::string{hint};
    info.solution = std::string{solution};

    this->infos.emplace_back(std::move(info));
}

void CRP::add(std::string_view input, const std::function<void()> &answer, std::string_view hint,
              std::string_view solution)
{
    Info info;
    info.input = std::string{input};

    std::ostringstream oss;
    std::streambuf *oldBuf = std::cout.rdbuf(oss.rdbuf());
    answer();
    std::cout.rdbuf(oldBuf);
    info.answer = this->split(oss.str());

    info.hint = std::string{hint};
    info.solution = std::string{solution};

    this->infos.emplace_back(std::move(info));
}

std::vector<std::string> CRP::split(std::string_view output)
{
    std::istringstream iss(std::string{output});
    std::vector<std::string> realLines;
    std::string line;
    while (std::getline(iss, line))
    {
        realLines.push_back(line);
    }
    return realLines;
}

double CRP::run(TestMode mode)
{
    std::cout << "源代码：" << std::endl;
    std::cout << this->source_code << std::endl << std::endl;
    int test_group_number = this->infos.size();
    int pass_number = 0;
    for (auto info : this->infos)
    {
        int attempt = 1;
        while (true)
        {
            if (!info.input.empty())
            {
                std::cout << "输入：" << std::endl;
                std::cout << info.input << std::endl << std::endl;
            }

            if (!info.hint.empty())
            {
                std::cout << "ℹ️ 提示：" << info.hint << std::endl << std::endl;
            }

            std::cout << "程序应该输出：" << std::endl;

            bool allCorrect = true;
            for (size_t i = 0; i < info.answer.size(); ++i)
            {
                std::cout << "第 " << (i + 1) << " 行: ";
                auto user_ans = read();
                if (user_ans == info.answer[i])
                {
                    if (mode == TestMode::practice)
                    {
                        std::cout << "✅ 正确" << std::endl << std::endl;
                    }
                }
                else
                {
                    if (mode == TestMode::practice)
                    {
                        std::cout << "❌ 错误" << std::endl << std::endl;
                    }
                    allCorrect = false;
                    break;
                }
            }
            if (mode == TestMode::examination)
            {
                std::cout << std::endl;
                if (allCorrect)
                {
                    ++pass_number;
                }
                break;
            }

            if (allCorrect)
            {
                std::cout << "全部正确！共 " << info.answer.size() << " 行，尝试次数：" << attempt << std::endl
                          << std::endl;
                break;
            }
            ++attempt;
        }

        if (!info.solution.empty())
        {
            if (mode == TestMode::practice)
            {
                std::cout << "📝 解析：" << info.solution << std::endl << std::endl;
            }
        }
    }
    return static_cast<double>(pass_number) / test_group_number;
}

void InteractTester::set_console_utf8()
{
#if _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

InteractTester::QuestionType InteractTester::query(int id)
{
    return type_vector[id - 1];
}

InteractTester::InteractTester()
{
#if _WIN32
    this->set_console_utf8();
#endif
    this->question_number = 0;
}

InteractTester::InteractTester(std::string_view title)
{
#if _WIN32
    this->set_console_utf8();
#endif
    this->question_number = 0;
    this->title = std::string{title};
}

void InteractTester::add(MCQ &&mcq)
{
    this->mcq.emplace_back(std::move(mcq));
    type_vector.emplace_back(QuestionType::MCQ);
    ++this->question_number;
}

void InteractTester::add(CRP &&crp)
{
    this->crp.emplace_back(std::move(crp));
    type_vector.emplace_back(QuestionType::CRP);
    ++this->question_number;
}

void InteractTester::run(TestMode mode)
{
    if (!this->title.empty())
    {
        std::cout << "😀 欢迎来到 " << title << " 测试程序!" << std::endl;
    }
    std::cout << "本次测试共有 " << question_number << " 道题目" << std::endl << std::endl;
    int average_score = 100 / question_number;
    int real_score = 0;
    int id = 1;
    while (id <= this->question_number)
    {
        std::cout << "第 " << id << " 题：" << std::endl << std::endl;
        auto type = this->query(id);
        if (type == QuestionType::MCQ)
        {
            auto result = this->mcq[mcq_index].run(mode);
            if (id != this->question_number)
            {
                real_score += result * average_score;
            }
            else
            {
                real_score += result * (100 - (this->question_number - 1) * average_score);
            }
            ++mcq_index;
        }
        else
        {
            auto result = this->crp[crp_index].run(mode);
            if (id != this->question_number)
            {
                real_score += result * average_score;
            }
            else
            {
                real_score += result * (100 - (this->question_number - 1) * average_score);
            }
            ++crp_index;
        }
        ++id;
    }
    if (mode == TestMode::practice)
    {
        std::cout << "🎉 恭喜通过所有测试！ 按回车键退出程序" << std::endl;
    }
    else
    {
        std::cout << "🎉 恭喜完成考试！ 得分：" << real_score << " 分 按回车键退出程序" << std::endl;
    }
    std::cin.get();
}

} // namespace lesson_test
