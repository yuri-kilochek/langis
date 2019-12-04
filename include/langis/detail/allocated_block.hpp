#ifndef LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_ALLOCATED_BLOCK
#define LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_ALLOCATED_BLOCK

#include <langis/detail/block.hpp>

#include <memory>
#include <utility>

namespace langis::detail {
///////////////////////////////////////////////////////////////////////////////

template <typename Allocator>
struct allocated_block
: block
{
    explicit
    allocated_block(Allocator const& allocator)
    : allocator_(allocator)
    {}

    void dispose()
    override
    {
        using allocator_traits = std::allocator_traits<Allocator>;
        using real_type = typename allocator_traits::value_type;
        auto real_this = static_cast<real_type*>(this);

        auto allocator = std::move(allocator_);
        allocator_traits::destroy(allocator, real_this);
        allocator_traits::deallocate(allocator, real_this, 1);
    }

private:
    Allocator allocator_;
};

template <typename Block, typename ProtoAllocator, typename... Args>
auto allocate_block(ProtoAllocator const& proto_allocator, Args&& args)
-> block::ptr<Block>
{
    using proto_allocator_traits = std::allocator_traits<ProtoAllocator>;

    using allocator_traits
        = typename proto_allocator_traits::template rebind_traits<Block>;
    using allocator_type = typename allocator_traits::allocator_type;
    allocator_type allocator(proto_allocator);

    auto* block = allocator_traits::allocate(allocator, 1);
    try {
        allocator_traits::construct(allocator,
                                    block, std::forward<Args>(args)...);
    } catch (...) {
        allocator_traits::deallocate(allocator, block, 1);
        throw;
    }
    return detail::block::ptr<Block>(block);
}

///////////////////////////////////////////////////////////////////////////////
}

#endif
