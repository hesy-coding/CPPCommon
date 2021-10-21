//
// Created by wjl on 2021/10/18.
//

#ifndef CPPCOMMON_RECT_H
#define CPPCOMMON_RECT_H
#include "base/BaseDefs.h"

namespace cppcommon {
    class Point {
    public:
        Point(): _x(0), _y(0) {}
        Point(float x, float y): _x(x), _y(y) {}
        Point(long x, long y): _x(static_cast<float>(x)), _y(static_cast<float>(y)) {}

        float X() const {
            return _x;
        }

        float Y() const {
            return _y;
        }

    private:
        float _x;
        float _y;
    };

    class Size {
    public:
        Size(): _width(0), _height(0) {}
        Size(float width, float height): _width(width), _height(height) {}
        Size(long width, long height): _width(static_cast<float>(width)), _height(static_cast<float>(height)) {}

        float Width() const {
            return _width;
        }

        float Height() const {
            return _height;
        }

    private:
        float _width;
        float _height;
    };

    class Rect {
    public:
        Rect(const Point &p, const Size &size): _point(p), _size(size) {}
        Rect(float x, float y, float width, float height)
        : _point(x, y), _size(width, height) {}

#if defined(CPP_CMMN_OS_WIN)
        explicit Rect(const RECT &rc)
        : _point(rc.left, rc.top), _size(rc.right - rc.left, rc.bottom - rc.top) {}
#endif

        const Point & point() const {
            return _point;
        }

        const Size & size() const {
            return _size;
        }

        float Left() const {
            return _point.X();
        }

        float Right() const {
            return _point.X() + _size.Width();
        }

        float Top() const {
            return _point.Y();
        }

        float Bottom() const {
            return _point.Y() + _size.Height();
        }

    private:
        Point _point;
        Size _size;
    };
}
#endif //CPPCOMMON_RECT_H
