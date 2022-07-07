#include <iostream>
#include <deque>
#include <stack>
#include <string>


void print_sequence(const std::deque<char>& sequence, int to_open, int to_close)
{
    for (const auto& el: sequence) {
        if (el == '(') {
            to_open--;
            to_close++;
        }
        else {
            to_close--;
        }
        std::cout << el;
    }
    for (; to_open > 0; --to_open, ++to_close)
        std::cout << '(';
    for (; to_close > 0; --to_close)
        std::cout << ')';
    std::cout << std::endl;
}

void change_in_depth(std::deque<char>& sequence, std::stack<char>& await,
                     const int i, const int j, const int half_size)
{
    await.push(sequence.back());
    sequence.pop_back();

    int dpth = 0;
    for (;;) {
        while (sequence.back() != '(') {
            sequence.pop_back();
            dpth++;
        }
        await.push(sequence.back());
        sequence.pop_back();
        dpth--;
    }

    int allowed_to_push = half_size - await.size();
    for (int k = 1; k - 1 < j; ++k) {
        if (allowed_to_push){
            sequence.push_back(')');
            allowed_to_push--;
        }
        else if (!await.empty()) {
            sequence.push_back(await.top());
            await.pop();
            sequence.push_back(')');
        }

    }
}

int main()
{
    int half_size = 0;
    std::cin >> half_size;
    int size  = 2 * half_size;

    std::deque<char> sequence;
    for (int i = 0; i < half_size; ++i)
        sequence.push_back('(');
    int to_open = half_size;
    int to_close = 0;
    std::stack<char> await;

//    std::string a("()(())(");
//    sequence.clear();
//    for (const auto& i: a)
//        sequence.push_back(i);
//    await.push('(');

//    change_in_depth(sequence, await, 2, 2, half_size);

    print_sequence(sequence, to_open, to_close);
    for (int i = 1; i < half_size; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int k = 1; sequence.size() < size - 1; ++k) {
                std::cout << "sequence size " << sequence.size() << std::endl;
                for (int q = 0; q < j; ++q){
                    sequence.pop_back();
                }
                for (int q = 0; q < k; ++q){
                    sequence.push_back(')');
                }
                for (int q = 0; q < j; ++q){
                    sequence.push_back('(');
                }


                print_sequence(sequence, to_open, to_close);
            }
            std::cout << "seq ";
            for (const auto& i : sequence)
                std::cout << i;
            std::cout << " "<< i << " " << j << std::endl;

            change_in_depth(sequence, await, i, j, half_size);

            std::cout << "stack " << await.size() << " seq ";
            for (const auto& i : sequence)
                std::cout << i;
            std::cout << std::endl;
            while (!await.empty()) {
//                std::cout << await.top();
                sequence.push_back(await.top());
                await.pop();
            }
//            std::cout << std::endl;
            print_sequence(sequence, to_open, to_close);
        }
    }
    return 0;
}
