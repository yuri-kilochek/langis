#ifndef LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_SLOT_BLOCK
#define LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_SLOT_BLOCK

#include <langis/detail/block.hpp>

namespace langis::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct signal_block;

template <typename... Args>
struct slot_block
: block
{
    slot_block* next = nullptr;
    slot_block** prev_next = nullptr;
    strong_ptr<signal_block<Args...>> signal = nullptr;

    void disconnect() {
        if (!signal) { return; }
    }

    virtual
    void invoke(Args&&... args)
    = 0;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
