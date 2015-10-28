#ifndef GMB_UTILS_MARKDOWN_PARSING_HPP_INCLUDED
#define GMB_UTILS_MARKDOWN_PARSING_HPP_INCLUDED

#include <ostream>
#include <variant_operation/variant_operation.hpp>

namespace gmb { namespace utils { namespace markdown
{
  struct stack_item_proxy
  {
    using proxied_t = gmb::utils::basic_variant_operation<bool, char, std::ostream &, stack_item_proxy &> *;
    stack_item_proxy(proxied_t &p)
      : p_(p)
    { }

    proxied_t & get() const
    {
      return p_;
    }

  private:
    proxied_t &p_;
  };

  using stack_item_t = gmb::utils::basic_variant_operation<bool, char, std::ostream &, stack_item_proxy &>;

  void initialize_state();
  bool empty();
  stack_item_t & top();
  void push(stack_item_t const &item);
  stack_item_t pop();
  bool decode(char, std::ostream &);
  
}}}
#endif //GMB_UTILS_MARKDOWN_PARSING_HPP_INCLUDED
