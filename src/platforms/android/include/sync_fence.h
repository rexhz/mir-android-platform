/*
 * Copyright © 2013 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */
#ifndef MIR_GRAPHICS_ANDROID_SYNC_FENCE_H_
#define MIR_GRAPHICS_ANDROID_SYNC_FENCE_H_

#include "fence.h"
#include "mir/fd.h"
#include <memory>

namespace mir
{
namespace graphics
{
namespace android
{

class SyncFileOps
{
public:
    virtual ~SyncFileOps() = default;
    virtual int ioctl(int, int, void*) = 0;
    virtual int dup(int) = 0;
    virtual int close(int) = 0;
};

class RealSyncFileOps : public SyncFileOps
{
public:
    int ioctl(int fd, int req, void* dat);
    int dup(int fd);
    int close(int fd);
};

class SyncFence : public Fence
{
public:
    explicit SyncFence(std::shared_ptr<SyncFileOps> const&, Fd fd);

    void wait() override;
    bool wait_for(std::chrono::milliseconds) override;
    void reset_fence() override;
    void merge_with(NativeFence& merge_fd) override;
    NativeFence copy_native_handle() const override;
    NativeFence native_handle() const override;

private:
    SyncFence(SyncFence const&) = delete;
    SyncFence& operator=(SyncFence const&) = delete;

    Fd fence_fd;
    std::shared_ptr<SyncFileOps> const ops;

    int const infinite_timeout = -1;
};

}
}
}
#endif /* MIR_GRAPHICS_ANDROID_SYNC_FENCE_H_ */
