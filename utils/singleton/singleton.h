/*
 * SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#ifndef UTILS_SINGLETON_SINGLETON_H_
#define UTILS_SINGLETON_SINGLETON_H_

namespace utils
{
    template <typename T>
    class Singleton
    {
    public:
        static T *instance()
        {
            static T instance;
            return &instance;
        }

        Singleton(T &&) = delete;
        Singleton(const T &) = delete;
        void operator=(const T &) = delete;

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;
    };

}
#endif
