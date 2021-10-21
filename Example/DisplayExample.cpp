//
// Created by wjl on 2021/10/18.
//
#include <iostream>
#include "ui/display/DisplayInfo.h"
using namespace cppcommon;

int main() {
    auto infos = GetDisplayInfos();
    std::cout << "infos: " << infos.size() << std::endl;
}