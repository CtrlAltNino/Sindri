#include "pch.hpp"

#include "WorkflowSettings.hpp"

namespace Sindri
{
  WorkflowSettings::WorkflowSettings()
    : mSeed(mRandomDevice())
  {
  }
  auto
  WorkflowSettings::GetDimensions() -> TextureDimension
  {
    return mDimensions;
  }

  void
  WorkflowSettings::SetDimensions(TextureDimension textureDimension)
  {
    mDimensions = textureDimension;

    for (auto* observer : mObservers)
    {
      observer->OnDimensionsChanged();
    }
  }

  auto
  WorkflowSettings::GetChannelCount() -> ChannelCount
  {
    return mChannelCount;
  }

  void
  WorkflowSettings::SetChannelCount(ChannelCount channelCount)
  {
    mChannelCount = channelCount;

    for (auto* observer : mObservers)
    {
      observer->OnChannelCountChanged();
    }
  }

  auto
  WorkflowSettings::GetSeed() -> uint32_t
  {
    return mSeed;
  }

  auto
  WorkflowSettings::RandomizeSeed() -> uint32_t
  {
    mSeed = mRandomDevice();

    for (auto* observer : mObservers)
    {
      observer->OnSeedChanged();
    }

    return mSeed;
  }

  /**
   * @brief Sets the seed of the workflow
   *
   * @param seed The new seed for the workflow
   */
  void
  WorkflowSettings::SetSeed(uint32_t seed)
  {
    mSeed = seed;

    for (auto* observer : mObservers)
    {
      observer->OnSeedChanged();
    }
  }

  /**
   * @brief Registers an observer who will be notified at changes of the
   * workflow settings
   *
   * @param observer Observer pointer to register
   */
  void
  WorkflowSettings::RegisterObserver(IWorkflowSettingsObserver* observer)
  {
    mObservers.push_back(observer);
  }

  /**
   * @brief Removes an observer
   *
   * @param observer Observer to remove
   */
  void
  WorkflowSettings::UnregisterObserver(IWorkflowSettingsObserver* observer)
  {
    std::erase(mObservers, observer);
  }
}