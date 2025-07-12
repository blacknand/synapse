# 🧠 Synapse

Synapse is a high-performance, multi-threaded, in-memory C++20 cache. It's engineered from the ground up for massive concurrency, providing a robust and low-latency solution for demanding applications. The architecture is built around modern C++ practices, focusing on scalability, thread safety, and performance that is not just claimed, but proven through rigorous benchmarking.

This project serves as a deep dive into the complexities of concurrent systems design, implementing professional-grade techniques to build a foundational component for any large-scale service.

---

## Core Features

* **Massively Concurrent Hash Map**: Utilizes **sharded (striped) locking** to minimize lock contention, allowing for high-throughput access across multiple threads.
* **Advanced Concurrency Primitives**: Leverages `std::shared_mutex` to allow for concurrent reads, maximizing performance for read-heavy workloads.
* **Pluggable Eviction Policies**: Designed with a **strategy pattern** to easily switch between different cache eviction algorithms.
    * `LRUPolicy` (Least Recently Used) - *Implemented*
    * `LFUPolicy` (Least Frequently Used) - *Planned*
* **Quantitative Benchmarking**: Integrated with **Google Benchmark** to provide concrete data on throughput, latency, and scalability under various thread counts.
* **Modern C++ Design**: Built with C++20, using features like `std::optional`, `std::unique_ptr`, and a clean, modern API.

---

## Build and Test

Synapse uses CMake for building and Google Test for unit testing.

**Prerequisites:**
* A C++20 compatible compiler (GCC 10+, Clang 12+)
* CMake 3.16+
* Google Test (fetched automatically by CMake)
* Google Benchmark (fetched automatically by CMake)

**Build Instructions:**

```bash
# Clone the repository
git clone [https://github.com/your-username/synapse.git](https://github.com/your-username/synapse.git)
cd synapse

# Configure the build
cmake -B build -S .

# Build the project, tests, and benchmarks
cmake --build build

# Run tests
cd build
ctest

# Run benchmarks
./bench/run_benchmarks
