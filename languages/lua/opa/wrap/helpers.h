
#ifndef OPA_LUA_WRAP_HELPERS_H_
#define OPA_LUA_WRAP_HELPERS_H_

namespace opa {
namespace lua {
namespace wrap {

template <size_t... I>
struct Indexes {};

template <size_t N, size_t... I>
struct MakeIndexes {
  using type = typename MakeIndexes<N-1, N-1, I...>::type;
};

template <size_t... I>
struct MakeIndexes<0u, I...> {
  using type = Indexes<I...>;
};

template <size_t I, typename First, typename... Args>
struct TypeAt {
  static_assert(I < 1+sizeof...(Args), "Index out of bounds");
  using type = typename TypeAt<I-1, Args...>::type;
};

template <typename First, typename... Args>
struct TypeAt<0u, First, Args...> {
  using type = First;
};

} // namespace wrap
} // namespace lua
} // namespace opa

#endif // OPA_LUA_WRAP_HELPERS_H_

