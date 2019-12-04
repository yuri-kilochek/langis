#ifndef LANGIS_DETAIL_INCLUDE_GUARD_SLOT
#define LANGIS_DETAIL_INCLUDE_GUARD_SLOT

namespace langis {
///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct slot {
    template <typename... SignalArgs,
              typename Callable, typename... ActualArgs,
        std::enable_if_t<
            std::is_convertible_v<ActualArgs, Args>
        >*...>
    explicit
    slot(std::allocator_arg_t, Allocator const& allocator,
         langis::signal<SignalArgs...>& signal,
         Callable&& callbale, ActualArgs&&... args)
    :
    {}

    template <typename Callable, typename... Args_>
    explicit
    slot(langis::signal<Args...>& signal, Callable&& callbale, Args_&&... args)
    : slot(std::allocator_arg, std::allocator<char>(),
           signal, std::forward<Callable>(callable), std::forward<Args_>(args)...)
    {}

    slot()
    = default;

    slot(slot const&)
    = delete;

    slot(slot&&)
    = default;

    auto operator=(slot const&)
    -> slot&
    = delete;

    auto operator=(slot&&)
    -> slot&
    = default;



private:
    detail::strong_shared_ptr<detail::slot_block<Args...>> block_;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
