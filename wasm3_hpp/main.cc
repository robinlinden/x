#include <wasm3.h>

#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Not enough arguments\n";
        return 1;
    }

    std::unique_ptr<M3Environment, decltype([](auto *e) { m3_FreeEnvironment(e); })> env{
            m3_NewEnvironment()};
    if (env == nullptr) {
        std::cerr << "Unable to create environment\n";
        return 1;
    }

    constexpr std::uint32_t kStackSizeInBytes = 512;
    void *user_data = nullptr;
    std::unique_ptr<M3Runtime, decltype([](auto *r) { m3_FreeRuntime(r); })> runtime{
            m3_NewRuntime(env.get(), kStackSizeInBytes, user_data)};
    if (runtime == nullptr) {
        std::cerr << "Unable to create runtime\n";
        return 1;
    }

    std::ifstream wasm_file{argv[1], std::ifstream::binary | std::ifstream::in};
    if (!wasm_file) {
        std::cerr << "Unable to open wasm file\n";
        return 1;
    }

    IM3Module module = nullptr;
    std::vector<std::uint8_t> wasm_bytes{std::istreambuf_iterator{wasm_file}, {}};
    if (auto const *err = m3_ParseModule(env.get(), &module, wasm_bytes.data(), wasm_bytes.size()); err != m3Err_none) {
        std::cerr << "Unable to parse module: " << err << '\n';
        return 1;
    }

    assert(module != nullptr); // Filled in by m3_ParseModule.

    // Ownership of the module is transferred to the runtime here.
    if (auto const *err = m3_LoadModule(runtime.get(), module); err != m3Err_none) {
        std::cerr << "Unable to load module: " << err << '\n';
        m3_FreeModule(module);
        return 1;
    }
}
