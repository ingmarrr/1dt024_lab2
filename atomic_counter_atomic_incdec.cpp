#include "atomic_counters.hpp"
#include <atomic>

atomic_counter_atomic_incdec::atomic_counter_atomic_incdec()
    : atomic_counter()
    , m_value(0) {
}

int atomic_counter_atomic_incdec::increment() 
{
    return m_value.fetch_add(1, std::memory_order_seq_cst);
}

int atomic_counter_atomic_incdec::decrement() 
{
    return m_value.fetch_sub(1, std::memory_order_seq_cst);
}

void atomic_counter_atomic_incdec::set(int value) 
{
    m_value.store(std::memory_order_seq_cst);
}

int atomic_counter_atomic_incdec::get() 
{
    return m_value.load(std::memory_order_seq_cst);
}
