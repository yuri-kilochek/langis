#ifndef LANGIS_DETAIL_INCLUDE_GUARD_SIGNAL
#define LANGIS_DETAIL_INCLUDE_GUARD_SIGNAL

#include <langis/detail/signal_state.hpp>

#include <memory>

namespace langis {
///////////////////////////////////////////////////////////////////////////////

template <typename Signature, typename ProtoAllocator = std::allocator<void>>
struct signal;

template <typename ProtoAllocator, typename... Args>
struct signal<void(Args...), ProtoAllocator> {
    explicit
    signal(ProtoAllocator const& proto_allocator)
    noexcept
    : proto_allocator_(proto_allocator)
    {}

    signal()
    = default;

    signal(signal&&)
    = default;

    signal(signal const&)
    = delete;

    friend
    void swap(signal& a, signal& b)
    noexcept
    {
        using std::swap;
        swap(a.proto_allocator_, b.proto_allocator_);
        swap(a.state_, b.state_);
    }

    auto operator=(signal&&)
    = default;

    auto operator=(signal const&)
    = delete;

    friend
    void langis::connect<Args...>(signal<void(Args...), ProtoAllocator>&,
                                  slot<Args...>& slot);

    template <typename ActualArgs>
    void operator(ActualArgs&&... args)
    const noexcept
    {
        if (state_) {
            state_->emit(std::forward<ActualArgs>(args)...);
        }
    }

private:
    [[no_unique_address]]
    ProtoAllocator proto_allocator_;

    std::weak_ptr<detail::signal_state<ProtoAllocator, Args...>> state_;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
