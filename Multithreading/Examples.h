#pragma once

#include <functional>
#include <future>

void ExamplesRun();

//template <typename Future, typename Work>
//auto then(Future f, Work w) -> std::future<decltype(w(f.get()))>
//{
//    return std::async([&] { return w(f.get()); });
//}
//
//auto then(std::future<int> f, std::function<bool(int)> w) ->
//std::future<decltype(w(f.get()))>
//{
//    return std::async([&] { return w(f.get()); });
//}
//
