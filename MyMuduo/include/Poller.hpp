#pragma once
#include "NonCopyable.hpp"
#include "Channel.hpp"
#include <vector>
#include <unordered_map>

class EventLoop;

using ChannelList = vector<Channel *>;
using ChannelMap = unordered_map<int, Channel *>;

// 每一个EventLoop对应一个Poller
// io复用模块 muduo中多路事件分发器的核心

class Poller : NonCopyable
{
public:
    Poller(EventLoop *loop);
    virtual ~Poller() = default;

    // 监控事件，使用channel来具体操作
    virtual TimeStamp poll(int timeout, ChannelList *active_channels) = 0;
    virtual void update_channel(Channel *channel) = 0;
    virtual void remove_channel(Channel *channel) = 0;
    
    
    //判断channel是否在当前poller中
    bool has_channel(Channel *channel) const;
    //获取这个事件循环的poller
    static Poller *new_defaultPoller(EventLoop *loop);
protected:
    //key: fd  value
    // fd所属channel
    ChannelMap channels_;
private:
    EventLoop *owner_loop_; //polllers所属事件循环
};
