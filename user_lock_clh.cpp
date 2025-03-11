#include "user_locks.hpp"

user_lock_clh::user_lock_clh()
    : user_lock()
    , m_tail(&m_cells[2]) {
    m_local[0].local_cell = &m_cells[0];
    m_local[0].previous = nullptr;
    m_local[1].local_cell = &m_cells[1];
    m_local[1].previous = nullptr;

    m_cells[0] = false;
    m_cells[1] = false;
    m_cells[2] = false;
}

void user_lock_clh::lock(int thread_id) {
    
    local_l *l = &m_local[thread_id]; 
    *l->local_cell = true;  //init to “busy”
    l->previous = m_tail.exchange(l->local_cell, std::memory_order_seq_cst);    //*L(tail) now point to our I* 
    while (*l->previous != 0) {}    //spin unit prev is done 
}

void user_lock_clh::unlock(int thread_id) {
    local_l *l = &m_local[thread_id];
    *l->local_cell = false;     /* release the lock */
    l->local_cell = l->previous;    /* reuse the previous guy’s *P*/
}
