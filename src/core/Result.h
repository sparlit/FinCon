#pragma once
#include <variant>
#include <string>

namespace core {

template<typename T>
class Result {
public:
    Result(const T& val) : data_(val) {}
    Result(T&& val) : data_(std::move(val)) {}
    Result(const std::string& err) : data_(err) {}
    Result(std::string&& err) : data_(std::move(err)) {}

    bool has_value() const { return std::holds_alternative<T>(data_); }
    const T& value() const { return std::get<T>(data_); }
    const std::string& error() const { return std::get<std::string>(data_); }

    operator bool() const { return has_value(); }
    const T* operator->() const { return &value(); }

private:
    std::variant<T, std::string> data_;
};

// Helper for creating errors
inline auto Unexpected(std::string err) {
    return err;
}

} // namespace core
