#pragma once

#include <stdio.h>

#include <time.h>

#include <iostream>
#include <iterator>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <algorithm>
#include <random>
#include <deque>
#include <unordered_map>
#include <chrono>

#include <string>
#include <sstream>

int AllTasks();

typedef std::vector<int> SlnType;
  
int ChangeEndian();
std::string RemoveDuplicates(std::string str);
void Rotate(std::vector<int> &arr, size_t shift);

bool IsAnagram(const std::string &str1, const std::string &str2);

