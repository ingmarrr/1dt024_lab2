#include "atomic_counters.hpp"
#include <mutex>

atomic_counter_lock::atomic_counter_lock()
    : atomic_counter()
    , m_value(0)
    , m_lock() {
}

int atomic_counter_lock::increment() {
    std::lock_guard<std::mutex> lock(m_lock);
    int prev_value = m_value;
    m_value = m_value + 1;
    return prev_value;
}

int atomic_counter_lock::decrement() {
    std::lock_guard<std::mutex> lock(m_lock);
    int prev_value = m_value;
    m_value = m_value - 1;
    return prev_value;
}

void atomic_counter_lock::set(int value) {
    std::lock_guard<std::mutex> lock(m_lock);
    m_value = value;
}

int atomic_counter_lock::get() {
    std::lock_guard<std::mutex> lock(m_lock);
    return m_value;
}
