#pragma once

#include <functional>
#include <optional>
#include <unordered_map>
#include <cassert>

namespace hq
{
template <typename EnumClass>
class StateMachine
{
public:
    using StateType              = EnumClass;
    using ResultType             = std::optional<StateType>;
    using LeaveFunctionType      = std::function<void()>;
    using TransitionFunctionType = std::function<ResultType()>;

    StateMachine(StateType initialState, TransitionFunctionType&& enterFunc, TransitionFunctionType&& tickFunc,
                 LeaveFunctionType&& leaveFunc)
    {
        _currentState = initialState;
        _states.emplace(std::make_pair(initialState, StateMachineState(initialState, std::move(enterFunc),
                                                                       std::move(tickFunc), std::move(leaveFunc))));
    };

    void addState(StateType state, TransitionFunctionType&& enterFunc, TransitionFunctionType&& tickFunc,
                  LeaveFunctionType&& leaveFunc)
    {
        _states.emplace(std::make_pair(
            state, StateMachineState(state, std::move(enterFunc), std::move(tickFunc), std::move(leaveFunc))));
    }

    void changeState(StateType state)
    {
        auto currIt = _states.find(_currentState);
        assert(currIt != _states.end());
        currIt->second.leaveFunc();
        auto iter = _states.find(state);
        assert(iter != _states.end());
        _currentState         = iter->second.state;
        ResultType transition = currIt->second.enterFunc();
        if (transition)
        {
            changeState(*transition);
        }
    }

    void tick()
    {
        auto currIt = _states.find(_currentState);
        assert(currIt != _states.end());
        ResultType transition = currIt->second.tickFunc();
        if (transition)
        {
            changeState(*transition);
        }
    }

    StateType currentState() const
    {
        return _currentState;
    }

private:
    struct StateMachineState
    {
        StateMachineState(StateType iState, TransitionFunctionType&& iEnter, TransitionFunctionType&& iTick,
                          LeaveFunctionType&& iLeave)
            : state(iState)
            , enterFunc(std::move(iEnter))
            , tickFunc(std::move(iTick))
            , leaveFunc(std::move(iLeave))
        {
        }

        StateType              state;
        TransitionFunctionType enterFunc;
        TransitionFunctionType tickFunc;
        LeaveFunctionType      leaveFunc;
    };

    StateType                                        _currentState;
    std::unordered_map<StateType, StateMachineState> _states;
};

// Context variant
template <typename EnumClass, typename Context>
class StateMachineWithContext
{
public:
    using StateType              = EnumClass;
    using ContextType            = Context;
    using ResultType             = std::optional<StateType>;
    using LeaveFunctionType      = std::function<void(ContextType&)>;
    using TransitionFunctionType = std::function<ResultType(ContextType&)>;

    StateMachineWithContext(Context& context, StateType initialState, TransitionFunctionType&& enterFunc,
                            TransitionFunctionType&& tickFunc, LeaveFunctionType&& leaveFunc)
        : _context(context)
    {
        _currentState = initialState;
        _states.emplace(std::make_pair(initialState, StateMachineState(initialState, std::move(enterFunc),
                                                                       std::move(tickFunc), std::move(leaveFunc))));
    };

    void addState(StateType state, TransitionFunctionType&& enterFunc, TransitionFunctionType&& tickFunc,
                  LeaveFunctionType&& leaveFunc)
    {
        _states.emplace(std::make_pair(
            state, StateMachineState(state, std::move(enterFunc), std::move(tickFunc), std::move(leaveFunc))));
    }

    void changeState(StateType state)
    {
        auto currIt = _states.find(_currentState);
        assert(currIt != _states.end());
        currIt->second.leaveFunc(_context);
        auto iter = _states.find(state);
        assert(iter != _states.end());
        _currentState         = iter->second.state;
        ResultType transition = currIt->second.enterFunc(_context);
        if (transition)
        {
            changeState(*transition);
        }
    }

    void tick()
    {
        auto currIt = _states.find(_currentState);
        assert(currIt != _states.end());
        ResultType transition = currIt->second.tickFunc(_context);
        if (transition)
        {
            changeState(*transition);
        }
    }

    StateType currentState() const
    {
        return _currentState;
    }

private:
    struct StateMachineState
    {
        StateMachineState(StateType iState, TransitionFunctionType&& iEnter, TransitionFunctionType&& iTick,
                          LeaveFunctionType&& iLeave)
            : state(iState)
            , enterFunc(std::move(iEnter))
            , tickFunc(std::move(iTick))
            , leaveFunc(std::move(iLeave))
        {
        }

        StateType              state;
        TransitionFunctionType enterFunc;
        TransitionFunctionType tickFunc;
        LeaveFunctionType      leaveFunc;
    };

    ContextType&                                     _context;
    StateType                                        _currentState;
    std::unordered_map<StateType, StateMachineState> _states;
};
}  // hq namespace
