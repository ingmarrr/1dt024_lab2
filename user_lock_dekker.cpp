#include "user_locks.hpp"
#include <atomic>


// also works with std::memory_order_acquire

user_lock_dekker::user_lock_dekker()
    : user_lock() {
        m_flag[0].store(false, std::memory_order_seq_cst);
        m_flag[1].store(false, std::memory_order_seq_cst);
        m_turn.store(0, std::memory_order_seq_cst);
}

void user_lock_dekker::lock(int thread_id) {
    int other_thread = 1-thread_id;

    m_flag[thread_id].store(true, std::memory_order_seq_cst);

    while (m_flag[other_thread].load(std::memory_order_seq_cst))
    {
        if (m_turn.load(std::memory_order_seq_cst) != thread_id) {
            m_flag[thread_id].store(false, std::memory_order_seq_cst);
            while (m_turn.load(std::memory_order_seq_cst) != thread_id)  { 
            } 
            
            m_flag[thread_id].store(true, std::memory_order_seq_cst);
        }
    } 
}

void user_lock_dekker::unlock(int thread_id) {
    int other_thread = 1-thread_id;

    m_turn.store(other_thread, std::memory_order_seq_cst);
    m_flag[thread_id].store(false, std::memory_order_seq_cst);

}
