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
