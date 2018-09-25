#pragma once

enum stage
{
  stageIdle,
  stageStartup,
  stageReady,
  stageLeaderLoad,
  stageFilmLoad,
  stageSecurityTimeout
};

stage currentStage = stageStartup;

class Stage
{
  protected:
    Stage() {};
    virtual ~Stage() {};

  public:
    void run()
    {
      while (m_StageRunning)
      {
        stageWork();
      }
    }

  protected:
    virtual void stageWork()
    {
      logger.warning("Empty work");
      delay(1000);
    }
  private:
    bool m_StageRunning = true;
};

class StageIdle : public Stage
{
  public:
    StageIdle() : Stage()
    {
      logger.info("Idle stage");
    }
};

class StageStartup : public Stage
{
  public:
    StageStartup() : Stage()
    {
      logger.info("Startup stage");
    }
};
