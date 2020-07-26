/*
** EPITECH PROJECT, 2020
** DLLoader.hpp
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <link.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

template<typename T>
class DLLoader {
    public:
        DLLoader(std::string const &path) {
            this->_path = path;
            this->_handle = dlopen(this->_path.c_str(), RTLD_LAZY);
            if (this->_handle == NULL) {
                std::string error = dlerror();
                std::cout << error << std::endl;
                exit (84);
            }
        };
        ~DLLoader() {
            dlclose(this->_handle);
        };
        T *getInstance(std::string entry_point) {
            T* (*ptr)(void);
            ptr = reinterpret_cast<T *(*)(void)>(dlsym(this->_handle, entry_point.c_str()));
            if (ptr == NULL)
                return NULL;
            return ptr();
        };
        DLLoader &operator=(DLLoader const &copy) {
            if (&copy != this)
                this->_handle = copy._handle;
            return this;
        }
        const std::string getName() {
            return this->_path;
        }

    private:
        std::string _path;
        void *_handle;
    protected:
    private:
};

#endif /* !DLLOADER_HPP_ */
