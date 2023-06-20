#ifndef WASM3_HPP_WASM3_HPP_
#define WASM3_HPP_WASM3_HPP_

#include <iosfwd>
#include <memory>
#include <optional>

namespace wasm3 {

struct StackSize {
    int bytes;
};

class Module {
public:
    Module() = default;
    Module &operator=(Module &&) = default;
    Module(Module &&) = default;
    ~Module();

    static std::optional<Module> load(StackSize, std::istream &wasm_data);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace wasm3

#endif
