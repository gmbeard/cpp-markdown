#include "parsing.hpp"
#include "states.hpp"

using namespace gmb::utils::markdown;

bool base_state::operator()(char c, std::ostream & os, stack_item_proxy &p)
{
  switch(c) {
    case '#':
      if(!written_text_) {
        push(stack_item_t(header_state()));
      //  written_text_ |= 0x01;
      }
      else {
        return false;
      }
      break;
//    case '*':
//      written_text_ |= 0x01; 
//      push(stack_item_t(emphasis_state()));
//      break;
    case '`':
      push(stack_item_t(code_state()));
      break;
    case '\r':
      return true;
    case '\n':
      if(written_text_) {
        os << "</p>"; 
      }
      written_text_ = 0x00;
      return true;
    default:
      if(!written_text_) {
        os << "<p>";
      }
      written_text_ |= 0x01;
      return false;
  }

  return top()(std::move(c), os, p);
}

bool header_state::operator()(char c, std::ostream & os, stack_item_proxy &p)
{
  switch(c) {
    case '#':
      if(!written_text_) {
        level_ += inc_;
      }
      return true;
//    case '*':
//      push(stack_item_t(emphasis_state()));
//      written_text_ |= 0x01;
//      break;
//    case '`':
//      push(stack_item_t(code_state()));
//      written_text_ |= 0x01;
//      break;
    case '\r':
      if(written_text_) {
        os << "</h" << level_ << ">";
      }
      pop();
      break;
    case '\n':
      if(written_text_) {
        os << "</h" << level_ << ">";
      }
      pop();
      break;
    default:
      if(!written_text_) {
        os << "<h" << level_ << ">";
      }
      written_text_ |= 0x01;
      return false;
  }

  return top()(std::move(c), os, p);
}

bool emphasis_state::operator()(char c, std::ostream & os, stack_item_proxy &)
{
  //  TODO(Greg): Implement
  return false;
}

bool code_state::operator()(char c, std::ostream & os, stack_item_proxy &p)
{
  switch(c) {
    case '`':
      if(!written_text_) {
        level_++;
      }
      else {
        level_--;
      }
      if(level_ == 0) {
        os << "</code>";
        written_text_ = 0x00;
        pop();
      }
      return true;
//    case '\r':
//    case '\n':
//      if(!written_text_) {
//        pop();
//      }
//      else {
//        return false;
//      }
//      break;
    default:
      if(!written_text_) {
        os << "<code>";
      }
      written_text_ |= 0x01;
      return false;
  }

 // return top()(std::move(c), os, p);
}

bool text_state::operator()(char c, std::ostream & os, stack_item_proxy &)
{
  //  TODO(Greg): Implement
  return false;
}

