/*** 
 * @Author: shengli.liu && shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:13
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-05-18 11:38:13
 * @FilePath: \MytessCode\MyCode.h
 * @Description: 
 * @
 * @Copyright (c) 2026 by shengli.liu, All Rights Reserved. 
 */
/***
 * @Author: shengli.liu && shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:13
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-02-06 16:38:56
 * @FilePath: \MytessCode\MyCode.h
 * @Description:
 * @
 * @Copyright (c) 2026 by shengli.liu, All Rights Reserved.
 */

#ifndef MYCODE_H
#define MYCODE_H
#include <iostream>
#include <map>
#include <stack>
#include <unordered_map>
#include <vector>
#include <unordered_set>
namespace MYCODE {
using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
class Solution {
 public:
  std::string convert(string s, int numRows);
  int reverse(int x);
  int myAtoi(string s);
  bool isPalindrome(int x);
  bool isMatch(string s, string p);
  int maxArea(vector<int>& height);
  string intToRoman(int num);
  int romanToInt(string s);
  string longestCommonPrefix(vector<string>& strs);
  vector<vector<int>> threeSum(vector<int>& nums);
  int threeSumClosest(vector<int>& nums, int target);
  vector<string> letterCombinations(string digits);
  // leetcode 23
  vector<string> generateParenthesis(int n);
  vector<string> generateParenthesis1(int n);
  // leetcode 79
  bool exist(vector<vector<char>>& board, string word);
  bool exist1(vector<vector<char>>& board, string word);
  //leetcode 23
  ListNode* mergeKLists(vector<ListNode*>& lists);
  ListNode* mergeKLists1(vector<ListNode*>& lists);
  ListNode* mergeKLists2(vector<ListNode*>& lists);
  //leetcode 24
  ListNode* swapPairs(ListNode* head);

  vector<int> dailyTemperatures(vector<int>& temperatures);

  // leetcode 61
  ListNode* rotateRight(ListNode* head, int k);

  vector<ListNode*> Solution:: splitListToParts(ListNode* head, int k);
  //203
  ListNode* removeElements(ListNode* head, int val);
  ListNode* removeElements1(ListNode* head, int val);
  //3217
  ListNode* modifiedList(vector<int>& nums, ListNode* head);
  ListNode* modifiedList1(vector<int>& nums, ListNode* head);
  //83
  ListNode* deleteDuplicates(ListNode* head);
  //82
  ListNode* deleteDuplicates_82(ListNode* head);
  //237
  void deleteNode(ListNode* node);
  //1669
  ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2);
  //2487
  ListNode* removeNodes(ListNode* head);
 private:
  ListNode* mergeTwoLists(ListNode* a, ListNode* b);
  ListNode* merge(vector<ListNode*>& lists, int l, int r);
  void back_track_generate_parenthesis(int n, int left_num, int right_num,
                                       std::string str);
  void back_track_generate_parenthesis_no_res(
      int n, std::vector<string>& generateParenthesisRes);
  std::vector<string> generateParenthesisRes;
  // leetcode 79
  void board_DFS(vector<vector<char>>& board, string& word,
                 vector<vector<bool>>& visited, int i, int j, int k,
                 bool& find);
};

}  // namespace MYCODE

#endif  // MYCODE_H