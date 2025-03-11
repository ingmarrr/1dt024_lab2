#include "atomic_counters.hpp"
#include <atomic>

atomic_counter_atomic_cas::atomic_counter_atomic_cas()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_atomic_cas::increment() 
{
    int expected, desired;
    do {
        expected = m_value.load(std::memory_order_release);
        desired = expected + 1;
    } while (!m_value.compare_exchange_weak(expected, desired, 
        std::memory_order_release, std::memory_order_relaxed
    ));
    return expected;
}

int atomic_counter_atomic_cas::decrement() 
{
    int expected, desired;
    do {
        expected = m_value.load(std::memory_order_release);
        desired = expected - 1;
    } while (!m_value.compare_exchange_weak(expected, desired, 
        std::memory_order_release, std::memory_order_relaxed
    ));
    return expected;
}

void atomic_counter_atomic_cas::set(int value) 
{
    m_value.store(value, std::memory_order_release);
}

int atomic_counter_atomic_cas::get() 
{
    return m_value.load(std::memory_order_release);
}