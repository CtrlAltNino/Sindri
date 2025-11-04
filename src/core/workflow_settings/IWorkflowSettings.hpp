#pragma once

#include "IWorkflowSettingsObserver.hpp"
#include "TextureTypes.hpp"
namespace Sindri
{
  class IWorkflowSettings
  {
  public:
    virtual ~IWorkflowSettings() = default;

    /**
     * @brief Get the dimensions of the current workflow
     *
     * @return 1D, 2D or 3D
     */
    virtual auto
    GetDimensions() -> TextureDimension = 0;

    /**
     * @brief Sets the dimensions of the workflow
     *
     * @param textureDimension New dimensions
     */
    virtual void
    SetDimensions(TextureDimension textureDimension) = 0;

    /**
     * @brief Gets the amount of channels to use for the output
     *
     * @return Amount of channels for the output texture
     */
    virtual auto
    GetChannelCount() -> ChannelCount = 0;

    /**
     * @brief Sets the desired channels for the work flow
     *
     * @param channelCount Desired channel count
     */
    virtual void
    SetChannelCount(ChannelCount channelCount) = 0;

    /**
     * @brief Gets the current seed
     *
     * @return  Current seed
     */
    virtual auto
    GetSeed() -> uint32_t = 0;

    /**
     * @brief Randomizes the current seed and returns it
     *
     * @return The seed
     */
    virtual auto
    RandomizeSeed() -> uint32_t = 0;

    /**
     * @brief Sets the seed of the workflow
     *
     * @param seed The new seed for the workflow
     */
    virtual void
    SetSeed(uint32_t seed) = 0;

    /**
     * @brief Registers an observer who will be notified at changes of the
     * workflow settings
     *
     * @param observer Observer pointer to register
     */
    virtual void
    RegisterObserver(IWorkflowSettingsObserver* observer) = 0;

    /**
     * @brief Removes an observer
     *
     * @param observer Observer to remove
     */
    virtual void
    UnregisterObserver(IWorkflowSettingsObserver* observer) = 0;
  };
}