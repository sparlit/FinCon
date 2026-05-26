#pragma once
#include <variant>
#include <string>

namespace FinConCore {

template<typename T>
class FinConResult {
public:
    FinConResult(const T& val) : data_(val) {}
    FinConResult(T&& val) : data_(std::move(val)) {}
    FinConResult(const std::string& err) : data_(err) {}
    FinConResult(std::string&& err) : data_(std::move(err)) {}

    bool has_value() const { return std::holds_alternative<T>(data_); }
    const T& value() const { return std::get<T>(data_); }
    const std::string& error() const { return std::get<std::string>(data_); }

    operator bool() const { return has_value(); }
    const T* operator->() const { return &value(); }

private:
    std::variant<T, std::string> data_;
};

inline auto FinConUnexpected(std::string err) {
    return err;
}

}
