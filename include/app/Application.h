#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "resource/ResourceHolder.h"
#include "resource/ResourceIdentifiers.h"
#include "player/Player.h"
#include "states/StateStack.h"
#include "music/MusicPlayer.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>




class Application : public sf::NonCopyable
{
	public:
								Application();

		void					Run();
		
	private:

		void					ProcessInput();
		void					Update(sf::Time dt);
		void					Render();

		void					UpdateStatistics(sf::Time dt);
		void					RegisterStates();

	private:

		static const sf::Time	TimePerFrame;

		sf::RenderWindow		m_window;
		TextureHolder			m_textures;
	  	FontHolder				m_fonts;
		Player					m_player;
        MusicPlayer             m_musicPlayer;


		StateStack				m_stateStack;

		sf::Text				m_statisticsText;
        sf::Time				m_statisticsUpdateTime;
		std::size_t				m_statisticsNumFrames;
};

#endif //APPLICATION_H_
