#ifndef LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_SIGNAL_BLOCK
#define LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_SIGNAL_BLOCK

#include <langis/detail/block.hpp>

#include <mutex>

namespace langis::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct slot_block;

template <typename... Args>
struct signal_block
: block
{
    std::mutex mutex;
    slot_block<Args...>* first_slot;

    void retain()
    const noexcept
    { use_count_.fetch_add(1, std::memory_order_relaxed); }

    void release()
    const noexcept
    {
        if (use_count_.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            dispose();
        }
    }

private:
    mutable
    std::atomic<std::size_t> use_count_;

    virtual
    void dispose()
    const noexcept
    = 0;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
