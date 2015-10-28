#include <cassert>

#include "parsing.hpp"
#include "states.hpp"

#define MYNS gmb::utils::markdown

using namespace MYNS;

namespace
{
  using stack_ptr_t = stack_item_t *;

  char stack[sizeof(stack_item_t) * (1 << (8*sizeof(char)))];
  stack_ptr_t stack_ptr = reinterpret_cast<stack_ptr_t>(&stack[0]);
}

void MYNS::initialize_state()
{
#if _DEBUG
  assert(empty());
#endif
  push(stack_item_t(base_state()));
}

bool MYNS::empty()
{
  return stack_ptr == reinterpret_cast<stack_item_t *>(&stack[0]);
}

stack_item_t & MYNS::top()
{
#if _DEBUG
  assert(!empty());
#endif
  return *(stack_ptr-1);
}

void MYNS::push(stack_item_t const &item)
{
  new (stack_ptr) stack_item_t(item);
  stack_ptr++;
}

stack_item_t MYNS::pop()
{
#if _DEBUG
  assert(!empty());
#endif
  auto tmp = *(stack_ptr-1);
  (stack_ptr-1)->~stack_item_t();
  stack_ptr--;

  return std::move(tmp);
}

bool MYNS::decode(char c, std::ostream &os)
{
  return (*(stack_ptr-1))(std::move(c), os, stack_item_proxy(stack_ptr));
}
  
