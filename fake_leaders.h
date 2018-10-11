#pragma once

#include "timeouts.h"

bool fakeLeadersActive = false;

const PROGMEM int fakeLeaderTimeout = FAKE_LEADER_TIMEOUT;
const PROGMEM int fakeLeaderToFilm = FAKE_LEADER_TO_FILM_TIMEOUT;
int fakeFilmTimeout = FAKE_FILM_TIMEOUT;
const PROGMEM unsigned long fakeLeaderInterval = FAKE_LEADER_INTERVAL;

unsigned long nextTimeout = 0;
void(*nextAfter)(void) = 0;

void sendFakeLeader();

void fakeFilmEnd()
{
  if (fakeLeadersActive)
  {
    logger.info(String(F("Fake film end. Sending next after ")) + String(fakeLeaderInterval) + F("ms"));
    //film_l_element.setOpen(true);

    nextTimeout = fakeLeaderInterval;
    nextAfter = sendFakeLeader;
  }
  else
  {
    nextAfter = nullptr;
    logger.error(F("Fake film end. Not sending next"));
  }
}

void sendFakeFilm()
{
  logger.info(String(F("Sending fake film. Length: ")) + String(fakeFilmTimeout) + F("ms"));
  if (fakeFilmTimeout > 0)
  {
    film_l_element.setOpen(false);
  }

  nextTimeout = fakeFilmTimeout;
  nextAfter = fakeFilmEnd;
}

void fakeLeaderEnd()
{
  logger.info(String(F("Fake leader end. Sending fake film after ")) + String(fakeLeaderToFilm) + F("ms"));
  leader_element.setOpen(true);

  nextTimeout = fakeLeaderToFilm;
  nextAfter = sendFakeFilm;
}

void sendFakeLeader()
{
  logger.info(String(F("Fake leader sent. Length: ")) + String(fakeLeaderTimeout) + F("ms"));
  leader_element.setOpen(false);

  nextTimeout = fakeLeaderTimeout;
  nextAfter = fakeLeaderEnd;

}

void startSendingFakeLeaders()
{
  if (!fakeLeadersActive)
  {
    fakeLeadersActive = true;
    logger.notice(F("Fake leaders started"));
    sendFakeLeader();
  }
  else
  {
    logger.warning(F("Fake leaders already started"));
  }

}

void stopSendingFakeLeaders()
{
  if (fakeLeadersActive)
  {
    fakeLeadersActive = false;
    logger.notice(F("Fake leaders stopped"));
  }
  else
  {
    logger.warning(F("Fake leaders not running"));
  }
}
