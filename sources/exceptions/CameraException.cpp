//
// Created by brian on 5/16/19.
//

#include "CameraException.hpp"

jf::exceptions::CameraException::CameraException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}
