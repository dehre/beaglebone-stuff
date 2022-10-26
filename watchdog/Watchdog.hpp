#pragma once

#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <fcntl.h>
#include <ios>
#include <linux/watchdog.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

class Watchdog
{
  public:
    Watchdog(unsigned int interval)
    {
        m_fd = open(Watchdog::path_to_dev, O_RDWR);
        if (m_fd < 0)
        {
            std::string errmsg{"Failed to open watchdog device: "};
            errmsg.append(std::strerror(errno));
            throw std::ios::failure{errmsg};
        }

        int rc{ioctl(m_fd, WDIOC_SETTIMEOUT, &interval)};
        if (rc < 0)
        {
            std::string errmsg{"Failed to set the watchdog interval: "};
            errmsg.append(std::strerror(errno));
            throw std::runtime_error{errmsg};
        }
    }

    void feed()
    {
        int rc{ioctl(m_fd, WDIOC_KEEPALIVE, NULL)};
        if (rc < 0)
        {
            std::string errmsg{"Failed to write watchdog keepalive: "};
            errmsg.append(std::strerror(errno));
            throw std::runtime_error{errmsg};
        };
    }

    ~Watchdog()
    {
        if (m_fd != -1)
        {
            /* ignore errors in destructor */
            write(m_fd, "V", 1);
            close(m_fd);
        }
    }

  private:
    int m_fd{-1};
    static constexpr const char *path_to_dev{"/dev/watchdog"};
};
