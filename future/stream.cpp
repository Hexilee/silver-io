/*
 * Created by 李晨曦 on 2019-07-03.
 */

#include "future/stream.hpp"

auto sio::future::operator<<(std::ostream &os, const FlowStatus &stat) -> std::ostream & {
    switch (stat) {
        case FlowStatus::Pending:
            os << "Pending";
            break;
        case FlowStatus::Continue:
            os << "Continue";
            break;
        case FlowStatus::Break:
            os << "Break";
            break;
    }
    return os;
}