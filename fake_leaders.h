#pragma once

#include "timeouts.h"


class FakeLeaders
{
  public:
    static void start()
    {
      if (!m_FakeLeadersActive)
      {
        m_FakeLeadersActive = true;
        logger.notice(F("Fake leaders started"));

        if (m_LaunchOnStart)
        {
          sendFakeLeader();
        }
      }
      else
      {
        logger.warning(F("Fake leaders already started"));
      }
    }

    static void stop()
    {
      if (m_FakeLeadersActive)
      {
        m_FakeLeadersActive = false;
        logger.notice(F("Fake leaders stopped"));
      }
      else
      {
        //logger.warning(F("Fake leaders not running"));
      }
    }

    static unsigned long m_NextTimeout;
    static void(*m_NextAfter)(void);


  private:
    static bool m_FakeLeadersActive;
    static bool m_LaunchOnStart;

    static void fakeFilmEnd()
    {
      if (m_FakeLeadersActive)
      {
        logger.info(String(F("Fake film end. Sending next after ")) + String(FAKE_LEADER_INTERVAL) + F("ms"));

        m_NextTimeout = FAKE_LEADER_INTERVAL;
        m_NextAfter = sendFakeLeader;
      }
      else
      {
        m_NextAfter = nullptr;
        logger.notice(F("Fake film end. Not sending next"));
        m_LaunchOnStart = true;
      }
    }

    static void sendFakeFilm()
    {
      logger.info(String(F("Sending fake film. Length: ")) + String(FAKE_FILM_TIMEOUT) + F("ms"));
      if (FAKE_FILM_TIMEOUT > 0)
      {
        film_l_element.setOpen(false);
      }

      m_NextTimeout = FAKE_FILM_TIMEOUT;
      m_NextAfter = fakeFilmEnd;
    }

    static void fakeLeaderEnd()
    {
      logger.info(String(F("Fake leader end. Sending fake film after ")) + String(FAKE_LEADER_TO_FILM_TIMEOUT) + F("ms"));
      leader_element.setOpen(true);

      m_NextTimeout = FAKE_LEADER_TO_FILM_TIMEOUT;
      m_NextAfter = sendFakeFilm;
    }

    static void sendFakeLeader()
    {
      if (m_FakeLeadersActive)
      {
        logger.info(String(F("Fake leader sent. Length: ")) + String(FAKE_LEADER_TIMEOUT) + F("ms"));
        leader_element.setOpen(false);

        m_NextTimeout = FAKE_LEADER_TIMEOUT;
        m_NextAfter = fakeLeaderEnd;

        m_LaunchOnStart = false;
      }
    }
};

unsigned long FakeLeaders::m_NextTimeout = 0;
void(*FakeLeaders::m_NextAfter)(void) = 0;
bool FakeLeaders::m_FakeLeadersActive = false;
bool FakeLeaders::m_LaunchOnStart = true;
