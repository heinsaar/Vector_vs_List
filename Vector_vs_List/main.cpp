#include <algorithm>
#include <iostream> 
#include <iomanip> 
#include <vector> 
#include <chrono> 
#include <random>
#include <list> 

const int N = 1000;
using ms = std::chrono::milliseconds;

int random(int N)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d(0, N);
    return d(gen);
}

template<class Container>
auto grow(Container& c)
{
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < N; ++i)
    {
        auto pos = c.begin();
        auto r = random(N);
        while (pos != c.end() && r > *pos)
        {
            ++pos;
        }
        c.insert(pos, r);
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

template<class Container>
auto shrink(Container& c)
{
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < N; ++i)
    {
        auto pos = c.begin();
        std::advance(pos, random(c.size() - 1));
        c.erase(pos);
    }

    auto end = std::chrono::system_clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

int main()
{
    std::vector<int> vector;
    std::list<int>   list;

    std::cout << "When N = " << N << "\n\n";

    auto v_grow   = grow(vector);
    auto v_shrink = shrink(vector);
    std::cout << "Vector:\n";
    std::cout << "    Insertion: " << std::setw(7) << v_grow              << std::setfill(' ') << " ms\n";
    std::cout << "    Deletion:  " << std::setw(7) << v_shrink            << std::setfill(' ') << " ms\n";
    std::cout << "    Total:     " << std::setw(7) << (v_grow + v_shrink) << std::setfill(' ') << " ms";

    std::cout << "\n\n-------------------------\n\n";

    auto l_grow   = grow(list);
    auto l_shrink = shrink(list);
    std::cout << "List:\n";
    std::cout << "    Insertion: " << std::setw(7) << l_grow              << std::setfill(' ') << " ms\n";
    std::cout << "    Deletion:  " << std::setw(7) << l_shrink            << std::setfill(' ') << " ms\n";
    std::cout << "    Total:     " << std::setw(7) << (l_grow + l_shrink) << std::setfill(' ') << " ms\n\n";

    std::cout << "Vector faster: x" << (double)(l_grow + l_shrink) / (v_grow + v_shrink) << "\n\n";
}