#pragma once

bool fakeLeadersActive = false;

const PROGMEM int fakeLeaderTimeout = 5000;
const PROGMEM int fakeLeaderToFilm = 1000;
int fakeFilmTimeout = 2000;
const PROGMEM int fakeLeaderInterval = 3000;


void sendFakeLeader();

void fakeFilmEnd()
{

  if (fakeLeadersActive)
  {
    logger.info(String(F("Fake film end. Sending next after ")) + String(fakeLeaderInterval) + F("ms"));
    film_l_element.setOpen(true);
    t.after(fakeLeaderInterval, sendFakeLeader);
  }
  else
  {
    logger.error(F("Fake film end. Not sending next"));
  }
}

void sendFakeFilm()
{
  logger.info(String(F("Sending fake film. Length: ")) + String(fakeFilmTimeout) + F("ms"));
  film_l_element.setOpen(false);
  t.after(fakeFilmTimeout, fakeFilmEnd);
}

void fakeLeaderEnd()
{
  logger.info(String(F("Fake leader end. Sending fake film after ")) + String(fakeLeaderToFilm) + F("ms"));
  leader_element.setOpen(true);
  t.after(fakeLeaderToFilm, sendFakeFilm);
}

void sendFakeLeader()
{
  logger.info(String(F("Fake leader sent. Length: ")) + String(fakeLeaderTimeout) + F("ms"));
  leader_element.setOpen(false);
  t.after(fakeLeaderTimeout, fakeLeaderEnd);
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
