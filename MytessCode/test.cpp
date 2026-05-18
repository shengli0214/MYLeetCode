/*** 
 * @Author: shengli0214 shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:14
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-01-20 19:20:49
 * @FilePath: \MytessCode\test.cpp
 * @Description: 
 * @
 * @Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */


#include <iostream>
// #include "MySort.h"
#include <algorithm>
#include <stack>
#include <set>
#include "MyGraphnew.h"
#include "MyCode.h"
#include "MyGraphTemplate.h"


int main()
{

	// mygraphnew::graph G = mygraphnew::initGraph();
    // G = mygraphnew::BFS(G,G.v[2]);
    // mygraphnew::printPath(G, G.v[2], G.v[6]);

	// std::vector<int> A({ 32, 34, 21, 13, 78, 24, 1,156 });
	// std::cout << "helloworld" << std::endl;
	// // std::sort(A.rbegin(),A.rend());
	// // mysortPrint(A);
	// // insert_sort(A);
	// // {
	// // 	std::vector<int> bak_T(A.size(),0);
	// // 	merge_sort(A,0,A.size(),bak_T);
	// // };
	// heap_sort(A);
	// int i = 1;
	// // std::cout << right(i) << std::endl;
	// mysortPrint(A);
	MYCODE::Solution solution;
	// std::string s("aab");
	// std::string a("c*a*b");
    std::cout << "test begin" << std::endl;
	// std::vector<int> height({1,8,6,2,5,4,8,3,7});
	// auto p = solution.isMatch(s,a);
	// std::cout << "p " << p << std::endl;
	// int vol{solution.maxArea(height)};
	// std::cout << "vol = " << vol << std::endl;
	std::vector<int> height({-2,0,0,2,2});
	// std::vector<std::string> res{solution.generateParenthesis1(3)};
	solution.threeSum(height);
	// for (auto &r : res)
	// {
	// 	std::cout << r << std::endl;
	// }
	// std::vector<char> a1{'A','B','C','E'};
	// std::vector<char> a2{'S','F','C','S'};
	// std::vector<char> a3{'A','D','E','E'};

	std::vector<char> a1{'C','A','A'};
	std::vector<char> a2{'A','A','A'};
	std::vector<char> a3{'B','C','D'};
	std::vector<std::vector<char>> test_board{a1,a2,a3};
	// std::string word = "ABCCED";
	std::string word = "AAB";
	if(solution.exist(test_board,word)){
		std::cout << "find" << std::endl;
	}else{
		std::cout << " not find " << std::endl;
	}
	// test_board.emplace_back{a1};

	// std::cout << solution.intToRoman(10) << std::endl;
	// std::cout << solution.threeSum(height);
	// int y = solution.reverse(x);
	// std::cout <<  y  << std::endl;
	// int z = INT32_MAX + 1;
	// std::string s1("-91283472332");
	// std::string s2("2147483648");
	// int rev1 = solution.myAtoi(s2);
	// int rev = solution.myAtoi(s1);
	// std::cout << "rev = " << rev << std::endl;
	// std::cout << "rev1 = " << rev1 << std::endl;
	// std::cout << "z = " << z << std::endl;

	// int x = 123321;
	// bool y = solution.isPalindrome(x);
	// std::cout << "y=" << y << std::endl;

	// std::stack<int> s;
	// // 向栈中添加元素
    // s.push(10);
    // s.push(20);
    // s.push(30);
 	// // 打印栈顶元素
    // std::cout << "Top element is: " << s.top() << std::endl; // 输出: Top element is: 30
    // int n = 6;
    // mygraptemplate::Graph<int> graph(n);
    // std::set<int> edgeInput[n];
    // graph.Insert(0, 1, 50);
    // graph.Insert(0, 2, 10);
    // graph.Insert(0, 4, 70);
    // graph.Insert(1, 2, 15);
    // graph.Insert(1, 4, 10);
    // graph.Insert(2, 0, 20);
    // graph.Insert(2, 3, 15);
    // graph.Insert(3, 1, 20);
    // graph.Insert(3, 4, 35);
    // graph.Insert(4, 3, 30);
    // graph.Insert(5, 3, 3);
    // // //测试弗洛伊德算法
    // graph.Floyd();

	// graph.Dijkstra(0);

	// return(0);
}