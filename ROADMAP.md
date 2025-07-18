# The 4-Week "Synapse" Sprint Roadmap

---

### **Week 1: Build the Concurrent Core** 🏗️

* **Goal**: Implement and test the sharded hash map. This is the foundation and the most critical demonstration of your concurrency skills.
* **Tasks**:
    1.  **Implement `Shard` and `ConcurrentHashMap`**: Create the core structures. The `ConcurrentHashMap` will hold a `std::vector` of `Shard`s, and each `Shard` will contain a `std::unordered_map` and its own `std::shared_mutex`.
    2.  **Implement Core API**: Code the `insert`, `get`, and `erase` functions. Ensure you use `std::shared_lock` for `get` and `std::unique_lock` for `insert`/`erase` to leverage the read-write capabilities of the mutex.
    3.  **Write Initial Multi-threaded Tests**: Use Google Test to immediately confirm your locking strategy is correct by spawning several threads to perform concurrent reads and writes.

---

### **Week 2: Integrate a Basic Eviction Policy** 🔄

* **Goal**: Demonstrate your ability to manage locking across different components—a key senior-level challenge.
* **Tasks**:
    1.  **Create a simple `LRUPolicy` class**: This class will manage a `std::list` of keys to track usage order, protected by its own `std::mutex`.
    2.  **Integrate into a `Cache` class**: The main `Cache` class will orchestrate interactions between the `ConcurrentHashMap` and the `LRUPolicy`.
    3.  **Implement Strict Lock Ordering**: To prevent deadlocks, establish and enforce a strict locking order. For any operation, you must **always lock the map's shard first, then lock the policy's mutex.**

---

### **Week 3: Prove It with Benchmarks** 📊

* **Goal**: Quantify your "high-performance" claim with hard data.
* **Tasks**:
    1.  **Set up Google Benchmark**: Integrate the benchmarking library into your build.
    2.  **Write Multi-threaded Benchmarks**: Create tests that simulate realistic workloads (e.g., 90% reads, 10% writes).
    3.  **Run and Graph Results**: Use Google Benchmark's `Threads()` function to test with 1, 2, 4, 8, and 16 threads. Plot the results (operations/second vs. thread count) to visually demonstrate the scalability of your design.

---

### **Week 4: Refactor, Document, and Polish** ✨

* **Goal**: Package the project for presentation. A brilliant project with poor documentation will not get noticed.
* **Tasks**:
    1.  **Refactor (Time Permitting)**: If time allows, refactor the `LRUPolicy` to use the Strategy design pattern by extracting an abstract `EvictionPolicy` base class. This demonstrates foresight in your design.
    2.  **Write a Killer `README.md`**: Your README is your project's storefront. It must clearly explain the architecture (sharded locking), showcase your performance graphs, and provide simple build instructions.
    3.  **Code Cleanup**: Review your entire codebase. Add comments explaining complex logic, especially the locking hierarchy. Ensure the public API is clean and well-documented.