#pragma once

typedef enum stage
{
  stageIdle,
  stageStartup,
  stageReady,
  stageLeaderLoad,
  stageLeaderEnd,
  stageFilmLoad,
  stageSecurityTimeout
} stage;

typedef enum film_type
{
  film_none,
  film_110, // narrow
  film_135, // normal
  film_120, // wide
} film_type;

String filmTypeToString(film_type tp)
{
  switch (tp)
  {
    case film_none: return F("None"); break;
    case film_110: return F("110"); break;
    case film_135: return F("135"); break;
    case film_120: return F("120"); break;
  }
}


film_type filmTypeL = film_none;
film_type filmTypeR = film_none;
