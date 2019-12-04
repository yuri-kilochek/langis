#ifndef LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_BLOCK
#define LANGIS_DETAIL_INCLUDE_GUARD_DETAIL_BLOCK

#include <memory>

namespace langis::detail {
///////////////////////////////////////////////////////////////////////////////

struct block {
    virtual
    void dispose()
    = 0;

    struct disposer {
        void operator()(block* ptr)
        const noexcept
        { ptr->dispose(); }
    };

    template <typename Block>
    using ptr = std::unique_ptr<Block, disposer>;
};

///////////////////////////////////////////////////////////////////////////////
}

#endif
