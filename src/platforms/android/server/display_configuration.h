/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIR_GRAPHICS_ANDROID_DISPLAY_CONFIGURATION_H_
#define MIR_GRAPHICS_ANDROID_DISPLAY_CONFIGURATION_H_

#include "mir/graphics/display_configuration.h"
#include "hwc_configuration.h"
#include <array>

namespace mir
{
namespace graphics
{
namespace android
{

class DisplayConfiguration : public graphics::DisplayConfiguration
{
public:
    DisplayConfiguration(DisplayConfigurationOutput primary,
                         MirPowerMode primary_mode,
                         DisplayConfigurationOutput external,
                         MirPowerMode external_mode);

    DisplayConfiguration(DisplayConfigurationOutput primary,
                         MirPowerMode primary_mode,
                         DisplayConfigurationOutput external,
                         MirPowerMode external_mode,
                         DisplayConfigurationOutput virt_config);
#ifdef ANDROID_CAF
    DisplayConfiguration(DisplayConfigurationOutput primary,
                         MirPowerMode primary_mode,
                         DisplayConfigurationOutput external,
                         MirPowerMode external_mode,
                         DisplayConfigurationOutput tertiary,
                         MirPowerMode tertiary_mode,
                         DisplayConfigurationOutput virt_config);
#endif



    DisplayConfiguration(DisplayConfiguration const& other);
    DisplayConfiguration& operator=(DisplayConfiguration const& other);

    virtual ~DisplayConfiguration() = default;

    void for_each_card(std::function<void(DisplayConfigurationCard const&)> f) const override;
    void for_each_output(std::function<void(DisplayConfigurationOutput const&)> f) const override;
    void for_each_output(std::function<void(UserDisplayConfigurationOutput&)> f) override;
    std::unique_ptr<graphics::DisplayConfiguration> clone() const override;

    DisplayConfigurationOutput& primary();
    DisplayConfigurationOutput& external();
#ifdef ANDROID_CAF
    DisplayConfigurationOutput& tertiary();
#endif
    DisplayConfigurationOutput& virt();
    DisplayConfigurationOutput& operator[](DisplayConfigurationOutputId const&);

    void set_virtual_output_to(int width, int height);
    void disable_virtual_output();

private:
#ifdef ANDROID_CAF
    std::array<DisplayConfigurationOutput, 4> configurations;
#else
    std::array<DisplayConfigurationOutput, 3> configurations;
#endif
    DisplayConfigurationCard card;
};


}
}
}
#endif /* MIR_GRAPHICS_ANDROID_DISPLAY_CONFIGURATION_H_ */
