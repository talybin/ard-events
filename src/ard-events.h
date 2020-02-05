#pragma once
#include <functional>
#include <list>

namespace ard
{
    /// Provides core functionality.
    struct io_context
    {
        /// Type of event queue storage.
        using event_queue_type = std::list<std::function<bool()>>;

        /*!
        @brief Get event queue.

        Event queue contains handlers to be invoked each time
        process_events is called. Handlers returning true
        considered done and will be removed from the queue.

        @return Reference to static event queue.
        */
        static event_queue_type& event_queue() {
            static event_queue_type que;
            return que;
        }
    };

    /*!
    @brief Process events in event queue.

    Call it from loop() method.

    Go thru handlers in event queue. Ready handlers (that
    return true) are removed from the queue.
    If any handler calls ard::process_events it won't participate
    in called processing, e.g. all handlers invokes only once.
    If any handler creates a new event (with ard::set_timeout,
    ard::set_interval, ...) this new event will not be processed
    in the same loop.

    Example:
    @code {.cpp}
    void loop() {
        ard::process_events();
    }
    @endcode
    */
    inline void process_events()
    {
        auto& que = io_context::event_queue();

        // Temporary move event queue to a new list to avoid double
        // call to the same function (if cb calls ard::process_events).
        // Also for new events (ex. callback calls ard::set_timeout)
        // to be placed in separate event list (que).
        io_context::event_queue_type tmp { std::move(que) };

        for (auto it = tmp.begin(); it != tmp.end();) {
            if ((*it)())
                // Callback returned true, it should be removed.
                it = tmp.erase(it);
            else
                // Callback returned false, it should remain.
                ++it;
        }

        // At this point que list may have new events added by callbacks.
        // Insert remaining processed callbacks in the begining of the que.
        que.splice(que.begin(), std::move(tmp));
    }

    /*!
    @brief Run function after specified time.

    @param ms   Milliseconds to wait before invoke the handler.
    @param cb   Callback handler to invoke on timeout.

    Example:
    @code {.cpp}
    ard::set_timeout(5000, [] {
        // Do something on timeout
    });
    @endcode
    */
    inline void set_timeout(size_t ms, std::function<void()> cb)
    {
        io_context::event_queue().emplace_back(
            [cb = std::move(cb), stop = millis() + ms]() {
                return millis() >= stop && (cb(), true);
            });
    }

    /*!
    @brief Run the same function every number of milliseconds.

    This method tries hard to not loose precision. If interval
    between event processing is greater than given milliseconds,
    it will wait less amount of time than before.

    @param ms   Milliseconds to wait before invoke the handler.
    @param cb   Callback handler to invoke every given number
                milliseconds.

    Example:
    @code {.cpp}
    // Run test() function every second
    ard::set_interval(1000, test);
    @endcode
    */
    inline void set_interval(size_t ms, std::function<void()> cb)
    {
        io_context::event_queue().emplace_back(
            [cb = std::move(cb), ms, start = millis()]() mutable
            {
                if ((millis() - start) >= ms) {
                    start += ms;
                    cb();
                }
                return false;
            });
    }

    /*!
    @brief Execute function at the next processing of events.

    Calling this method will release execution and queue the
    callback to be invoked later. Callback will be executed on
    next call to ard::process_events.

    @param cb   Callback handler.

    Example:
    @code {.cpp}
    // Post invoke function test()
    ard::post(test);
    @endcode
    */
    inline void post(std::function<void()> cb)
    {
        io_context::event_queue().emplace_back([cb = std::move(cb)]() {
            return (cb(), true);
        });
    }

} // namespace ard

