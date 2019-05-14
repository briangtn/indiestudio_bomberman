/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** CompenentParticle
*/

/* Created the 14/05/2019 at 13:57 by Charlie Jeanneau */

#ifndef COMPENENTPARTICLE_HPP_
#define COMPENENTPARTICLE_HPP_

#include "Component.hpp"
#include "ComponentCreatedEvent.hpp"
#include "irrlicht.h"
#include "ECSWrapper.hpp"
#include <iostream>

namespace jf {

	class ComponentParticle : public jf::components::Component {
		public:

			ComponentParticle(jf::entities::Entity &entity, irr::core::aabbox3d<irr::f32> emiterSize,\
irr::core::vector3df initialDirection, std::pair<int, int> emitRate, std::pair<irr::video::SColor,\
irr::video::SColor> darkBrightColor, std::pair<int, int> minMaxAge, int angle,\
std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize);

			~ComponentParticle() {
				EMIT_DELETE(ComponentParticle);
			}

			irr::core::aabbox3d<irr::f32> getEmiterSize() const;
			void setEmiterSize(irr::core::aabbox3d<irr::f32> emiterSize);

			irr::core::vector3df getInitialDirection() const;
			void setInitialDirection(irr::core::vector3df initialDirection);

			std::pair<int, int> getEmitRate() const;
			void setEmitRate(std::pair<int, int> emitRate);

			std::pair<irr::video::SColor, irr::video::SColor> getDarkBrightColor() const;
			void setDarkBrightColor(std::pair<irr::video::SColor, irr::video::SColor> darkBrightColor);

			std::pair<int, int> getMinMaxAge() const;
			void setMinMaxAge(std::pair<int, int> minMaxAge);

			int getAngle() const;
			void setAngle(int angle);

			std::pair<irr::core::dimension2df, irr::core::dimension2df> getMinMaxSize() const;
			void setMinMaxSize(std::pair<irr::core::dimension2df, irr::core::dimension2df> minMaxsize);

		protected:

		private:
			irr::core::aabbox3d<irr::f32> _emiterSize;
			irr::core::vector3df _initialDirection;
			std::pair<int, int> _emitRate;
			std::pair<irr::video::SColor, irr::video::SColor> _darkBrightColor;
			std::pair<int, int> _minMaxAge;
			int _angle;
			std::pair<irr::core::dimension2df, irr::core::dimension2df> _minMaxSize;
	};

}

#endif /* !COMPENENTPARTICLE_HPP_ */
