/*
 * Created by 李晨曦 on 2019-06-30.
 */
#include <boost/coroutine2/all.hpp>
#include <iostream>

template<typename T>
using boost_coroutine = boost::coroutines2::coroutine<T>;
using std::cout;
using std::endl;
auto foo(boost_coroutine<int>::push_type &push) -> void {
    push(1);
    push(2);
}

auto main() -> int {
    boost_coroutine<int>::pull_type pull(foo);
    cout << pull.get() << endl;
    cout << !pull << endl;
    pull();
    cout << pull.get() << endl;
    cout << !pull << endl;
    pull();
    cout << pull.get() << endl;
    cout << !pull << endl;
    pull();
    cout << pull.get() << endl;
    cout << !pull << endl;
}