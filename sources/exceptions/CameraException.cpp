//
// Created by brian on 5/16/19.
//

#include "exceptions/CameraException.hpp"

indie::exceptions::CameraException::CameraException(const std::string &err, const std::string &where)
    : ECSException(err, where)
{

}
