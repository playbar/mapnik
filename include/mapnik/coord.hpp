/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_COORD_HPP
#define MAPNIK_COORD_HPP

// boost
#include <boost/operators.hpp>

// stl
#include <iomanip>
#include <sstream>

namespace mapnik {
template <typename T,int dim>
struct coord {
    typedef T type;
};

template <typename T>
struct coord<T,2>
    : boost::addable<coord<T,2>,
                     boost::addable2<coord<T,2>,T,
                                     boost::subtractable<coord<T,2>,
                                                         boost::subtractable2<coord<T,2>,T,
                                                                              boost::dividable2<coord<T,2>, T,
                                                                                                boost::multipliable2<coord<T,2>, T > > > > > >

{
    typedef T type;
    T x;
    T y;
public:
    coord()
        : x(),y() {}
    coord(T x_,T y_)
        : x(x_),y(y_) {}
    template <typename T2>
    coord (const coord<T2,2>& rhs)
        : x(type(rhs.x)),
          y(type(rhs.y)) {}


    coord<T,2>& operator=(coord<T,2> rhs)
    {
        swap(rhs);
        return *this;
    }

    template <typename T2>
    coord<T,2>& operator=(const coord<T2,2>& rhs)
    {
        coord<T,2> tmp(rhs);
        swap(rhs);
        return *this;
    }

    template <typename T2>
    bool operator==(coord<T2,2> const& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    coord<T,2>& operator+=(coord<T,2> const& rhs)
    {
        x+=rhs.x;
        y+=rhs.y;
        return *this;
    }

    coord<T,2>& operator+=(T rhs)
    {
        x+=rhs;
        y+=rhs;
        return *this;
    }

    coord<T,2>& operator-=(coord<T,2> const& rhs)
    {
        x-=rhs.x;
        y-=rhs.y;
        return *this;
    }

    coord<T,2>& operator-=(T rhs)
    {
        x-=rhs;
        y-=rhs;
        return *this;
    }

    coord<T,2>& operator*=(T t)
    {
        x*=t;
        y*=t;
        return *this;
    }
    coord<T,2>& operator/=(T t)
    {
        x/=t;
        y/=t;
        return *this;
    }
private:
    void swap(coord<T,2> & rhs)
    {
        std::swap(this->x, rhs.x);
        std::swap(this->y, rhs.y);
    }
};

template <typename T>
struct coord<T,3>
{
    typedef T type;
    T x;
    T y;
    T z;
public:
    coord()
        : x(),y(),z() {}
    coord(T x_,T y_,T z_)
        : x(x_),y(y_),z(z_) {}

    template <typename T2>
    coord (coord<T2,3> const& rhs)
        : x(type(rhs.x)),
          y(type(rhs.y)),
          z(type(rhs.z)) {}

    coord<T,3> operator=(coord<T,3> rhs)
    {
        swap(rhs);
        return *this;
    }

    template <typename T2>
    coord<T,3>& operator=(coord<T2,3> const& rhs)
    {
        coord<T,3> tmp(rhs);
        swap(tmp);
        return *this;
    }
private:
    void swap(coord<T,3> & rhs)
    {
        std::swap(this->x, rhs.x);
        std::swap(this->y, rhs.y);
        std::swap(this->z, rhs.z);
    }
};

typedef coord<double,2> coord2d;
typedef coord<int,2> coord2i;


template <typename charT,typename traits,typename T ,int dim>
inline std::basic_ostream<charT,traits>&
operator << (std::basic_ostream<charT,traits>& out,
             const coord<T,dim>& c);

template <typename charT,typename traits,typename T>
inline std::basic_ostream<charT,traits>&
operator << (std::basic_ostream<charT,traits>& out,
             const coord<T,2>& c)
{
    std::basic_ostringstream<charT,traits> s;
    s.copyfmt(out);
    s.width(0);
    s << "coord2(" << std::setprecision(16)
      << c.x << "," << c.y<< ")";
    out << s.str();
    return out;
}

template <typename charT,typename traits,typename T>
inline std::basic_ostream<charT,traits>&
operator << (std::basic_ostream<charT,traits>& out,
             const coord<T,3>& c)
{
    std::basic_ostringstream<charT,traits> s;
    s.copyfmt(out);
    s.width(0);
    s << "coord3(" << std::setprecision(16)
      << c.x << "," << c.y<< "," << c.z<<")";
    out << s.str();
    return out;
}
}

#endif // MAPNIK_COORD_HPP
