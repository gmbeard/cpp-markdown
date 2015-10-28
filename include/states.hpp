#ifndef GMB_UTILS_MARKDOWN_STATES_HPP_INCLUDED
#define GMB_UTILS_MARKDOWN_STATES_HPP_INCLUDED

#include <ostream>
//#include "parsing.hpp"

namespace gmb { namespace utils { namespace markdown
{
  struct stack_item_proxy;

  struct base_state
  {
    bool operator()(char, std::ostream &, stack_item_proxy &);
  private:
    char written_text_ = 0x00;
  };

  struct header_state
  {
    bool operator()(char, std::ostream &, stack_item_proxy &);
  private:
    size_t level_ = 0;
    int inc_ = 1;
    char written_text_ = 0x00;
  };

  struct emphasis_state
  {
    bool operator()(char, std::ostream &, stack_item_proxy &);
  };

  struct code_state
  {
    bool operator()(char, std::ostream &, stack_item_proxy &);
  private:
    size_t level_ = 0;
    int inc_ = 1;
    char written_text_ = 0x00;
  };

  struct text_state
  {
    bool operator()(char, std::ostream &, stack_item_proxy &);
  };

}}}

#endif //GMB_UTILS_MARKDOWN_STATES_HPP_INCLUDED
