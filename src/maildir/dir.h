#pragma once

#include <filesystem>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "entry.h"

namespace fs = std::filesystem;

namespace maildir
{

  fs::path &resolve(fs::path &);

  fs::path locate();

  bool is_maildir(const fs::path &);

  class maildir_iterator
  {
  public:
    typedef Entry value_type;
    typedef ptrdiff_t difference_type;
    typedef const Entry *pointer;
    typedef const Entry &reference;
    typedef std::input_iterator_tag iterator_category;

    maildir_iterator() : m_state(Empty) {}
    maildir_iterator(const fs::path &path) : m_state(Initial), m_path(path)
    {
      next();
    }

    maildir_iterator &operator++()
    {
      next();
      return *this;
    }
    maildir_iterator operator++(int)
    {
      auto old = *this;
      next();
      return old;
    }
    const Entry &operator*() const
    {
      return *m_current;
    }
    bool operator==(const maildir_iterator &other) const
    {
      if (m_state == Empty)
        return other.m_state == Empty;
      else if (m_state != other.m_state)
        return false;
      else
        return m_current->path() == other.m_current->path();
    }
    bool operator!=(const maildir_iterator &other)
    {
      return !(*this == other);
    }

    maildir_iterator begin()
    {
      return *this;
    }
    maildir_iterator end()
    {
      return maildir_iterator();
    }

  private:
    void next();
    bool dir_end() const;
    void set_empty();

    enum State
    {
      Empty,
      Initial,
      ReadingNew,
      ReadingCur,
    } m_state;
    std::optional<fs::path> m_path;
    std::optional<fs::directory_iterator> m_dir;
    std::optional<Entry> m_current;
  };

}
