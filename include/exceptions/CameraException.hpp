//
// Created by brian on 5/16/19.
//

#ifndef INDIESTUDIO_CAMERAEXCEPTION_HPP
#define INDIESTUDIO_CAMERAEXCEPTION_HPP

#include <string>
#include "Exceptions.hpp"

namespace indie {
    namespace exceptions {
        class CameraException : public jf::ECSException {
        public:
            explicit CameraException(const std::string &err, const std::string &where = "");
        };
    }
}

#endif //INDIESTUDIO_CAMERAEXCEPTION_HPP
