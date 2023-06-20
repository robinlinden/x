#include "wasm3_hpp/wasm3.hpp"

#include <wasm3.h>

#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

namespace wasm3 {

struct Module::Impl {
    std::unique_ptr<M3Environment, decltype([](auto *e) { m3_FreeEnvironment(e); })> env;
    std::unique_ptr<M3Runtime, decltype([](auto *r) { m3_FreeRuntime(r); })> runtime;
    std::vector<std::uint8_t> wasm_bytes;
};

Module::~Module() = default;

std::optional<Module> Module::load(StackSize stack_size, std::istream &wasm_data) {
    if (!wasm_data || wasm_data.eof()) {
        std::cerr << "Unable to use wasm data\n";
        return std::nullopt;
    }

    decltype(Module::Impl::env) env{m3_NewEnvironment()};
    if (env == nullptr) {
        std::cerr << "Unable to create environment\n";
        return std::nullopt;
    }

    void *user_data = nullptr;
    decltype(Module::Impl::runtime) runtime{m3_NewRuntime(env.get(), stack_size.bytes, user_data)};
    if (runtime == nullptr) {
        std::cerr << "Unable to create runtime\n";
        return std::nullopt;
    }

    IM3Module module = nullptr;
    std::vector<std::uint8_t> wasm_bytes{std::istreambuf_iterator{wasm_data}, {}};
    if (auto const *err = m3_ParseModule(env.get(), &module, wasm_bytes.data(), wasm_bytes.size()); err != m3Err_none) {
        std::cerr << "Unable to parse module: " << err << '\n';
        return std::nullopt;
    }

    assert(module != nullptr); // Filled in by m3_ParseModule.

    // Ownership of the module is transferred to the runtime here.
    if (auto const *err = m3_LoadModule(runtime.get(), module); err != m3Err_none) {
        std::cerr << "Unable to load module: " << err << '\n';
        m3_FreeModule(module);
        return std::nullopt;
    }

    Module m;
    m.impl_ = std::make_unique<Module::Impl>(std::move(env), std::move(runtime), std::move(wasm_bytes));
    return std::optional<Module>{std::move(m)};
}

} // namespace wasm3
