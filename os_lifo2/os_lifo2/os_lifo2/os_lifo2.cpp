// os_lifo2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <stack>
#include <utility>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


double lifo(int intensity, int max_exec_time)
{
    std::stack<std::tuple<int, int, int>> q;
    int time = 0;
    double wait = 0;
    int cnt = 0;
    double sleep = 0;
    for (int i = 0; i < 100000; i++)
    {
        int ff = 0;//rand()%3-1;
        if ((i + ff) % intensity == 0)
        {
            int x = rand() % max_exec_time + 1;
            q.emplace(x, x, i);
        }
        time++;
        if (!q.empty())
        {
            std::get<0>(q.top())--;
            if (std::get<0>(q.top()) == 0)
            {
                cnt++;
                wait += time - std::get<1>(q.top()) - std::get<2>(q.top());
                q.pop();
            }
        }
        else
            sleep++;
    }
    return wait / cnt;
    while (!q.empty())
    {
        time++;
        std::get<0>(q.top())--;
        if (std::get<0>(q.top()) == 0)
        {
            //std::cout << "###  " << time << ' ' << std::get<1>(q.top()) << ' ' << std::get<2>(q.top()) << ' ' << time - std::get<1>(q.top()) - std::get<2>(q.top()) << '\n';
            wait += time - std::get<1>(q.top()) - std::get<2>(q.top());
            q.pop();
        }
    }
    //std::cout << '!' << wait << '\n';
    return wait / cnt;
}

void calculate_time(double time)
{
    for (int i = 0; i < 1000000; i += 1000)
    {

    }
}

double rlifo(int intensity, int max_exec_time, int kilk = 100000)
{
    std::stack<std::tuple<int, int, int>> q;
    int time = 0;
    double wait = 0;
    int cnt = 0;
    double sleep = 0;
    for (int i = 0; i < kilk; i++)
    {
        int ff = rand() % 3 - 1;
        if ((i + ff) % intensity == 0)
        {
            int x = rand() % max_exec_time + 1;
            q.emplace(x, x, i);
        }
        time++;
        if (!q.empty())
        {
            std::get<0>(q.top())--;
            if (std::get<0>(q.top()) == 0)
            {
                cnt++;
                wait += time - std::get<1>(q.top()) - std::get<2>(q.top());
                q.pop();
            }
        }
        else
            sleep++;
    }
    return wait / cnt;
    while (!q.empty())
    {
        time++;
        std::get<0>(q.top())--;
        if (std::get<0>(q.top()) == 0)
        {
            //std::cout << "###  " << time << ' ' << std::get<1>(q.top()) << ' ' << std::get<2>(q.top()) << ' ' << time - std::get<1>(q.top()) - std::get<2>(q.top()) << '\n';
            wait += time - std::get<1>(q.top()) - std::get<2>(q.top());
            q.pop();
        }
    }
    //std::cout << '!' << wait << '\n';
    return wait / cnt;
}

int get_time(double time)
{
    int qq = 0;
    for (int i = 0; i < 10; i++)
    {
        int now = 100;
        //std::cout << rlifo(17, 32, now) << "!!!!!!!!!1\n";
        while (abs(rlifo(17, 32, now) - time) > 1)
        {
            //std::cout << now << ' ' <<  rlifo(17, 32, now) << "!!!!!\n",
            if (time == 375)
                std::cout << now << ' ' << rlifo(17, 32, now) << "!!!!!\n",
                std::cin.get();
            now += 100;
        }
        qq += now;
    }
    return qq / 10;
}

int main()
{
    srand(time(0));
    //std::cout << lifo(4, 9);
    int intet = 17;
    double exec_t = 0;
    for (int i = 1; i <= 32; i++)
    {
        int cnt = 100;
        double sum = 0;
        for (int j = 0; j < cnt; j++)
            sum += lifo(intet, i);
        exec_t = std::max(exec_t, sum / cnt);
        std::cout << ' ' << ' ' << sum / cnt << '\n';
    }
    return 0;
    int t = rlifo(intet, 32, 10000000);
    int ans = 0;
    for (int i = 0; i < 1000000000; i += 1000)
        if (abs(rlifo(intet, 32, i) - t) < 1)
        {
            ans = i;
            break;
        }
    for (int i = 30000; i <= 60000; i += 1000)
    {
        int cnt = 100;
        double sum = 0;
        for (int j = 0; j < cnt; j++)
            sum += rlifo(intet, 32, 60000 - i);
        std::cout << ' ' << ' ' << std::max((double)0, exec_t + sum / cnt) << '\n';
    }/*
    for(int i = 25; i < 500; i += 25)
        std::cout << i << ' ' << get_time(i) << '\n';
    return 0;*/
}