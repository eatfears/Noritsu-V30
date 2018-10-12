#pragma once

#include "timeouts.h"


class FakeLeaders
{
  public:
    static void start()
    {
      if (!m_fakeLeadersActive)
      {
        m_fakeLeadersActive = true;
        logger.notice(F("Fake leaders started"));

        if (m_launchOnStart)
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
      if (m_fakeLeadersActive)
      {
        m_fakeLeadersActive = false;
        logger.notice(F("Fake leaders stopped"));
      }
      else
      {
        logger.warning(F("Fake leaders not running"));
      }
    }

    static unsigned long m_nextTimeout;
    static void(*m_nextAfter)(void);


  private:
    static bool m_fakeLeadersActive;
    static bool m_launchOnStart;

    static void fakeFilmEnd()
    {
      if (m_fakeLeadersActive)
      {
        logger.info(String(F("Fake film end. Sending next after ")) + String(FAKE_LEADER_INTERVAL) + F("ms"));

        m_nextTimeout = FAKE_LEADER_INTERVAL;
        m_nextAfter = sendFakeLeader;
      }
      else
      {
        m_nextAfter = nullptr;
        logger.notice(F("Fake film end. Not sending next"));
        m_launchOnStart = true;
      }
    }

    static void sendFakeFilm()
    {
      logger.info(String(F("Sending fake film. Length: ")) + String(FAKE_FILM_TIMEOUT) + F("ms"));
      if (FAKE_FILM_TIMEOUT > 0)
      {
        film_l_element.setOpen(false);
      }

      m_nextTimeout = FAKE_FILM_TIMEOUT;
      m_nextAfter = fakeFilmEnd;
    }

    static void fakeLeaderEnd()
    {
      logger.info(String(F("Fake leader end. Sending fake film after ")) + String(FAKE_LEADER_TO_FILM_TIMEOUT) + F("ms"));
      leader_element.setOpen(true);

      m_nextTimeout = FAKE_LEADER_TO_FILM_TIMEOUT;
      m_nextAfter = sendFakeFilm;
    }

    static void sendFakeLeader()
    {
      if (m_fakeLeadersActive)
      {
        logger.info(String(F("Fake leader sent. Length: ")) + String(FAKE_LEADER_TIMEOUT) + F("ms"));
        leader_element.setOpen(false);

        m_nextTimeout = FAKE_LEADER_TIMEOUT;
        m_nextAfter = fakeLeaderEnd;

        m_launchOnStart = false;
      }
    }
};

unsigned long FakeLeaders::m_nextTimeout = 0;
void(*FakeLeaders::m_nextAfter)(void) = 0;

bool FakeLeaders::m_fakeLeadersActive = false;
bool FakeLeaders::m_launchOnStart = true;
