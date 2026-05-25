/***
 * @Author: shengli.liu && shengli_liu14@126.com
 * @Date: 2025-02-17 22:49:12
 * @LastEditors: shengli0214 shengli_liu14@126.com
 * @LastEditTime: 2026-01-26 19:38:21
 * @FilePath: \MytessCode\MyCode.cpp
 * @Description:
 * @
 * @Copyright (c) 2026 by shengli.liu, All Rights Reserved.
 */

#include "MyCode.h"



namespace MYCODE {
using namespace std;
/***
 * @description:
 * @param {string} s
 * @param {int} numRows
 * @return {*}
 */
// std::pair
std::string Solution::convert(string s, int numRows) {
  if (s.size() <= 1 || numRows <= 1 || s.size() < numRows) {
    return s;
  }
  // std::vector<std::string> ;
  std::vector<std::string> Middle_string(numRows, std::string());
  std::int32_t flag = -1;
  std::uint32_t line_number = 0;
  string returnString;
  // for (int32_t i = 0; i != s.size(); ++i){
  for (auto& c : s) {
    Middle_string.at(line_number).push_back(c);
    if (line_number == 0 || line_number == numRows - 1) {
      flag = -flag;
    }
    line_number += flag;
  }
  for (uint32_t i = 0; i != numRows; ++i) {
    returnString += Middle_string.at(i);
  }
}

/***
 * @description:
 * @analysis
 * INT32_MAX 2147483647
 * INT32_MIN -2147483647 - 1 //2143847412
 * remainder = x % 10 rev = rev*10 + remainder  x /= 10  if remainder > 0 ==>
 * rev*10 + remainder <= INT32_MAX  == INT32_MAX/10 * 10 + 7
 * [rev - INT32_MAX/10]*10 <= 7 - remainder
 * x top digit is  1 or 2 ==> The last remainder 7 - remainder is  6|5
 * rev <=  INT32_MAX/10 +(|0.6|0.5)
 * so rev > INT32_MAX/10 is the only condition that rev*10+remainder could
 * be out of range INT32_MAX
 *
 * remainder < 0 ==> rev*10 + remainder >= INT32_MIN ==>
 * rev >= INT32_MIN/10 - (0.6|0.7)
 * so rev < INT32_MIN/10 is the only condition that rev*10+remainder could
 * be out of range INT32_MIN
 * while
 * @param {int} x
 * @return {*}
 */
int Solution::reverse(int x) {
  int rev = 0;  // return value
  while (x != 0) {
    // int remValue = x % 10;
    if (rev > INT32_MAX / 10 || rev < INT32_MIN / 10) {
      rev = 0;
      break;
    }
    rev = rev * 10 + x % 10;
    x /= 10;
  }
  return rev;
}

int Solution::myAtoi(string s) {
  int rev = 0;
  int flag = 1;
  bool start = true;
  bool sign_flag = true;
  for (auto& c : s) {
    if (start && c == ' ') {
      continue;
    }
    start = false;
    if (sign_flag) {
      sign_flag = false;
      if (flag == 1 && c == '-') {
        flag = -1;
        continue;
      } else if (c == '+') {
        continue;
      }
    }
    if (c < '0' || c > '9') {
      break;
    }
    if ((flag == 1) &&
        ((rev > INT32_MAX / 10) || ((INT32_MAX / 10 == rev) && (c > '7')))) {
      rev = INT32_MAX;
      break;
    }
    if ((flag == -1) &&
        ((rev < INT32_MIN / 10) || ((INT32_MIN / 10 == rev) && (c > '8')))) {
      rev = INT32_MIN;
      break;
    }
    rev = rev * 10 + flag * (c - '0');
  }
  return rev;
}

bool Solution::isPalindrome(int x) {
  // bool rev = false;
  int rem_flip = 0;
  if (x < 0 || (x % 10 == 0 && x != 0)) {
    return false;
  }
  while (rem_flip < x) {
    rem_flip = rem_flip * 10 + x % 10;
    x /= 10;
  }
  return (rem_flip == x || rem_flip / 10 == x);
  // bool start = true;
  // while (x >= 0){
  //     if (start && (x % 10 == 0 || x <10)){
  //         if (x < 10){
  //             rev = true;
  //         }
  //         break;
  //     }
  //     start = false;
  //     rem_flip = rem_flip * 10 + x % 10;
  //     x /= 10;
  //     if (rem_flip == x) {
  //         rev = true;
  //         break;
  //     } else if (x - rem_flip*10 >= 0 && x - rem_flip*10 < 10){
  //         rev = true;
  //         break;
  //     } else if(x - rem_flip* 10 < 0){
  //         break;
  //     }
  // }
  // return rev;
}

bool Solution::isMatch(string s, string p) {
  auto m = s.size();
  auto n = p.size();
  std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
  dp[0][0] = true;
  for (int j = 2; j < n + 1; ++j) {
    if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
  }

  for (int i = 1; i < m + 1; ++i) {
    for (int j = 1; j < n + 1; ++j) {
      if (p[j - 1] != '*') {
        dp[i][j] =
            dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
      } else {
        dp[i][j] = dp[i][j - 2] ||
                   (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
      }
    }
  }
  return dp[m][n];
}

int Solution::maxArea(vector<int>& height) {
  int temp{0U};
  int vol{0U};
  auto p_front{height.begin()};
  auto p_rear{std::prev(height.end())};
  std::size_t size{height.size() - 1U};
  while (p_front != p_rear) {
    if (*p_front <= *p_rear) {
      temp = *p_front * size;
      p_front++;

    } else {
      temp = *p_rear * size;
      p_rear--;
    }
    size--;
    vol = std::max(temp, vol);
  }
  return vol;
}

string Solution::intToRoman(int num) {
  // map<int,string> int_roman_containers{{1000,"M"},{900,"CM"},
  // {500,"D"},{400,"CD"},{100,"C"},{90,"XC"},
  // {50,"L"},{40,"XL"},{10,"X"},{9,"IX"},{5,"V"},
  // {4,"IV"},{1,"I"}};
  // int_roman_containers.
  // int rem;
  std::pair<int, string> int_roman_containers[] = {
      {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
      {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
      {5, "V"},    {4, "IV"},   {1, "I"}};
  string roman_string;
  for (auto int_to_roman : int_roman_containers) {
    while (int_to_roman.first <= num) {
      roman_string += int_to_roman.second;
      num -= int_to_roman.first;
    }
  }
  // for(auto
  // iter{int_roman_containers.rbegin()};iter!=int_roman_containers.rend();++iter){
  //     while(iter->first <= num){
  //         roman_string += iter->second;
  //         num -= iter->first;
  //     }
  // }

  return roman_string;
}

int Solution::romanToInt(string s) {
  std::unordered_map<char, int> roman_to_int_containers{
      {'M', 1000}, {'D', 500}, {'C', 100}, {'L', 50},
      {'X', 10},   {'V', 5},   {'I', 1}};
  int value{0};
  for (auto iter{s.begin()}; iter != s.end(); ++iter) {
    {
      if (next(iter) == s.end() ||
          roman_to_int_containers.at(*iter) >=
              roman_to_int_containers.at(*(next(iter)))) {
        value += roman_to_int_containers.at(*iter);
      } else {
        value -= roman_to_int_containers.at(*iter);
      }
    }
  }
  return value;
}

string Solution::longestCommonPrefix(vector<string>& strs) {
  //   string longest_prefix_strs;
  auto length{strs.at(0).size()};
  if (length == 0U) {
    return "";
  }
  // for(auto str:strs){
  for (std::size_t i{0U}; i < length; ++i) {
    // auto current_char =
    for (std::size_t j{1U}; j < strs.size(); ++j) {
      if (i == strs.at(j).size() || strs.at(j).at(i) != strs.at(0).at(i)) {
        // break;
        return strs.at(0).substr(0, i);
      }
    }
  }
  return strs.at(0);
}

/// @brief 给你一个整数数组 nums ，
/// 判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k
/// ， 同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0
/// 且不重复的三元组。 注意：答案中不可以包含重复的三元组。
/// @param nums
/// @return
vector<vector<int>> Solution::threeSum(vector<int>& nums) {
  std::size_t length = nums.size();
  std::vector<std::vector<int>> temp;
  std::sort(nums.begin(), nums.end());
  for (std::size_t index1{0U}; index1 < length - 2; ++index1) {
    std::size_t index2{index1 + 1};
    std::size_t index3{length - 1};
    if (index1 > 0 && nums.at(index1) == nums.at(index1 - 1)) {
      continue;
    }
    while (index2 < index3) {
      if (index2 > index1 + 1 && nums.at(index2) == nums.at(index2 - 1)) {
        ++index2;
        continue;
      }
      if (-nums.at(index1) - nums.at(index2) > nums.at(index3)) {
        ++index2;
      } else if (-nums.at(index1) - nums.at(index2) < nums.at(index3)) {
        --index3;
      } else if (-nums.at(index1) - nums.at(index2) == nums.at(index3)) {
        temp.push_back({nums.at(index1), nums.at(index2), nums.at(index3)});
        ++index2;
        --index3;
      }
    }
  }
  return temp;
}

/// @brief 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。
/// 请你从 nums 中选出三个整数，使它们的和与 target 最接近。
/// 返回这三个数的和。
/// 假定每组输入只存在恰好一个解
/// @param nums
/// @param target
/// @return
int Solution::threeSumClosest(vector<int>& nums, int target) {
  std::size_t length{nums.size()};
  int temp_diff{std::numeric_limits<int>::max()};
  std::sort(nums.begin(), nums.end());
  for (std::size_t index1{0U}; index1 < length - 2; ++index1) {
    std::size_t index2{index1 + 1};
    std::size_t index3{length - 1};
    int temp;
    if (index1 > 0U && nums.at(index1) == nums.at(index1 - 1)) {
      continue;
    }
    while (index2 < index3) {
      if (index2 > index1 + 1 && nums.at(index2) == nums.at(index2 - 1)) {
        ++index2;
        continue;
      }
      if (index3 < length - 1 && nums.at(index3) == nums.at(index3 + 1)) {
        --index3;
        continue;
      }
      temp = nums.at(index1) + nums.at(index2) + nums.at(index3) - target;
      temp_diff = std::abs(temp) < std::abs(temp_diff) ? temp : temp_diff;
      if (temp < 0) {
        index2++;
      } else if (temp > 0) {
        index3--;
      } else {
        break;
      }
    }
    if (temp_diff == 0) {
      break;
    }
  }
  return temp_diff + target;
}

/// @brief 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
/// 答案可以按 任意顺序 返回。
/// 给出数字到字母的映射如下（与电话按键相同）。
/// 注意 1 不对应任何字母
/// @param digits
/// @return

vector<string> Solution::letterCombinations(string digits) {}

// 数字 n 代表生成括号的对数，
// 请你设计一个函数，用于能够生成所有可能的并且
// 有效的 括号组合。
// vector<string> Solution::generateParenthesis(int n) {
//   /*
//   n=0; ''
//   n=1;('');
//   n=2 ('')（1）
//   n=2 ((1))+''

//   n=3 ('') +(2); -> ()()() + ()(())
//   n=3 ((1))+(1)->(())()
//   n=3((2))+''(()())+((()))

//   dp(0) dp(1)
//   dp(2) = (dp(0)) + dp(1),（dp（1））+dp(0)
//   dp
//     */
//   //  std::vector<string> result;
//   //  return result;
//   back_track_generate_parenthesis(n, 0, 0, "");
//   return generateParenthesisRes;
// }

/**
 * @description:
 * @return {*}
 */


vector<string> Solution::generateParenthesis1(int n) {
  std::vector<string> Res;
  back_track_generate_parenthesis_no_res(n, Res);
  return Res;
}



bool Solution::exist(vector<vector<char>>& board, string word) {
  // for (int i{0};i<board.size();++i)
  int m{0};
  int n{0};
  if (!board.empty()) {
    m = board.at(0).size();  // colunm size
    n = board.size();        // line size
  }

  bool find{false};
  vector<vector<bool>> visited(n, vector<bool>(m, false));
  for (int i{0}; i < n && !find; ++i) {
    for (int j{0}; j < m && !find; ++j) {
      board_DFS(board, word, visited, i, j, 0, find);
    }
  }
  return find;
}


/*
请你将所有链表合并到一个升序链表中，返回合并后的链表。
示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：
输入：lists = []
输出：[]
示例 3：
输入：lists = [[]]
输出：[]
提示：
k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4
*/
/***
 * @description:
 * @return {*}
 */
ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
  // ListNode* p1{nullptr};
  ListNode* ans{nullptr};
  for (size_t i{0}; i < lists.size(); ++i) {
    ans = mergeTwoLists(ans, lists.at(i));
  }
  return ans;
}

// a b
/***
 * @description:
 * @param {ListNode*} a
 * @param {ListNode*} b
 * @return {*}
 */


ListNode* Solution::mergeKLists1(vector<ListNode*>& lists) {
  return merge(lists, 0, lists.size() - 1);
}



ListNode* Solution::mergeKLists2(vector<ListNode*>& lists) {
  // ListNode* p1{nullptr};
}

// LC24
ListNode* Solution::swapPairs(ListNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return nullptr;
  }
  ListNode* p_rear{nullptr};
  ListNode* p_dummy{head};
  ListNode* p_ans;
  if (p_dummy->next != nullptr) {
    p_ans = p_dummy->next;
  } else {
    p_ans = p_dummy;
    return p_ans;
  }
  while (p_dummy != nullptr) {
    p_rear == p_dummy->next;
    if (p_rear != nullptr) {
      p_dummy = p_rear->next;
    }
  }
}

//

//
// Given an array of integers temperatures represents the daily temperatures,
// return an array answer such that answer[i] is the number of days you have
//  to wait after the ith day to get a warmer temperature.
//  If there is no future day for which this is possible,
//  keep answer[i] == 0 instead.

// Example 1:
// Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]
// Example 2:
// Input: temperatures = [30,40,50,60]
// Output: [1,1,1,0]
// Example 3:
// Input: temperatures = [30,60,90]
// Output: [1,1,0]

vector<int> Solution::dailyTemperatures(vector<int>& temperatures) {
  // 73->s
  //  std::stack<int> stk;
  std::stack<std::pair<int, int>> stk;
  std::vector<int> ans(temperatures.size(), 0);
  // int pre_index{0};
  // // std::int32_t curr_high_temperature{INT32_MIN};
  // std::int32_t curr_high_temperature{std::numeric_limits<int32_t>::min()};
  for (int index = 0; index < temperatures.size(); ++index) {
    if (stk.empty() || temperatures.at(index) < stk.top().second) {
      stk.emplace(std::make_pair(index, temperatures.at(index)));
    } else {
      while (!stk.empty() && temperatures.at(index) > stk.top().second) {
        ans.at(stk.top().first) = index - stk.top().first;
        stk.pop();
      }
      stk.emplace(std::make_pair(index, temperatures.at(index)));
    }
  }
  // while (!stk.empty()) {
  //   ans.at(stk.top().first) = 0;
  //   stk.pop();
  // }
  return ans;
}

// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
// Input: head = [0,1,2], k = 4
// Output: [2,0,1]

ListNode* Solution::rotateRight(ListNode* head, int k) {
  if (head == nullptr) {
    return nullptr;
  }
  ListNode* p_ans{nullptr};
  ListNode* p_rem{nullptr};
  int list_len{0};
  ListNode* iter{head};
  int list_rem{0};
  while (iter != nullptr) {
    ++list_len;
    iter = iter->next;
  }
  if (list_len == k) {
    p_ans = head;
  }
  list_rem = list_len - k % list_len;
  while (list_rem) {
    --list_rem;
  }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

vector<ListNode*> Solution::splitListToParts(ListNode* head, int k) {
  ListNode* curr{head};
  int num{0};
  while (curr != nullptr) {
    ++num;
    curr = curr->next;
  }
  int quantient = num / k;  // 10 3  4 3 3   15 4 3   4443
  int remainder = num % k;  // 10 3 1       // 15 4 3
  vector<ListNode*> parts(k, nullptr);
  curr = head;
  for (int i{0}; i < k && curr != nullptr; ++i) {
    // while (curr != nullptr) {
    parts.at(i) = curr;
    int loops = quantient + (i < remainder ? 1 : 0);
    for (int j{1}; j < loops; ++j) {
      curr = curr->next;
    }
    ListNode* vec_next_head{curr->next};
    curr->next = nullptr;
    curr = vec_next_head;
    //}
  }
  return parts;
}

// 给你一个链表的头节点 head 和一个整数 val ，
// 请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
ListNode* Solution::removeElements(ListNode* head, int val) {
  ListNode* dummy = new ListNode();
  ListNode* tail{dummy};
  ListNode* curr{head};
  while (curr != nullptr) {
    if (curr->val == val) {
      curr = curr->next;
    } else {
      tail->next = curr;
      tail = tail->next;
    }
  }
  tail->next = nullptr;
  return dummy->next;
}

ListNode* Solution::removeElements1(ListNode* head, int val) {
  ListNode* dummy = new ListNode(0, head);
  ListNode* curr{dummy};
  while (curr->next != nullptr) {
    if (curr->next->val == val) {
      ListNode* del_node = curr->next;
      curr->next = del_node->next;
      delete del_node;
    } else {
      curr = curr->next;
    }
  }
  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}

// 给你一个整数数组 nums 和一个链表的头节点 head。
// 从链表中移除所有存在于 nums 中的节点后，返回修改后的链表的头节点。
ListNode* Solution::modifiedList(vector<int>& nums, ListNode* head) {
  std::sort(nums.begin(), nums.end());
  ListNode* dummy = new ListNode(0, head);
  ListNode* curr{dummy};
  while (curr->next != nullptr) {
    if (std::binary_search(nums.begin(), nums.end(), curr->next->val)) {
      ListNode* del_node = curr->next;
      curr->next = del_node->next;
      delete del_node;  // Leetcode 会自动清理，而报错 ，工程上需要这样写
    } else {
      curr = curr->next;
    }
  }
  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}

ListNode* Solution::modifiedList1(vector<int>& nums, ListNode* head) {
  std::unordered_set<int> st(nums.begin(), nums.end());
  ListNode dummy(0, head);
  ListNode* curr{&dummy};
  while (curr->next != nullptr) {
    if (st.count(curr->next->val) != 0) {
      ListNode* del_node = curr->next;
      curr->next = del_node->next;
      delete del_node;  // Leetcode 会自动清理，而报错 ，工程上需要这样写
    } else {
      curr = curr->next;
    }
  }
  // ListNode* newHead = dummy->next;
  // delete dummy;
  return dummy.next;
}

// 给定一个已排序的链表的头 head ， 删除所有重复的元素，
// 使每个元素只出现一次 。返回 已排序的链表 。
ListNode* Solution::deleteDuplicates(ListNode* head) {
  ListNode dummy(0, head);
  ListNode* curr{dummy.next};
  while (curr != nullptr) {
    while (curr->next != nullptr && curr->val == curr->next->val) {
      curr->next = curr->next->next;
    }
    curr = curr->next;
  }
  return dummy.next;
}

// 给定一个已排序的链表的头 head ， 删除原始链表中
// 所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。
ListNode* Solution::deleteDuplicates_82(ListNode* head) {
  ListNode dummy(0, head);
  ListNode* curr{&dummy};
  if (curr->next->val == curr->next->next->val) {
    int DupVal = curr->next->val;
    while (curr->next != nullptr && curr->next->val == DupVal) {
      curr->next = curr->next->next;
    }
  } else {
    curr = curr->next;
  }
  return dummy.next;
}

// 有一个单链表的 head，我们想删除它其中的一个节点 node。
// 给你一个需要删除的节点 node 。你将 无法访问 第一个节点  head。
// 链表的所有值都是 唯一的，并且保证给定的节点 node 不是链表中的最后一个节点。
// 删除给定的节点。注意，删除节点并不是指从内存中删除它。这里的意思是：
// 给定节点的值不应该存在于链表中。
// 链表中的节点数应该减少 1。
// node 前面的所有值顺序相同。
// node 后面的所有值顺序相同。
void Solution::deleteNode(ListNode* node) {
  node->val = node->next->val;
  node->next = node->next->next;
}

// 给你两个链表 list1 和 list2 ，它们包含的元素分别为 n 个和 m 个。
// 请你将 list1 中下标从 a 到 b 的全部节点都删除，并将list2
// 接在被删除节点的位置。
ListNode* Solution::mergeInBetween(ListNode* list1, int a, int b,
                                   ListNode* list2) {
  ListNode* ptr_a{nullptr};
  ListNode* ptr_b_1{nullptr};
  // ListNode dummy(0,list1);
  ListNode* curr_ptr{list1};
  int curr_pos{0};
  while (curr_pos <= b + 1) {
    if (curr_pos == a - 1) {
      ptr_a = curr_ptr;
    }
    if (curr_pos == b + 1) {
      ptr_b_1 = curr_ptr;
      break;
    }
    ++curr_pos;
    curr_ptr = curr_ptr->next;
  }
  ptr_a->next = list2;
  ListNode* curr_ptr_b{list2};
  while (curr_ptr_b->next != nullptr) {
    curr_ptr_b = curr_ptr_b->next;
  }
  curr_ptr_b->next = ptr_b_1;
  return list1;
}

ListNode* Solution::removeNodes(ListNode* head) {
  std::stack<ListNode*> stk;
  for (ListNode* curr{head}; curr != nullptr; curr = curr->next) {
    stk.emplace(curr);
  }
  ListNode* PtrRtn{nullptr};
  for (; !stk.empty(); stk.pop()) {
    // nullptr 保留最后一个节点
    if (PtrRtn == nullptr || stk.top()->val >= PtrRtn->val) {
      stk.top()->next = PtrRtn;
      PtrRtn = stk.top();
    }
  }
  return PtrRtn;
}

ListNode* Solution::insertGreatestCommonDivisors(ListNode* head) {
  ListNode* node{head};
  while (node != nullptr) {
    node->next = new ListNode(gcd(node->val, node->next->val), node->next);
    node = node->next->next;
  }
  return node;
}

// ListNode* Solution::insertionSortList(ListNode* head) {

// }





}  // namespace MYCODE
