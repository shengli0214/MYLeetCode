#include "MyCode.h"

namespace MYCODE {
using namespace std;

ListNode* Solution::mergeTwoLists(ListNode* a, ListNode* b) {
  if (a == nullptr) {
    return b;
  } else if (b == nullptr) {
    return a;
  }
  ListNode head;
  ListNode* tail{&head};
  ListNode* aPtr{a};
  ListNode* bPtr{b};
  while (aPtr != nullptr && bPtr != nullptr) {
    if (aPtr->val < bPtr->val) {
      tail->next = aPtr;
      aPtr = aPtr->next;
    } else {
      tail->next = bPtr;
      bPtr = bPtr->next;
    }
    tail = tail->next;
  }
  tail->next = (aPtr != nullptr) ? aPtr : bPtr;
  return head.next;
}

ListNode* Solution::merge(vector<ListNode*>& lists, int l, int r) {
  if (l == r) {
    return lists[l];
  }
  if (l > r) {
    return nullptr;
  }
  int mid = (l + r) >> 1;
  return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
}

void Solution::back_track_generate_parenthesis_no_res(
    int n, std::vector<string>& Res) {
  // std::stack<string> stk;
  std::stack<std::tuple<string, int, int>> stk;
  // if n == 3 then "(" -> stack "((" -> stack "(((" -> stack
  // right < left then "((()"   then"((())"  then "((()))"
  // so the solution upper space occupation very high
  //
  if (n == 0) {
    return;
  }
  // stk.top
  stk.push({"", 0, 0});
  while (!stk.empty()) {
    std::tuple<string, int, int> top_elem{stk.top()};
    stk.pop();
    if ((std::get<1>(top_elem) == n) && (std::get<2>(top_elem) == n)) {
      Res.emplace_back(std::get<0>(top_elem));
      continue;
    }
    if (std::get<2>(top_elem) < std::get<1>(top_elem)) {
      stk.emplace(std::make_tuple(std::get<0>(top_elem) + ")",
                                  std::get<1>(top_elem),
                                  std::get<2>(top_elem) + 1));
    }
    if (std::get<1>(top_elem) < n) {
      stk.emplace(std::make_tuple(std::get<0>(top_elem) + "(",
                                  std::get<1>(top_elem) + 1,
                                  std::get<2>(top_elem)));
    }
  }

  // while ((std::get<1>(stk.top())) < n) {
  //   // std::tuple<string, int, int> stk_top;
  //   if (!stk.empty()) {
  //     stk.push(std::make_tuple(std::get<0>(stk.top()) + "(",
  //                              std::get<1>(stk.top()) + 1,
  //              std::get<2>(stk.top())));
  //     // stk_top.first += stk.top().first;
  //     // stk_top.first = stk.top().first + "(";
  //     // stk_top.second =
  //   }
  //   // stk.push("(");
  // }
}

void Solution::board_DFS(vector<vector<char>>& board, string& word,
                         vector<vector<bool>>& visited, int i, int j, int k,
                         bool& find) {
  if (find) {
    return;
  }
  if (visited[i][j]) {
    return;
  }
  if (board.at(i).at(j) != word.at(k)) {
    return;
  }
  if (k == word.length() - 1) {
    find = true;
    return;
  }
  visited.at(i).at(j) = true;
  vector<pair<int, int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  for (auto const& dir : dirs) {
    int new_i{i + dir.first};
    int new_j{j + dir.second};
    if ((new_i >= 0 && new_i < board.size()) &&
        (new_j >= 0 && new_j < board.at(0).size())) {
      // visited.at(new_i).at(new_j) = true;
      board_DFS(board, word, visited, new_i, new_j, k + 1, find);
    }
    if (find) {
      break;
    }
  }
  visited.at(i).at(j) = false;
}
bool Solution::exist1(vector<vector<char>>& board, string word) {
  if (board.empty() || board[0].empty() || word.empty()) {
    return false;
  }
  unordered_map<char, int> board_cnt;
  unordered_map<char, int> word_cnt;
  for (auto const& row : board) {
    for (char c : row) board_cnt[c]++;
  }
  for (char c : word) {
    if (++word_cnt[c] > board_cnt[c]) {
      return false;
    }
  }
  int rows{board.size()};
  int cols{board[0].size()};
  const vector<pair<int, int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  stack<tuple<int, int, int, bool>> stk;
  for (int i{0}; i < rows; ++i) {
    for (int j{0}; j < cols; ++j) {
      if (board[i][j] != word[0]) {
        continue;
      }
      board[i][j] = '\0';
      stk.emplace(i, j, 0, false);
      while (!stk.empty()) {
        auto& frame{stk.top()};
        int curr_i = get<0>(frame);
        int curr_j = get<1>(frame);
        int curr_k = get<2>(frame);
        bool is_processed = get<3>(frame);
        if (!is_processed) {
          if (curr_k == word.length() - 1) {
            board[curr_i][curr_j] = word[curr_k];
            return true;
          }
          get<3>(frame) = true;

          for (auto it{dirs.rbegin()}; it != dirs.rend(); ++it) {
            int new_i{curr_i + it->first};
            int new_j{curr_j + it->second};
            if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols &&
                board[new_i][new_j] == word[curr_k + 1]) {
              // 原地标记访问
              board[new_i][new_j] = '\0';
              stk.emplace(new_i, new_j, curr_k + 1, false);
            }
          }
        } else {
          board[curr_i][curr_j] = word[curr_k];
          stk.pop();
        }
      }
    }
  }
  return false;
}

int Solution::gcd(int x, int y) { return (x % y == 0 ? y : gcd(y, x % y)); }



} //#end namespace MYCODE