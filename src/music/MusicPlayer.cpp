#include "music/MusicPlayer.h"
#include "log/Log.h"


MusicPlayer::MusicPlayer()
: m_music()
, m_fileNames()
, m_volume(0.0f)
{
    m_fileNames[Music::MenuTheme]       = "Data/Music/13 It Only Takes One Shot (From the.mp3";
    m_fileNames[Music::MissionTheme]    = "Data/Music/06 My Least Favorite Life( From the.mp3";
}

void MusicPlayer::Play( Music::ID_t theme )
{
    if (!m_music.openFromFile(m_fileNames[theme]))
    {
        LogError("Can't open music " + m_fileNames[theme]);
        return;
    }
}

void MusicPlayer::Stop()
{
    m_music.stop();
}


void MusicPlayer::SetLoop(bool loop)
{
    m_music.setLoop(loop);
}

void MusicPlayer::SetPaused( bool paused )
{
    if (paused)
        m_music.pause();
    else
        m_music.play();
}

void MusicPlayer::SetVolume( float volume )
{
    volume = volume < 0.0f ? 0.0f : volume;
    volume = volume > 100.0f ? 100.0f : volume;

    m_music.setVolume(volume);
}

