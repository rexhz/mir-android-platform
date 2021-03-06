/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_MOCK_ANDROID_NATIVE_BUFFER_H_
#define MIR_TEST_DOUBLES_MOCK_ANDROID_NATIVE_BUFFER_H_

#include "src/platforms/android/include/native_buffer.h"
#include "mir/geometry/size.h"
#include <gmock/gmock.h>

namespace mir
{
namespace test
{
namespace doubles
{

struct MockAndroidNativeBuffer : public graphics::android::NativeBuffer
{
    MockAndroidNativeBuffer()
    {
        using namespace testing;
        ON_CALL(*this, anwb())
            .WillByDefault(Return(&stub_anwb));
        ON_CALL(*this, handle())
            .WillByDefault(Return(native_handle.get()));
        ON_CALL(*this, copy_fence())
            .WillByDefault(Return(-1));
    }

    MockAndroidNativeBuffer(geometry::Size sz)
        : MockAndroidNativeBuffer()
    {
        stub_anwb.width = sz.width.as_int();
        stub_anwb.height = sz.height.as_int();
    }

    MOCK_CONST_METHOD0(anwb, ANativeWindowBuffer*());
    MOCK_CONST_METHOD0(handle, buffer_handle_t());
    MOCK_CONST_METHOD0(copy_fence, graphics::android::NativeFence());
    MOCK_CONST_METHOD0(fence, graphics::android::NativeFence());

    MOCK_METHOD1(ensure_available_for, void(graphics::android::BufferAccess));
    MOCK_METHOD2(ensure_available_for, bool(graphics::android::BufferAccess, std::chrono::milliseconds));
    MOCK_METHOD2(update_usage, void(graphics::android::NativeFence&, graphics::android::BufferAccess));
    MOCK_METHOD0(reset_fence, void());

    MOCK_METHOD0(lock_for_gpu, void());
    MOCK_METHOD0(wait_for_unlock_by_gpu, void());
    ANativeWindowBuffer stub_anwb;
    std::unique_ptr<native_handle_t> native_handle =
        std::make_unique<native_handle_t>();
};
}
}
}

#endif /* MIR_TEST_DOUBLES_MOCK_ANDROID_NATIVE_BUFFER_H_ */
